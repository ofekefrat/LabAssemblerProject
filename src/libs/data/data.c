#include "data.h"

/* addIntArray: handle the .data directive: read every number in the line and add it to the memory image. */
void addIntArray(char* line, int* ind, Word* dataArray) {
    int i = *ind;
    int num;

    while (line[i] != '\n' && i+1 < strlen(line)) {
        num = readNextNumber(line, &i);
        skipWhiteSpaces(line, &i);
        if (line[i] != '\n' && i+1 < strlen(line)) verifyComma(line, &i);
        if (num != INT_MIN) {
            if (num < (1 << 15)) {
                dataArray[dataCounter++].value = num;
            }
            else
                printError("number is too big");
        }
    }

    *ind = i;
}

/* addString: handle the .string directive: read every character in the string and add it to the memory image. */
void addString(char* line, int* ind, Word* dataArray) {
    int i = *ind;
    while (i < strlen(line) && line[i] != '\"') i++;

    for ( i+=1; i < strlen(line) && line[i] != '\"'; i++) {
        dataArray[dataCounter++].value = (int) line[i];
    }

    dataArray[dataCounter++].value = 0;
    *ind = i;
}