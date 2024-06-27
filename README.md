Chat Server and Client Application
A simple C++ chat server and client application using Winsock. This project supports multiple clients, private messaging, and group messaging.

Features
Multithreaded Server: Handles multiple clients simultaneously.
Broadcast Messaging: Send messages to all connected clients.
Private Messaging: Directly message a specific user.
Group Messaging: Create groups and send messages to all members.
Usage
Broadcast: Type and send a message.
Private Message: /msg <username> <message>
Create Group: /group <group_name> <username1> <username2> ...
Group Message: /gmsg <group_name> <message>
Building and Running
Compile Server: cl /EHsc server.cpp /link Ws2_32.lib
Compile Client: cl /EHsc client.cpp /link Ws2_32.lib
Run Server: server.exe
Run Client: client.exe
License
MIT License
