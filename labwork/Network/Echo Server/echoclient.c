#include  <stdio.h>
#include  <stdlib.h>
#include  <errno.h>
#include  <string.h>

#include  <netdb.h>
#include  <sys/types.h>
#include  <netinet/in.h>
#include  <sys/socket.h>

#define PORT 6400       /* the port client will be connecting to */
#define MAXDATASIZE 255 /* max number of bytes we can get at once */

int main(int argc, char** argv)
{
	int  sockfd, n;

   /*Stores received data from server*/
	char recvline[MAXDATASIZE + 1];
   /*Stores sent data from client*/
   char sendline[MAXDATASIZE + 1];
   
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		perror("usage: a.out <IPaddress>");
		exit(1);
	}

	printf("Echo Client\n");

	while(1)
	{
		if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			perror("socket error");

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(PORT); /*Echo Server*/

		if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		{
			printf("inet_pton error for %s", argv[1]);
			exit(1);
		}

		//scanf("%[^\n]s", sendline);
		if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
			perror("connect error");

		fgets(sendline, MAXDATASIZE, stdin);
		write(sockfd, sendline, strlen(sendline));

		n = read(sockfd, recvline, MAXDATASIZE);
		recvline[n] = 0;        /* null terminate */
		printf(">> %s", recvline);

		if (n < 0)
			perror("Read Error");

		close(sockfd);
	}
	return 0;	
}
