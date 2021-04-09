## TCP Connection Facade in C
This is a simple collections of methods that allows a user to establish a network with a remote machine via TCP. The program can operate in either server or client mode.

`main.c` showcases how the library can be used. Run it with:

#### Server mode
For running a server, you only need to specify which port number the socket should be bound to. The method is: 

```
int connection = openSocketConnection(char port);
if (connection > -1) {
    printf("Success.\n");
}
```


#### Client mode
In order to connect to a remote socket, you need to specify the host and port by calling: 

```
int connection = connectToSocket(char port, char host);
if (connection > -1) {
    printf("Success.\n");
}
```

#### Communication
```
char reply[] = "Hello, World!";
int success = write(connection, reply, sizeof(reply));
if (success > -1) {
    printf("Success.\n");
}
```