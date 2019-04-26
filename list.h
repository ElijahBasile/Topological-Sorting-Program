/*
 * list.h
 *
 *  Created on: Apr 15, 2019
 *      Author: Elijah Basile
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// structures

typedef struct list_node {
	void* dataPtr;
	struct list_node* link;
} NODE;

typedef struct {
	int count;
	NODE* pos;
	NODE* head;
	NODE* rear;
	int (*compare) (void* argu1, void* argu2);
} LIST;

// prototype definitions

LIST*	createList		(int (*compare) (void* argu1, void* argu2));
LIST*	destroyList		(LIST* list);
int		addNode			(LIST* pList, void* dataInPtr);
bool	removeNode		(LIST* pList, void* ketPtr, void** dataOutPtr);
bool	searchList		(LIST* pList, void* pArgu, void** pDataOut);
bool	retrieveNode	(LIST* pList, void* pArgu, void** dataOutPtr);
bool	traverse		(LIST* pList, int fromWhere, void** dataOutPtr);

int		listCount	(LIST* pList);
bool	emptyList	(LIST* pList);
bool	fullList	(LIST* pList);

bool	_insert		(LIST* pList, NODE* pPre, void* dataInPtr);
void	_delete		(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr);
bool	_search		(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu);


#endif /* LIST_H_ */
