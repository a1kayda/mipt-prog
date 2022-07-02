//
//  b.c
//  7.1(messages)
//
//  Created by mac on 15/11/2018.
//  Copyright © 2018 mac. All rights reserved.
//

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main(void)
{
    int msqid;
    char pathname[]="09-1a.c";
    key_t  key;
    int len, maxlen;
    
    struct mymsgbuf
    {
        long mtype;
        long long int mtext;
    } mybuf;
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    
    while (1) {
        
        maxlen = 81;
        
        if (( len = (int)msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        
        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(0);
        }
        
        printf("message type = %ld, info = %lld\n", mybuf.mtype, mybuf.mtext);
    }
    
    return 0;
}

