/*
 * interface.h
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "graph.h"

void menu();
void convertData (GRAPH* graph);
void buildGraphFromFile (GRAPH* graph, FILE* fptr);
int compare (void* argu1, void* argu2);

#endif /* INTERFACE_H_ */
