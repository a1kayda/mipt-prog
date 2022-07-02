//
//  main.c
//  05-4.c
//
//  Created by mac on 18.10.2018.
//  Copyright © 2018 mac. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int a[3];

void * Func1(void *dummy)
{
    pthread_t mythid;
    mythid = pthread_self();
    for(int i = 0; i < 10000000; i++)
    {
        a[0]+=1;
        a[1]+=1;
    }
    
    return NULL;
}
void * Func2(void *dummy)
{
    pthread_t mythid;
    mythid = pthread_self();
    for(int i = 0; i < 10000000; i++)
    {
        a[1]+=1;
        a[2]+=1;
    }
    
    return NULL;
}

int main() {
    pthread_t thid1, thid2;
    int result;
    for(int i = 0; i < 3; i++)
    {
        a[i] = 0;
    }
    result = pthread_create( &thid1, (pthread_attr_t *)NULL, Func1, NULL);
    
    if(result != 0){
        printf ("Error on thread 1 create, return value = %d\n", result);
        exit(-1);
    }
    
    result = pthread_create( &thid2, (pthread_attr_t *)NULL, Func2, NULL);
    
    if(result != 0){
        printf ("Error on thread 2 create, return value = %d\n", result);
        exit(-1);
    }
    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);
    printf("a[0] = %d\na[1] = %d\na[0] + a[1] = %d\na[2] = %d\n", a[0], a[1], a[0]+a[1], a[2]);
    return 0;
}
