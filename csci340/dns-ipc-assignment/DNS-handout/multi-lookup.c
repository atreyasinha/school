//
//  aksinha
//  multi-lookup.c
//  Assignment 6: DNS Resolver via IPC
//
//  Created by Atreya Sinha on 12/04/21.
//  Copyright 2021 Atreya Sinha. All rights reserved.
//

#include "util.h"
#include "multi-lookup.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SHMOBJ_HOST "/host"
#define SHMOBJ_THREAD_STATUS "/thread_status"
#define SHMOBJ_COUNTER "/counter"
#define SHMOBJ_Q_LOCK "/q_lock"
#define SHMOBJ_F_LOCK "/f_lock"
#define SHMOBJ_CV_Q_FILL "/cv_q_fill"
#define SHMOBJ_CV_Q_EMPTY "/cv_q_empty"

pthread_mutex_t *q_lock = NULL, *f_lock = NULL;
pthread_mutexattr_t m_q_attr, m_f_attr;

pthread_cond_t *cond_q_fill = NULL, *cond_q_empty = NULL;
pthread_condattr_t cond_q_fill_attr, cond_q_empty_attr;

char *host_shared_msg;
int *count, *thread_status;
int cond_q_fill_shared, cond_q_empty_shared, q_lock_shared, f_lock_shared, 
                    shmfd_host, shmfd_counter, shmfd_thread_status, state;

FILE *outputfp = NULL, *inputfp = NULL;

