#ifndef word_h
#define word_h

#include "../src/main.h"
#include "../src/libraries.h"

typedef struct Word {
    int destinationAM : 2;
    int sourceAM : 2;
    int opcode : 4;
    int firstPT: 2;
    int secondPT: 2;
}Word;

#endif //word_h
