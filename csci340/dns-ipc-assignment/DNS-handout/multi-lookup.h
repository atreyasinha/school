//
//  aksinha
//  multi-lookup.h
//  Assignment 6: DNS Resolver via IPC
//
//  Created by Atreya Sinha on 12/04/21.
//  Copyright 2021 Atreya Sinha. All rights reserved.
//

#ifndef MULTILOOKUP_H
#define MULTILOOKUP_H

#define MAX_INPUT_FILES 10
#define MIN_RESOLVER_THREADS 2
#define MINARGS 3
#define USAGE "<inputFilePath> <outputFilePath>"
#define SBUFSIZE 1025
#define INPUTFS "%1024s"
#define QUEUE_SIZE 10
#define MAX_IP_LENGTH INET6_ADDRSTRLEN
#include "util.h"


void *requester(void *v);
void *resolver();

#endif

