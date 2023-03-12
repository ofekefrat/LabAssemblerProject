#include "linked_list.h"

Node* newNode(Item item) {
    Node* temp = (Node*) malloc(sizeof(Node));
    Node new = { item, NULL };
    *temp = new;
    return temp;
}

void addToList(List* pList, Node* pNode) {
    if (pList->head == NULL)
        pList->head = pNode;

    else if (pList->tail != NULL)
        pList->tail->next = pNode;

    pList->tail = pNode;
}