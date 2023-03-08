#ifndef linked_list_h
#define linked_list_h

#include "../../root.h"

union Item {
    Macro macro;
    Label label;
    char line[MAX_LINE_LENGTH];
};

struct Node {
    Item item;
    struct Node* next;
};

struct List {
    Node* head;
    Node* tail;
};

Node* newNode(Item item);
void addToList(List list, Node* node);

#endif //linked_list_h
