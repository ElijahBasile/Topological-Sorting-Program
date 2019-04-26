/*
 * graph.h
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>

#include "queue.h"
#include "stack.h"

// Structures

typedef struct {
	int count;
	struct vertex* first;
	int (*compare) (void* argu1, void* argu2);
} GRAPH;

typedef struct vertex {
	struct vertex* pNextVertex;
	void* dataPtr;
	int inDegree;
	int outDegree;
	short processed;
	struct arc* pArc;
} VERTEX;

typedef struct arc {
	struct vertex* destination;
	struct arc* pNextArc;
} ARC;

// prototype declarations

GRAPH* graphCreate (int (*compare) (void* argu1, void* arg2));
GRAPH* graphDestroy (GRAPH* graph);

void graphInsVrtx	(GRAPH* graph, void* dataInPtr);
int graphDltVrtx	(GRAPH* graph, void* dltKey);
int graphInsArc		(GRAPH* graph, void* pFromKey, void* pToKey);
int graphDltArc		(GRAPH* graph, void* pFromKey, void* pToKey);

int graphRetrVrtx	(GRAPH* graph, void* pKey, void** pDataOut);
int graphFrstArc	(GRAPH* graph, void* pKey, void** pDataOut);

void graphDpthFrst	(GRAPH* graph, void (*process) (void* dataPtr));
void graphBrdthFrst	(GRAPH* graph, void (*process) (void* dataPtr));

bool graphEmpty	(GRAPH* graph);
bool graphFull	(GRAPH* graph);
int graphCount	(GRAPH* graph);

#endif /* GRAPH_H_ */
















