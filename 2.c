#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
 
int main()
{
int a;
pid_t pid, ppid, chpid;
chpid = fork();
pid = getpid();
ppid = getppid();
printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a); 

return 0;

}
