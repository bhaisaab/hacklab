#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEST_PORT 13
#define MAXLINE 100

int main(int argc, char **argv)
{
	int sockfd,n;
	char recvline[MAXLINE+1];
	struct sockaddr_in dest_addr;

    if(argc != 2)
    {
      printf("[USAGE] a.out <IP>\n");
      exit(1);
    }

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("[Client] socket() error!!!!");
		return 0;
	}

	/* host byte order */
	dest_addr.sin_family = AF_INET;
	
	/* short, network byte order */
	dest_addr.sin_port = htons(DEST_PORT);
	
	if(inet_pton(AF_INET, argv[1], &dest_addr.sin_addr)<=0)
	{
		printf("inet_pton error for %s",argv[1]);
		return 0;
	}
	
	/* zero the rest of the struct */
	memset(&(dest_addr.sin_zero), 0, sizeof dest_addr);
	if(connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("[CLIENT] connect() error");
		return 0;
	}

	/*...other codes...*/
	while((n=read(sockfd,recvline,MAXLINE))>0)
	{
		recvline[n]='\0';
		printf("%s",recvline);
	}
	if(n<0)
	{
		printf("read error");
		return 0;
	}
	return 0;
}
