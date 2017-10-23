#include "linkedList.h"
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>

/* TO COMPILE:
 Linux: gcc -shared -Wl,-soname,linkedList -o linkedList.so -fPIC add.c
 Mac: gcc -shared -Wl,-install_name,linkedList.so -o linkedList.so -fPIC test.c
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
   /* create the sentinels */
   lst->firstLink = (struct DLink *) malloc(sizeof(struct DLink));
   lst->lastLink = (struct DLink *) malloc (sizeof(struct DLink));
   assert (lst->firstLink != 0);
   assert(lst->lastLink != 0);
   
   lst->firstLink->prev = 0;
   lst->firstLink->next = lst->lastLink;
   
   lst->lastLink->next = 0;
   lst->lastLink->prev = lst->firstLink;
  
   lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/
void _removeLink(struct linkedList *lst, struct DLink *l)
{

	l->next->prev = l->prev;
	l->prev->next = l->next;
	free(l);
   	lst->size--;
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

/*
	_addLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/
/* Adds Before the provided link, l */
void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
   struct DLink * lnk = (struct DLink *) malloc(sizeof(struct DLink));
   assert(lnk != 0);

	lnk->next = l;
	lnk->prev = l->prev;
	lnk->value = v;
	
	l->prev->next = lnk;
	l->prev = lnk;
   
   	lst->size++;
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/

int isEmptyList(struct linkedList *lst) {
   return (lst->firstLink->next == lst->lastLink);
   //or return(lst->size == 0)
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	struct DLink *lnk = lst->firstLink->next;
	
	while(lnk != lst->lastLink)
	{
		printf("%d->", lnk->value);
		lnk = lnk->next;
	}
	
	printf("\n");
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

	_addLinkBefore(lst, lst->firstLink->next, e);
	
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {
  
  _addLinkBefore(lst, lst->lastLink, e);
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
   assert(!isEmptyList(lst));
   return lst->firstLink->next->value;
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
	assert(!isEmptyList(lst));
	return lst->lastLink->prev->value;
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
   assert(! isEmptyList(lst));
  	
   _removeLink(lst, lst->firstLink->next);
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
	assert(!isEmptyList(lst));

	_removeLink(lst, lst->lastLink->prev);	
}

/* ************************************************************************
	Stack Interface Functions
************************************************************************ */

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
	assert(lst != 0);
	addBackList(lst, v);
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
	struct DLink *current;

	assert(lst != 0);
	assert(!isEmptyList(lst));
	current = lst->firstLink->next; /* Initialize current */
	while(current != lst->lastLink)
	{
		if(EQ(current->value,e))
			return 1;
		current=current->next;
	}
	return 0;
}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
	assert(lst != 0);
	assert(!isEmptyList(lst));
	struct DLink *current;
	current = lst->firstLink->next; /* Initialize current */
	while(current != lst->lastLink)
	{
		if(EQ(current->value,e))
		{
			_removeLink(lst,current);
			break; /* Only remove one copy of it */
		}
		current=current->next;
	}
}