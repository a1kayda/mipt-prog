 #include <sys/types.h>
 #include <unistd.h>
 #include <stdio.h>

int main()
{
	printf("%d\n", getuid());
	return(0);
}

