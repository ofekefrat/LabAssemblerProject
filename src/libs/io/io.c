#include "io.h"
extern int lineCount;
extern char* currentFileName;

int isDataDirective(const char* word) { return (!strcmp(word, "data")); }
int isStringDirective(const char* word) { return (!strcmp(word, "string")); }
int isExternDirective(const char* word) { return (!strcmp(word, "extern")); }
int isEntryDirective(const char* word) { return (!strcmp(word, "entry")); }

int hasLabel(const char* line) {
    int i;
    for (i=0; i < strlen(line); i++) {
        if (line[i] == ':') {
            if (i <= MAX_LABEL_LENGTH)
                return 1;

            printError("Label name is too long");
            return LABEL_ERROR;
        }
    }
    return 0;
}

int isDirective(const char* line, int* ind) {
    int i;
    i = *ind;

    if (line[i] == '.') {
        *ind = ++i;
        return 1;
    }
    return 0;
}

void skipWhiteSpaces(const char* line, int* ind) {
    int i = *ind;
    while (line[i] != '\n' && (line[i] == ' ' || line[i] == '\t')) i++;
    *ind = i;
}

void skipWord(const char* line, int* ind) {
    int i = *ind;
    while (stillInWord(line, i)) i++;
    *ind = i;
}

void skipLabel(const char* line, int* ind) {
    int i = *ind;
    while (line[i] != '\n' && line[i] != ':') i++;

    if (line[i] != '\n') {
        *ind = ++i;
    }
    *ind = i;
}

int isInstruction(const char* word) {
    int i;
    char* ops[] = OPCODES;
    for (i=0; i < NUM_OF_OPCODES; i++)
        if (!strcmp(word, ops[i])) return i+1;

    return 0;
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

int readLabelName(char* buffer, int* ind, const char* line) {
    int i = *ind, j=0;

    memset(buffer, 0, MAX_LABEL_LENGTH);

    skipWhiteSpaces(line, &i);
    if (!isalpha(line[i])) {
        printError("first character in label name must be alphabetical");
        return LABEL_ERROR;
    }
    buffer[j++] = line[i++];

    while (j < MAX_LABEL_LENGTH && i < strlen(line) && line[i] != ':') {
        if (!isalnum(line[i])) {
            printError("Only digits and alphabetical characters allowed in label name");
            return LABEL_ERROR;
        }

        buffer[j++] = line[i++];
    }
    skipLabel(line, &i);

    *ind = i;
    return 1;
}

void printError(const char* str) {
    printf("\nin %s, line %d: %s\n", currentFileName, lineCount, str);
    if (!error) error=1;
}

int isDef(const char* line) {
    char word[MAX_LINE_LENGTH];
    int i=0;
    skipWhiteSpaces(line, &i);

    readNextWord(word, line, &i, sizeof(word));
    if (!strcmp(word, "mcr")) return 1;
    return 0;
}

void readMacroName(const char* line, char* buffer) {
    char word[MAX_MACRO_NAME_LENGTH];
    int i=0;

    readNextWord(word, line, &i, sizeof(word));
    if (!strcmp(word, "mcr")) {
        readNextWord(word, line, &i, sizeof(word));
    }

    strcpy(buffer, word);
}

int isEndmcr(const char* line) {
    int i=0;
    char word[MAX_LINE_LENGTH];

    skipWhiteSpaces(line, &i);
    readNextWord(word, line, &i, sizeof(word));

    skipWhiteSpaces(line, &i);
    if (!strcmp(word, "endmcr")) {
        if (line[i] != '\n' && i < strlen(line)) {
            printError("superfluous characters after endmcr");
        }
        return 1;
    }
    return 0;
}


Node* isSpread(List macros, const char* line, char* labelBuffer) {
    int i=0;
    char name[MAX_LINE_LENGTH];
    Node* currentNode;
    skipWhiteSpaces(line, &i);
    if (hasLabel(line)) {
        readLabelName(labelBuffer, &i, line);
    }

    readMacroName(line, name);

    skipWhiteSpaces(line, &i);
    currentNode = macros.head;
    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.macro.name, name))
            return currentNode;
        currentNode = currentNode->next;
    }

    return NULL;
}

int readNextNumber(const char* line, int* ind) {
    char digits[MAX_DIGITS];
    int i = *ind, j=0;

    memset(digits, 0, MAX_DIGITS);

    skipWhiteSpaces(line, &i);
    if (line[i] == '-') digits[j++] = line[i++];
    else if (line[i] == '+') i++;
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

int isRegisterOperand(const char* operand) {
    if (strlen(operand) == 2 && operand[0] == 'r' && isdigit(operand[1]))
        return 1;
    return 0;
}

int isJumpOperand(const char* line, int i) {
    while (stillInWord(line, i)) {
        if (i < MAX_LABEL_LENGTH && line[i] == '(') return 1;
        i++;
    }
    return 0;
}

void checkWhiteChar(const char* line, int i) {
    if (line[i] == ' ' || line[i] == '\t') printError("white characters not allowed inside parameter");
}

void readNextOperand(const char *line, int *ind, char* operand, size_t size) {
    int i = *ind, j=0;
    skipWhiteSpaces(line, &i);
    while (stillInWord(line, i) && line[i] != ',' && line[i] != ')' && j < size) operand[j++] = line[i++];
    *ind = i;
}

int stillInWord(const char* line, int i) {
    return (i < strlen(line) && line[i] != '\n' && line[i] != ' ' && line[i] != '\t');
}

void readNextWord(char* buffer, const char* line, int* ind, size_t size) {
    int i = *ind, j=0;
    memset(buffer, 0, size);

    skipWhiteSpaces(line, &i);

    while (j < size && stillInWord(line, i)) {
        buffer[j++] = line[i++];
    }
    *ind = i;
}


void makeObLine(Word word, int i, char* newLine) {
    char address[ADDRESS_PRINT_LENGTH];
    char value[WORD_STR_LENGTH];

    memset(address, 0, ADDRESS_PRINT_LENGTH);
    memset(value, 0, WORD_STR_LENGTH);

    sprintf(address,"0%d", i+RESERVED_SPACE);

    binTranslator(word.value, value);
    reverseWord(value);

    sprintf(newLine, "%s\t%s\n", address, value);
}

void reverseWord(char* buff) {
    int i;
    char temp[WORD_STR_LENGTH];
    memset(temp, 0, WORD_STR_LENGTH);

    strcpy(temp, buff);
    memset(buff, 0, WORD_STR_LENGTH);

    for (i=0; i < WORD_LENGTH; i++) {
        buff[i] = temp[WORD_LENGTH-i-1];
    }
}

void binTranslator(unsigned int num, char* buff) {
    int i=0;
    while (i < WORD_LENGTH) { /* printing base-2 (binary) representation */
        if (num & (1 << i))
            buff[i++] = '/';
        else
            buff[i++] = '.';
    }
}
