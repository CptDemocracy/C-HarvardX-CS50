#include "Slot.h"
#include <string.h>

Slot* SlotNew  (size_t  elemSize, 
                  void* item, 
                 size_t hashCode) 
{
	if (elemSize < 1) {
		return NULL;
	}
	if (item == NULL) {
		return NULL;
	}
	Slot* slot  	= (Slot*)malloc(sizeof(Slot));
	slot->_elemSize = elemSize;
	slot->_hashCode = hashCode;
	slot->_item 	= calloc(elemSize, sizeof(char));
	memcpy(slot->_item, item, elemSize);
	return slot;
}

int SlotDispose(Slot* slot) {
    if (slot == NULL) {
		return 1;
	}
	free(slot->_item);	
	free(slot);
	return 0;
}