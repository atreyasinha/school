//
//  aksinha
//  pager-predict.c
//  Assignment 4: Virtual Paging Assignment
//				  Best predictive paging implementation
//
//  Created by Atreya Sinha on 10/31/21.
//  Copyright 2021 Atreya Sinha. All rights reserved.
//


/*
 * File: pager-predict.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains a predictive pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"
#include "limits.h"
#include "assert.h"

#define FLAG -1

struct p_stat {
    int page;
    int *timestamp;
};

typedef struct p_stat stat;

int lru(int proctmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], Pentry q[MAXPROCESSES], int *lru_temp);
int count_pages(stat *p);
void sort_page(stat *p);

void update_time(int proctmp, Pentry q[MAXPROCESSES], int pagetmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], int tick);
void paging(int proctmp, Pentry q[MAXPROCESSES], stat page_pred[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES]);
void active_processes(int proctmp, Pentry q[MAXPROCESSES], int pagetmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], 
						int active_procs[MAXPROCESSES], int lru_temp);

void init(int proctmp, int pagetmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], 
						stat page_pred[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES], int active_procs[MAXPROCESSES]);

void insert(int proctmp, int pagetmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], 
				stat page_pred[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES], Pentry q[MAXPROCESSES], int prev, 
					int current_procs[MAXPROCESSES], int cur);



void pageit(Pentry q[MAXPROCESSES]) {

	/* This file contains the stub for a predictive pager */
	/* You may need to add/remove/modify any part of this file */

	/* Static vars */
	static int initialized = 0;
	static int tick = 1; // artificial time
	static int timestamps[MAXPROCESSES][MAXPROCPAGES], active_procs[MAXPROCESSES], current_procs[MAXPROCESSES];
	static stat page_pred[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES];

	/* Local vars */
	int proctmp, pagetmp, lru_temp, prev, cur;
	proctmp = pagetmp = lru_temp = prev = cur = 0;
	

	/* initialize static vars on first run */
	if (!initialized) {
		/* Init complex static vars here */
		init(proctmp, pagetmp, timestamps, page_pred, active_procs);
		initialized = 1;
	}

	insert(proctmp, pagetmp, timestamps, page_pred, q, prev, current_procs, cur);
	update_time(proctmp, q, pagetmp, timestamps, tick);
	active_processes(proctmp, q, pagetmp, timestamps, active_procs, lru_temp);
	paging(proctmp, q, page_pred);

	/* advance time for next pageit iteration */
	tick++;
}



int lru(int proctmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], Pentry q[MAXPROCESSES], int *lru_temp) {
    int temp;

    for (int i = 0; i < MAXPROCPAGES; i++) {
        if (q[proctmp].pages[i]) {
			if (timestamps[proctmp][i] < INT_MAX) {
				*lru_temp = i;
				temp = 0;
			}
        }
    }

    return temp;
}

int count_pages(stat *p) {
	int i = 0;
	for (i = 0; p[i].page != FLAG && i < MAXPROCPAGES; i++);
	return i;
}

void sort_page(stat *p) {
	int c = count_pages(p);

	int loop = 0;
	int i = 1;
	stat temp;
	
	while (loop) {
		loop = 0;
		for (; i < c; i++) {
			assert(p[i - 1].timestamp != NULL && p[i].timestamp != NULL);

            if (*(p[i - 1].timestamp) < *(p[i].timestamp)) {
                temp = *(p + (i - 1));
				*(p + (i - 1)) = *(p + i);
				*(p + i) = temp;
				loop = 1;
            }
		}
	}
}

void update_time(int proctmp, Pentry q[MAXPROCESSES], int pagetmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], int tick) {
	for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
		if (q[proctmp].active) {
			pagetmp = q[proctmp].pc - 1 / PAGESIZE;
			timestamps[proctmp][pagetmp] = tick;
		}
	}
}

void paging(int proctmp, Pentry q[MAXPROCESSES], stat page_pred[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES]) {
	for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
		stat *s;

		if (q[proctmp].active) {
			for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
				s = page_pred[proctmp][(q[proctmp].pc + 100) / PAGESIZE];
				sort_page(s);
				
				for (int i = 0; i < count_pages(s); i++) {
					pagein(proctmp, s[i].page);
				}
			}
		}
	}
}

void active_processes(int proctmp, Pentry q[MAXPROCESSES], int pagetmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], 
						int active_procs[MAXPROCESSES], int lru_temp) {
	for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
		if (q[proctmp].active) {
			pagetmp = q[proctmp].pc / PAGESIZE;
			
			if (pagein(proctmp, pagetmp)) {
				active_procs[proctmp] = 0;
            	continue;
			}

			if (q[proctmp].pages[pagetmp] == 1 
				|| active_procs[proctmp] 
				|| lru(proctmp, timestamps, q, &lru_temp))			continue;

			active_procs[proctmp] = 1;

			if (!pageout(proctmp, lru_temp)) {
				fprintf(stderr, "pager-predict not yet implemented. Exiting...\n");
				exit(EXIT_FAILURE);
			}
		}

		for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++)	pageout(proctmp, pagetmp);
	}
}

void init(int proctmp, int pagetmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], 
						stat page_pred[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES], int active_procs[MAXPROCESSES]) {
	int i = 0;
	
	for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
		for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++) {
			timestamps[proctmp][pagetmp] = 0;

			for (i = 0; i < MAXPROCPAGES; i++) {
				page_pred[proctmp][pagetmp][i].page = FLAG;
				page_pred[proctmp][pagetmp][i].timestamp = NULL;
			}
		}

		active_procs[proctmp] = 0;
	}
}

void insert(int proctmp, int pagetmp, int timestamps[MAXPROCESSES][MAXPROCPAGES], 
				stat page_pred[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES], Pentry q[MAXPROCESSES], int prev, 
					int current_procs[MAXPROCESSES], int cur) {
	for (proctmp = 0; proctmp < MAXPROCESSES; proctmp++) {
		if (q[proctmp].active) {
			prev = current_procs[proctmp] / PAGESIZE;
			current_procs[proctmp] = q[proctmp].pc;
			cur = q[proctmp].pc / PAGESIZE;

			if (cur != prev) {
				pageout(proctmp, prev);

				stat *new = page_pred[proctmp][prev];

				for (pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++) {
					if (new[pagetmp].page == cur)	break;
					else if (new[pagetmp].page == FLAG) {
						new[pagetmp].timestamp = &(timestamps[proctmp][pagetmp]);
						new[pagetmp].page = cur;
						break;
					}
				}
			}
		}
	}
}