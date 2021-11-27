//
//  aksinha
//  multi-lookup.c
//  Assignment 5: DNS Resolver Write Up
//
//  Created by Atreya Sinha on 11/21/21.
//  Copyright 2021 Atreya Sinha. All rights reserved.
//

#include "util.h"
#include "multi-lookup.h"
#include <pthread.h>
#include <unistd.h>
#include "queue.h"

FILE *outputfp = NULL, *inputfp = NULL;
pthread_mutex_t q_mutex, o_mutex;
queue q;
int thread_status = 0;

int main(int argc, char const *argv[]) {
    if (argc < MINARGS || argc >= MAX_INPUT_FILES) {
        fprintf(stderr, "Invalid amount of arguments: %d\n", (argc - 1));
        fprintf(stderr, "Usage:\n %s %s\n", argv[0], USAGE);
        return EXIT_FAILURE;
    }

    outputfp = fopen(argv[(argc - 1)], "w");
    if (!outputfp) {
        perror("Error: Bogus Output File Path");
	    return EXIT_FAILURE;
    }

    pthread_t threads_requested[argc - 2];
    pthread_t threads_resolved[MIN_RESOLVER_THREADS];

    if (pthread_mutex_init(&q_mutex, NULL) || pthread_mutex_init(&o_mutex, NULL)) {
		fprintf(stdout,"Error: Mutex Initialization ended!\n");
		return EXIT_FAILURE;
	}

    if (queue_init(&q, QUEUE_SIZE) == QUEUE_FAILURE) {
		fprintf(stderr, "Error: Queue Initialization ended!\n");
		return EXIT_FAILURE;
	}
    
    int i;
    for (i = 0; i < argc - 2; i++)                  pthread_create(&threads_requested[i], NULL, requester, (void*) argv[i+1]);
    for (i = 0; i < MIN_RESOLVER_THREADS; i++)      pthread_create(&threads_resolved[i], NULL, resolver, NULL);
    for (i = 0; i < argc - 2; i++)                  pthread_join(threads_requested[i], NULL);
    
    thread_status = 1;
    for (i = 0; i < MIN_RESOLVER_THREADS; i++)      pthread_join(threads_resolved[i], NULL);
    
    // destroy mutex objects
    pthread_mutex_destroy(&q_mutex);                
    pthread_mutex_destroy(&o_mutex);
    
    fclose(outputfp);                               // close output file
    
    queue_cleanup(&q);                              // free memory from queue

    return 0;
}

void *requester(void *v) {
    char host_name[SBUFSIZE];

    inputfp = fopen(v, "r");

    // Read File and Process
	while(fscanf(inputfp, INPUTFS, host_name) > 0) {
        while (1) {
			pthread_mutex_lock(&q_mutex);           // lock 

            if (queue_is_full(&q)) {
				pthread_mutex_unlock(&q_mutex);     // unlock
				usleep(rand() % 100);               // sleep
            } else {
                char *host_string = malloc(SBUFSIZE);
                strncpy(host_string, host_name, SBUFSIZE);
				queue_push(&q, host_string);        // push
				pthread_mutex_unlock(&q_mutex);     // unlock
                break;
            }
        }
	}

    // close input file
	fclose(inputfp);

	return 0;
}

void *resolver() {
    char *host_name, firstipstr[MAX_IP_LENGTH];

    while (!queue_is_empty(&q) || !thread_status) {
        pthread_mutex_lock(&q_mutex);                                   // lock 

        if (queue_is_empty(&q))     pthread_mutex_unlock(&q_mutex);     // unlock
        else {
            host_name = queue_pop(&q);

            if (host_name) {
                pthread_mutex_unlock(&q_mutex);                         // unlock

                // Error looking up Address: Name or service not known
                // dnslookup error: 
                if (dnslookup(host_name, firstipstr, sizeof(firstipstr)) == UTIL_FAILURE) {
                    fprintf(stderr, "dnslookup error: %s\n", host_name);
		            strncpy(firstipstr, "", sizeof(firstipstr));
                }

                pthread_mutex_lock(&o_mutex);                           // lock
                fprintf(outputfp, "%s,%s\n", host_name, firstipstr);
                pthread_mutex_unlock(&o_mutex);                         // unlock
            }

            free(host_name);                                            // free poped string
        }
    }
    
    return 0;
}