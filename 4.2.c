#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2], i = 0;
    /* Попытка создать pipe */
    if (pipe(fd) < 0) {
        /* Если создать pipe не удалось, печатаем об этом
         сообщение и прекращаем работу */
        printf("Can`t create pipe");
        exit(-1);
    }
    for(i = 0;;i++)
    {
        write(fd[1] , "m", 1);
        printf("%d\n", i);
        }
    return 0;
}

