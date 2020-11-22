       #include <sys/mman.h>
       #include <sys/stat.h>        /* For mode constants */
       #include <fcntl.h>           /* For O_* constants */

       #include <unistd.h>
       #include <sys/types.h>


#include <string.h>
#include <stdio.h>


int main()
{
	size_t size = 1<<20;

	int memd = shm_open("/test.shm", O_CREAT | O_RDWR, 0666);
	if (memd  == -1)
	{
		perror("open");
	}

	int res = ftruncate(memd, size);
	if (res == -1)
	{
		perror("ftruncate");
	}

	void *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, memd, 0);
	if (p != (void*) -1)
		memset(p, 13, size);
	else
		perror("mmap");
}