int main(int argc, char* argv[]) {
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

    /********************************************************************************
    * 
    *                                  HOST START
    * 
    ********************************************************************************/
	shmfd_host = shm_open(SHMOBJ_HOST, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
    if (shmfd_host < 0) {
        perror("In shm_open(): shmfd_host");
        exit(1);
    }
    ftruncate(shmfd_host, 10 * SBUFSIZE * sizeof(char));
    // fprintf(stderr, "Created shared memory object %s\n", SHMOBJ_HOST);
    host_shared_msg = (char *) mmap(NULL, 10 * SBUFSIZE * sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd_host, 0);
    if (host_shared_msg == NULL) {
        perror("Error on mmap on host_shared_msg\n");
        exit(1);
    }
    // fprintf(stderr, "Shared memory segment allocated correctly ((%ld bytes)).\n", 10 * SBUFSIZE * sizeof(char));
    /********************************************************************************
    * 
    *                                  HOST END
    * 
    ********************************************************************************/



    /********************************************************************************
     * 
     *                                  THREAD STATUS START
     * 
     ********************************************************************************/
	shmfd_thread_status = shm_open(SHMOBJ_THREAD_STATUS, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
	if (shmfd_thread_status < 0) {
		perror("In shm_open(): shmfd_thread_status");
        exit(1);
	}
	ftruncate(shmfd_thread_status, sizeof(int));
    // fprintf(stderr, "Created shared memory object %s\n", SHMOBJ_THREAD_STATUS);
	thread_status = (int *) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd_thread_status, 0);
	if (thread_status == NULL) {
		perror("Error on mmap on count\n");
        exit(1);
	}
    // fprintf(stderr, "Shared memory segment allocated correctly ((%ld bytes)).\n", sizeof(int));
	*thread_status = 1;
    /********************************************************************************
    * 
    *                                  THREAD STATUS END
    * 
    ********************************************************************************/



    /********************************************************************************
    * 
    *                                  COUNTER START
    * 
    ********************************************************************************/
	shmfd_counter = shm_open(SHMOBJ_COUNTER, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
	if (shmfd_counter < 0) {
		perror("In shm_open(): shmfd_counter");
        exit(1);
	}
	ftruncate(shmfd_counter, sizeof(int));
    // fprintf(stderr, "Created shared memory object %s\n", SHMOBJ_COUNTER);
	count = (int *) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd_counter, 0);
	if (count == NULL) {
		perror("Error on mmap on count\n");
        exit(1);
	}
    // fprintf(stderr, "Shared memory segment allocated correctly ((%ld bytes)).\n", sizeof(int));
	*count = 0;
    /********************************************************************************
    * 
    *                                  COUNTER END
    * 
    ********************************************************************************/



    /********************************************************************************
    * 
    *                                  QUEUE LOCK START
    * 
    ********************************************************************************/
	q_lock_shared = shm_open(SHMOBJ_Q_LOCK, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
	if (q_lock_shared < 0) {
		perror("In shm_open(): q_lock_shared");
        exit(1);
	}
	ftruncate(q_lock_shared, sizeof(pthread_mutex_t));
    // fprintf(stderr, "Created shared memory object %s\n", SHMOBJ_Q_LOCK);
	q_lock = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, q_lock_shared, 0);
	if (q_lock == NULL) {
		perror("Error on mmap on q_lock\n");
        exit(1);
	}
    // fprintf(stderr, "Shared memory segment allocated correctly ((%ld bytes)).\n", sizeof(pthread_mutex_t));
    /********************************************************************************
    * 
    *                                  QUEUE LOCK END
    * 
    ********************************************************************************/



	/********************************************************************************
    * 
    *                                  FILE LOCK START
    * 
    ********************************************************************************/
	f_lock_shared = shm_open(SHMOBJ_F_LOCK, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
	if (f_lock_shared < 0) {
		perror("In shm_open(): f_lock_shared");
        exit(1);
	}
	ftruncate(f_lock_shared, sizeof(pthread_mutex_t));
    // fprintf(stderr, "Created shared memory object %s\n", SHMOBJ_F_LOCK);
	f_lock = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, f_lock_shared, 0);
	if (f_lock == NULL) {
		perror("Error on mmap on f_lock\n");
        exit(1);
	}
    // fprintf(stderr, "Shared memory segment allocated correctly ((%ld bytes)).\n", sizeof(pthread_mutex_t));
    /********************************************************************************
    * 
    *                                  FILE LOCK END
    * 
    ********************************************************************************/



	/********************************************************************************
    * 
    *                                  CV FILL START
    * 
    ********************************************************************************/
	cond_q_fill_shared = shm_open(SHMOBJ_CV_Q_FILL, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
	if (cond_q_fill_shared < 0) {
		perror("In shm_open(): cond_q_fill_shared");
        exit(1);
	}
	ftruncate(cond_q_fill_shared, sizeof(pthread_cond_t));
    // fprintf(stderr, "Created shared memory object %s\n", SHMOBJ_CV_Q_FILL);
	cond_q_fill = (pthread_cond_t*) mmap(NULL, sizeof(pthread_cond_t), PROT_READ | PROT_WRITE, MAP_SHARED, cond_q_fill_shared, 0);
	if (cond_q_fill == NULL) {
		perror("Error on mmap on condition\n");
        exit(1);
	}
    // fprintf(stderr, "Shared memory segment allocated correctly ((%ld bytes)).\n", sizeof(pthread_cond_t));
    /********************************************************************************
    * 
    *                                  CV FILL END
    * 
    ********************************************************************************/



    /********************************************************************************
    * 
    *                                  CV EMPTY START
    * 
    ********************************************************************************/
	cond_q_empty_shared = shm_open(SHMOBJ_CV_Q_EMPTY, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG);
	if (cond_q_empty_shared < 0) {
		perror("In shm_open(): cond_q_empty_shared");
        exit(1);
	}
	ftruncate(cond_q_empty_shared, sizeof(pthread_cond_t));
    // fprintf(stderr, "Created shared memory object %s\n", SHMOBJ_CV_Q_EMPTY);
	cond_q_empty = (pthread_cond_t*) mmap(NULL, sizeof(pthread_cond_t), PROT_READ | PROT_WRITE, MAP_SHARED , cond_q_empty_shared, 0);
	if (cond_q_empty == NULL) {
		perror("Error on mmap on condition\n");
        exit(1);
	}
    // fprintf(stderr, "Shared memory segment allocated correctly ((%ld bytes)).\n", sizeof(pthread_cond_t));
    /********************************************************************************
    * 
    *                                  CV EMPTY END
    * 
    ********************************************************************************/


    // mutex attribute initialization
	pthread_mutexattr_init(&m_q_attr);
    pthread_mutexattr_init(&m_f_attr);

	if (pthread_mutexattr_setpshared(&m_q_attr, PTHREAD_PROCESS_SHARED) || pthread_mutexattr_setpshared(&m_f_attr, PTHREAD_PROCESS_SHARED)
        || pthread_mutex_init(q_lock, &m_q_attr) || pthread_mutex_init(f_lock, &m_f_attr)) {
            fprintf(stdout,"Error: Mutex Initialization ended!\n");
            return EXIT_FAILURE;
	}

	if (pthread_condattr_setpshared(&cond_q_fill_attr, PTHREAD_PROCESS_SHARED) || pthread_condattr_setpshared(&cond_q_empty_attr, PTHREAD_PROCESS_SHARED)
        || pthread_cond_init(cond_q_empty, &cond_q_empty_attr) || pthread_cond_init(cond_q_fill, &cond_q_fill_attr)) {
            fprintf(stdout,"Error: Conditional Variable Initialization ended!\n");
            return EXIT_FAILURE;
	}

	int i, threads_resolved[argc - 2];
    for (i = 0; i < argc - 2; i++)          {  if ((threads_resolved[i] = fork()) == 0) { resolver(NULL); exit(0); }  }
	for (i = 1; i < argc - 2; i++)          requester(argv[i]);
	*thread_status = 0;
	for (i = 0; i < argc; i++)              waitpid(threads_resolved[i], &state, WUNTRACED | WCONTINUED);

    // destroy mutex objects
    pthread_mutex_destroy(q_lock);
	pthread_mutex_destroy(f_lock);
    pthread_mutexattr_destroy(&m_q_attr);
	pthread_mutexattr_destroy(&m_f_attr);
    pthread_cond_destroy(cond_q_fill);
	pthread_cond_destroy(cond_q_empty);
	pthread_condattr_destroy(&cond_q_empty_attr);
	pthread_condattr_destroy(&cond_q_fill_attr);
	
    // requesting the removal of the shm object     --  shm_unlink()
    if (shm_unlink(SHMOBJ_CV_Q_EMPTY) || shm_unlink(SHMOBJ_CV_Q_FILL) || shm_unlink(SHMOBJ_F_LOCK)
	            || shm_unlink(SHMOBJ_Q_LOCK) || shm_unlink(SHMOBJ_COUNTER) || shm_unlink(SHMOBJ_THREAD_STATUS)
                || shm_unlink(SHMOBJ_HOST)) {
                    perror("In shm_unlink()");
                    exit(1);
    }

    fclose(outputfp);                               // close output file

	return EXIT_SUCCESS;
}

void* requester(void* v) {
	char host_name[SBUFSIZE];

    inputfp = fopen(v, "r");

    // Read File and Process
	while(fscanf(inputfp, INPUTFS, host_name) > 0) {
        while (*count == QUEUE_SIZE - 1)       pthread_cond_wait(cond_q_empty, q_lock);
        pthread_mutex_lock(q_lock);                // lock 
        strncpy(&host_shared_msg[*count * SBUFSIZE], host_name, SBUFSIZE);
        (*count)++;
        pthread_cond_signal(cond_q_fill);
		pthread_mutex_unlock(q_lock); 
	}

    // close input file
	fclose(inputfp);

	return 0;
}

void* resolver() {
    char *host_name, firstipstr[MAX_IP_LENGTH];
	
	while (*thread_status) {
        pthread_mutex_lock(q_lock);                                    // lock
	    while (!*count)                     pthread_cond_wait(cond_q_fill, q_lock);

        while (*count) {
            host_name = (char*) malloc(SBUFSIZE * sizeof(char));
            int t = (*count);
            
            if (*count > 0) { t = (*count - 1); if (t < 0) t = 0; }
            strncpy(host_name, &host_shared_msg[t * SBUFSIZE], SBUFSIZE);
            (*count)--;

            if (host_name) {
                pthread_mutex_unlock(q_lock);                         // unlock

                // Error looking up Address: Name or service not known
                // dnslookup error: 
                if (dnslookup(host_name, firstipstr, sizeof(firstipstr)) == UTIL_FAILURE) {
                    fprintf(stderr, "dnslookup error: %s\n", host_name);
                    strncpy(firstipstr, "", sizeof(firstipstr));
                }

                pthread_mutex_lock(f_lock);                           // lock
                fprintf(outputfp, "%s,%s\n", host_name, firstipstr);
                pthread_cond_signal(cond_q_empty);
                pthread_mutex_unlock(f_lock);                         // unlock
            }

            free(host_name);                                          // free poped string
        }
	}

	return 0;
}
