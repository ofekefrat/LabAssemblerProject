#ifndef linked_list_h
#define linked_list_h

#include "../../root.h"

/* newNode: an initializer for nodes in general. returns pointer for a new node */
Node* newNode(Item item);

/* addToList: add a new node to any linked list.*/
void addToList(List* pList, Node* pNode);

#endif
