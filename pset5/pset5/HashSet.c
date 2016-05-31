#include "HashSet.h"
#include "PrimeHelper.h"
#include <string.h>

/**
 * HashSet .ctor
 * 
 * Allocates memory on the heap for a HashSet and then initializes
 * all of HashSet's member variables.
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
HashSet* HashSetNew(size_t elemSize, 
						int (*_hash)(void*, size_t))
{
	// return NULL if elemSize is 0.
	// elemSize < 1 looks more logical than just elemSize == 0
	// since in the future elemSize could be changed to an int.
	if (elemSize < 1) {
		return NULL;
	}
	HashSet* set	= (HashSet*)malloc(sizeof(HashSet));
	
	// we don't want to proceed if malloc failed.
	if (set == NULL) { 
		return NULL; 
	}
	
	set->_elemSize	= elemSize;
	set->_capacity	= getMinPrime();
	set->_count		= 0;
	
	// allocate space and zero out all bytes.
	// it is of utmost importance to zero out the bytes since
	// our implementation depends on NULL pointers to signal
	// vacant space for a bucket.
	//
	// earlier implementation filled all the space with objects
	// of type List but then I decided it was quite inefficient.
	set->_buckets	= calloc(set->_capacity, sizeof(List*));
	
	// we don't want to proceed if calloc failed.
	if (set->_buckets == NULL) {
		return NULL;
	}
	
	// if _hash function pointer is NULL, default to the default
	// HashSetHash function.
	if (_hash == NULL) {
	    set->_hash = HashSetHash;
	} else {
	    set->_hash = _hash;
	}
	return set;
}

/**
 * HashSet .dtor
 * 
 * Deallocates memory used by a HashSet object.
 * 
 */ 
int HashSetDispose(HashSet* set) {
	if (set == NULL) {
		return 1;
	}
	for (size_t i = 0; i < set->_capacity; ++i) {
		List* currBucket = set->_buckets[i];
		if (currBucket != NULL) {
			
			// free the slots
			for (int i = 0; i < ListGetLength(currBucket); ++i) {
				SlotDispose(*((Slot**)currBucket->_items + i));
			}
			
			// free the bucket
			ListDispose(currBucket);
		}
	}
	free(set->_buckets);
	free(set);
	return 0;
}

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
int HashSetHash(void* pItem, size_t elemSize) {
	if (pItem == NULL) {
		return 0;
	}
	if (elemSize < 1) {
		return 0;
	}
	int bufferSizeBytes = elemSize + sizeof(int) - elemSize % sizeof(int);
	void* buffer = calloc(bufferSizeBytes, 1);
	
	// do not proceed if calloc failed
	if (buffer == NULL) {
		return 0;
	}
	memcpy(buffer, pItem, elemSize);
	
	int* begin = (int*)(buffer);
	int* end   = (int*)((char*)buffer + bufferSizeBytes);
	
	int hashCode = 0;
	for (int* pntr = begin; pntr < end; ++pntr) {
		hashCode ^= (*pntr);
	}

	free(buffer);
	return hashCode;
}

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
bool HashSetAddItem(HashSet* set, void* pItem) {
    if (set == NULL) {
        return false;
    }
    
    if (pItem == NULL) {
        return false;
    }
    
    if (HashSetContainsItem(set, pItem)) {
    	return false;
    }
    
    // if EnsureCapacity fails, we return false
    if (HashSetEnsureCapacity(set, set->_count + 1) != 0) {
		return false;
	}
    
    size_t hashCode    = (size_t)set->_hash(pItem, set->_elemSize);
	size_t bucketIndex = hashCode % set->_capacity;
    List*  bucket      = set->_buckets[bucketIndex];
	if (bucket == NULL) {
        set->_buckets[bucketIndex] = ListNew(sizeof(Slot*), NULL);
        
        // if ListNew (List .ctor) failed, we return false
        if (set->_buckets[bucketIndex] == NULL) {
        	return false;
        }
        
		bucket = set->_buckets[bucketIndex];
    }

    Slot* slot = SlotNew(set->_elemSize, pItem, hashCode);
    
    // if SlotNew failed, we return false
    if (slot == NULL) {
    	return false;
    }
    
    // if ListAddItem failed (non-zero ret val indicates that), we
    // return false
   	if (ListAddItem(bucket, &slot) != 0) {
   		return false;
   	}
    ++set->_count;
    
    return true;
}

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
int HashSetEnsureCapacity(HashSet* set, size_t minCapacity) {
	if (minCapacity > MAX_CAPACITY) {
		return 1;
	}
    if (set == NULL) {
        return 1;
    }
    if (minCapacity < 1) {
        return 1;
    }
    if (minCapacity > set->_capacity) 
    {
		size_t capacity = set->_capacity;
        while (capacity < minCapacity) {
			if (capacity > MAX_CAPACITY) {
				return 1;
			}
			capacity = expandPrime(capacity);
		}
		minCapacity = capacity;
        
        // we must zero out the memory - our convention to pinpoint
        // vacant spaces for buckets depends on NULL pointers!
        List** newBuckets  = calloc(minCapacity, sizeof(List*));
        
        // do not proceed if calloc failed.
        if (newBuckets == NULL) {
        	return 1;
        }
        
        for (size_t i = 0; i < set->_capacity; ++i) {
			List* currBucket = set->_buckets[i];
			if (currBucket != NULL) {
				Slot* currSlot = NULL;
				for (int i = 0; i < ListGetLength(currBucket); ++i) {
					ListGetItem(currBucket, i, &currSlot);
					size_t hashCode = currSlot->_hashCode;
					int bucketIndex = hashCode % minCapacity;
					if (newBuckets[bucketIndex] == NULL) {
						newBuckets[bucketIndex] = ListNew(sizeof(Slot*), NULL);
						
						// if ListNew (List .ctor) failed, we return false
				        if (newBuckets[bucketIndex] == NULL) {
				        	return false;
				        }
				        
					}
					ListAddItem(newBuckets[bucketIndex], &currSlot);
				}
				// dispose of the list but not of the slots contained in it,
				// since we just "juggled" the pointer to the slots to another
				// bucket (List object)
				ListDispose(currBucket);
			}
		}
    	free(set->_buckets);
    	set->_buckets  = newBuckets;
    	set->_capacity = minCapacity;
    }
    return 0;
}

