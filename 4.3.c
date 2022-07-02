//
//  4.3.c
//  
//
//  Created by mac on 04.10.2018.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int fd1[2], fd2[2], res;
    int a, b, sum;
    if (pipe(fd1) < 0)
    {
        printf("Can`t create pipe1");
        exit(-1);
    }
    if (pipe(fd2) < 0)
    {
        printf("Can`t create pipe2");
        exit(-1);
    }
    res = fork();
    if(res < 0)
    {
        printf("fork eror");
        exit(-1);
    }
    else if(res > 0)
    {
        close(fd1[0]);
        close(fd2[1]);
        scanf("%d%d", &a, &b);
        write(fd1[1], &a, sizeof(int));
        write(fd1[1], &b, sizeof(int));
        read(fd2[0], &sum, sizeof(int));
        printf("%d\n", sum);
    }
    else
    {
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0], &a, sizeof(int));
        read(fd1[0], &b, sizeof(int));
        sum = a + b;
        write(fd2[1], &sum, sizeof(int));
    }
    return 0;
}
