#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

void usage(int argc, char **argv) {
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("example: %s 127.0.0.1 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

#define BUFSZ 501

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != addrparse(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != connect(s, addr, sizeof(storage))) {
        logexit("connect");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    char buf[BUFSZ];
    while (1) {
        memset(buf, 0, BUFSZ);
        printf("mensagem> ");
        fgets(buf, BUFSZ - 1, stdin);
        size_t count = send(s, buf, strlen(buf), 0);
        if (count != strlen(buf)) {
            logexit("send");
        }

        memset(buf, 0, BUFSZ);
        unsigned total = 0;
        while (1) {
            int received = 0;
            count = recv(s, buf + total, BUFSZ - total, 0);
            for(int i=0;i<count;i++){
                if(buf[i] == '\n'){
                    received = 1;
                    break;
                }
            }
            if(received) break;
            if (count == 0) {
                // Connection terminated.
                break;
            }
            total += count;
        }
        fputs(buf, stdout);
    }
    close(s);
    exit(EXIT_SUCCESS);
}