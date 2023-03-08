#ifndef datatypes_h
#define datatypes_h

#define WORD_LENGTH 14

typedef struct Macro Macro;
typedef struct Label Label;
typedef union Item Item;
typedef struct Node Node;
typedef struct List List;
typedef struct Word {
    unsigned int value : WORD_LENGTH;
}Word;

#endif //datatypes_h
