# Terminal-Based Chat Application

This is a simple terminal-based chat application implemented in C++ using sockets. It allows users on the same local network to communicate via text messages.

## Features

- *Group Chat*: Create groups of users and send messages visible only to group members.
- *Private Messaging*: Send private messages to individual users.
- *Terminal Interface*: User-friendly interface using standard input/output.
- *Multi-threaded Server*: Handles multiple client connections concurrently.

## Requirements

- *C++ Compiler*: Compatible with C++11 or higher.
- *Windows OS*: Developed and tested on Windows using Winsock.
- *Local Network*: Users must be connected to the same local network.

## How to Use

1.Download both the files on your device ans save it in a folder.

2.Run the terminal on the same folder on all devices and then proceed.

### Server (server.cpp)

Use a C++ compiler/Terminal to build the server executable on the host device.

```bash
g++ -o server server.cpp-1ws2_32 -1pthread

```

#### Compile the Client

To compile the client code, use the following command on the devices connected to the host :


```bash
g++ -o client client.cpp -1ws2_32 -1pthread
```

### Running the Application

#### Start the Server

Run the compiled server executable on host device. The server will start and listen for incoming client connections on port 12345.


```bash
./server
```

#### Start the Client

Run the compiled client executable on devices connected to host. You will be prompted to enter a username to identify yourself in the chat.



```bash
./client
```

## Usage

### Commands

* *Broadcast Message:* Simply type your message and press Enter. This will send the message to all
connected clients.
* *Private Message:* To send a private message to a specific user, use the following format:


```bash
/msg <username> <message>
```
Example:

```cpp
/msg Alice Hello, Alice!
 ``` 

* *Create Group:* To create a group, use the following format:


```bash
/group <group_name> <member1> <member2> ...
```
Example:

```bash
/group DevTeam Alice Bob Charlie
 ``` 

* *Send Group Message:* To send a message to a group, use the following format:


```bash
/gmsg <group_name> <message>
```
Example:

```bash
/gmsg DevTeam Hey team, let's meet at 2 PM.
```

### Handling Client Disconnects

If a client disconnects, the server will automatically remove the client from the list and notify other clients that the user has left the chat.

## Code Overview

### Server Code (server.cpp)

The server code is responsible for:
* Accepting incoming client connections.
* Receiving and broadcasting messages.
* Handling private and group messaging.
* Managing client disconnections.

Key components include:
* *Multithreading:* Each client connection is handled in a separate thread.
* *Synchronization:* A mutex (clients_mutex) is used to ensure thread-safe access to the shared client list.

### Client Code (client.cpp)

The client code is responsible for:
* Connecting to the server.
* Sending messages to the server.
* Receiving and displaying messages from the server.

Key components include:
* *Threading:* A separate thread is used to listen for incoming messages from the server.

## Dependencies

* *Winsock2 Library:* The project uses Windows Sockets 2 for network communication. Ensure that the Ws2_32.lib is linked during compilation.

## Contributing
* Contributions are welcome! If you have any improvements or bug fixes, please submit a pull request.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements
* This project uses the Winsock2 library for network communication.
* Inspiration for this project came from exploring basic networking concepts in C++.
