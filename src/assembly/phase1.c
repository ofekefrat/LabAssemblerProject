#include "assembly.h"

/* phase1: the first phase of assembly. */
void phase1(FILE *source, Word *dataArray, Word *instructionArray, List *symbolTable) {

    int i, labelFlag, r;
    char line[MAX_LINE_LENGTH], labelName[MAX_LABEL_LENGTH], word[MAX_TYPE_LENGTH];

    rewind(source);
    lineCount=0;

    while (fgets(line, MAX_LINE_LENGTH, source)) {
        /* updating & resetting what's necessary */
        lineCount++;
        i=0;
        labelFlag=0;
        memset(word, 0, sizeof(word));
        memset(labelName, 0, sizeof(labelName));

        skipWhiteSpaces(line, &i);

        if (line[i] == ';' || line[i] == '\n') continue;

        if (hasLabel(line)) {
            labelFlag=1;
            r = readLabelName(labelName, &i, line);
            if (r == LABEL_ERROR) continue;
            if (!isUniqueLabelName(labelName, *symbolTable)) {
                continue;
            }
        }

        skipWhiteSpaces(line, &i);

        if (isDirective(line, &i)) {
            if (i == strlen(line)) {
                printError("No directive name entered");
                continue;
            }

            readNextWord(word, line, &i, sizeof(word));

            if (isDataDirective(word) || isStringDirective(word)) {
                if (labelFlag)
                    addLabel(labelName, "data", dataCounter+RESERVED_SPACE, symbolTable);

                if (isDataDirective(word))
                    addIntArray(line, &i, dataArray);
                else
                    addString(line, &i, dataArray);
            }

            else if (isExternDirective(word)) {
                if (labelFlag) printError("Cannot label a .extern directive");
                readNextWord(word, line, &i, sizeof(word));
                isUniqueLabelName(word, *symbolTable);
                addLabel(word, "external", 0, symbolTable);
            }

            else if (isEntryDirective(word))
                continue;
            else
                printError("unknown directive");
        }

        else { /* line is not a directive */
            if (labelFlag)
                addLabel(labelName, "code", instructionCounter+RESERVED_SPACE, symbolTable);

            readNextWord(word, line, &i, sizeof(word));

            if ((r=isInstruction(word)))
                addInstruction(line, &i, --r, instructionArray);
            else
                printError("unknown command");
        }
    }
    if (dataCounter + instructionCounter > MAX_MEMORY)
        printError("maximum memory exceeded");
}

