#include "cs537.h"
#include "request.h"
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 10000 
/////////////////////////////////////////
// server.c: A very, very simple web server
//
// To run:
//  server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
/////////////////////////////////////////////////////

// CS537: Parse the new arguments too


/////////////////////////////////////
// strcut for in args to producer //
///////////////////////////////////

typedef struct __myarg_t {
	struct sockaddr_in *clientaddr;
	int listenfd;
} myarg_t;


////////////////////////////
// Put and Get routines  //
//////////////////////////

int buffer[MAX]; //buffe size
int fill_index;
int use_index;
int count;
int real_size;

void put(int value) 
{
	buffer[fill_index] = value;
	fill_index = (fill_index + 1) % real_size;
	count++; 
}

int get() {
	int tmp = buffer [use_index];
	use_index = (use_index + 1) % real_size;
	count--;
	return tmp;
}

////////////////////////////
// Producer and consumer //
//////////////////////////

pthread_cond_t empty, fill;
pthread_mutex_t mutex;

///////////////
// producer //
/////////////

void *producer (void *arg) {
	// upack paras
	myarg_t *m = (myarg_t *) arg;
	struct sockaddr_in *clientaddr = m->clientaddr;	
	int listenfd = m->listenfd;
	while (1){
		// clientaddr, listenfd
		int clientlen = sizeof(*clientaddr);
		int connfd = Accept(listenfd, (SA *)clientaddr, (socklen_t *) &clientlen);
		pthread_mutex_lock(&mutex);
		while (count == real_size)
			pthread_cond_wait(&empty, &mutex);
		put(connfd);
		pthread_cond_signal(&fill);
		pthread_mutex_unlock(&mutex);
	}
}

///////////////
// consumer //
/////////////

void *consumer(void *arg){
	while (1){
		int connfd;
		pthread_mutex_lock(&mutex);
                while (count == 0)
                        pthread_cond_wait(&fill, &mutex);
                connfd = get();
		requestHandle(connfd);
                Close(connfd);
		pthread_cond_signal(&empty);
                pthread_mutex_unlock(&mutex);
		
	}
}






void getargs(int *port, int *num_thread, int *buffer_size, int argc, char *argv[])
{
    if (argc != 4) {
	fprintf(stderr, "Usage: %s <port> <threads> <buffers>\n", argv[0]);
	exit(1);
    }
    *port = atoi(argv[1]);
    *num_thread = atoi(argv[2]);
    *buffer_size = atoi(argv[3]);
}


int main(int argc, char *argv[])
{
    int listenfd, port, num_thread, buffer_size;
    struct sockaddr_in clientaddr;
    /* initalzaiton for pthread_mutex & ptread_cond */ 
    int rc = pthread_mutex_init(&mutex, NULL);
    assert(rc == 0);
    
    rc = pthread_cond_init(&empty, NULL);
    assert(rc == 0);
    
    rc = pthread_cond_init(&fill, NULL);
    assert(rc == 0);

    getargs(&port,&num_thread, &buffer_size, argc, argv);
    pthread_t *worker_pool = malloc(num_thread * sizeof(pthread_t));
    pthread_t master;

    // pass real size
    real_size = buffer_size;
    listenfd = Open_listenfd(port);
    
    ///////////////////////////////// 
    // CS537: Create some threads //
    ///////////////////////////////
    
    /* producer thread */
    myarg_t args;
    args.listenfd = listenfd;
    args.clientaddr = &clientaddr;    	
    pthread_create(&master, NULL, producer, &args);

    /* consumer thread */
    int i;
    for (i = 0; i < num_thread; i++)
    {
	pthread_create(&worker_pool[i], NULL, consumer, NULL);
    }
    
    // main loops forever
    pthread_join(master, NULL);
	
	// CS537: In general, don't handle the request in the main thread.
	// Save the relevant info in a buffer and have one of the worker threads 
	// do the work.
    return 0;
}


    



 
