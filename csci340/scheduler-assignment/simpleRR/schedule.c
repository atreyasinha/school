//
//  aksinha
//  schedule.c
//  Assignment 3: Simple Round Robin Schedular
//
//  Created by Atreya Sinha on 10/05/21.
//  Copyright 2021 Atreya Sinha. All rights reserved.
//
#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>

struct node {
	PCB *p;
	struct node *next;
	struct node *prev;
} *left, *right;

/**
 * Function to initialize any global variables for the scheduler.
 */
void init(){
	left = NULL;
	right = NULL;
}

/**
 * Function to add a process to the scheduler
 * @Param process - Pointer to the process control block for the process that
 * 			needs to be scheduled. PCB is defined in the header.
 * @return true/false response for if the addition was successful
 */
int addProcess(PCB* process){
	struct node *cur;
	cur = (struct node *) malloc( sizeof(struct node));

	cur->p = process;
	cur->next = NULL;

	if (!hasProcess()) {
		left = cur;
		right = cur;
	} else {
		left->next = cur;
		left = cur;
	}

	return 0;
}

/**
 * Function to get the next process from the scheduler
 * @Param time - pass by reference variable to store the quanta of time
 * 		the scheduled process should run for
 * @Return returns pointer to process control block that needs to be executed
 * 		returns NULL if there is no process to be scheduled.
 */
PCB* nextProcess(int *time){
	if (hasProcess()) {
		*time = 4;
        
		PCB* cur;
		cur = right->p;

		if (left != right) right = right->next;
		else {
			right = NULL;
			left = NULL;
		}

        return cur;
	}
	return NULL;
}

/**
 * Function that returns a boolean 1 True/0 False based on if there are any
 * processes still scheduled
 * @Return 1 if there are processes still scheduled 0 if there are no more
 *		scheduled processes
 */
int hasProcess(){
	if (left == NULL && right == NULL) return 0;
	return 1;
}
