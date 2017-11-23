#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

struct hashLink
{
	KeyType key;					 /*the key is what you use to look up a hashLink*/
	ValueType value;			 /*the value stored with the hashLink, a pointer to int in the case of concordance*/
	struct hashLink *next; /*notice how these are like linked list nodes*/
};
typedef struct hashLink hashLink;

struct hashMap
{
	hashLink **table; /*array of pointers to hashLinks*/
	int tableSize;		/*number of buckets in the table*/
	int count;				/*number of hashLinks in the table*/
};
typedef struct hashMap hashMap;

int stringHash(hashMap* ht, char *str)
{
	int hash;
	if (HASHING_FUNCTION == 1)
	{
		hash = stringHash1(str) ;
	}
	else if (HASHING_FUNCTION == 2)
	{
		hash = stringHash2(str);
	}
	return hash % ht->tableSize;
}

/*the first hashing function you can use*/
int stringHash1(char *str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char *str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i + 1) * str[i]; // the difference between 1&2
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap(struct hashMap *ht, int tableSize)
{
	int index;
	if (ht == NULL)
		return;
	ht->table = (hashLink **)malloc(sizeof(hashLink *) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for (index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize)
{
	assert(tableSize > 0);
	hashMap *ht;
	ht = (hashMap *)malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
void _freeMap(struct hashMap *ht)
{
	int i;
	struct hashLink *temp;
	struct hashLink *temp2;
	for (i = 0; i < ht->tableSize; i++)
	{
		temp = ht->table[i];
		while (temp != 0)
		{
			temp2 = temp->next;
			free(temp->key);
			free(temp->value); /* also free the memory pointed by value*/
			free(temp);
			temp = temp2;
		}
	}
	free(ht->table);
	ht->count = 0;
	ht->table = 0;
	ht->tableSize = 0;
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht)
{
	assert(ht != 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize
Remember what you had to do for the dynamic array!
This isn't elegant. Values have to be moved.
*/
void _setTableSize(struct hashMap *ht, int newTableSize)
{
	/* ✅ TODO */
	// Create a newer bigger better hash tree
	hashMap* newMap = createMap(newTableSize);
	hashLink* link;

	// Push current values into the new hash
	// Iterate the buckets and the links
	for(int i = 0; i < ht->tableSize; i++)
	{
		link = ht->table[i];
		while (link != NULL)
		{
			insertMap(newMap, link->key, link->value);
			link = link->next;
		}
	}

	/* Dereferencing; idk dafaq this whichcraft is but it semi makes sense;
	*		assign the value to the pointer?
	* 	https://stackoverflow.com/questions/14224831/meaning-of-referencing-and-dereferencing
	*/
	*ht = *newMap;
	// Release the kraken
	free(newMap);

}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".
 
 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap(struct hashMap *ht, KeyType k, ValueType v)
{
	/* ✅ TODO */

	/** I'm resizing first rather than later because I was thinking that it requires one less move,
	 * 	(Although I'm sure that move is very cheap anyways.)
	 * 	but it could then leave the table overloaded if it's the last one added that tips the scales
	 * 	wait... unless I increment numbers to begin with! Then it should be accurate.
	*/
	ht->count++;
	if ((double)tableLoad(ht) >= LOAD_FACTOR_THRESHOLD)
	{
		_setTableSize(ht, size(ht) * 2);
	}

	/** Remove the key if it exists, I could have just removed the old value and 
	 *	updated it (like the comments say) buuut ¯\_(ツ)_/¯
	 *	I figure it cleans the code up go going this way, although it has more operations they'll be fast.
	*/
	if (containsKey(ht, k))
	{
		removeKey(ht, k);
	}

	int index = stringHash(ht, k);
	hashLink* link = (hashLink*) malloc(sizeof(struct hashLink));
	hashLink* firstLink = ht->table[index];

	// Init Link
	link->key = k;
	link->value = v;
	link->next = firstLink; // Make the first link a second place link :magic:

	// Push our link to the front
	ht->table[index] = link;
}

/**
 * Iterates the links to find a link by the given key in the corresponding bucket
 * Helps dry up the code from redundant iterations
 */
hashLink* getLink(hashMap *ht, KeyType k)
{
	int index = stringHash(ht, k);
	hashLink* link = ht->table[index];

	// Iterate our links in the given bucket
	while(link != NULL) {
		if(link->key == k)
		{
			return link; // Most definitely OVERLY YESSS!!!
		}
		link = link->next;
	}

	// Not found -RIP-
	return NULL;
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType atMap(struct hashMap *ht, KeyType k)
{
	/* ✅ TODO */
	hashLink* link = getLink(ht, k);
	return link == NULL ? NULL : link->value;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey(struct hashMap *ht, KeyType k)
{
	/* ✅ TODO */
	return getLink(ht, k) == NULL ? 0 : 9001; // Most definitely OVERLY YESSS!!!
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey(struct hashMap *ht, KeyType k)
{
	/* ✅ TODO */
	// Got dammit jannet, this ain't no double linked list or I'd be done already with my getLink
	int index = stringHash(ht, k);
	hashLink* link = ht->table[index];
	hashLink* previousLink = link;


	// Short Circuit; not even close to existing
	if (link == NULL)
	{
		return;
	}

	// Find our link while keeping track of the previous link
	while(link != NULL)
	{
		// Found it Coach
		if (link->key == k)
		{
			break;
		}
		previousLink = link;
		link = link->next;
	}

	// Link not found 404; rage quit
	if (link == NULL)
	{
		return;
	}

	/// Slice'n Dice
	// We're in first place
	if (previousLink == link)
	{
		// You are the weakest link, goodbye
		ht->table[index] = link->next;
		// Only link that exists; rasta en pasta; so lonely
		// At first I was going to check if next was null, but figured that doesn't matter
	}
	else
	{
		previousLink->next = link->next;
	}

	// Hide the evidence
	free(link->key);
	free(link->value);
	free(link); // Take that Zelda I WIN
	ht->count--;
}

/*
 returns the number of hashLinks in the table
 */
int size(struct hashMap *ht)
{
	/* ✅ TODO */
	return ht->count;
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
	/* ✅ TODO */
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{
	/* ✅ TODO */
	int emptyBuckets = 0;
	// Iterate buckets and determine if they're empty
	for(int i = 0; i < ht->tableSize; i++)
	{
		if (ht->table[i] == NULL)
		{
			emptyBuckets++;
		}
	}
	return emptyBuckets;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
	/* ✅ TODO */
	return (float)ht->count / (float)ht->tableSize;
}

/* print the hashMap */
void printMap(struct hashMap *ht)
{
	int i;
	struct hashLink *temp;
	for (i = 0; i < capacity(ht); i++)
	{
		temp = ht->table[i];
		if (temp != 0)
		{
			printf("\nBucket Index %d -> ", i);
		}
		while (temp != 0)
		{
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp = temp->next;
		}
	}
}