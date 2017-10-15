#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* TO COMPILE:
 Linux: gcc -shared -Wl,-soname,linkedList -o linkedList.so -fPIC linkedList.c
 Mac: gcc -shared -Wl,-install_name,linkedList.so -o linkedList.so -fPIC linkedList.c
*/

/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/


void _initList (struct linkedList *lst) {
	// Create Sentinels
	struct DLink *fLink = (struct DLink *)malloc(sizeof(struct DLink));	
	struct DLink *lLink = (struct DLink *)malloc(sizeof(struct DLink));
	
	// Set linkedList
	lst->firstLink = fLink;
	lst->lastLink = lLink;
	lst->size = 0;	

	// Set Sentinels
	fLink->next = lLink; // prev NULL
	lLink->prev = fLink; // next NULL
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = (struct linkedList *)malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_findLink
	param: lst the linkedList
	param: l the link to find
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/
struct DLink *_findLink(struct linkedList *lst, TYPE v)
{
	// Start with the link after our starting sentinel 
	struct DLink *link = lst->firstLink->next;
	// while(link != l && link != lst->lastLink) { // this prevents you from adding a link before the lst->lastLink
	while(link->value != v) {
		link = link->next;
	}

	if (link->value == v) {
		return link;
	}
	else {
		return NULL;
	}
}

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	struct DLink *prevLink = l->prev;

	// Create New Link
	struct DLink *link = malloc(sizeof(struct DLink));
	link->value = v;
	link->prev = prevLink;
	link->next = l;

	// Handle Left Update
	prevLink->next = link;

	// Handle Right Update
	l->prev = link;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the link to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/
void _removeLink(struct linkedList *lst, struct DLink *l)
{
	struct DLink *next = l->next;
	struct DLink *prev = l->prev;

	// Drop Link
	prev->next = next;
	next->prev = prev;

	// Free Memory - You're FREEE!!!
	free(l);

	// Update Metadata
	lst->size--;
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/
int isEmptyList(struct linkedList *lst) {
	return(lst->size == 0);
}

/* De-allocate all links of the list

	param: 	lst		pointer to the linked list
	pre:	none
	post:	All links (including the two sentinels) are de-allocated
*/
void freeLinkedList(struct linkedList *lst)
{
	while(!isEmptyList(lst)) {
		/* remove the link right after the first sentinel */
		_removeLink(lst, lst->firstLink->next);
	}
	/* remove the first and last sentinels */
	free(lst->firstLink);
	free(lst->lastLink);
}

/* 	Deallocate all the links and the linked list itself. 

	param: 	v		pointer to the dynamic array
	pre:	v is not null
	post:	the memory used by v->data is freed
*/
void deleteLinkedList(struct linkedList *lst)
{
	assert (lst != 0);
	freeLinkedList(lst);
	free(lst);
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	/* FIXME: you must write this */

}

/* ************************************************************************
	Deque Interface Functions
************************************************************************ */

/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/
void addFrontList(struct linkedList *lst, TYPE e)
{
	struct DLink *fLink = lst->firstLink;
	struct DLink *nextLink = fLink->next;

	// New link
	struct DLink *link = (struct DLink *)malloc(sizeof(struct DLink));	
	link->value = e;
	link->prev = fLink;
	link->next = nextLink;

	// Update pointers
	fLink->next = link;
	nextLink->prev = link;
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/
void addBackList(struct linkedList *lst, TYPE e)
{
	struct DLink *lLink = lst->lastLink;
	struct DLink *prevLink = lLink->prev;

	// New link
	struct DLink *link = (struct DLink *)malloc(sizeof(struct DLink));
	link->value = e;
	link->prev = prevLink;
	link->next = lLink;

	//Update pointers
	lLink->prev = link;
	prevLink->next = link;
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/
TYPE frontList (struct linkedList *lst) {
	return(lst->firstLink->next->value);
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/
TYPE backList(struct linkedList *lst)
{
	return(lst->lastLink->prev->value);
}



/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/
void removeFrontList(struct linkedList *lst) {
	
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/
void removeBackList(struct linkedList *lst)
{	
	/* FIXME: you must write this */
	
}
