#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>


int main()
{
	key_t tok = ftok("/tmp/msg.temp", 1);

	struct message {
 	   long mtype;
    	   char mtext[80];
	} msg;

	int msgid = msgget(tok, 0666 | IPC_CREAT);



	size_t size = msgrcv(msgid, &msg, 80, 0, 0);

	FILE * f = fopen("/home/box/message.txt", "w");
	fwrite(msg.mtext, size, 1, f);
	fclose(f);
}
