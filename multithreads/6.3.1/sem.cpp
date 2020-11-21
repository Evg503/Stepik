#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

           union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };


int main()
{
	key_t key = ftok("/tmp/sem.temp", 1);

	int sems = semget(key, 16, IPC_CREAT | 0666);

	for(int i = 0; i < 16; ++i)
	{

		semun val;
		val.val = i;

		semctl(sems, i, SETVAL, val); 
	}
}

