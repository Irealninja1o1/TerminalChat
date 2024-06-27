# TerminalChat
Chat Server and Client Application
This repository contains a basic chat server and client application implemented in C++. The server supports multiple clients, private messaging, and group messaging functionalities. Both the server and client use Windows Sockets (Winsock) for network communication.

Features
Multithreaded Server: Handles multiple clients concurrently using threads.
Broadcast Messaging: Clients can send messages to all connected clients.
Private Messaging: Clients can send private messages to specific users.
Group Messaging: Clients can create groups and send messages to all group members.
User Management: Tracks usernames associated with each client for personalized communication.
Getting Started
Prerequisites
Windows OS
C++ Compiler (e.g., MSVC)
Winsock2 library
Building the Project
Compile the Server
