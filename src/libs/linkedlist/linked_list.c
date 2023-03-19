#include "linked_list.h"

/* newNode: an initializer for nodes in general. returns pointer for a new node */
Node* newNode(Item item) {
    Node* temp = (Node*) malloc(sizeof(Node));
    Node new;
    new.item = item;
    new.next = NULL;
    *temp = new;
    return temp;
}

/* addToList: add a new node to any linked list.*/
void addToList(List* pList, Node* pNode) {
    if (pList->head == NULL)
        pList->head = pNode;

    else if (pList->tail != NULL)
        pList->tail->next = pNode;

    pList->tail = pNode;
}