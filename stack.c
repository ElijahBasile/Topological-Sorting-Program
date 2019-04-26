/*
 * stack.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "stack.h"

STACK* createStack () {
	// local definitions
	STACK* stack;

	// statements
	stack = (STACK*)malloc(sizeof(STACK));
	if (stack) {
		stack->count = 0;
		stack->top = NULL;
	} // if
	return stack;
} // createStack

bool pushStack (STACK* stack, void* dataInPtr) {
	// local definitions
	STACK_NODE* newPtr;

	//statements
	newPtr = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	if (!newPtr)
		return false;

	newPtr->dataPtr = dataInPtr;

	newPtr->link = stack->top;
	stack->top = newPtr;

	(stack->count)++;
	return true;
} // pushStack

void* popStack (STACK* stack) {
	// local definitions
	void* dataOutPtr;
	STACK_NODE* temp;

	// statements
	if (stack->count == 0)
		dataOutPtr = NULL;
	else {
		temp = stack->top;
		dataOutPtr = stack->top->dataPtr;
		stack->top = stack->top->link;
		free(temp);
		(stack->count)--;
	} // else
	return dataOutPtr;
} // popStack

void* stackTop (STACK* stack) {
	// statements
	if (stack->count == 0)
		return NULL;
	else
		return stack->top->dataPtr;
} // stackTop

bool emptyStack (STACK* stack) {
	// statements
	return (stack->count == 0);
} // emptyStack

bool fullStack (STACK* stack) {
	// local definitions
	STACK_NODE* temp;

	// statements
	if ((temp = (STACK_NODE*)malloc(sizeof(*(stack->top))))) {
		free(temp);
		return false;
	} // if

	// malloc failed
	return true;
} // fullStack

int stackCount (STACK* stack) {
	// statements
	return stack->count;
} // stackCount

STACK* destroyStack (STACK* stack) {
	// local definitions
	STACK_NODE* temp;

	// statements
	if (stack) {
		// delete all nodes in stack
		while (stack->top != NULL) {
			// delete data entry
			free (stack->top->dataPtr);

			temp = stack->top;
			stack->top = stack->top->link;
			free(temp);
		} // while

		// stack now empty. destroy stack head node
		free (stack);
	} // if stack
	return NULL;
}







