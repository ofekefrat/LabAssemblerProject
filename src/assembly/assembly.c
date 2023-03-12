#include "assembly.h"

/* ERRORS: */
/*TODO confusion about cell size*/
/*TODO negative numbers*/
/*TODO free allocated memory*/

/* UNLESS THERE'S AN ERROR:*/
/*TODO Make .ext file*/
/*TODO Make .ent file*/


int dataCounter=0, instructionCounter=0;

void compile(FILE* source, const char* oldFileName) {
    char newFileName[MAX_FILE_NAME];
    FILE* objectFile;
/*    Word memoryImage[MAX_MEMORY];*/
    Word dataArray[MAX_DATA];
    Word instructionArray[MAX_INSTRUCTIONS];

    initializeWordArray(dataArray, MAX_DATA, 0);
    initializeWordArray(instructionArray, MAX_INSTRUCTIONS, INST_ERROR);

    List symbolTable = { NULL, NULL };
    List externalSymbols = { NULL, NULL };
    List entrySymbols = { NULL, NULL };

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

    updateMemoryImage(instructionArray);


    objectFile = fopen(newFileName, "w+");
    makeObFile(objectFile, instructionArray, dataArray);
    putchar('\n');
    putchar('\n');
    printFileContent(objectFile);

    fclose(objectFile);
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

void updateMemoryImage(Word* instructionArray) {
    int i;
    unsigned int oldAddress;
    Word* currentInst;

    for (i=0; instructionArray[i].value != INST_ERROR; i++) {
        currentInst = &instructionArray[i];
        if ((currentInst->value & reloc) == reloc) {
            oldAddress = ((~3) & currentInst->value) >> 2;
            currentInst->value = reloc | ((oldAddress + RESERVED_SPACE) << 2);
        }
    }
}

void makeObFile(FILE* file, Word* instructionArray, Word* dataArray) {
    int i=0, lineC;
    char newLine[MAX_LINE_LENGTH];


    while (instructionArray[i].value != INST_ERROR) {
        memset(newLine, 0, MAX_LINE_LENGTH);
        makeObLine(instructionArray[i], i, newLine);
        fputs(newLine, file);
        i++;
    }
    lineC = i;
    i=0;

    while (i < dataCounter) {
        memset(newLine, 0, MAX_LINE_LENGTH);
        makeObLine(dataArray[i], lineC+i, newLine);
        fputs(newLine, file);
        i++;
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
