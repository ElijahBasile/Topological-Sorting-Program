/*
 * queue.h
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#ifndef QUEUE_H_
#define QUEUE_H_

// structures
typedef struct node {
	void* dataPtr;
	struct node* next;
} QUEUE_NODE;

typedef struct {
	QUEUE_NODE* front;
	QUEUE_NODE* rear;
	int count;
} QUEUE;

// prototype declarations

QUEUE*	createQueue		(void);
QUEUE*	destroyQueue	(QUEUE* queue);

bool	dequeue		(QUEUE* queue, void** itemPtr);
bool	enqueue		(QUEUE* queue, void*  itemPtr);
bool	queueFront	(QUEUE* queue, void** itemPtr);
bool	queueRear	(QUEUE* queue, void** itemPtr);
int		queueCount	(QUEUE* queue);

bool	emptyQueue	(QUEUE* queue);
bool	fullQueue	(QUEUE* queue);

#endif /* QUEUE_H_ */
