#include <pthread.h>
#include <stdio.h>
       #include <sys/types.h>
       #include <unistd.h>


void *f(void*)
{
	while(true);
}


int main()
{
	pthread_t thread_id;
	pthread_create (&thread_id, NULL, f, NULL);
	FILE *f = fopen("/home/box/main.pid", "w");
	fprintf(f, "%d", getpid());
	fclose(f);
	pthread_join(thread_id, NULL);
}


