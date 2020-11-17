#include <sys/types.h>
#include <stdio.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

int main()
{
	mq_attr attr {O_RDONLY|O_CREAT, 10, 1024, 0};
	
	int queue = mq_open("/test.mq", O_RDONLY|O_CREAT,0666, &attr);

	char buff[1024];

	size_t size = mq_receive(queue, buff, 1024, NULL);

	FILE * f = fopen("/home/box/message.txt", "w");
	fwrite(buff, size, 1, f);
	fclose(f);
}
