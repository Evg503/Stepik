#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void my_proc(bool is_child)
{
	const char* pid_file = is_child?"/home/box/pid_child":"/home/box/pid_parent";
	FILE* f = fopen(pid_file, "w");
	fprintf(f, "%d", getpid());
	fclose(f);
	signal(SIGTERM,is_child? SIG_DFL:SIG_IGN);
}

int main()
{
	if(fork())
	{ //parent
		my_proc(false);
		int status;
		wait(&status);
		while(1) sleep(1);
	}
	else
	{//child
		my_proc(true);	
		while(1) sleep(1);
	}
}


