#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <thread>
#include <string>

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

const char notfound [] ="HTTP/1.0 404 NOT FOUND\r\n"
			"Content-Type: text/html\r\n"
			"\r\n";


const char filetemplate[] = 	"HTTP/1.0 200 OK\r\n"
				"Content-Length: %ld\r\n"
				"Content-Type: text/html\r\n"
				"\r\n";

void filenotfound(int sock)
{
	write(sock, notfound, sizeof(notfound) -1);
}

void runconnection(int sock)
{
	char buffer[3000];

	printf("Start connection\n");
	ssize_t size;
	if((size = read(sock, buffer, sizeof buffer))>0)
	{
		std::string filename;
		write(1, buffer, size);
		write(1, "---\n", 4);
		if(strncmp(buffer, "GET ", 4) == 0)
		{
			filename = config.root;
			for(char *p = buffer+4; *p && (*p != ' ') && (*p != '?');++p)
				filename += *p;
		
			int fd = open(filename.c_str(), O_RDONLY);
			if(fd > 0)
			{
				off_t fsize = lseek(fd, 0, SEEK_END);
				lseek(fd, 0, SEEK_SET);

				int hsize = sprintf(buffer,filetemplate, fsize);
				write(sock, buffer, hsize);

				int rv;
				if((rv = sendfile( sock, fd, 0, fsize)) < 0)
				{
					printf( "Warning: sendfile returned %d (errno %d)\n", rv, errno);
				}

			}
			else
			{
				filenotfound(sock);
			}

		}
	}
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
		daemon(1,1);

	runserver();
	printf("Stop!\n");

}
