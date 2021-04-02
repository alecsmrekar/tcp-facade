#ifndef SOCKETFACADE_LIBRARY_H
#define SOCKETFACADE_LIBRARY_H

void startServing(char *, int *);

extern int awaitConnections(int);

int connectToSocket(int);

extern int openSocketConnection(char[], int);

#endif //SOCKETFACADE_LIBRARY_H
