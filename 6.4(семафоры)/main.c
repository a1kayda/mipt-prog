//
//  main.c
//  6.4(семафоры)
//
//  Created by mac on 08.11.2018.
//  Copyright © 2018 mac. All rights reserved.


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void Operation(int semid, int sem_num, int sem_op)
{
    struct sembuf mybuf;
    mybuf.sem_flg = 0;
    mybuf.sem_num = sem_num;
    mybuf.sem_op = sem_op;
    semop(semid, &mybuf, 1);
}

int main()
{
    int semid, result;
    char pathname[] = "1.c";
    key_t key;
    if((key = ftok(pathname,0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if((semid = semget(key, 2, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get semid\n");
        exit(-1);
    }
    result = fork();
    if(result < 0)
    {
        printf("Can\'t fork child\n");
        exit(-1);
        }
    if(result == 0)
    {
        Operation(semid, 0, 1);
        while(1)
        {
            printf("www\n");
            Operation(semid, 0, -1);
            Operation(semid, 1, -1);
            Operation(semid, 0, 1);
            Operation(semid, 1, 1);
            printf("aaaa\n");
        }
    }
    else
    {
        Operation(semid, 1, 1);
        while(1)
        {
            printf("qqq\n");
            Operation(semid, 1, -1);
            Operation(semid, 0, -1);
            Operation(semid, 0, 1);
            Operation(semid, 1, 1);
            printf("bbbb\n");
        }
    }
        return 0;
    }
