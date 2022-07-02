//
//  main.c
//  7.3(server)
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
#include <unistd.h>


#define LAST_MESSAGE 255

int main(void)
{
    
    int msqid;
    char pathname[]="1.c";
    key_t  key;
    int len, maxlen, result;
    
    struct mymsgbuf
    {
        long mtype;
        int mtext[3];
    } mybuf;
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    
    maxlen = 81;
    
    while(1){
        
        if (( len = (int)msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        printf("get N1 = %d, N2 = %d, message type = %ld", mybuf.mtext[0], mybuf.mtext[1], mybuf.mtype);
        result = fork();
        if(result < 0)
        {
            printf("Can\'t fork\n");
            exit(-1);
        }
        if(result == 0)
        {
            
            mybuf.mtext[2] = mybuf.mtext[0] * mybuf.mtext[1];
            mybuf.mtype = 25;
            len = 3 * sizeof(int) + 1;
            if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }
            exit(0);
        }
        
    }

    return 0;
}
