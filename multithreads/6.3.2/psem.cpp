       #include <fcntl.h>           /* For O_* constants */
       #include <sys/stat.h>        /* For mode constants */
       #include <semaphore.h>



int main()
{
       sem_t * sem = sem_open("/test.sem", O_CREAT, 0666, 66);
}


