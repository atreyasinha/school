//
//  aksinha
//  schedule.c
//  Assignment 3: Multilevel Round Robin Scheduler
//
//  Created by Atreya Sinha on 10/05/21.
//  Copyright 2021 Atreya Sinha. All rights reserved.
//
#include "schedule.h"
#include <stdlib.h>

struct node 
{
    PCB *p;
    struct node *next;
    struct node *prev;
}   *left_one, *right_one,
    *left_two, *right_two,
    *left_three, *right_three,
    *left_four, *right_four;

int index;
int count;

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

    left_four = NULL;
    right_four = NULL;

    index = 0;
    count = -1;
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

    switch (process->priority) {
        case 0:
            if (right_one || left_one) left_one->next = cur;
            else {
                right_one = cur;
            }
            left_one = cur;
            break;
        case 1:
            if (right_two || left_two) left_two->next = cur;
            else {
                right_two = cur;
            }
            left_two = cur;
            break;
        case 2:
            if (right_three || left_three) left_three->next = cur;
            else {
                right_three = cur;
            }
            left_three = cur;
            break;
        case 3:
            if (right_four || left_four) left_four->next = cur;
            else {
                right_four = cur;
            }
            left_four = cur;
            break;
        
        default:
            return 1;
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
        count = (count + 1) % 4;

        switch (count) {
            case 0:
                if (right_one) { 
                    index = 1;
                    break;
                }
                if (right_two) { 
                    count = (count + 1) % 4;
                    index = 2;
                    break;
                }
                if (right_three) { 
                    count = (count + 2) % 4;
                    index = 3;
                    break;
                }
                if (right_four) { 
                    count = (count + 3) % 4;
                    index = 4;
                    break;
                }
            case 1:
                if (right_two) { 
                    index = 2;
                    break;
                }
                if (right_three) { 
                    count = (count + 1) % 4;
                    index = 3;
                    break;
                }
                if (right_four) { 
                    count = (count + 2) % 4;
                    index = 4;
                    break;
                }
                if (right_one) { 
                    count = (count + 3) % 4;
                    index = 1;
                    break;
                }
            case 2:
                if (right_three) { 
                    index = 3;
                    break;
                }
                if (right_four) { 
                    count = (count + 1) % 4;
                    index = 4;
                    break;
                }
                if (right_one) { 
                    count = (count + 2) % 4;
                    index = 1;
                    break;
                }
                if (right_two) { 
                    count = (count + 3) % 4;
                    index = 2;
                    break;
                }
            case 3:
                if (right_four) { 
                    index = 4;
                    break;
                }
                if (right_one) { 
                    count = (count + 1) % 4;
                    index = 1;
                    break;
                }
                if (right_two) { 
                    count = (count + 2) % 4;
                    index = 2;
                    break;
                }
                if (right_three) { 
                    count = (count + 3) % 4;
                    index = 3;
                    break;
                }
        }
        
        PCB* cur;
        cur = (PCB *) malloc( sizeof(PCB));

        *time = 5 - index;

        switch (index) {
            case 1:
                cur = right_one->p;
                right_one = right_one->next;
                if (!right_one) left_one = NULL;
                break;
            case 2:
                cur = right_two->p;
                right_two = right_two->next;
                if (!right_two) left_two = NULL;
                break;
            case 3:
                cur = right_three->p;
                right_three = right_three->next;
                if (!right_three) left_three = NULL;
                break;
            case 4:
                cur = right_four->p;
                right_four = right_four->next;
                if (!right_four) left_four = NULL;
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
    if (!right_one && !right_two && !right_three && !right_four) return 0;
	return 1;
}
