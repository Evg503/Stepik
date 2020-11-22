#include <pthread.h>


void *f(void*)
{
	while(true);
}


int main()
{
	pthread_t thread_id;
	pthread_create (&thread_id, NULL, f, NULL);

	pthread_join(thread_id, NULL);
}


