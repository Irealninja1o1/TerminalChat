#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <algorithm>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 12345
#define BUFFER_SIZE 1024

using namespace std;

vector<SOCKET> clients;
vector<string> usernames;
unordered_map<string, vector<SOCKET>> groups;
mutex clients_mutex;

void broadcast(const string& message, SOCKET source_client) {
    lock_guard<mutex> guard(clients_mutex);
    for (SOCKET client : clients) {
        if (client != source_client) {
            send(client, message.c_str(), message.length(), 0);
        }
    }
}

void send_private_message(const string& message, const string& username) {
    lock_guard<mutex> guard(clients_mutex);
    auto it = find(usernames.begin(), usernames.end(), username);
    if (it != usernames.end()) {
        size_t index = distance(usernames.begin(), it);
        SOCKET client_socket = clients[index];
        send(client_socket, message.c_str(), message.length(), 0);
    }
}

void send_group_message(const string& message, const string& group_name) {
    lock_guard<mutex> guard(clients_mutex);
    auto it = groups.find(group_name);
    if (it != groups.end()) {
        for (SOCKET client_socket : it->second) {
            send(client_socket, message.c_str(), message.length(), 0);
        }
    }
}

void handle_client(SOCKET client_socket) {
    char buffer[BUFFER_SIZE];
    string username;

    // Receive username
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        username = string(buffer);
        usernames.push_back(username);
    }

    string welcome_message = username + " has joined the chat.\n";
    broadcast(welcome_message, client_socket);

    while (true) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            break;
        }
        buffer[bytes_received] = '\0';
        string message(buffer);

        // Check for personal message command
        if (message.substr(0, 5) == "/msg ") {
            size_t space_pos = message.find(' ', 5);
            if (space_pos != string::npos) {
                string target_username = message.substr(5, space_pos - 5);
                string private_message = username + " (private): " + message.substr(space_pos + 1);
                send_private_message(private_message, target_username);
            }
        }
        // Check for create group command
        else if (message.substr(0, 7) == "/group ") {
            size_t space_pos = message.find(' ', 7);
            if (space_pos != string::npos) {
                string group_name = message.substr(7, space_pos - 7);
                string members_list = message.substr(space_pos + 1);
                vector<string> member_names;
                size_t pos = 0;
                while ((pos = members_list.find(' ')) != string::npos) {
                    member_names.push_back(members_list.substr(0, pos));
                    members_list.erase(0, pos + 1);
                }
                member_names.push_back(members_list); // Add the last member

                vector<SOCKET> group_members;
                for (const string& member_name : member_names) {
                    auto it = find(usernames.begin(), usernames.end(), member_name);
                    if (it != usernames.end()) {
                        size_t index = distance(usernames.begin(), it);
                        group_members.push_back(clients[index]);
                    }
                }
                groups[group_name] = group_members;

                string group_created_message = "Group '" + group_name + "' created with members: " + members_list + "\n";
                send_group_message(group_created_message, group_name);
            }
        }
        // Check for group message command
        else if (message.substr(0, 6) == "/gmsg ") {
            size_t space_pos = message.find(' ', 6);
            if (space_pos != string::npos) {
                string group_name = message.substr(6, space_pos - 6);
                string group_message = username + " (group " + group_name + "): " + message.substr(space_pos + 1);
                send_group_message(group_message, group_name);
            }
        } else {
            string broadcast_message = username + ": " + message;
            broadcast(broadcast_message, client_socket);
        }
    }

    // Remove client on disconnect
    {
        lock_guard<mutex> guard(clients_mutex);
        auto it = find(clients.begin(), clients.end(), client_socket);
        if (it != clients.end()) {
            size_t index = distance(clients.begin(), it);
            clients.erase(it);
            usernames.erase(usernames.begin() + index);
        }
    }
    closesocket(client_socket);
    string leave_message = username + " has left the chat.\n";
    broadcast(leave_message, INVALID_SOCKET);
}

int main() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cerr << "WSAStartup failed: " << iResult << endl;
        return 1;
    }

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET) {
        cerr << "Socket creation failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        cerr << "Bind failed: " << WSAGetLastError() << endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR) {
        cerr << "Listen failed: " << WSAGetLastError() << endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    cout << "Server started on port " << PORT << endl;

    while (true) {
        SOCKET client_socket = accept(server_fd, NULL, NULL);
        if (client_socket == INVALID_SOCKET) {
            cerr << "Accept failed: " << WSAGetLastError() << endl;
            closesocket(server_fd);
            WSACleanup();
            return 1;
        }

        {
            lock_guard<mutex> guard(clients_mutex);
            clients.push_back(client_socket);
        }

        thread(handle_client, client_socket).detach();
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}
