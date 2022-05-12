#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

int main()
{
    char server_message[256] = "You have reached the server";

    // create the server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    char client_response[256];
    recv(client_socket, &client_response, sizeof(client_response), 0);

    printf("The client sent the data : %s\n", client_response);


    // send the message
    send(client_socket, server_message, sizeof(server_message), 0);

    // close the socket
    close(server_socket);


    return 0;
}


#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

int main()
{
    // create a socket
    int network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    // check for error in the connection
    if(connection_status == -1)
    {
        printf("There was an error in making a connection to the server\n\n");
    }

    char hello[256] = "Hello from client";
    send(network_socket, hello, sizeof(hello), 0);
    
    // receive data from the server
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print out the server's response
    printf("The server sent the data : %s\n", server_response);

    // close the socket
    close(network_socket);

    return 0;
}
