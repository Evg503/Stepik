#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct Config {

	const char * host;
	int port;
	const char * root;
	bool is_daemon;

} config = {0, 0, 0, true};



void print_config()
{
	printf(" Host:\"%s\"\n", config.host);
	printf(" Root:\"%s\"\n", config.root);
	printf(" Port:%d\n", config.port);
	printf(" Is daemon:\"%s\"\n", config.is_daemon?"Daemon":"Not");
}

int main(int argc, char** argv)
{

	int opt;
	while((opt = getopt(argc, argv, "h:p:d:D")) != -1)
	{
		switch (opt)
		{
			case 'h':
				config.host = optarg;
				break;
			case 'p':
				config.port = atoi(optarg);
				break;
			case 'd':
				config.root = optarg;
				break;
			case 'D':
				config.is_daemon = false;
		}
	}


	print_config();

	if(config.is_daemon)
		daemon(0,0);

	sleep(10);
	printf("Stop!\n");

}
