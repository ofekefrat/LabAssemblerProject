#include "assembly.h"

void addInstruction(const char* line, int* ind, int opcode, Cell** instructionArray) {
    Cell sourceOperand, destOperand, instruction;
    Cell* sentinel = NULL;
    int i=*ind;
    instruction.value = opcode << OPCODE_POS;

    skipWhiteSpaces(line, &i);
    if ((opcode >= mov && opcode <= sub) || opcode == lea) {
        if ((sentinel = getSourceOperand(line, &i, opcode, &instruction)) != NULL) {
            sourceOperand = *sentinel;
        }
    }

}

Cell* getSourceOperand(const char* line, int* ind, int opcode, Cell* instruction) {
    int i = *ind;
    Cell sourceOperand;
    Cell regWord1, regWord2;
    int regNum;

    int* pInt = NULL;
    if (line[i] == '#') {
        if (opcode == lea) {
            printError("Illegal operand for operation");
            return NULL;
        }
        else { /* not lea */
            readNextNumber(line, &i, pInt);
            if (!verifyComma(line, &i)) return NULL;
            else { /* comma is there */
                if (pInt != NULL) {
                    if (*pInt < (1 << 15))
                        sourceOperand.value = *pInt; /* no modifications needed for instruction word */
                    else printError("number is too big");
                }
                else return NULL;
            }
        }
    }
    else if (line[i] == 'r') {
        if (i+2 >= strlen(line)) {
            printError("not enough operands");
            return NULL;
        }
        if (isdigit(line[++i])) {
            i++;
            if (line[i] == ' ' || line[i] == '\t' || line[i] == ',') {
                regNum = (int) line[i-1] - '0';

            }
        }
    }
}


