#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"common.h"

struct Message{
    int x;
    int y;
};

typedef struct Message message;

int addLocations(message vec[], char *x, char *y, int count,int csock, size_t value){
    int found = 0;
    int xCord = atoi(x);
    int yCord = atoi(y);

    if(count == 50){
        char text[] = "limit exceeded";
        sendMessage(csock, text, value);
        return 0;
    }



    for(int i=0; i<count;i++){
        if(vec[i].x == xCord && vec[i].y == yCord){
            found = 1;
            break;
        }
    }

    char buf[500] = {0};
    if(found){
        sprintf(buf, "%d %d already exists\n", xCord,yCord);
        sendMessage(csock,buf, value);
        return 0;
    }
    vec[count].x = xCord;
    vec[count].y = yCord;
    sprintf(buf,"%d %d added\n", xCord, yCord);
    sendMessage(csock,buf, value);
    return 1;
}

int removeFromList(message vec[], char *x, char *y, int count, int csock, size_t value){
    int found = 0;
    int position = 0;
    int xCord = atoi(x);
    int yCord = atoi(y);
    char buf[500] = {0};

    for(int i=0;i<count;i++){
        if(vec[i].x == xCord && vec[i].y == yCord){
            found = 1;
            position = i;
            break;
        }
    }
    if(!found){
        sprintf(buf,"%d %d does not exist\n", xCord, yCord);
        sendMessage(csock,buf,value);
        return 0;
    }

    for(int i=position; i<count-1;i++){
        vec[i].x = vec[i+1].x;
        vec[i].y = vec[i+1].y;
    }
    sprintf(buf,"%d %d removed\n", xCord, yCord);
    sendMessage(csock,buf,value);
    return 1;
}

void listAllItems(message vec[], int count, int csock, size_t value){
    if(count == 0){
        char text[] = "none";
        sendMessage(csock,text,value);
        return;
    }

    char buf[500] = {0};
    for(int i=0;i<count;i++){
    char list[40] = {0};
        if(i == count -1){
            sprintf(list, "%d %d\n", vec[i].x, vec[i].y);
            strcat(buf,list);
        }
        else{
            sprintf(list, "%d %d ", vec[i].x, vec[i].y);
            strcat(buf,list);
        }
    }
    sendMessage(csock,buf,value);
    return;
}

void query(message vec[], char *x, char *y, int count, int csock, size_t value){
    if(count == 0){
        char text[] = "none";
        sendMessage(csock,text,value);
        return;
    }
    int position = 0;
    int xCord = atoi(x);
    int yCord = atoi(y);
    float min = 100000;
    char buf[500] = {0};

    for(int i=0;i<count; i++){
        float distance = 0;
        distance = sqrt(pow((xCord - vec[i].x),2) + pow((yCord - vec[i].y),2));
        if(distance < min){
            min = distance;
            position = i;
        }
    }

    sprintf(buf,"%d %d\n", vec[position].x, vec[position].y);
    sendMessage(csock, buf,value);
}