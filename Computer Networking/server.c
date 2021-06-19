#include "common.h"
#include "messages.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

message vec[50];

void usage(int argc, char **argv) {
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

void initialize(){
    for(int i=0;i<50;i++){
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
    printf("bound to %s, waiting connections\n", addrstr);
    int incrementer = 0;
    while (1) {
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            logexit("accept");
        }

        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);
        // printf("[log] connection from %s\n", caddrstr);

        char buf[BUFSZ];
        memset(buf, 0, BUFSZ);
        size_t count = recv(csock, buf, BUFSZ-1, 0);
        char xCord[12] = {0};
        char yCord[12] = {0};
        int index= 0;
        if(buf[0] != 'l'){
            for(int i=0; i<sizeof(buf)-32; i++){
            if(buf[i] == ' '){
                index++;
                continue;
            }

            if(index == 1){
                strncat(xCord, &buf[i], 1);
            }
            if(index == 2){
                strncat(yCord, &buf[i], 1);
            }
        }

        }
        if(buf[0] == 'a'){
            int added = addLocations(vec,xCord,yCord,incrementer,csock,count);
            if(added){
                incrementer++;
            }
        }
        else if(buf[0] == 'r'){
            int removed = removeFromList(vec,xCord,yCord,incrementer,csock,count);
            if(removed){
                incrementer--;
            }
        }
        else if(buf[0] == 'l'){
            listAllItems(vec,incrementer,csock, count);
        }
        else if(buf[0] == 'q'){
            query(vec,xCord,yCord,incrementer,csock,count);
        }
        else{
            printf("later implemented\n");
        }
        
        close(csock);
    }

    exit(EXIT_SUCCESS);
}