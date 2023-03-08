#include "io.h"

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
    skipWhiteSpaces(line, ind);
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
    while (i < strlen(line) && (line[i] == ' ' || line[i] == '\t')) i++;
    *ind = i;
}

int isInstruction(const char* word, char** ops) {
    int i;

    for (i=0; i < sizeof(ops); i++)
        if (!strcmp(word, ops[i])) return i+1;

    return 0;
}

int readLabelName(char* buffer, int* ind, const char* line) {
    int i = *ind;
    if (!isalpha(line[i])) {
        printError("first character in label name must be alphabetical");
    }
    buffer[0] = line[i];

    for (; i < strlen(line) && line[i] != ':'; i++) {
        if (i < MAX_LABEL_LENGTH) {
            if (!isalnum(line[i])) {
                printError("Only digits and alphabetical character allowed in label name");
                return LABEL_ERROR;
            }
            buffer[i] = line[i];
        }
    }

    if (strlen(buffer) > MAX_LABEL_LENGTH) {
        strcpy(buffer, "error");
    }
    *ind = i;
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

//TODO Verify & allow macro spreads inside labels
Node* isSpread(List macros, const char* line) {

    Node* currentNode = macros.head;
    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.macro.name, line))
            return currentNode;
    }

    return NULL;
}
int isRegisterOperand(const char* operand) {
    int res;
    if (strlen(operand) > 2 && operand[0] == 'r'/*&& isdigit(operand[1])*/) {
        res = operand[1] - '0';
        if (res <= NUM_OF_REGS) return 1;
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
    return (*ind < strlen(line) && line[*ind] != ' ' && line[*ind] != '\t' && line[*ind] != '\n');
}
