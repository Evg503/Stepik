#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
	int fds[2];
	char buff[1024];
	socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
	if(fork())
	{ //parent
		for(;;)
		{
			write(fds[0], "Hello", 5);
			ssize_t size = read(fds[0], buff, sizeof(buff)-1);
			buff[size]=0;
			printf("parent read:[%s]\n", buff);
		}
	}
	else
	{ //child
		for(;;)
		{
	                ssize_t size = read(fds[1], buff, sizeof(buff)-1);
        	        buff[size]=0;
                	printf("child read:[%s]\n", buff);
			write(fds[1], "World", 5);
		}
	}

}

