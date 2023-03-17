#include "assembly.h"

/* ERRORS: */
/*TODO confusion about cell size */
/*TODO limit the number of "words"? */
/*TODO label doesn't exist */

int dataCounter=0, instructionCounter=0;

void compile(FILE* source, const char* oldFileName) {
    char newFileName[MAX_FILE_NAME];
    FILE* objectFile, *entFile, *extFile;
    Word dataArray[MAX_DATA];
    Word instructionArray[MAX_INSTRUCTIONS];
    List symbolTable = { NULL, NULL };
    List externalSymbols = { NULL, NULL };
    List entrySymbols = { NULL, NULL };

    memset(newFileName, 0, MAX_FILE_NAME);
    initializeWordArray(dataArray, MAX_DATA, 0);
    initializeWordArray(instructionArray, MAX_INSTRUCTIONS, INST_ERROR);

    sprintf(newFileName, "%s.ob", oldFileName);

    phase1(source,
           dataArray,
           instructionArray,
           &symbolTable);

    if (error) {
        printf("Errors found, stopping..\n");
        return;
    }

    updateDataAddresses(&symbolTable);

    phase2(source,
           instructionArray,
           &symbolTable,
           &externalSymbols,
           &entrySymbols);

    if (error) {
        printf("Errors found, stopping..\n");
        return;
    }
    fclose(source);
    freeSymbolTable(symbolTable.head);

    objectFile = fopen(newFileName, "w+");
    makeObFile(objectFile, instructionArray, dataArray);
    putchar('\n');
    putchar('\n');
    printFileContent(objectFile);
    fclose(objectFile);

    if (entrySymbols.head != NULL) {
        memset(newFileName, 0, MAX_FILE_NAME);
        sprintf(newFileName, "%s.ent", oldFileName);
        entFile = fopen(newFileName, "w+");
        makeExtraFile(entFile, entrySymbols);
        putchar('\n');
        putchar('\n');
        printFileContent(entFile);
    }


    freeSymbolTable(entrySymbols.head);

    if (externalSymbols.head != NULL) {
        memset(newFileName, 0, MAX_FILE_NAME);
        sprintf(newFileName, "%s.ext", oldFileName);
        extFile = fopen(newFileName, "w+");
        makeExtraFile(extFile, externalSymbols);
        putchar('\n');
        putchar('\n');
        printFileContent(extFile);
    }

    freeSymbolTable(externalSymbols.head);


}

void updateDataAddresses(List* symbolTable) {
    Node* currentLabel = symbolTable->head;

    while (currentLabel) {
        if (!strcmp(currentLabel->item.label.type, "data")) {
            currentLabel->item.label.value += instructionCounter;
        }
        currentLabel = currentLabel->next;
    }
}

void makeObFile(FILE* file, Word* instructionArray, Word* dataArray) {
    int i=0, lineC;
    char newLine[MAX_OB_LINE];


    while (instructionArray[i].value != INST_ERROR) {
        memset(newLine, 0, MAX_OB_LINE);
        makeObLine(instructionArray[i], i, newLine);
        fputs(newLine, file);
        i++;
    }
    lineC = i;
    i=0;

    while (i < dataCounter) {
        memset(newLine, 0, MAX_OB_LINE);
        makeObLine(dataArray[i], lineC+i, newLine);
        fputs(newLine, file);
        i++;
    }
}

void makeExtraFile(FILE* file, List list) {
    char newLine[MAX_ENT_LINE];
    char spaces[MAX_LABEL_LENGTH+4];
    char name[MAX_LABEL_LENGTH+4];
    int address;
    Label currentLabel;

    Node* currentNode = list.head;
    int addressInd = getNumberStartInd(list);

    while (currentNode) {
        memset(newLine, 0, MAX_ENT_LINE);
        memset(name, 0, MAX_LABEL_LENGTH+4);
        memset(spaces, 0, MAX_LABEL_LENGTH+4);
        currentLabel = currentNode->item.label;
        strcpy(name, currentLabel.name);
        setSpaces(spaces, addressInd - ((int) strlen(name)));
        address = currentLabel.value;

        sprintf(newLine, "%s%s%d\n", name, spaces, address);
        fputs(newLine, file);
        currentNode = currentNode->next;
    }
}

void setSpaces(char* spaces, int amount) {
    int i;
    for (i=0; i < amount; i++) {
        spaces[i] = ' ';
    }
}

void freeSymbolTable(Node* node) {
    if (node == NULL) return;

    freeSymbolTable(node->next);
    free(node);
}

void initializeWordArray(Word* array, int size, int value) {
    int i;

    for (i=0; i < size; i++)
        array[i].value = value;
}

int getNumberStartInd(List list) {
    Node* currentNode = list.head;
    size_t currLen, longest=0;

    while (currentNode) {
        currLen = strlen(currentNode->item.label.name);
        if (currLen > longest)
            longest = currLen;
        currentNode = currentNode->next;
    }

    return (int) (longest + 5);
}
