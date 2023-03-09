#include "assembly.h"

void phase2(FILE* source,
            Word* instructionArray,
            List* symbolTable,
            List* externalSymbols,
            List* entrySymbols) {

    int i;
    char line[MAX_LINE_LENGTH], word[MAX_TYPE_LENGTH];
    Item tempItem;
    Label* pLabel;
    int lineCount=0;

    instructionCounter=0;

    while (fgets(line, MAX_LINE_LENGTH, source)) {
        skipWhiteSpaces(line, &i);

        if (line[i] == ';' || line[i] == '\n') continue;

        if (hasLabel(line)) {
            skipLabel(line, &i);
        }
        skipWhiteSpaces(line, &i);

        readNextWord(word, line, &i);

        if (isDirective(line, &i)) {

            if (isEntryDirective(word)) {
                skipWhiteSpaces(line, &i);
                readNextWord(word, line, &i);
                pLabel = getLabel(word, *symbolTable);

                if (pLabel) {
                    tempItem.label = *pLabel;
                    addToList(entrySymbols, newNode(tempItem));
                }
            } else continue;
        }
        else
            completeInstruction(line, &i, instructionArray, symbolTable, externalSymbols);

        lineCount++;
    }
}
