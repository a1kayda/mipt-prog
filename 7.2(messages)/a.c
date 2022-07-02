//
//  main.c
//  7.2(messages)
//
//  Created by mac on 15/11/2018.
//  Copyright © 2018 mac. All rights reserved.
//

//
//  main.c
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
    char pathname[]="1.c";
    key_t  key;
    int i = 0, len, maxlen;
    
    struct mymsgbuf
    {
        long mtype;
        int mtext;
    } mybuf;
    
    /* Create or attach message queue  */
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    
    
    while(1){
        
        i++;
        
        maxlen = 81;
        
        scanf("%d", &mybuf.mtext);
        
        len = sizeof(int);
        
        mybuf.mtype = 1;
        
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
        
        if (( len = (int)msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0)) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        /*
        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(0);
        }
        
        if(i == 6)
        {
            mybuf.mtype = LAST_MESSAGE;
            len         = 0;
            
            if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }
        }*/
        printf("message type = %ld, Nfactorial = %d\n", mybuf.mtype, mybuf.mtext);
    }
    
    
    return 0;
}
