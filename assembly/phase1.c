#include "phase1.h"

int lineCount=1;

FILE* phase1(FILE* source,
             Word* dataArray,
             Word* instructionArray,
             Label** symbolTable,
             Label** externalSymbols,
             Label** entrySymbols,
             char** ops) {
    int i, j, labelFlag=0, r=0;
    char line[MAX_LINE_LENGTH], labelName[MAX_LABEL_LENGTH], word[MAX_TYPE_LENGTH];
    FILE* output = fopen("pp1.txt", "w+");


    while (fgets(line, MAX_LINE_LENGTH, source)) {

        i=0;
        j=0;
        memset(word, 0, sizeof(word));
        memset(labelName, 0, sizeof(labelName));

        skipWhiteSpaces(line, &i);

        if (line[i] == ';' || line[i] == '\n') continue;

        if (hasLabel(line)) {
            labelFlag=1;
            r = readLabelName(labelName, &i, line);
            if (r == LABEL_ERROR) continue;
        }

        if (isDirective(line, &i)) {
            if (i == strlen(line)) {
                printError("No directive name entered");
                continue;
            }
            while (i < MAX_TYPE_LENGTH && i < strlen(line) && line[i] != ' ' && line[i] != '\t') {
                word[j++] = line[i++];
            }

            if (isDataDirective(word) || isStringDirective(word)) {
                if (labelFlag)
                    addDataLabel(labelName, symbolTable);

                if (isDataDirective(word)) addIntArray(line, &i, dataArray);
                else addString(line, &i, dataArray);
            }

            else if (isExternDirective(word)) {
                readLabelName(labelName, &i, line);
                addExternLabel(labelName, symbolTable);
            }

            else if (isEntryDirective(word)) continue;
            else printError("unknown directive");
        }

        else { /* line is not a directive */
            while (i < MAX_TYPE_LENGTH && i < strlen(line) && line[i] != ' ' && line[i] != '\t' && line[i] != '(') {
                word[j++] = line[i++];
            }

            if ((r=isInstruction(word, ops))) {
                r--;
                if (labelFlag)
                    addInstructionLabel(labelName, symbolTable);

                addInstruction(line, &i, r, instructionArray, symbolTable, externalSymbols);
            }
        }

        lineCount++;
    }

    if (error) {
        printf("Errors found, stopping..\n");
        exit(1);
    }

    return output;
}

int hasLabel(const char* line) {
    int i;
    for (i=0; i < strlen(line); i++) {
        if (line[i] == ':') {
            if (i <= MAX_LABEL_LENGTH) return 1;
            printError("Label name is too long");
            return 0;
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