#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#ifdef EVGENY
#define PID_FILE "my.pid"
#else
#define PID_FILE "/home/box/pid"
#endif


int main()
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	FILE* f = fopen(PID_FILE, "w");
	fprintf(f,"%d", getpid());
	fclose(f);
	for(;;)
	{
		sleep(1);
	}
}
