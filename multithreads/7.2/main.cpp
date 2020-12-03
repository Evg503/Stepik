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

pthread_mutex_t mutex;
void* wait_mutex(void*)
{
	pthread_mutex_lock(&mutex);
	printf("Mutex!\n");
	pthread_mutex_unlock(&mutex);
	return NULL;
}

pthread_spinlock_t spinlock;
void* wait_spinlock(void*)
{
        pthread_spin_lock(&spinlock);
        printf("SPINLOCK!\n");
        pthread_spin_unlock(&spinlock);
	return NULL;
}

pthread_rwlock_t rwlock;
void* wait_rlock(void*)
{
        pthread_rwlock_rdlock(&rwlock);
        printf("Read!\n");
        pthread_rwlock_unlock(&rwlock);
	return NULL;
}

void* wait_wlock(void*)
{
        pthread_rwlock_wrlock(&rwlock);
        printf("Write!\n");
        pthread_rwlock_unlock(&rwlock);
	return NULL;
}

void run_wait_mutex()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	pthread_t thread;
	pthread_create(&thread, NULL, wait_mutex, NULL);
	pthread_detach(thread);
	pthread_mutex_unlock(&mutex);
}

void run_wait_rwlock()
{
        pthread_rwlock_init(&rwlock, NULL);
        pthread_rwlock_wrlock(&rwlock);
        pthread_t thread1;
        pthread_create(&thread1, NULL, wait_rlock, NULL);
        pthread_detach(thread1);
        pthread_t thread2;
        pthread_create(&thread2, NULL, wait_wlock, NULL);
        pthread_detach(thread2);
	pthread_rwlock_unlock(&rwlock);
}

void run_wait_spinlock()
{
        pthread_spin_init(&spinlock, 0);
        pthread_spin_lock(&spinlock);
        pthread_t thread;
        pthread_create(&thread, NULL, wait_spinlock, NULL);
        pthread_detach(thread);
        pthread_spin_unlock(&spinlock);
}

int main()
{
	save_pid();

	run_wait_mutex();
	run_wait_spinlock();
	run_wait_rwlock();
	sleep(10);
}
