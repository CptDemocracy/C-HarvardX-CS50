#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

#define LIST_DEFAULT_CAPACITY	4

typedef struct List {
	int   _itemSize;
	int   _length;
	int	  _capacity;
	void* _items;
	int	(*_dispose)(void*);
} List;

List* ListNew			(size_t itemSize, int (*dispose)(void*));
int ListDispose			(List* list);
int ListGetLength		(List* list);
int ListGetItem			(List* list, int index, void* outResult);
int ListSetItem			(List* list, int index, void* item);
int ListAddItem			(List* list, void* item);
int ListEnsureCapacity	(List* list, int minCapacity);
int ListGetCapacity		(List* list);
int ListRemoveItem		(List* list, void* item);
int ListRemoveItemAt	(List* list, int index);

#endif