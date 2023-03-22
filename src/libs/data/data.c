#include "data.h"
/* addIntArray: handle the .data directive: read every number in the line and add it to the memory image. */
void addIntArray(char* line, int* ind, Word* dataArray) {
    int i = *ind;
    int num;

    while (i+1 < strlen(line) && line[i] != '\n') {
        num = readNextNumber(line, &i);
        skipWhiteSpaces(line, &i);
        if (i+1 < strlen(line) && line[i] != '\n') verifyComma(line, &i);
        if (num != INT_MIN) {
            if (num < (1 << WORD_LENGTH) && num > (-(1 << WORD_LENGTH))) {
                dataArray[dataCounter++].value = num;
            }
            else
                printError("number is too big");
        }
        else return;
    }

    *ind = i;
}

/* addString: handle the .string directive: read every character in the string and add it to the memory image. */
void addString(char* line, int* ind, Word* dataArray) {
    int i = *ind;
    skipWhiteSpaces(line, &i);

    if (i >= strlen(line) || line[i] == '\n') {
        printError("no string entered");
        return;
    }
    if (line[i] != '\"')
        printError("string must be initiated with \"");

    for ( i+=1; i < strlen(line) && line[i] != '\"'; i++) {
        dataArray[dataCounter++].value = (int) line[i];
    }

    if (i < strlen(line) && line[i] != '\"') {
        printError("string must be terminated with \"");
    }

    dataArray[dataCounter++].value = 0;
    *ind = i;
}