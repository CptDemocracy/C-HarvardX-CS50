#ifndef _HASHSET_H_
#define _HASHSET_H_

#define MAX_CAPACITY	0x7fffffffU

#include "List.h"
#include "Slot.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct HashSet {
	List** _buckets;
	size_t _elemSize;
	size_t _capacity;
	size_t _count;
    int (*_hash)    (void*, size_t);
} HashSet;

HashSet* HashSetNew         (size_t elemSize, 
								int (*_hash)(void*, size_t));
/**
 * HashSet .ctor
 * 
 * Allocates memory on the heap for a HashSet object and then
 * initializes all of HashSet's member variables.
 * 
 * Originally it would require the third argument to be a function
 * pointer void (*dispose)(void*) which would enable the HashSet's
 * .dtor to free any memory it holds independently without us having
 * to go through its internals manually. Unfortunately, I had to
 * drop that functionality since the CS50's compilers have the flag
 * -Wall set which ultimately treats all warnings as errors. And
 * hence it was impossible to, say, pass the SlotDispose(Slot*)
 * function as an argument to HashSetDispose without an error.
 * 
 */								


int  HashSetDispose         (HashSet* pSet);
/**
 * HashSet .dtor
 * 
 * Deallocates memory used by a HashSet object.
 * 
 */ 


int  HashSetHash            (void* item, size_t elemSize);
/**
 * A hash function used by the HashSet by default. Clients can override
 * the hash function by passing a function pointer to their hash function
 * as an argument to the HashSet's constructor.
 * 
 * This given function is my work so I, perhaps, may take credit for it,
 * even though, I am sure there's a million hash functions that work in
 * a similar, if not the same manner.
 * 
 * Basically each item is allocated a buffer with a buffer size that is
 * a multiple of sizeof(int). All bytes inside the buffer are zeroed out
 * so that we don't hash garbage. We then proceed to XOR each sizeof(int)-
 * sized chunk of the buffer with each other. After we are done, we free
 * the buffer and return the hash code.
 * 
 */ 
 
 
bool HashSetAddItem         (HashSet* set, void* item);
/**
 * Adds an item to a HashSet object. Memory is copied so that both client
 * and the hash table itself have two independent copies of the item.
 * It is important to note, however, that item argument requires a pointer
 * to the client's item, and not the item itself. Also, if a client chooses
 * to contain pointers inside the hash table, only copies of the pointers
 * will be made and not the actual object pointed to by the pointer. Thus
 * we make use of a shallow-copy in our hash table.
 * 
 */ 


int  HashSetEnsureCapacity  (HashSet* set, size_t minCapacity);
/**
 * Makes sure a hash table has enough memory to contain a minCapacity objects. 
 * Regardless of whether the minCapacity argument is a prime number, the 
 * function always allocates enough memory to hold a prime number of objects,
 * which is either greater or equal to the original minCapacity argument.
 * 
 * The maximum minCapacity allowed is 0x7fffffff. I've imposed this limit so
 * that we don't accidentally overflow and then do something funky with memory
 * if someone passes a huge minCapacity argument.
 * 
 */ 


bool HashSetContainsItem   	(HashSet* set, void* item);
/**
 * Returns true if a hash table contains an item at address pItem
 * and false if it doesn't and/or set or pItem are NULL.
 * 
 */ 


int  HashSetGetCount		(HashSet* set);
/**
 * Returns the number of entries inside a hash table.
 * 
 */ 


#ifdef HASH_SET_BUCKET_COUNT
	int HashSetGetBucketCount(HashSet* set);
	/**
	 * If HASH_SET_BUCKET_COUNT is defined, this function calculates the number
	 * of buckets inside a hash table.
	 * 
	 */ 
#endif

#endif