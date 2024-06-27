#TerminalChat

This repository contains a basic chat server and client application
implemented in C++. The server supports multiple clients, private
messaging, and group messaging functionalities. Both the server and
client use Windows Sockets (Winsock) for network communication.

##Features##

-   ##Multithreaded Server:## Handles multiple clients concurrently
    using threads.

-   ##Broadcast Messaging:## Clients can send messages to all connected
    clients.

-   ##Private Messaging:## Clients can send private messages to specific
    users.

-   ##Group Messaging:## Clients can create groups and send messages to
    all group members.

-   ##User Management:## Tracks usernames associated with each client
    for personalized communication.

##Getting Started##

##Prerequisites##

-   Windows OS

-   C++ Compiler (e.g., MSVC)

-   Winsock2 library

##Building the Project##

##Compile the Server##

To compile the server code, use the following command in your terminal
or command prompt:

sh

Copy code

cl /EHsc server.cpp /link Ws2_32.lib

##Compile the Client##

To compile the client code, use the following command:

sh

Copy code

cl /EHsc client.cpp /link Ws2_32.lib

##Running the Application##

##Start the Server##

Run the compiled server executable. The server will start and listen for
incoming client connections on port 12345.

sh

Copy code

server.exe

##Start the Client##

Run the compiled client executable. You will be prompted to enter a
username to identify yourself in the chat.

sh

Copy code

client.exe

##Usage##

##Commands##

-   ##Broadcast Message:## Simply type your message and press Enter.
    This will send the message to all connected clients.

-   ##Private Message:## To send a private message to a specific user,
    use the following format:

> plaintext
>
> Copy code
>
> /msg \<username\> \<message\>
>
> Example:
>
> plaintext
>
> Copy code
>
> /msg Alice Hello, Alice!

-   ##Create Group:## To create a group, use the following format:

> plaintext
>
> Copy code
>
> /group \<group_name\> \<member1\> \<member2\> \...
>
> Example:
>
> plaintext
>
> Copy code
>
> /group DevTeam Alice Bob Charlie

-   ##Send Group Message:## To send a message to a group, use the
    following format:

> plaintext
>
> Copy code
>
> /gmsg \<group_name\> \<message\>
>
> Example:
>
> plaintext
>
> Copy code
>
> /gmsg DevTeam Hey team, let\'s meet at 2 PM.

##Handling Client Disconnects##

If a client disconnects, the server will automatically remove the client
from the list and notify other clients that the user has left the chat.

##Code Overview##

##Server Code (server.cpp)##

The server code is responsible for:

-   Accepting incoming client connections.

-   Receiving and broadcasting messages.

-   Handling private and group messaging.

-   Managing client disconnections.

Key components include:

-   ##Multithreading:## Each client connection is handled in a separate
    thread.

-   ##Synchronization:## A mutex (clients_mutex) is used to ensure
    thread-safe access to the shared client list.

##Client Code (client.cpp)##

The client code is responsible for:

-   Connecting to the server.

-   Sending messages to the server.

-   Receiving and displaying messages from the server.

Key components include:

-   ##Threading:## A separate thread is used to listen for incoming
    messages from the server.

##Dependencies##

-   ##Winsock2 Library:## The project uses Windows Sockets 2 for network
    communication. Ensure that the Ws2_32.lib is linked during
    compilation.

##Contributing##

Contributions are welcome! If you have any improvements or bug fixes,
please submit a pull request.

##License##

This project is licensed under the MIT License. See the LICENSE file for
details.

##Acknowledgements##

-   This project uses the Winsock2 library for network communication.

-   Inspiration for this project came from exploring basic networking
    concepts in C++.
