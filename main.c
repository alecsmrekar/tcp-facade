#include <stdio.h>
#include "library.h"
#include<unistd.h>

void serve(char port[]) {
    int serv = openSocketConnection(port, 0);
    int connection = awaitConnections(serv);
    if (connection != -1) {
        printf("\nSomeone connected successfully\n");
        char reply[] = "Welcome!";
        int success = write(connection, reply, sizeof(reply));
        if (success > -1) {
            printf("Sent welcome message.\n");
        }
        else {
            printf("Failed sending welcome message.\n");
        }
    }
    else {
        printf("Unable to open socket\n");
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
    while ((c = getopt(argc, argv, "s:a:")) != -1) {
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
        cnt++;
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


