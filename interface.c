/*
 * interface.c
 *
 *  Created on: Apr 14, 2019
 *      Author: Elijah Basile
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "interface.h"
#include "graph.h"
#include "stack.h"
#include "queue.h"
#include "topsort.h"
#include "list.h"


void menu () {
	// local definitions
	GRAPH* graph = graphCreate(*compare);

	// statements
	convertData (graph);

	VERTEX* vertexList[graph->count];

	topSort (graph, vertexList);

	printf("== Topological Sort ==\n");
	for (int i = 0; i < graph->count; i++) {
		printf ("%c\n",*(char *)(vertexList[i])->dataPtr);
	}

	graph = graphDestroy(graph);
}

void convertData(GRAPH* graph) {
	FILE* fptr;
	char filename[256];
	bool isValid = false;
	char choice;

	do {
		fflush(stdin);
		printf("Enter the TXT file you wish to extract the edges from.\n");
		scanf("%s",filename);
		if (!(fptr = fopen(filename,"r"))) {
			printf("******* File Not Found *******\n");
			printf("e:		Enter a new file name \n");
			printf("q:		Quit this Menu.		  \n");
			while (!isValid) {
				isValid = true;
				fflush(stdin);
				choice = getchar();
				switch (choice) {
					case 'e':
						break;
					case 'q':
						return;
					default:
						printf("Enter valid input.\n");
						isValid = false;
				}
			}
		} else
			break;
	} while (true);



	buildGraphFromFile(graph,fptr);

	fclose(fptr);

}

void buildGraphFromFile (GRAPH* graph, FILE* fptr) {
	char* line = (char*)malloc(sizeof(char)*100);
	void* buffer;

	while(!feof(fptr)) {
		char* fromValue = (char*)malloc(sizeof(char));
		char* toValue = (char*)malloc(sizeof(char));
		fgets(line,256,fptr);
		*fromValue = *line;
		*toValue = *(line+2);
		if (graphRetrVrtx(graph,fromValue,&buffer) == -2) {
			graphInsVrtx (graph, fromValue);
		}
		if (graphRetrVrtx(graph,toValue,&buffer) == -2) {
			graphInsVrtx (graph, toValue);
		}
		graphInsArc (graph, fromValue, toValue);
	} // while feof
	free(line);
}

int compare (void* argu1, void* argu2) {
	if (!argu2)
		return 1;
	if (*(char *)(argu1) < *(char *)(argu2))
		return -1;
	if (*(char *)(argu1) > *(char *)(argu2))
		return 1;
	if (*(char *)(argu1) == *(char *)(argu2))
		return 0;
	return 0;
}
