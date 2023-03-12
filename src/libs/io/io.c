#include "io.h"
extern int lineCount;

int hasLabel(const char* line) {
    int i;
    for (i=0; i < strlen(line); i++) {
        if (line[i] == ':') {
            if (i <= MAX_LABEL_LENGTH) return 1;
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

int isDataDirective(const char* word) {
    return (!strcmp(word, "data"));
}
int isStringDirective(const char* word) { return (!strcmp(word, "string")); }
int isExternDirective(const char* word) { return (!strcmp(word, "extern")); }
int isEntryDirective(const char* word) { return (!strcmp(word, "entry")); }

void skipWhiteSpaces(const char* line, int* ind) {
    int i = *ind;
    while (line[i] != '\n' && (line[i] == ' ' || line[i] == '\t')) i++;
    *ind = i;
}

int skipLabel(const char* line, int* ind) {
    int i = *ind;
    while (line[i] != '\n' && line[i] != ':') i++;

    if (line[i] != '\n') {
        *ind = ++i;
        return 1;
    }
    *ind = i;
    return 0;
}

int isInstruction(const char* word) {
    int i;
    char* ops[] = OPCODES;
    for (i=0; i < NUM_OF_OPCODES; i++)
        if (!strcmp(word, ops[i])) return i+1;

    return 0;
}

int readLabelName(char* buffer, int* ind, const char* line) {
    int i = *ind, j=0;

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
    printf("in line %d: %s\n", lineCount, str);
    if (!error) error=1;
}

int isDef(const char* line) {

    if (strlen(line) < 4 || line[0] != 'm' || line[1] != 'c' || line[2] != 'r' || line[3] != ' ')
        return 0;

    return 1;
}

Node* isSpread(List macros, const char* line, char* buffer) {
    int i=0;
    if (hasLabel(line)) {
        readLabelName(buffer, &i, line);
    }

    skipWhiteSpaces(line, &i);
    Node* currentNode = macros.head;
    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.macro.name, line+i))
            return currentNode;
        currentNode = currentNode->next;
    }

    return NULL;
}
int isRegisterOperand(const char* operand) {
    int res;
    if (strlen(operand) > 2 && operand[0] == 'r'/*&& isdigit(operand[1])*/) {
        res = operand[1] - '0';
        if (res <= NUM_OF_REGS)
            return 1;
        else {
        }
    }
    return 0;
}

void readNextOperand(const char *line, int *ind, char* operand) {
    int i = *ind, j=0;
    skipWhiteSpaces(line, &i);
    while (stillInWord(line, &i) && line[i] != ',') operand[j++] = line[i++];
    *ind = i;
}

int stillInWord(const char* line, const int* ind) {
    return (line[*ind] != '\n' && line[*ind] != ' ' && line[*ind] != '\t');
}

void readNextWord(char* buffer, const char* line, int* ind) {
    int i = *ind, j=0;
    while (j < MAX_TYPE_LENGTH && stillInWord(line, &i)) {
        buffer[j++] = line[i++];
    }
    *ind = i;
}


void makeObLine(Word word, int i, char* newLine) {
    char address[ADDRESS_PRINT_LENGTH];
    char value[WORD_STR_LENGTH];

    memset(address, 0, ADDRESS_PRINT_LENGTH);
    memset(value, 0, WORD_STR_LENGTH);

    snprintf(address, ADDRESS_PRINT_LENGTH,"0%d", i+RESERVED_SPACE);

    binTranslator(word.value, value);
    reverseWord(value);

    snprintf(newLine, MAX_LINE_LENGTH, "%s\t%s\n", address, value);
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

void printFileContent(FILE* file) {
    char line[MAX_LINE_LENGTH];
    rewind(file);
    while (fgets(line, MAX_LINE_LENGTH, file)) { // fgets, not EOF
        printf("%s", line);
    }
}
