#ifndef SOCKETFACADE_LIBRARY_H
#define SOCKETFACADE_LIBRARY_H

int startServing(char *, int *);

extern int awaitConnections(int);

int connectToSocket(char[], char[]);

extern int openSocketConnection(char[]);

#endif //SOCKETFACADE_LIBRARY_H
