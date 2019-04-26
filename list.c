/*
 * list.c
 *
 *  Created on: Apr 15, 2019
 *      Author: Elijah Basile
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

LIST* createList (int (*compare) (void* argu1, void* argu2)) {
	// local definitions
	LIST* list;

	// statements
	list = (LIST*)malloc(sizeof(LIST));
	if (list) {
		list->head = NULL;
		list->pos = NULL;
		list->rear = NULL;
		list->count = 0;
		list->compare = compare;
	} // if

	return list;
} // createList

int addNode (LIST* pList, void* dataInPtr) {
	// local definitions
	bool found;
	bool success;

	NODE* pPre;
	NODE* pLoc;

	// statements
	found = _search (pList, &pPre, &pLoc, dataInPtr);
	if (found)
		// duplicate keys not allowed
		return (+1);

	success = _insert (pList, pPre, dataInPtr);
	if (!success)
		// Overflow
		return (-1);
	return (0);
} // addNode

bool _insert (LIST* pList, NODE* pPre, void* dataInPtr) {
	// local definitions
	NODE* pNew;

	// statements
	if (!(pNew = (NODE*)malloc(sizeof(NODE))))
		return false;

	pNew->dataPtr = dataInPtr;
	pNew->link = NULL;

	if (pPre == NULL) {
		// adding before first node or to empty list
		pNew->link = pList->head;
		pList->head = pNew;
		if (pList->count == 0)
			// adding to empty list. set rear
			pList->rear = pNew;
	} // if pPre
	else {
		// adding in middle or at end
		pNew->link = pPre->link;
		pPre->link = pNew;

		// now check for add at end of list
		if (pNew->link == NULL)
			pList->rear = pNew;
	} // if else

	(pList->count)++;
	return true;
} // _insert

bool removeNode (LIST* pList, void* keyPtr, void** dataOutPtr) {
	// local definitions
	bool found;

	NODE* pPre;
	NODE* pLoc;

	// statements
	found = _search (pList, &pPre, &pLoc, keyPtr);
	if (found)
		_delete (pList, pPre, pLoc, dataOutPtr);

	return found;
} // removeNode

void _delete (LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr) {
	// statements
	*dataOutPtr = pLoc->dataPtr;
	if (pPre == NULL)
		// deleting first node
		pList->head = pLoc->link;
	else
		// deleting any other node
		pPre->link = pLoc->link;

	// test for deleting last node
	if (pLoc->link == NULL)
		pList->rear = pPre;

	(pList->count)--;
	free(pLoc);
} // _delete

bool searchList (LIST* pList, void* pArgu, void** pDataOut) {
	// local definitions
	bool found;

	NODE* pPre;
	NODE* pLoc;

	// statements
	found = _search (pList, &pPre, &pLoc, pArgu);
	if (found)
		*pDataOut = pLoc->dataPtr;
	else
		*pDataOut = NULL;
	return found;
} // searchList

bool _search (LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu) {
	// Macro Definition
	#define COMPARE \
		( ((* pList->compare) (pArgu, (*pLoc)->dataPtr)) )

	#define COMPARE_LAST \
		((* pList->compare) (pArgu, pList->rear->dataPtr))

	// local definitions
	int result;

	// statements
	*pPre = NULL;
	*pLoc = pList->head;
	if (pList->count == 0)
		return false;

	// test for argument > last node in list
	if ( COMPARE_LAST > 0 ) {
		*pPre = pList->rear;
		*pLoc = NULL;
		return false;
	} // if

	while ( (result = COMPARE) > 0 ) {
		// Have not found search argument location
		*pPre = *pLoc;
		*pLoc = (*pLoc)->link;
	} // while

	 if (result == 0)
		 // argument found--success
		 return true;
	 else
		 return false;
} // _search

bool retrieveNode (LIST* pList, void* pArgu, void** dataOutPtr) {
	// local definitions
	bool found;

	NODE* pPre;
	NODE* pLoc;

	// statements
	found = _search (pList, &pPre, &pLoc, pArgu);
	if (found) {
		*dataOutPtr = pLoc->dataPtr;
		return true;
	} // if

	*dataOutPtr = NULL;
	return false;
} // retrieveNode

bool emptyList (LIST* pList) {
	// statements
	return (pList->count == 0);
} // emptyList

bool fullList (LIST* pList) {
	// local definitions
	NODE* temp;

	// statements
	if ((temp = (NODE*)malloc(sizeof(*(pList->head))))) {
		free(temp);
		return false;
	} // if

	// dynamic memory full
	return true;
} // fullList

int listCount (LIST* pList) {
	// statements
	return pList->count;
} // listCount

bool traverse (LIST* pList, int fromWhere, void** dataPtrOut) {
	// statements
	if (pList->count == 0)
		return false;

	if (fromWhere == 0) {
		// start from first node
		pList->pos = pList->head;
		*dataPtrOut = pList->pos->dataPtr;
		return true;
	} // if fromWhere
	else {
		// start from current position
		if (pList->pos->link == NULL)
			return false;
		else {
			pList->pos = pList->pos->link;
			*dataPtrOut = pList->pos->dataPtr;
			return true;
		} // if else
	} // if fromWhere else
} // traverse

LIST* destroyList (LIST* pList) {
	// local definitions
	NODE* deletePtr;

	// statements
	if (pList) {
		while (pList ->count > 0) {
			// first delete data
			free (pList->head->dataPtr);

			// now delete node
			deletePtr = pList->head;
			pList->head = pList->head->link;
			pList->count--;
			free(deletePtr);
		} // while
		free (pList);
	} // if
	return NULL;
} // destroyList








