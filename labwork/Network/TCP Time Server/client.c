#include  <stdio.h>
#include  <stdlib.h>
#include  <errno.h>
#include  <string.h>

#include  <unistd.h>
#include  <netdb.h>
#include  <sys/types.h>
#include  <netinet/in.h>
#include  <sys/socket.h>
#define PORT 8020     /* the port client will be connecting to */
#define MAXDATASIZE 100 /* max number of bytes we can get at once */

int
main(int argc, char **argv)
{
	int     sockfd, n;
	char    recvline[MAXDATASIZE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		perror("usage: a.out <IPaddress>");
		exit(1);
	}

  while(1)
  {
	  if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		  perror("socket error");

	  bzero(&servaddr, sizeof(servaddr));
	  servaddr.sin_family = AF_INET;
	  servaddr.sin_port = htons(PORT); /* to daytime server */

	  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	  {
		  printf("inet_pton error for %s", argv[1]);
		  exit(1);
	  }

	  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		  perror("connect error");

	  while ( (n = read(sockfd, recvline, MAXDATASIZE)) > 0)
	  {
		  recvline[n] = 0;        /* null terminate */
		  printf("Reply from server::");
		  if (fputs(recvline, stdout) == EOF)
		  perror("fputs error");
	  }
	  if (n < 0)
		  perror("read error");

	  close(sockfd);
  }
	return 0;
}

