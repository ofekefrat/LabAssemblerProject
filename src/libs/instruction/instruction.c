#include "instruction.h"

/*TODO Addressing method 2*/
/*TODO non-existent register*/

/* look for SOURCE/OPERAND AM (respectively) in first instruction word to fill in blanks*/
void addInstruction(const char *line,
                    int *ind,
                    int opcode,
                    Word* instructionArray) {

    Word sourceOperand, destOperand, instruction;
    char operand1[MAX_LABEL_LENGTH], operand2[MAX_LABEL_LENGTH];
    int i = *ind, regSrc = reg << SOURCE_AM_IND , regDest = reg << DEST_AM_IND;

    sourceOperand.value = INST_ERROR;
    destOperand.value = INST_ERROR;

    memset(operand1, 0, MAX_LABEL_LENGTH);
    memset(operand2, 0, MAX_LABEL_LENGTH);

    instruction.value = opcode << OPCODE_IND;

    /* source operand */
    if (twoOps(opcode)) {
        skipWhiteSpaces(line, &i);
        readNextOperand(line, &i, operand1);
        sourceOperand = getSourceOperand(operand1, opcode, &instruction);

        if (!verifyComma(line, &i)) {
            printError("Missing comma");
        }
    }

    /* destination operand */
    if (opcode < rts) {
        skipWhiteSpaces(line, &i);
        readNextOperand(line, &i, operand2);
        destOperand = getDestOperand(operand2, opcode, &instruction);
    }

    if ((instruction.value & regDest) == regDest) {
        destOperand.value = immediate;
        destOperand.value |= (operand2[1] - '0') << DEST_AM_IND;
        if ((instruction.value & regSrc) == regSrc) {
            destOperand.value |= (operand1[1] - '0') << (DEST_AM_IND+6);
        }
    }
    else if ((instruction.value & regSrc) == regSrc) {
        sourceOperand.value = immediate;
        sourceOperand.value |= (operand1[1] - '0') << (DEST_AM_IND+6);
    }

    *ind = i;
    instructionArray[instructionCounter++] = instruction;

    if (twoOps(opcode)) {
        if (sourceOperand.value == INST_ERROR) return;
        instructionArray[instructionCounter++] = sourceOperand;
    }

    if (opcode < rts) {
        if (destOperand.value == INST_ERROR) return;
        instructionArray[instructionCounter++] = destOperand;
    }
}

void completeInstruction(const char* line, int* ind, Word* instructionArray, List* symbolTable, List* externalSymbols) {
    char operand[MAX_LABEL_LENGTH];
    Word instruction, *currentOperand;
    int i = *ind;

    instruction = instructionArray[instructionCounter];

    if (!labelsInInstruction(instruction)) return;

    currentOperand = &instructionArray[++instructionCounter];

    memset(operand, 0, MAX_LABEL_LENGTH);

    skipWhiteSpaces(line, &i);
    readNextOperand(line, &i, operand);
    if ((currentOperand->value & MISSING_LABEL) == MISSING_LABEL)
        *currentOperand = labelOp(operand, symbolTable, externalSymbols);

    if (twoOps(instruction.value & 15 << OPCODE_IND)) {
        currentOperand = &instructionArray[++instructionCounter];
        if ((currentOperand->value & MISSING_LABEL) == MISSING_LABEL) {
            memset(operand, 0, MAX_LABEL_LENGTH);
            verifyComma(line, &i);
            readNextOperand(line, &i, operand);
            labelOp(operand, symbolTable, externalSymbols);
            *currentOperand = labelOp(operand, symbolTable, externalSymbols);
        }
    }
    *ind = i;
}

int labelsInInstruction(Word instruction) {
    int res=0;
    if ((instruction.value & rts << OPCODE_IND) == rts << OPCODE_IND
    ||  (instruction.value & stop << OPCODE_IND) == stop << OPCODE_IND ) return 0;

    res += ((instruction.value & label << SOURCE_AM_IND) == label << SOURCE_AM_IND);
    res += ((instruction.value & label << DEST_AM_IND) == label << DEST_AM_IND);
    return res;
}

int twoOps(int opcode) {
    return ((opcode >= mov && opcode <= sub) || opcode == lea);
}

Word getSourceOperand(const char* operand, int opcode, Word* instruction) {
    Word sourceOperand = { INST_ERROR };
    int r, i=1; /* it's disgusting and get rid of it, you know what you did*/

    if (operand[0] == 0) /* no operands */
        printError("not enough operands");

    /* immediate number operand */
    else if (operand[0] == '#')
        if (opcode == lea)
            printError("Illegal operand for operation");
        else
            sourceOperand = immediateOp(operand, &i);

        /* register operand */
    else if ((r=isRegisterOperand(operand)))
        if (opcode == lea)
            printError("Illegal operand for operation");
        else {
            if (r > 0 && r <= NUM_OF_REGS)
                instruction->value |= reg << SOURCE_AM_IND;
        }

        /* ADDRESSING METHOD 2? */
/*        else if () {}*/

        /* label operand */
    else {
        instruction->value |= label << SOURCE_AM_IND;
        sourceOperand.value = MISSING_LABEL;
    }

    return sourceOperand;
}

Word getDestOperand(const char* operand, int opcode, Word* instruction) {
    Word destOperand = { INST_ERROR };

    int i=1; /* it's disgusting and get rid of it, you know what you did*/

    if (operand[0] == 0) /* no operands */
        printError("not enough operands");

    /* immediate number */
    else if (operand[0] == '#')
        if (opcode == cmp || opcode == prn)
            destOperand = immediateOp(operand, &i);
        else
            printError("Illegal operand for operation");

    else if (isRegisterOperand(operand))
        instruction->value |= reg << DEST_AM_IND;

        /* address method 2*/
/*        else if()*/

    /* label */
    else  {
        instruction->value |= label << DEST_AM_IND;
        destOperand.value = MISSING_LABEL;
    }

    return destOperand;
}

Word immediateOp(const char* operand, int* ind) {
    Word sourceOperand = { INST_ERROR };
    int num = readNextNumber(operand, ind);
    if (num != INT_MIN) {
        if (num < (1 << (WORD_LENGTH-2))) {
            sourceOperand.value = immediate;
            sourceOperand.value |= num;
        }
        else printError("number is too big");
    }
    return sourceOperand;
}

Word labelOp(const char* operand, List* symbolTable, List* externalSymbols) {
    Word sourceOperand;
    Item temp;

    Label* pLabel = getLabel(operand, *symbolTable);

    if (pLabel != NULL) {
        if (!strcmp(pLabel->type, "external")) {
            sourceOperand.value = ext;

            temp.label = *pLabel;
            addToList(externalSymbols, newNode(temp));
        }
        else {
            sourceOperand.value = reloc;
        }
        sourceOperand.value |= pLabel->value << 2;
    }
    else
        sourceOperand.value = MISSING_LABEL;

    return sourceOperand;
}



