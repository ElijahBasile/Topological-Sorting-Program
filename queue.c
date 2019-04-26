/*
 * queue.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "queue.h"


QUEUE* createQueue (void) {
	// local definitions
	QUEUE* queue;

	// statements
	queue = (QUEUE*)malloc(sizeof(QUEUE));
	if (queue) {
		queue->front = NULL;
		queue->rear = NULL;
		queue->count = 0;
	} // if
	return queue;
} // createQueue

bool enqueue (QUEUE* queue, void* itemPtr) {
	// local definitions
	QUEUE_NODE* newPtr;

	// statements
	if (!(newPtr = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE))))
		return false;

	newPtr->dataPtr = itemPtr;
	newPtr->next = NULL;

	if (queue->count == 0)
		// inserting into null queue
		queue->front = newPtr;
	else
		queue->rear->next = newPtr;

	(queue->count)++;
	queue->rear = newPtr;
	return true;
}

bool dequeue (QUEUE* queue, void** itemPtr) {
	// local definitions
	QUEUE_NODE* deleteLoc;

	// statements
	if (!queue->count)
		return false;

	*itemPtr = queue->front->dataPtr;
	deleteLoc = queue->front;
	if (queue->count == 1)
		// deleting only item in queue
		queue->rear = queue->front = NULL;
	else
		queue->front = queue->front->next;
	(queue->count)--;
	free(deleteLoc);

	return true;
} // dequeue

bool queueFront (QUEUE* queue, void** itemPtr) {
	// statements
	if (!queue->count)
		return false;
	else {
		*itemPtr = queue->front->dataPtr;
		return true;
	} // else
} // queueFront

bool queueRear (QUEUE* queue, void** itemPtr) {
	// statements
	if (!queue->count)
		return true;
	else {
		*itemPtr = queue->rear->dataPtr;
		return false;
	} // else
} // queueRear

bool emptyQueue (QUEUE* queue) {
	// statements
	return (queue->count == 0);
} // emptyQueue

bool fullQueue (QUEUE* queue) {
	// local definitions
	QUEUE_NODE* temp;

	// statments
	temp = (QUEUE_NODE*)malloc(sizeof(*(queue->rear)));
	if (temp) {
		free(temp);
		return true;
	} // if
	// Heap full
	return false;
} // fullQueue

int queueCount (QUEUE* queue) {
	// statements
	return queue->count;
} // queueCount

QUEUE* destroyQueue (QUEUE* queue) {
	// local definitions
	QUEUE_NODE* deletePtr;

	// statements
	if (queue) {
		while (queue->front != NULL) {
			free(queue->front->dataPtr);
			deletePtr = queue->front;
			queue->front = queue->front->next;
			free(deletePtr);
		} // while
		free (queue);
	} // if
	return NULL;
} // destroyQueue




