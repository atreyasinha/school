//
//  aksinha
//  pager-lru.c
//  Assignment 4: Virtual Paging Assignment
//				  LRU paging implementation
//
//  Created by Atreya Sinha on 10/31/21.
//  Copyright 2021 Atreya Sinha. All rights reserved.
//

/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) {

	/* This file contains the stub for an LRU pager */
	/* You may need to add/remove/modify any part of this file */

	/* Static vars */
	static int initialized = 0;
	static int tick = 1; // artificial time
	static int timestamps[MAXPROCESSES][MAXPROCPAGES];

	/* Local vars */
	int proctmp;
	int pagetmp;
	int temp_tick;
	int evict;

	/* initialize static vars on first run */
	if (!initialized) {
		for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
			for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++) {
				timestamps[proctmp][pagetmp] = 0;
			}
		}
		initialized = 1;
	}

	/* TODO: Implement LRU Paging 
	fprintf(stderr, "pager-lru not yet implemented. Exiting...\n");
	exit(EXIT_FAILURE); */
	for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
		if (q[proctmp].active) {
			pagetmp = q[proctmp].pc / PAGESIZE;
			timestamps[proctmp][pagetmp] = tick;

			if (pagein(proctmp, pagetmp))	continue;

			temp_tick = tick + 1;
			for (pagetmp = 0; pagetmp < q[proctmp].npages; pagetmp++) {
				if (timestamps[proctmp][pagetmp] < temp_tick) {
					if (q[proctmp].pages[pagetmp]) {
						temp_tick = timestamps[proctmp][pagetmp];
						evict = pagetmp;
					}
				}
			}
			
			pageout(proctmp, evict);
		}
	}

	/* advance time for next pageit iteration */
	tick++;
}
