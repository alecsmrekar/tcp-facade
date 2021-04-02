#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

#include "library.h"

int isVerbose = 0;
struct sockaddr_in clientaddr; // Structure describing an Internet socket address
socklen_t addrlen;              // client address length

int connectToSocket(char portChar[], char charIP[]) {
    int socket_desc;
    struct sockaddr_in server;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        perror("Could not create socket");
        return -1;
    }

    server.sin_addr.s_addr = inet_addr(charIP);
    server.sin_family = AF_INET;
    int intPort;
    sscanf(portChar, "%d", &intPort);

    // htons() accepts port as an integer
    server.sin_port = htons(intPort);

    //Connect to remote server
    int tryConnect = connect(socket_desc, (struct sockaddr *) &server, sizeof(server));
    if (tryConnect < 0) {
        return -1;
    }
    return socket_desc;
}

int openSocketConnection (char portChar[]) {
    int socketFD; // New socket file descriptor
    startServing(portChar, &socketFD);
    printf("Server started at port no. %s\n", portChar);
    return socketFD;
}

int awaitConnections (int socketFD) {
    addrlen = sizeof(clientaddr);
    int connection = accept(socketFD, (struct sockaddr *) &clientaddr, &addrlen);
    return connection;
}

void startServing(char *port, int *socketFD) {
    struct addrinfo hints, *res, *p;

    // getaddrinfo for host
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;              // IP protocol family
    hints.ai_socktype = SOCK_STREAM;        // Sequenced, reliable, connection-based byte streams

    /*
     * hostname parameter for getaddrinfo:
     *   can be either a domain name, such as "example.com", an address string, such as "127.0.0.1",
     *   or NULL, in which case the address 0.0.0.0 or 127.0.0.1 is assigned depending on the hints flags.
     */

    int errcode = getaddrinfo(NULL, port, &hints, &res) != 0;
    if (errcode) {
        perror("getaddrinfo() error");
        return -1;
    }

    // socket and bind
    // getaddrinfo retruns a linked list of potential addressed you can connect to
    // loop and try to connect to every one
    for (p = res; p != NULL; p = p->ai_next) {
        /* socket()
                Create a new socket of type TYPE in domain DOMAIN, using
                protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
                Returns a file descriptor for the new socket, or -1 for errors.
          */
        *socketFD = socket(p->ai_family, p->ai_socktype, 0);
        if (*socketFD == -1) {
            continue;
        }

        /*
         * bind()
         *  Give the socket file descriptor the local address ADDR (which is LEN bytes long)
         * */
        if (bind(*socketFD, p->ai_addr, p->ai_addrlen) == 0) {
            break; // Bind is successful, stop trying
        }
    }
    if (p == NULL) {
        perror("socket() or bind()");
        return -1;
    }

    // Release the memory used for the socket linked list
    freeaddrinfo(res);


    /* listen()
           Prepare to accept connections on socket FD.
           N connection requests will be queued before further requests are refused.
    */
    int listenResult = listen(*socketFD, 1);
    if (listenResult != 0) {
        perror("listen() error");
        return -1;
    }
}
