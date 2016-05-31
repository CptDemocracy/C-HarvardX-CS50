#ifndef _SLOT_H_
#define _SLOT_H_

#include <stdlib.h>

typedef struct Slot {
	size_t _elemSize;
	size_t _hashCode;
	void*  _item;
} Slot;

/**
 * Allocates memory for a Slot object on the heap
 * and initializes its member variables.
 */
Slot* SlotNew	(size_t elemSize, 
                    void*  item, 
                    size_t hashCode);
                     
/**
 * Deallocates memory used by a Slot object.
 */
int SlotDispose (Slot* slot);

#endif