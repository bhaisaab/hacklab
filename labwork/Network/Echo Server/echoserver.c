#include  <stdio.h>
#include  <stdlib.h>
#include  <errno.h>
#include  <string.h>

#include  <unistd.h>
#include  <sys/types.h>
#include  <netinet/in.h>
#include  <sys/socket.h>
#include  <sys/wait.h>

#define MYPORT 6400     /* the port users will be connecting to */
#define LQ_LEN 100      /* how many pending connections queue will hold */
#define MAXDATASIZE 255 /* max number of bytes we can get at once */

int main()
{
	int sockfd, newfd; /* listen on sock_fd, new connection on newfd */

	struct sockaddr_in servaddr;      /* my address information */
	struct sockaddr_in their_addr; /* connector's address information */
	int sin_size, n;

	char buff[MAXDATASIZE];

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("Socket error");
		exit(1);
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;           /* host byte order */
	servaddr.sin_port = htons(MYPORT);       /* host to network short, network byte order */
	servaddr.sin_addr.s_addr = INADDR_ANY;

	/*Bind*/
	if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1) 
	{
		perror("Bind failed");
		exit(1);
	}

	/*Listen*/
	if (listen(sockfd, LQ_LEN) == -1) 
	{
		perror("Listen failed");
		exit(1);
	}

	/*Accept*/
	while (1)
	{ 
		/* main accept() loop */
		sin_size = sizeof(struct sockaddr_in);

		if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) < 0)
		{
			perror("[Echo Server] Accept Error");
			//continue;
		}
		
		bzero(buff, MAXDATASIZE+1);

   	while ((n = read(newfd, buff, MAXDATASIZE)) > 0)
		{
			 buff[n] = 0;        /* null terminate */
       int lead = their_addr.sin_addr.s_addr; /*Assuming little endian address*/
		   printf("@%d.%d.%d.%d: %s", (lead<<24>>24)&0xff, (lead<<16>>24)&0xff, (lead<<8>>24)&0xff, (lead>>24)&0xff, buff);

			write(newfd, buff, strlen(buff));
		}

		if (n < 0)
			perror("[Echo Server] Read Error");
	
		close(newfd);
	}
   close(sockfd);
}

