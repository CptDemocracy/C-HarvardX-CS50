#include <stdlib.h>
#include <string.h>
#include "List.h"

List* ListNew(size_t itemSize, int (*dispose)(void*)) {
	if (itemSize < 1) {
		return NULL;
	}
	List* list = malloc(sizeof(List));
	if (list == NULL) {
		return NULL;
	}
	list->_items = malloc(LIST_DEFAULT_CAPACITY * itemSize);
	if (list->_items == NULL) {
		return NULL;
	}
	list->_itemSize	= itemSize;
	list->_length	= 0;
	list->_capacity	= LIST_DEFAULT_CAPACITY;
	list->_dispose	= dispose;
	
	return list;
}

int ListGetLength(List* list) {
	if (list == NULL) {
		return 0;
	}
	return list->_length;
}

int ListGetItem(List* list, int index, void* outResult) {
	if (list == NULL) {
		return 1;
	}
	if (index < 0 || index >= list->_length) {
		return 1;
	}
	memcpy(outResult, (void*)((char*)list->_items + index * list->_itemSize), list->_itemSize);
	return 0; 
}

int ListSetItem(List* list, int index, void* item) {
	if (list == NULL) {
		return 1;
	}
	if (index < 0 || index >= list->_length) {
		return 1;
	}
	
	void* destAddr = (void*)((char*)list->_items + index * list->_itemSize);
	memcpy(destAddr, item, list->_itemSize);
	return 0;
}

int ListAddItem(List* list, void* item) {
	if (list == NULL) {
		return 1;
	}
	if (ListEnsureCapacity(list, list->_length + 1)) {
		return 1;
	}
	
	void* destAddr = (void*)((char*)list->_items + list->_length * list->_itemSize);
	memcpy(destAddr, item, list->_itemSize);
	++list->_length;

	return 0;
}

int ListEnsureCapacity(List* list, int minCapacity) {
	if (list == NULL) {
		return 1;
	}
	if (minCapacity < 0) {
		return 1;
	}
	if (list->_capacity < minCapacity) {
		minCapacity = list->_capacity * 2 > minCapacity ? list->_capacity * 2 : minCapacity;
		if (! (list->_items = realloc(list->_items, minCapacity * list->_itemSize))) {
			return 1;
		}
		list->_capacity = minCapacity;
	}
	return 0;
}

int ListGetCapacity(List* list){
	if (list == NULL) {
		return 0;
	}
	return list->_capacity;
}

int ListRemoveItem(List* list, void* item) {
	if (list == NULL) {
		return 1;
	}
	for (int i = 0; i < ListGetLength(list); ++i) {
		if (!memcmp((void*)((char*)list->_items + i * list->_itemSize), 
			&item,
			list->_itemSize)) 
		{
			return ListRemoveItemAt(list, i);
		}
	}
	return 1;
}

int ListRemoveItemAt(List* list, int index) {
	if (list == NULL) {
		return 1;
	}
	if (index < 0 || index >= list->_length) {
		return 1;
	}
	memmove((void*)((char*)list->_items + index * list->_itemSize), 
			(void*)((char*)list->_items + (index + 1) * list->_itemSize), 
			(list->_length - index + 1) * list->_itemSize);
	--list->_length;
	return 0;
}

int ListDispose(List* list) {
	if (list == NULL) {
		return 1;
	}
	if (list->_dispose != NULL) {
		for (int i = 0; i < list->_length; ++i) {
			list->_dispose((void*)((char*)list->_items + i * list->_itemSize));
		}
	}
	free(list->_items);
	free(list);
	return 0;
}