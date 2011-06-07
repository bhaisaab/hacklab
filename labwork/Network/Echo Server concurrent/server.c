#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MYPORT 5300
#define MAXLINE 100

int main()
{
	int sockfd,connfd,n;  /* socket file descriptor */
	char buff[100];
	char recvline[MAXLINE+1];
	time_t ticks;
	pid_t childpid;
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
	listen(sockfd,100);
    printf("Echo server up & running!\n");
	int sin_size = sizeof(struct sockaddr_in);
	for(; ;)
	{
		connfd=accept(sockfd,(struct sockaddr *)&client_addr,&sin_size);
    
    int add = client_addr.sin_addr.s_addr;

		if((childpid = fork()) == 0)
		{
		     	/*...read...*/
			 while((n=read(connfd,recvline,MAXLINE))>0)
			 {
				 recvline[n]='\0';
				 printf("Client IP:%d.%d.%d.%d >>%s\n",(add<<24>>24)&0x000000ff, (add<<16>>24) &0x000000ff,
		                                               (add<<8>>24)&0x000000ff, (add>>24) &0x000000ff, recvline);
				 write(connfd,recvline,strlen(recvline));
			 }
			 if(n<0)
			 {
				 printf("read error");
				 return 0;
			 }	

		}
	
		close(connfd);
	}

	close(sockfd);

	return 0;
}
