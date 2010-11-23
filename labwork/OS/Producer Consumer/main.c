#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef int buffer_item;
#define BUFFER_SIZE 10
#define TRUE 1

buffer_item buffer[BUFFER_SIZE];
/* The mutex lock */
pthread_mutex_t mutex;

/* the semaphores */
sem_t full, empty;

/* buffer counter */
int counter;

pthread_t tid;       //Thread ID
pthread_attr_t attr; //Set of thread attributes

void *producer(void *param); /* the producer thread */
void *consumer(void *param); /* the consumer thread */

int sendData(buffer_item item, int sender)
{
   return 0;
}

void initializeData() 
{

   /* Create the mutex lock */
   pthread_mutex_init(&mutex, NULL);

   /* Create the full semaphore and initialize to 0 */
   sem_init(&full, 0, 0);

   /* Create the empty semaphore and initialize to BUFFER_SIZE */
   sem_init(&empty, 0, BUFFER_SIZE);

   /* Get the default attributes */
   pthread_attr_init(&attr);

   /* init buffer */
   counter = 0;
}


/* Add an item to the buffer */
int insert_item(buffer_item item) {
   /* When the buffer is not full add the item
      and increment the counter*/
   if(counter < BUFFER_SIZE) {
      buffer[counter] = item;
      counter++;
      return 0;
   }
   else { /* Error the buffer is full */
      printf("\x1b[41mBUFFER FULL\x1b[00m\n");
      return -1;
   }
}

/* Remove an item from the buffer */
int remove_item(buffer_item *item) {
   /* When the buffer is not empty remove the item
      and decrement the counter */
   if(counter > 0) {
      *item = buffer[(counter-1)];
      counter--;
      return 0;
   }
   else { /* Error buffer empty */
      printf("\x1b[41mBUFFER EMPTY\x1b[00m\n");
      return -1;
   }
}

/* Producer Thread */
void *producer(void *param) {
   buffer_item item;

   while(TRUE) {
      /* sleep for a random period of time */
      sleep(rand()%4);

      /* generate a random number */
      item = rand();

      /* acquire the empty lock */
      sem_wait(&empty);
      /* acquire the mutex lock */
      pthread_mutex_lock(&mutex);

      if(insert_item(item)) {
         fprintf(stderr, " Producer report error condition\n");
      }
      else {
         printf("producer produced %d\n", item);
         sendData(item, 0);
      }
      /* release the mutex lock */
      pthread_mutex_unlock(&mutex);
      /* signal full */
      sem_post(&full);
   }
}

/* Consumer Thread */
void *consumer(void *param) {
   buffer_item item;

   while(TRUE) {
      /* sleep for a random period of time */
      //sleep(rand() % 4);

      /* aquire the full lock */
      sem_wait(&full);
      /* aquire the mutex lock */
      pthread_mutex_lock(&mutex);
      if(remove_item(&item)) {
         fprintf(stderr, "Consumer report error condition\n");
      }
      else {
         printf("consumer consumed %d\n", item);
         sendData(item, 1);
      }
      /* release the mutex lock */
      pthread_mutex_unlock(&mutex);
      /* signal empty */
      sem_post(&empty);
   }
}


int main(int argc, char* argv[])
{
   int i;

   if(argc!=4)
    fprintf(stderr, "./a.out <INT, sleeptime> <INT, producers> <INT, consumers>\n");

   int mainSleepTime = atoi(argv[1]); /* Time in seconds for main to sleep */
   int numProd = atoi(argv[2]); /* Number of producer threads */
   int numCons = atoi(argv[3]); /* Number of consumer threads */

/* Initialize the app */
   initializeData();

   /* Create the producer threads */
   for(i = 0; i < numProd; i++) {
      /* Create the thread */
      pthread_create(&tid,&attr,producer,NULL);
    }

   /* Create the consumer threads */
   for(i = 0; i < numCons; i++) {
      /* Create the thread */
      pthread_create(&tid,&attr,consumer,NULL);
   }

   /* Sleep for the specified amount of time in milliseconds */
   sleep(mainSleepTime);

   /* Exit the program */
   printf("Exiting the program\n");
   exit(0);

}
