#ifndef directive_h
#define directive_h

#include "../src/libraries.h"
#include "../src/main.h"

#define MAX_WORDS 4
#define ONE_BIT 1
#define TWO_BITS 3
#define FOUR_BITS 15
#define AT 0
#define DAM 2
#define SAM 4
#define OPC 6
#define PAR1 10
#define PAR2 12


/* STRUCTURES */

typedef struct directive {
    int wCount;
    cell words[MAX_WORDS];
} directive;

typedef directive* pDirective;


/* METHODS */

directive getEmptyDir();
directive getDirCopy(pDirective);

#endif
