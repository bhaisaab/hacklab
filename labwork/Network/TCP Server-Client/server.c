#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MYPORT 13

int main()
{
	int sockfd,connfd;  /* socket file descriptor */
	char buff[100];
	time_t ticks;
	struct sockaddr_in my_addr,client_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Server-socket() error!");
		return 0;
	}

	/* host byte order */
	my_addr.sin_family = AF_INET;
	/* short, network byte order */
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
    /* zero the rest of the struct */
	memset(&(my_addr.sin_zero), 0, sizeof my_addr);
	if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("Server-bind() error! Try with higher permission, hint: sudo");
		exit(1);
	}

	/*....other codes....*/
	listen(sockfd,10);
    printf("Day Time Server Up and Running!\n");
	int sin_size = sizeof(struct sockaddr_in);
	for(; ;)
	{
		connfd=accept(sockfd,(struct sockaddr *)&client_addr,&sin_size);
        int add = client_addr.sin_addr.s_addr;
		printf("Client IP Address::%d.%d.%d.%d\n",(add<<24>>24)&0x000000ff, (add<<16>>24) &0x000000ff,
                                                  (add<<8>>24)&0x000000ff, (add>>24) &0x000000ff);

		time(&ticks);
		sprintf(buff,"%.24s\r\n",ctime(&ticks));
		write(connfd,buff,strlen(buff));
		
		close(connfd);
	}

	close(sockfd);

	return 0;
}
