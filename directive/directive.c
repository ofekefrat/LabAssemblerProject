/* shit for directives */

#include "directive.h"

directive getEmptyDir() {

    directive newDir;
    newDir.wCount = 0;

    return newDir;
}

directive getDirCopy(pDirective dir) {

    int i;
    directive temp = getEmptyDir();

    if (dir == NULL) {
        printf("getDirCopy received null pointer\n");
        exit(0);
    }

    for (i=0;  i < dir->wCount && i < MAX_WORDS; i++) {
        temp.words[i] = getCellCopy(&dir->words[i]);
        temp.wCount++;
    }

    return temp;
}


/* setters */
void setWord(pDirective dir, cell word) {

    if (dir == NULL) {
        printf("setWord received null directive pointer\n");
        exit(0);
    }

    if (word == NULL) {
        printf("setWord received null word pointer\n");
        exit(0);
    }

    dir->words[dir->wCount] = *word;
    dir->wCount++;
}

void setAccessType(pCell word, int type) {
    cell temp;

    if (type < 0 || type > 2) {
        printf("Access type out of range (0-2)\n");
        exit(0);
    }

}

void setDestAddressingMethod(cell word, int method) {

}

void setSourceAddressingMethod(pDirective dir, int wordInd) {

}

void setOpCode(pDirective dir, int wordInd) {

}

void setFirstParameterType(pDirective dir, int wordInd) {

}

void setSecondParameterType(pDirective dir, int wordInd) {

}


/* getters */
int checkBits(pCell word, int value) {
    return word->value & value;
}

int getAccessType(pCell word) {
    return checkBits(word, TWO_BITS << AT) ;
}

int getDestAddressingMethod(pCell word) {
    return checkBits(word, TWO_BITS << DAM) ;
}

int getSourceAddressingMethod(pCell word) {
    return checkBits(word, TWO_BITS << SAM);
}

int getOpCode(pCell word) {
    return checkBits(word, FOUR_BITS << OPC);
}

int getFirstParameterType(pCell word) {
    return checkBits(word, TWO_BITS << PAR2) ;
}

int getSecondParameterType(pCell word) {
    return checkBits(word, TWO_BITS << PAR2) ;
}
