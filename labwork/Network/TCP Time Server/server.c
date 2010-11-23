#include  <stdio.h>
#include  <stdlib.h>
#include  <errno.h>
#include  <string.h>
#include  <sys/types.h>
#include  <netinet/in.h>
#include  <sys/socket.h>
#include  <sys/wait.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MYPORT 8020      /* the port users will be connecting to */
#define BACKLOG 10       /* how many pending connections queue will hold */
#define MAXDATASIZE 100 /* max number of bytes we can get at once */

int main()
{
	int sockfd, newfd; /* listen on sock_fd, new connection on newfd */
	struct sockaddr_in servaddr;      /* my address information */
	char buff[MAXDATASIZE];
	struct sockaddr_in their_addr; /* connector's address information */
	int sin_size;
	time_t ticks;
	pid_t childpid;


	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket error");
		exit(1);
	}

	printf("Daytime server up & running!\n");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;           /* host byte order */
	servaddr.sin_port = htons(MYPORT);       /* short, network byte order */
	servaddr.sin_addr.s_addr = INADDR_ANY;   /* auto-fill with my IP */

	
	/*Bind*/
	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1) {
		perror("Bind failed");
		exit(1);
	}

	/*Listen*/
	if (listen(sockfd, BACKLOG) == -1) {
		perror("Listen failed");
		exit(1);
	}

	
	/*Accept*/
	while(1)
	{ /* main accept() loop */
		sin_size = sizeof(struct sockaddr_in);
		if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
		{
			perror("Accept error");
			continue;
		}
		
		if((childpid = fork()) == 0)
		{
			ticks = time(NULL);
			printf("\nServer::Connection from %s\n", inet_ntoa(their_addr.sin_addr));
			sprintf(buff, "%.24s\r\n", ctime(&ticks));
			write(newfd, buff, strlen(buff));
		}

		close(newfd); /* parent doesn't need this */
	}
	close(sockfd);
	return 0;
}

