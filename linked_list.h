#ifndef linked_list_h
#define linked_list_h

#include "pre/pre.h"
#include "assembly/assembly.h"

typedef union Item {
    Macro macro;
    Label label;
    char line[MAX_LINE_LENGTH];
}Item;

typedef struct Node {
    Item item;
    struct Node* next;
}Node;

typedef struct List {
    Node* head;
    Node* tail;
}List;

Node* newNode(Item item);
void addToList(List list, Node* node);

#endif //linked_list_h
