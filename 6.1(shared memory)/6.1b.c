//
//  main.c
//  6.1
//
//  Created by mac on 25.10.2018.
//  Copyright © 2018 mac. All rights reserved.
//

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
    char * array;
    int     shmid;
    int     new = 1;
    int     fd;
    char    pathname[] = "1.c";
    char    filename[] = "6.1a.c";
    key_t   key;
    
    if((fd = open(filename, O_RDWR, 0666)) < 0)
    {
        printf("Can`t open file\n");
        exit(-1);
    }
    
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    if((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
        
        if(errno != EEXIST){
            printf("Can\'t create shared memory\n");
            exit(-1);
        } else {
            if((shmid = shmget(key, 3*sizeof(int), 0)) < 0){
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }
    
    if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    
    printf("%s", array);
    
    if(shmdt(array) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
