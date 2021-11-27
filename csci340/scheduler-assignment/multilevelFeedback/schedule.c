//
//  aksinha
//  schedule.c
//  Assignment 3: Writing a Scheduler
//
//  Created by Atreya Sinha on 10/05/21.
//  Copyright 2021 Atreya Sinha. All rights reserved.
//
#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>

struct node 
{
    PCB *p;
    struct node *next;
    struct node *prev;
}   *left_one, *right_one,
    *left_two, *right_two,
    *left_three, *right_three;

int index;
int count;

void age_helper(struct node *r, struct node *l);

/**
 * Function to initialize any global variables for the scheduler.
 */
void init(){
	left_one = NULL;
    right_one = NULL;

    left_two = NULL;
    right_two = NULL;

    left_three = NULL;
    right_three = NULL;

    index = 0;
    count = -1;
}

/**
 * Function called every simulated time period to provide a mechanism
 * to age the scheduled processes and trigger feedback if needed.
 */
void age(){
	if (right_two) age_helper(right_two, left_two);
	if (right_three) age_helper(right_three, left_three);
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
    cur->prev = NULL;

    switch (process->priority) {
        case 0:
            if (right_one || left_one) {
                left_one->next = cur;
                cur->prev = left_one;
            }
            else {
                right_one = cur;
            }
            left_one = cur;
            break;
        case 1:
            if (right_two || left_two) {
                left_two->next = cur;
                cur->prev = left_two;
            } else {
                right_two = cur;
            }
            left_two = cur;
            break;
        case 2:
            if (right_three || left_three) {
                left_three->next = cur;
                cur->prev = left_three;
            } else {
                right_three = cur;
            }
            left_three = cur;
            break;
        
        default:
            return 1;
    }
	return 0;
}

/**
 * Function to get the next process from the scheduler
 * @Param time - pass by reference variable to store the quanta of time
 * 		the scheduled process should run for. Return -1 for FCFS.
 * @Return returns pointer to process control block that needs to be executed
 * 		returns NULL if there is no process to be scheduled.
 */
PCB* nextProcess(int *time){
    if (hasProcess()) {
        count = (count + 1) % 4;
        
		if (right_one) index = 1;
		if (!right_one && right_two) index = 2;
		if (!right_one && right_two && right_three) index = 3;


        PCB* cur;
        cur = (PCB *) malloc( sizeof(PCB));

        *time = 4 - index;

        switch (index) {
            case 1:
                cur = right_one->p;
				cur->age = 0;
                right_one = right_one->next;
                if (!right_one) left_one = NULL;
                break;
            case 2:
                cur = right_two->p;
				cur->age = 0;
                right_two = right_two->next;
                if (!right_two) left_two = NULL;
                break;
            case 3:
                cur = right_three->p;
				cur->age = 0;
                right_three = right_three->next;
                if (!right_three) left_three = NULL;
                break;
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
    if (!right_one && !right_two && !right_three) return 0;
	return 1;
}

void age_helper(struct node *r, struct node *l) {
	struct node *cur;
    cur = r;
    while (cur != NULL){
		cur->p->age = cur->p->age + 1;
		if (cur->p->age > 999) {
			PCB* p_cur;
        	p_cur = (PCB *) malloc( sizeof(PCB));
			
			p_cur->pid = cur->p->pid;
			p_cur->priority = 0;

			if (r == right_three) p_cur->priority = 1;

			addProcess(p_cur);

			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
		}
        cur = cur->next;
    }
}
