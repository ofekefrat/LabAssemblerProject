#include "assembly.h"

/* phase2: the second phase of assembly. */
void phase2(FILE* source,
            Word* instructionArray,
            List* symbolTable,
            List* externalSymbols,
            List* entrySymbols) {

    int i=0;
    char line[MAX_LINE_LENGTH], word[MAX_TYPE_LENGTH];
    Item tempItem;
    Label* pLabel;

    instructionCounter=0;
    lineCount=0;

    rewind(source);

    while (fgets(line, MAX_LINE_LENGTH, source)) {
        lineCount++;
        i=0;
        skipWhiteSpaces(line, &i);

        if (line[i] == ';' || line[i] == '\n') continue;

        if (hasLabel(line)) {
            skipLabel(line, &i);
        }
        skipWhiteSpaces(line, &i);

        if (isDirective(line, &i)) {

            readNextWord(word, line, &i, sizeof(word));
            if (isEntryDirective(word)) {
                skipWhiteSpaces(line, &i);
                readNextWord(word, line, &i, sizeof(word));
                pLabel = getLabel(word, *symbolTable);

                if (pLabel) {
                    tempItem.label = *pLabel;
                    addToList(entrySymbols, newNode(tempItem));
                }
                else {
                    printError("Entry cannot use undefined label");
                }
            } else continue;
        }
        else
            completeInstruction(line, &i, instructionArray, symbolTable, externalSymbols);
    }
}
