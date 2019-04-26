/*
 * stack.h
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#ifndef STACK_H_
#define STACK_H_

// Structures

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct stack_node {
	char dataPtr;
	struct stack_node* link;
} STACK_NODE;

typedef struct {
	int count;
	STACK_NODE* top;
} STACK;

STACK*	createStack 	();
bool	pushStack		(STACK* stack, void* dataInPtr);
void*	popStack		(STACK* stack);
void*	stackTop		(STACK* stack);
bool	emptyStack		(STACK* stack);
bool	fullStack		(STACK* stack);
int		stackCount		(STACK* stack);
STACK*	destroyStack	(STACK* stack);

#endif /* STACK_H_ */
