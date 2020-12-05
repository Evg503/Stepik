#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <thread>

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

void runconnection(int sock)
{

	printf("Start connection\n");
	sleep(3);
	printf("Stop connection\n");
	close(sock);
}
void runserver()
{
	int ls_fd;

	ls_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(config.port);

	if (bind(ls_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(ls_fd, SOMAXCONN) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	int new_sock;
	while (new_sock = accept(ls_fd, 0, 0))
	{
		printf("Accept! %d\n", new_sock);
		std::thread t(runconnection, new_sock);
		t.detach();
	}

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

	runserver();
	printf("Stop!\n");

}
