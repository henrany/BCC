#include "common.h"
#include "messages.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 501

message vec[50];

void usage(int argc, char **argv) {
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

// initialize the array for the locations to 0
void initialize() {
    for (int i = 0; i < 50; i++) {
        vec[i].x = 0;
        vec[i].y = 0;
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }

    initialize();

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage))) {
        logexit("bind");
    }

    if (0 != listen(s, 10)) {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    struct sockaddr_storage cstorage;
    struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
    socklen_t caddrlen = sizeof(cstorage);

    while (1) {
        // accept incoming connection 
        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            logexit("accept");
        }
        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);
        // two buffers, one for receiving the total message request 
        // the other for recieving intermediate messages;
        // incrementer for storing the total capacity of the array
        char buf[BUFSZ];
        char auxBuf[BUFSZ];
        int incrementer = 0;
        int breakFromLoop = 0;
        while (1) {
            // set the buffer data to 0
            if(breakFromLoop) break;
            memset(buf, 0, BUFSZ);
            memset(auxBuf,0, BUFSZ);
            size_t count = 0;
            // create an infinite loop to make sure all the messages 
            // are recieved
            // receive intermediate messges in the auxiliary buffer 
            // concatenate it to the main buffer to be processed
            while(1){
                if(buf[strlen(buf) - 1] == '\n') break;
                count += recv(csock, auxBuf, BUFSZ-1, 0);
                strcat(buf, auxBuf);
                memset(auxBuf, 0, BUFSZ);
            }
            fputs(buf, stdout);
            // getting the cordinate
            char xCord[6] = {0};
            char yCord[6] = {0};
            int index = 0;
            int currentPosition = 0;
            // Validating the size of the string.
            if (strlen(buf) > 500) {
                close(csock);
                breakFromLoop = 1;
            }
            // iterate throuth the message
            /// close the client when there's an invalid character in the message
            // if new line is encounterd, an operation must be performed 
            // check for first letter after or the letter after the new line 
            // and perform the operation of add, remove , list, search or close 
            for (int i = 0; i < sizeof(buf); i++) {
                if (buf[i] == ' ') {
                    index++;
                    continue;
                }

                if ((buf[i] < 'a' && buf[i] > 'z') &&
                    (buf[i] < 0 && buf[i] > 9) && buf[i] != ' ' &&
                    buf[i] != '\n') {
                    close(csock);
                    breakFromLoop = 1;
                }

                if (buf[i] == '\n') {
                    if (buf[currentPosition] == 'a') {
                        int added = addLocations(vec, xCord, yCord, incrementer,csock, count);
                        if (added) {
                            incrementer++;
                        }
                    } 
                    else if (buf[currentPosition] == 'r') {
                        int removed = removeFromList(vec, xCord, yCord,incrementer, csock, count);
                        if (removed) {
                            incrementer--;
                        }
                    } 
                    else if (buf[currentPosition] == 'l') {
                        listAllItems(vec, incrementer, csock, count);
                    } 
                    else if (buf[currentPosition] == 'q') {
                        query(vec, xCord, yCord, incrementer, csock, count);
                    } else if (buf[currentPosition] == 'k') {
                        close(csock);
                        breakFromLoop = 1;
                    }
                    index = 0;
                    memset(xCord, 0, 6);
                    memset(yCord, 0, 6);
                    currentPosition = i + 1;
                }

                if (index == 1) {
                    strncat(xCord, &buf[i], 1);
                }
                if (index == 2) {
                    strncat(yCord, &buf[i], 1);
                }
            }
        }

        close(csock);
    }

    exit(EXIT_SUCCESS);
}