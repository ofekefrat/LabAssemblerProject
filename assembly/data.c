#include "assembly.h"

void addIntArray(char* line, int* ind, Cell* dataArray) {
    int i = *ind;
    int* pInt = NULL;

    while (line[i] != '\n') {
        readNextNumber(line, &i, pInt);
        verifyComma(line, &i);
        if (pInt != NULL) {
            if (*pInt < (1 << 15))
                dataArray[dataCounter++].value = *pInt;
            else
                printError("number is too big");
        }
    }

    *ind = i;
}

void readNextNumber(const char* line, int* ind, int* pInt) {
    char digits[MAX_DIGITS];
    int i = *ind, j=0;

    memset(digits, 0, MAX_DIGITS);

    skipWhiteSpaces(line, &i);
    if (line[i] == '-') digits[j++] = line[i++];
    while (i < strlen(line) && isdigit(line[i])) digits[j++] = line[i++];
    *ind = i;

    if (!isdigit(digits[0])) printError("No digits found when expecting number");
    else *pInt = atoi(digits);
}

int verifyComma(const char* line, int* ind) {
    int i = *ind;
    skipWhiteSpaces(line, &i);

    if (line[i] == ',') {
        *ind = ++i;
        return 1;
    }
    printError("Missing comma");
    *ind = i;
    return 0;
}

void addString(char* line, int* ind, Cell* dataArray) {
    int i = *ind;
    while (i < strlen(line) && line[i] != '\"') i++;

    for ( i+=1; i < strlen(line) && line[i] != '\"'; i++) {
        dataArray[dataCounter++].value = (int) line[i];
    }

    dataArray[dataCounter++].value = 0;
    *ind = i;
}