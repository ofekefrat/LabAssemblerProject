#include "data.h"


void addIntArray(char* line, int* ind, Word* dataArray) {
    int i = *ind;
    int num;

    while (line[i] != '\n' && i+1 < strlen(line)) {
        num = readNextNumber(line, &i);
        skipWhiteSpaces(line, &i);
        if (line[i] != '\n' && i+1 < strlen(line)) verifyComma(line, &i);
        if (num != INT_MIN) {
            if (num < (1 << 15))
                dataArray[dataCounter++].value = num;
            else
                printError("number is too big");
        }
    }

    *ind = i;
}

int readNextNumber(const char* line, int* ind) {
    char digits[MAX_DIGITS];
    int i = *ind, j=0;

    memset(digits, 0, MAX_DIGITS);

    skipWhiteSpaces(line, &i);
    if (line[i] == '-') digits[j++] = line[i++];
    while (i < strlen(line) && isdigit(line[i])) digits[j++] = line[i++];
    *ind = i;

    if (!isdigit(digits[0])) {
        if (digits[0] != '-' || strlen(digits) < 2 || !isdigit(digits[1])) {
            printError("No digits found when expecting number");
            return INT_MIN;
        }
    }
    return atoi(digits);
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

void addString(char* line, int* ind, Word* dataArray) {
    int i = *ind;
    while (i < strlen(line) && line[i] != '\"') i++;

    for ( i+=1; i < strlen(line) && line[i] != '\"'; i++) {
        dataArray[dataCounter++].value = (int) line[i];
    }

    dataArray[dataCounter++].value = 0;
    *ind = i;
}