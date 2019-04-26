/*
 * topsort.h
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#ifndef TOPSORT_H_
#define TOPSORT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"
#include "stack.h"
#include "queue.h"
#include "list.h"

void topSort (GRAPH* graph, VERTEX* vertexList[]);

#endif /* TOPSORT_H_ */
