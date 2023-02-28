#include "word.h"

void Word_init(Word* self,
//               int accessType,
               int destinationAM,
               int sourceAM,
               int opcode,
               int firstPT,
               int secondPT) {
//    if (accessType < 0 || accessType > 2) {
//        printf("Access type out of range (0-2)\n");
//        exit(0);
//    }
//    self->accessType = accessType;

    if (destinationAM < 0 || destinationAM > 4) {
        printf("destination addressing method out of range (0-4)\n");
        exit(0);
    }
    self->destinationAM = destinationAM;

    if (sourceAM < 0 || sourceAM > 4) {
        printf("source addressing method out of range (0-4)\n");
        exit(0);
    }
    self->sourceAM = sourceAM;

    if (opcode < 0 || opcode > 16) {
        printf("opcode out of range (0-16)\n");
        exit(0);
    }
    self->opcode = opcode;

}

Word* Word_create(int value) {
    Word* result = (Word*) malloc(sizeof(Word));
//    Word_init(result, value);
    return result;
}

void destroyWord(Word* word) {
    if (word) {
        free(word);
    }
}
