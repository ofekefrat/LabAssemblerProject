#include "assembly.h"

int dataCounter, instructionCounter;

/* compile: produce the required files. */
void compile(FILE* source, const char* fileName) {
    char newFileName[MAX_FILE_NAME];
    FILE* objectFile, *entFile, *extFile;
    Word dataArray[MAX_DATA]; /* array for data to be put in the memory image */
    Word instructionArray[MAX_INSTRUCTIONS]; /* array for the instructions to be put in the memory image.*/
    List symbolTable = { NULL, NULL }; /* linked list for labels */
    List externalSymbols = { NULL, NULL }; /* a separate list for the external labels defined,
                                             * to later create .ext file*/
    List entrySymbols = { NULL, NULL }; /* same thing for entries. */

    dataCounter=0;
    instructionCounter=0;
    memset(newFileName, 0, MAX_FILE_NAME);
    initializeWordArray(dataArray, MAX_DATA, 0);
    initializeWordArray(instructionArray, MAX_INSTRUCTIONS, INST_ERROR);

    sprintf(newFileName, "%s.ob", fileName);

    phase1(source,
           dataArray,
           instructionArray,
           &symbolTable);

    updateDataAddresses(&symbolTable);

    phase2(source,
           instructionArray,
           &symbolTable,
           &externalSymbols,
           &entrySymbols);


    fclose(source);

    freeSymbolTable(symbolTable.head);

    if (error) {
        printf("Errors found, stopping..\n");
        freeSymbolTable(entrySymbols.head);
        freeSymbolTable(externalSymbols.head);
        return;
    }

    objectFile = fopen(newFileName, "w+");
    makeObFile(objectFile, instructionArray, dataArray);

    if (entrySymbols.head != NULL) {
        memset(newFileName, 0, MAX_FILE_NAME);
        sprintf(newFileName, "%s.ent", fileName);
        entFile = fopen(newFileName, "w+");
        makeExtraFile(entFile, entrySymbols);
    }


    freeSymbolTable(entrySymbols.head);

    if (externalSymbols.head != NULL) {
        memset(newFileName, 0, MAX_FILE_NAME);
        sprintf(newFileName, "%s.ext", fileName);
        extFile = fopen(newFileName, "w+");
        makeExtraFile(extFile, externalSymbols);
    }

    freeSymbolTable(externalSymbols.head);
}

/* updateDataAddresses: update addresses of data in the memory image to appear after the instructions. */
void updateDataAddresses(List* symbolTable) {
    Node* currentLabel = symbolTable->head;

    while (currentLabel) {
        if (!strcmp(currentLabel->item.label.type, "data")) {
            currentLabel->item.label.value += instructionCounter;
        }
        currentLabel = currentLabel->next;
    }
}

/* makeObFile: make the .ob file. */
void makeObFile(FILE* file, Word* instructionArray, Word* dataArray) {
    int i=0, lineC;
    char newLine[MAX_OB_LINE];

    sprintf(newLine, " %d \t%d\n", instructionCounter, dataCounter);
    fputs(newLine, file);

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
    fclose(file);
}

/* makeExtraFile: for creating the ext and ent files. */
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
    fclose(file);
}

/* setSpaces: place the required amount of spaces in the given buffer. */
void setSpaces(char* spaces, int amount) {
    int i;
    for (i=0; i < amount; i++) {
        spaces[i] = ' ';
    }
}

/* freeSymbolTable: free allocated memory used for a linked list (specifically for symbolTable) */
void freeSymbolTable(Node* node) {
    if (node == NULL) return;

    freeSymbolTable(node->next);
    free(node);
}

/* initializeWordArray: for initialization of the data and instruction arrays.*/
void initializeWordArray(Word* array, int size, int value) {
    int i;

    for (i=0; i < size; i++)
        array[i].value = value;
}

/* getNumberStartInd: get the index in which the address should start appearing (in ext and ent files) */
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
