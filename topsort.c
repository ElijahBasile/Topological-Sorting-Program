/*
 * topsort.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "interface.h"
#include "topsort.h"
#include "graph.h"
#include "queue.h"
#include "list.h"

void topSort (GRAPH* graph, VERTEX* vertexList[]) {
	QUEUE* queue = createQueue();
	int D[graph->count];
	VERTEX* currVert = graph->first;
	ARC* currArc;

	// initialize the list of in-degrees D[] in graph
	for (int i = 0; i < graph->count; i++) {
		D[i] = currVert->inDegree;
		currVert = currVert->pNextVertex;
	} // for graph->count

	// initialize queue to contain all vertices having zero in-degrees
	currVert = graph->first;
	for (int i = 0; i < graph->count; i++) {
		if (D[i] == 0)
			enqueue (queue, currVert);
		currVert = currVert->pNextVertex;
	}

	// process vertices in queue until the queue becomes empty
	int count = 0;
	while (!emptyQueue(queue)) {
		void* value = (void*)malloc(sizeof(VERTEX));
		dequeue(queue,&value);
		// ad to back of list
		vertexList[count] = value;
		count++;

		currVert = (VERTEX *)value;
		currArc = currVert->pArc;
		for (int i = 0; i < currVert->outDegree; i++) {
			// find the vertex to decrement
			int j;
			VERTEX* finder = graph->first;
			for (j = 0; finder != currArc->destination; j++)
				finder = finder->pNextVertex;
			//decrement vertex
			D[j]--;
			// if the vertex has zero in, add it to queue
			if (D[j] == 0)
				enqueue (queue, currArc->destination);
			currArc = currArc->pNextArc;
		}
	}

	// the list L now contains the vertices of the graph in topological order


}
