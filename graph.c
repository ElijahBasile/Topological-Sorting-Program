/*
 * graph.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "stack.h"
#include "queue.h"

GRAPH* graphCreate (int (*compare) (void* argu1, void* arg2)) {
	// statements
	GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));
	if (graph) {
		graph->count = 0;
		graph->first = NULL;
		graph->compare = compare;
	} else
		printf("\aMemory Overflow Exit 102\a\n"),
			exit (102);
	return graph;
}

GRAPH* graphDestroy (GRAPH* graph) {
	// local declarations
	VERTEX* currVert;
	VERTEX* tempVert;
	ARC* currArc;
	ARC* tempArc;

	// statements
	if (!graph)
		return NULL;

	currVert = graph->first;
	for (int i = 0; i < graph->count ; i++) {
		currArc = currVert->pArc;
		while (currArc) {
			tempArc = currArc->pNextArc;
			free (currArc);
			currArc = tempArc;
		}
		free(currVert->dataPtr);
		tempVert = currVert->pNextVertex;
		free (currVert);
		currVert = tempVert;
 	}

	free (graph);

	// graph empty
	return NULL;
}

void graphInsVrtx (GRAPH* graph, void* dataInPtr) {
	// local definitions
	VERTEX* newPtr;
	VERTEX* locPtr;
	VERTEX* predPtr;

	// statements
	newPtr = (VERTEX*)malloc(sizeof(VERTEX));
	if (newPtr) {
		newPtr->pNextVertex = NULL;
		newPtr->dataPtr = dataInPtr;
		newPtr->inDegree = 0;
		newPtr->outDegree = 0;
		newPtr->processed = 0;
		newPtr->pArc = NULL;
		(graph->count)++;
	} // if malloc
	else
		printf("Overflow error 100\a\n"),exit(100);

	// now find insertion point
	locPtr = graph->first;
	if (!locPtr)
		// empty graph. insert at beginning
		graph->first = newPtr;
	else {
		predPtr = NULL;
		while (locPtr && (graph->compare(dataInPtr, locPtr->dataPtr) > 0)) {
			predPtr = locPtr;
			locPtr = locPtr->pNextVertex;
		} // while
		if (!predPtr)
			// insert before first vertex
			graph->first = newPtr;
		else
			predPtr->pNextVertex = newPtr;
		newPtr->pNextVertex = locPtr;
	} // else
	return;
} // graphInsVrtx

int graphDltVrtx (GRAPH* graph, void* dltKey) {
	// local definitions
	VERTEX* predPtr;
	VERTEX* walkPtr;

	// statements
	if (!graph->first)
		return -2;

	// locate vertex to be deleted
	predPtr = NULL;
	walkPtr = graph->first;
	while (walkPtr && (graph->compare(dltKey,walkPtr->dataPtr) > 0)) {
		predPtr = walkPtr;
		walkPtr = walkPtr->pNextVertex;
	} // walkPtr &&
	if (!walkPtr || graph->compare(dltKey, walkPtr->dataPtr) != 0)
		return -2;

	// found vertex. test degree
	if ((walkPtr->inDegree > 0) || (walkPtr->outDegree) > 0)
		return -1;

	// OK to delete
	if (!predPtr)
		graph->first = walkPtr->pNextVertex;
	else
		predPtr->pNextVertex = walkPtr->pNextVertex;
	--graph->count;
	free (walkPtr);
	return 1;
} // graphDltVrtx

int graphInsArc (GRAPH* graph, void* pFromKey, void* pToKey) {
	// local definitions
	ARC* newPtr;
	ARC* arcPredPtr;
	ARC* arcWalkPtr;
	VERTEX* vertFromPtr;
	VERTEX* vertToPtr;

	// statements

	newPtr = (ARC*)malloc(sizeof(ARC));
	if (!newPtr)
		return -1;

	// locate source vertex
	vertFromPtr = graph->first;
	while (vertFromPtr && (graph->compare(pFromKey,vertFromPtr->dataPtr) > 0)) {
		vertFromPtr = vertFromPtr->pNextVertex;
	} // while vertFromPtr &&
	if (!vertFromPtr || (graph->compare(pFromKey, vertFromPtr->dataPtr) != 0))
		return -2;

	// now locate to vertex
	vertToPtr = graph->first;
	while (vertToPtr && graph->compare(pToKey, vertToPtr->dataPtr) > 0) {
		vertToPtr = vertToPtr->pNextVertex;
	} // while vertToPtr &&
	if (!vertToPtr || (graph->compare(pToKey, vertToPtr->dataPtr) != 0))
		return -3;

	// from and to vertices located. insert new arc
	++vertFromPtr->outDegree;
	++vertToPtr->inDegree;
	newPtr->destination = vertToPtr;
	if (!vertFromPtr->pArc) {
		// inserting first arc for this vertex
		vertFromPtr->pArc = newPtr;
		newPtr->pNextArc = NULL;
		return -1;
	} // if new arc

	// find insertion point in adjacency (arc) list
	arcPredPtr = NULL;
	arcWalkPtr = vertFromPtr->pArc;
	while (arcWalkPtr && graph->compare(pToKey, arcWalkPtr->destination->dataPtr) >= 0) {
		arcPredPtr = arcWalkPtr;
		arcWalkPtr = arcWalkPtr->pNextArc;
	} // arcWalkPtr &&

	if (!arcPredPtr)
		// insertion before first arc
		vertFromPtr->pArc = newPtr;
	else
		arcPredPtr->pNextArc = newPtr;
	newPtr->pNextArc = arcWalkPtr;
	return 1;
} // graphInsArc

int graphDltArc (GRAPH* graph, void* fromKey, void* toKey) {
	// local definitions
	VERTEX* fromVertexPtr;
	VERTEX* toVertexPtr;
	ARC* preArcPtr;
	ARC* arcWalkPtr;

	// statements

	if (!graph->first)
		return -2;

	// locate source vertex
	fromVertexPtr = graph->first;
	while (fromVertexPtr && (graph->compare(fromKey,fromVertexPtr->dataPtr) > 0))
		fromVertexPtr = fromVertexPtr->pNextVertex;

	if (!fromVertexPtr || graph->compare(fromKey,fromVertexPtr->dataPtr) != 0)
		return -2;

	// locate destination vertex in adjacency list
	if (!fromVertexPtr->pArc)
		return -3;

	preArcPtr = NULL;
	arcWalkPtr = fromVertexPtr->pArc;
	while (arcWalkPtr && (graph->compare(toKey,arcWalkPtr->destination->dataPtr) > 0)) {
		preArcPtr = arcWalkPtr;
		arcWalkPtr = arcWalkPtr->pNextArc;
	} // while arcWalkPtr &&
	if (!arcWalkPtr || (graph->compare(toKey,arcWalkPtr->destination->dataPtr) != 0))
		return -3;
	toVertexPtr = arcWalkPtr->destination;

	// from, toVertex & arcPtr located. delete arc
	--fromVertexPtr->outDegree;
	--toVertexPtr->inDegree;
	if (!preArcPtr)
		// deleting first arc
		fromVertexPtr->pArc = arcWalkPtr->pNextArc;
	else
		preArcPtr->pNextArc = arcWalkPtr->pNextArc;
	free (arcWalkPtr);
	return 1;
} // graphDltArc

int graphRetrVrtx (GRAPH* graph, void* pKey, void** pDataOut) {
	// local definitions
	VERTEX* curr;

	if (!graph)
		return -2;
	curr = graph->first;
	for (int i = 0; i < graph->count; i++) {
		if (graph->compare(pKey,curr->dataPtr) == 0) {
			*pDataOut = curr->dataPtr;
			return 1;
		}
		curr = curr->pNextVertex;
	}
	return -2;
}

void graphDpthFrst	(GRAPH* graph, void (*process) (void* dataPtr)) {
	bool success;
	VERTEX* walkPtr;
	VERTEX* vertexPtr;
	VERTEX* vertToPtr;
	STACK* stack;
	ARC* arcWalkPtr;

	if (!graph->first)
		return;

	// set processed flags to not processed
	walkPtr = graph->first;
	while (walkPtr) {
		walkPtr->processed = 0;
		walkPtr = walkPtr->pNextVertex;
	} // while

	// process each vertex in list
	stack = createStack();
	walkPtr = graph->first;
	while (walkPtr) {
		if (walkPtr->processed < 2) {
			if (walkPtr->processed < 1) {
				// push and set flag to pushed
				success = pushStack (stack, walkPtr);
				if (!success)
					printf("\aSTACK overflow 100\a\n"), exit(100);
				walkPtr->processed = 1;
			} // if process < 1
		} // if processed < 2
		// process descendants of vertex at stack top
		while (!emptyStack (stack)) {
			vertexPtr = popStack (stack);
			process (vertexPtr->dataPtr);
			vertexPtr->processed = 2;

			// push all vertices from adjacency list
			arcWalkPtr = vertexPtr->pArc;
			while (arcWalkPtr) {
				vertToPtr = arcWalkPtr->destination;
				if (vertToPtr->processed == 0) {
					success = pushStack (stack, vertToPtr);
					if (!success)
						printf("\aStack Overflow 101\a\n"),
							exit(101);
					vertToPtr->processed = 1;
				} // if vertToPtr
				arcWalkPtr = arcWalkPtr->pNextArc;
			} // while pWalkArc

		} // while !emptyStack
		walkPtr = walkPtr->pNextVertex;
	} // while walkPtr
	destroyStack (stack);
	return;
} // graphDpthFrst

void graphBrdthFrst (GRAPH* graph, void (*process) (void* dataPtr)) {
	// local definitions
	bool success;
	VERTEX* walkPtr;
	VERTEX* vertexPtr;
	VERTEX* vertToPtr;
	QUEUE* queue;
	ARC* arcWalkPtr;

	if (!graph->first)
		return;

	// set processed flags to not processed
	walkPtr = graph->first;
	while (walkPtr) {
		walkPtr->processed = 0;
		walkPtr = walkPtr->pNextVertex;
	} // while

	// process each vertex in list
	queue = createQueue();
	walkPtr = graph->first;
	while (walkPtr) {
		if (walkPtr->processed < 2) {
			if (walkPtr->processed < 1) {
				// push and set flag to queue
				success = enqueue(queue, walkPtr);
				if (!success)
					printf("\aQueue overflow 100\a\n"), exit(100);
				walkPtr->processed = 1;
			} // if process < 1
		} // if processed < 2
		// process descendants of vertex at queue front
		while (!emptyQueue (queue)) {
			dequeue (queue,&vertexPtr);
			process (vertexPtr->dataPtr);
			vertexPtr->processed = 2;

			// push all vertices from adjacency list
			arcWalkPtr = vertexPtr->pArc;
			while (arcWalkPtr) {
				vertToPtr = arcWalkPtr->destination;
				if (vertToPtr->processed == 0) {
					success = enqueue (queue, vertToPtr);
					if (!success)
						printf("\aQueue Overflow 101\a\n"),
							exit(101);
					vertToPtr->processed = 1;
				} // if vertToPtr
				arcWalkPtr = arcWalkPtr->pNextArc;
			} // while pWalkArc

		} // while !emptyQueue
		walkPtr = walkPtr->pNextVertex;
	} // while walkPtr
	destroyQueue (queue);
	return;
}

bool graphEmpty (GRAPH* graph) {
	// statements
	return (graph->count == 0);
}

int graphCount (GRAPH* graph) {
	// statements
	return graph->count;
}