/**
 * Returns true if a hash table contains an item at address pItem
 * and false if it doesn't and/or set or pItem are NULL.
 * 
 */ 
bool HashSetContainsItem(HashSet* set, void* pItem) {
	if (set == NULL) {
		return false;
	}
	if (pItem == NULL) {
		return false;
	}
	
	// must be unsigned - hash function is not required to return a positive
	// hash code but we require a positive value to hash to the right bucket.
	size_t hashCode    = (size_t)set->_hash(pItem, set->_elemSize);
    size_t bucketIndex = hashCode % set->_capacity;
    List* bucket    = set->_buckets[bucketIndex];
    if (bucket == NULL) {
    	
    	// no bucket given the hash code
    	return false;
    } else {
    	
    	// found the bucket, could be a collision
    	// check all slots in the bucket's chain for our item
        Slot* currSlot = NULL;
        for (int i = 0; i < ListGetLength(bucket); ++i) {
            ListGetItem(bucket, i, &currSlot);
            if ((hashCode == currSlot->_hashCode) 
            		&& (memcmp(pItem, currSlot->_item, set->_elemSize) == 0)) 
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Returns the number of entries inside a hash table.
 * 
 */ 
int HashSetGetCount(HashSet* set) {
	if (set == NULL) {
		return 0;
	}
	return set->_count;
}

/**
 * If HASH_SET_BUCKET_COUNT is defined, this function calculates the number
 * of buckets inside a hash table.
 * 
 */ 
#ifdef HASH_SET_BUCKET_COUNT
int HashSetGetBucketCount(HashSet* set) {
	if (set == NULL) {
		return -1;
	}
	int bucketCount = 0;
	for (size_t i = 0; i < set->_capacity; ++i) {
		List* currBucket = set->_buckets[i];
		if (currBucket != NULL) {
			++bucketCount;
		}
	}
	return bucketCount;
}
#endif