       #include <sys/ipc.h>
       #include <sys/shm.h>

#include <string.h>
#include <stdio.h>


int main()
{
	key_t key = ftok("/tmp/mem.temp", 1);
	size_t size = 1<<20;
	int memd = shmget(key, size, IPC_CREAT | 0666);
	void *p = shmat(memd, 0, 0);
	if (p != (void*) -1)
		memset(p, 42, size);
	else
		printf("error\n");
}

