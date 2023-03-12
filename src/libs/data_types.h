#ifndef data_types_h
#define data_types_h

#define WORD_LENGTH 14
#define MAX_LABEL_LENGTH (30+1) /* not including colon */
#define MAX_TYPE_LENGTH (9+1)
#define MAX_MACRO_NAME_LENGTH (74+1) /* max line length minus "mcr " */
#define MAX_LINE_LENGTH 81

typedef struct Macro Macro;
typedef struct Label Label;
typedef union Item Item;
typedef struct Node Node;
typedef struct List List;

struct List {
    Node* head;
    Node* tail;
};

struct Macro {
    char name[MAX_MACRO_NAME_LENGTH];
    List lines;
};

struct Label {
    char name[MAX_LABEL_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int value;
};

union Item {
    Macro macro;
    Label label;
    char line[MAX_LINE_LENGTH];
};

struct Node {
    Item item;
    struct Node* next;
};


typedef struct Word {
    short value;
}Word;

#endif
