#include <stdio.h>
#include "library.h"
#include<unistd.h>

void serve(char port[]) {
    int serv = openSocketConnection(port);
    int connection = -1;
    if (serv != -1) {
        connection = awaitConnections(serv);
        if (connection != -1) {
            printf("\nSomeone connected successfully\n");
            char reply[] = "Welcome!";
            int success = write(connection, reply, sizeof(reply));
            if (success > -1) {
                printf("Sent welcome message.\n");
            } else {
                printf("Failed sending welcome message.\n");
            }
        }
    }
    if (serv == -1) {
        printf("Unable to open socket\n");
    } else if (connection == -1) {
        printf("Unable to listen for incoming connections\n");
    }
}

void attach(char port[], char host[]) {
    int connection = connectToSocket(port, host);
    if (connection != -1) {
        printf("\nSuccessfully attached to server socket\n");
        char reply[] = "Hello, World!";
        int success = write(connection, reply, sizeof(reply));
        if (success > -1) {
            printf("Sent welcome message.\n");
        }
        else {
            printf("Failed sending welcome message.\n");
        }
    }
    else {
        printf("Unable to connect\n");
    }
}

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf("Please define a parameter: -s to server, -a to attach");
        return 0;
    }

    char c, *port, *host = NULL;
    int cnt = 1, isServer = 0;
    while ((c = getopt(argc, argv, "s:a:h:")) != -1) {
        switch (c) {
            case 's':       // Act as server
                port = argv[cnt+1];
                isServer = 1;
                break;
            case 'a':       // Act as client
                port = argv[cnt+1];
                break;
            case 'h':
                host = argv[cnt+1];
                break;
            default:
                break;
        }
        cnt = cnt + 2;
    }

    if (!host) {
        host = "127.0.0.1";
    }

    if (isServer) {
        serve(port);
    }
    else {
        attach(port, host);
    }
    return 0;
}


