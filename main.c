#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#include<stdio.h>
#include<sys/time.h>
#include <signal.h>


#define CONNMAX 2
#define BYTES 1024
#define NB_DISABLE 1
#define NB_ENABLE 0


// https://www.csd.uoc.gr/~hy556/material/tutorials/cs556-3rd-tutorial.pdf

char *ROOT;
int isServerMode = 1;
int listenfd; // file descriptor for the new socket
int clients[CONNMAX];

void error(char *);

int connectToServer(char[], char *);

void startServer(char *);

void consoleRespond(int);

static int keepRunning = 1;

void sighandler(int dummy) {
    keepRunning = 0;
}

//https://github.com/zrafa/onscreenkeyboard/blob/master/key.c
int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

void nonblock(int state) {
    struct termios ttystate;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state == NB_ENABLE) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    } else if (state == NB_DISABLE) {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

}

int main(int argc, char *argv[]) {
    struct sigaction act;
    act.sa_handler = sighandler;
    sigaction(SIGINT, &act, NULL);

    struct sockaddr_in clientaddr; // Structure describing an Internet socket address
    socklen_t addrlen;              // client address length
    char c;

    char PORT[] = "9001";
    int slot = 0; // We start at client slot 0

    //Parsing the command line arguments
    while ((c = getopt(argc, argv, "c:a:")) != -1)
        switch (c) {
            case 'c':
                strcpy(PORT, argv[2]);
                isServerMode = 0;
                break;
            case 'a':
                strcpy(PORT, argv[2]);
                isServerMode = 1;
                break;
            case '?':
                fprintf(stderr, "Wrong arguments given!!!\n");
                exit(1);
            default:
                exit(1);
        }

    int socketUsed;
    while (keepRunning) {
        if (isServerMode) {
            startServer(PORT);
            printf("Server started at port no. %s\n", PORT);
            addrlen = sizeof(clientaddr);
            socketUsed = accept(listenfd, (struct sockaddr *) &clientaddr, &addrlen);
            if (socketUsed < 0) {
                error("accept() error");
            }
            fprintf(stdout, "A client is attached\n");
        } else {
            socketUsed = connectToServer("127.0.0.1", PORT);
            fprintf(stdout, "Connected to server\n");
        }

        char reply[100];

        /*
         * Launch 2 thread in order to have non-blocking IO
         * The child thread handles incoming packets
         * The parent thread handles stdin and sending
         */
        if (fork() == 0) {
            consoleRespond(socketUsed);
            fprintf(stdout, "Killing consoleRespond thread\n");
            keepRunning = 0;
        } else {
            while (keepRunning){
                fprintf(stdout, "# ");
                scanf("%s", reply);
                int bytesize = sizeof(reply);
                write(socketUsed, reply, bytesize);
            }
        }
    }

    //Closing SOCKET
    shutdown(socketUsed, SHUT_RDWR);
    close(socketUsed);
    fprintf(stdout, "Closing socket and shutting down.\n");
    return EXIT_SUCCESS;
}

//start server
void startServer(char *port) {
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
        exit(1);
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
        listenfd = socket(p->ai_family, p->ai_socktype, 0);
        if (listenfd == -1) {
            continue;
        }

        /*
         * bind()
         *  Give the socket file descriptor the local address ADDR (which is LEN bytes long)
         * */
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
            break; // Bind is successful, stop trying
        }
    }
    if (p == NULL) {
        perror("socket() or bind()");
        exit(1);
    }

    // Release the memory used for the socket linked list
    freeaddrinfo(res);


    /* listen()
           Prepare to accept connections on socket FD.
           N connection requests will be queued before further requests are refused.
    */
    int listenResult = listen(listenfd, 1);
    if (listenResult != 0) {
        perror("listen() error");
        exit(1);
    }
}

void consoleRespond(int socketDesc) {
    char mesg[99999], *reqline[3], data_to_send[BYTES], path[99999];
    int rcvd, fd, bytes_read;

    // Fill a block of bytes with value (int) '\0'
    memset((void *) mesg, (int) '\0', 99999);

    int isClientConnected = 1;
    while (isClientConnected) {
        // Receive data from client and write it to buffer mesg, defined the length of the buffer
        rcvd = recv(socketDesc, mesg, 99999, 0);

        if (rcvd < 0) {    // receive error
            fprintf(stderr, ("recv() error\n"));
            isClientConnected = 0;
        } else if (rcvd == 0) {    // receive socket closed
            fprintf(stderr, "Client disconnected upexpectedly.\n");
            isClientConnected = 0;
        } else    // message received
        {
            fprintf(stdout, "> %s\n", mesg);
            /*char reply[] = "I'm connected.";
            int bytesize = sizeof(reply);
            write(socketDesc, reply, bytesize);*/
        }
    }


/*
    char input;
    int isQuit = 0;
    nonblock(NB_ENABLE);
    while (!isQuit) {
        usleep(1);
        isQuit = kbhit();
        if (isQuit != 0) {
            input = fgetc(stdin);
            if (input == 'q')
                isQuit = 1;
            else
                isQuit = 0;
        }
    }
    nonblock(NB_DISABLE);*/
}

int connectToServer(char ip[], char *port) {
    int socket_desc;
    struct sockaddr_in server;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        fprintf(stdout, "Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    int intPort;
    sscanf(port, "%d", &intPort);

    // htons() accepts port as an integer
    server.sin_port = htons(intPort);

    //Connect to remote server
    int tryConnect = connect(socket_desc, (struct sockaddr *) &server, sizeof(server));
    if (tryConnect < 0) {
        puts("connect error");
        return 1;
    }
    return socket_desc;
}