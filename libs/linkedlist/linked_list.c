#include "linked_list.h"

Node* newNode(Item item) {
    Node* temp = (Node*) malloc(sizeof(Node));
    Node new = { item, NULL };
    *temp = new;
    return temp;
}

void addToList(List list, Node* node) {
    if (list.head == NULL)
        list.head = node;

    if (list.tail != NULL)
        list.tail->next = node;

    list.tail = node;
}