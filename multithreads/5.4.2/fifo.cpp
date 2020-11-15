#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


const char* name_in = "/home/box/in.fifo";
const char* name_out = "/home/box/out.fifo";

int main()
{

	mkfifo(name_in, 0666);
	mkfifo(name_out, 0666);

	int in = open(name_in, O_RDONLY);
	int out = open(name_out, O_WRONLY);


	char buff[1024];
	for(;;)
	{
		ssize_t size = read(in, buff, sizeof(buff));
		write(out, buff, size);
	}
}

