#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void save_pid()
{
	FILE *f = fopen("/home/box/main.pid", "rw");

	fprintf(f, "%d", getpid());
	fclose(f);
}

pthread_cond_t cond;
pthread_mutex_t mutex;
void* wait_cond(void*)
{
	pthread_mutex_lock(&mutex);
	printf("condition?\n");
	pthread_cond_wait(&cond, &mutex);
	printf("Condition!\n");
	return NULL;
}

pthread_barrier_t barrier;
void* wait_barrier(void*)
{
        pthread_barrier_wait(&barrier);
        printf("Barrier!\n");
	return NULL;
}

void run_wait_cond()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);


	pthread_t thread;
	pthread_create(&thread, NULL, wait_cond, NULL);
	pthread_detach(thread);

	sleep(1);
	pthread_cond_broadcast(&cond);
}

void run_wait_barrier()
{
        pthread_barrier_init(&barrier, 0, 2);
        
	pthread_t thread;
        pthread_create(&thread, NULL, wait_barrier, NULL);
        pthread_detach(thread);

	printf("Wait battier2\n");
	pthread_barrier_wait(&barrier);
}

int main()
{
	save_pid();

	run_wait_cond();
	run_wait_barrier();
	sleep(5);
}
