#include "instruction.h"

/* TODO clear up jmp-like operand reception */

void addInstruction(const char *line,
                    int *ind,
                    int opcode,
                    Word* instructionArray) {

    Word sourceOperand, destOperand, jmpLabelOperand, instruction;
    char operand1[MAX_LABEL_LENGTH], operand2[MAX_LABEL_LENGTH], operand0[MAX_LABEL_LENGTH];
    int i = *ind;
    int regSrc = reg << SOURCE_AM_IND , regDest = reg << DEST_AM_IND
            , regPar1 = reg << PAR1_IND, regPar2 = reg << PAR2_IND;

    jmpLabelOperand.value = INST_ERROR;
    sourceOperand.value = INST_ERROR;
    destOperand.value = INST_ERROR;

    memset(operand1, 0, MAX_LABEL_LENGTH);
    memset(operand2, 0, MAX_LABEL_LENGTH);
    memset(operand0, 0, MAX_LABEL_LENGTH);

    instruction.value = opcode << OPCODE_IND;

    if (isJumper(opcode)) {
        skipWhiteSpaces(line, &i);
        if ((isJumpOperand(line, i))) {
            instruction.value |= jump << DEST_AM_IND;
            jmpLabelOperand.value = MISSING_LABEL;
            while (stillInWord(line, i) && line[i] != '(') {
                checkWhiteChar(line, i);
                i++;
            }
            i++;
            checkWhiteChar(line, i);

            readNextOperand(line, &i, operand1);
            sourceOperand = getSourceOperand(operand1, opcode, &instruction);

            checkWhiteChar(line, i);
            if (!verifyComma(line, &i))
                printError("Missing comma");

            checkWhiteChar(line, i);
            readNextOperand(line, &i, operand2);
            destOperand = getDestOperand(operand2, opcode+stop, &instruction);
            checkWhiteChar(line, i);
            skipWhiteSpaces(line, &i);
            if (line[i] != ')') printError("Missing closing bracket");
        }
        else {
            readNextOperand(line, &i, operand2);
            destOperand = getDestOperand(operand2, opcode, &instruction);
        }

        if ((instruction.value & regPar2) == regPar2) {
            destOperand.value = immediate;
            destOperand.value |= (operand2[1] - '0') << DEST_AM_IND;
            if ((instruction.value & regPar1) == regPar1) {
                destOperand.value |= (operand1[1] - '0') << (DEST_AM_IND+6);
            }
        }
        else if ((instruction.value & regPar1) == regPar1) {
            sourceOperand.value = immediate;
            sourceOperand.value |= (operand1[1] - '0') << (DEST_AM_IND+6);
        }
    }
    else {
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

    }

    *ind = i;
    instructionArray[instructionCounter++] = instruction;

    if (isJumper(opcode)) {
        if (jmpLabelOperand.value != INST_ERROR)
            instructionArray[instructionCounter++] = jmpLabelOperand;
    }

    if (twoOps(opcode) || isJumper(opcode)) {
        if (sourceOperand.value != INST_ERROR)
            instructionArray[instructionCounter++] = sourceOperand;
    }

    if (opcode < rts) {
        if (destOperand.value != INST_ERROR)
            instructionArray[instructionCounter++] = destOperand;
    }
}

void completeInstruction(const char* line, int* ind, Word* instructionArray, List* symbolTable, List* externalSymbols) {
    char operand[MAX_LABEL_LENGTH], operand2[MAX_LABEL_LENGTH];
    Word instruction, *currentOperand;
    int i = *ind, j=0, opcode, r;

    instruction = instructionArray[instructionCounter++];

    opcode = (instruction.value & (FULL_OPCODE_BITS << OPCODE_IND)) >> OPCODE_IND;
    if (opcode >= rts) return;

    currentOperand = &instructionArray[instructionCounter++];

    memset(operand, 0, MAX_LABEL_LENGTH);

    skipWhiteSpaces(line, &i);
    skipWord(line, &i);        /* skipping the operation field */
    skipWhiteSpaces(line, &i);

    if (isJumper(opcode)) {
        if ((r=isJumpOperand(line, i))) {
            skipWhiteSpaces(line, &i);
            while (stillInWord(line, i) && line[i] != '(') {
                operand[j++] = line[i++];
            }
            i++;
            *currentOperand = labelOp(operand, symbolTable, externalSymbols);
            currentOperand = &instructionArray[instructionCounter++];
            memset(operand, 0, MAX_LABEL_LENGTH);
        }
    }

    skipWhiteSpaces(line, &i);
    readNextOperand(line, &i, operand);

    if ((currentOperand->value & MISSING_LABEL) == MISSING_LABEL) {
        *currentOperand = labelOp(operand, symbolTable, externalSymbols);
    }

    if (twoOps(opcode) || r) {
        verifyComma(line, &i);
        memset(operand2, 0, MAX_LABEL_LENGTH);
        readNextOperand(line, &i, operand2);
        if (!(isRegisterOperand(operand) && isRegisterOperand(operand2))) {
            currentOperand = &instructionArray[instructionCounter++];
            if ((currentOperand->value & MISSING_LABEL) == MISSING_LABEL)
                *currentOperand = labelOp(operand2, symbolTable, externalSymbols);
        }
    }
    *ind = i;
}

int twoOps(int opcode) {
    return ((opcode >= mov && opcode <= sub) || opcode == lea);
}

Word getSourceOperand(const char* operand, int opcode, Word* instruction) {
    Word sourceOperand = { INST_ERROR };
    int i=1, r; /* it's disgusting and get rid of it, you know what you did*/

    if (operand[0] == 0) /* no operands */
        printError("not enough operands");

    /* immediate number operand */
    else if (operand[0] == '#')
        if (opcode == lea)
            printError("Illegal operand for operation");
        else
            sourceOperand = immediateOp(operand, &i);

        /* register operand */
    else if ((isRegisterOperand(operand)))
        if (opcode == lea)
            printError("Illegal operand for operation");
        else {
            r = operand[1] - '0';
            if (r > 0 && r <= NUM_OF_REGS) {
                if (isJumper(opcode))
                    instruction->value |= reg << PAR1_IND;
                else
                    instruction->value |= reg << SOURCE_AM_IND;
            }
            else {
                printError("non-existent register");
            }
        }

    else {
        if (isJumper(opcode))
            instruction->value |= label << PAR1_IND;
        else
            instruction->value |= label << SOURCE_AM_IND;

        sourceOperand.value = MISSING_LABEL;
    }

    return sourceOperand;
}

int isJumper(int opcode) {
    return (opcode == bne || opcode == jmp || opcode == jsr);
}

Word getDestOperand(const char* operand, int opcode, Word* instruction) {
    Word destOperand = { INST_ERROR };

    int i=1, r; /* it's disgusting and get rid of it, you know what you did*/

    if (operand[0] == 0) /* no operands */
        printError("not enough operands");

    /* immediate number */
    else if (operand[0] == '#')
        if (opcode == cmp || opcode == prn)
            destOperand = immediateOp(operand, &i);
        else
            printError("Illegal operand for operation");

    else if (isRegisterOperand(operand)) {
        r = operand[1] - '0';
        if (r > 0 && r <= NUM_OF_REGS) {
            if (opcode > stop)
                instruction->value |= reg << PAR2_IND;
            else
                instruction->value |= reg << DEST_AM_IND;

        }
        else {
            printError("non-existent register");
        }
    }

    /* label */
    else  {
        if (opcode > stop)
            instruction->value |= label << PAR2_IND;
        else
            instruction->value |= label << DEST_AM_IND;

        destOperand.value = MISSING_LABEL;
    }

    return destOperand;
}

Word immediateOp(const char* operand, int* ind) {
    Word operandWord = { INST_ERROR };
    int num = readNextNumber(operand, ind);
    if (num != INT_MIN) {
        if (num < (1 << (WORD_LENGTH-2))) {
            operandWord.value = immediate;
            operandWord.value |= (num << 2);
        }
        else printError("number is too big");
    }
    return operandWord;
}

Word labelOp(const char* operand, List* symbolTable, List* externalSymbols) {
    Word operandWord;
    Item temp;

    Label* pLabel = getLabel(operand, *symbolTable);

    if (pLabel != NULL) {
        if (!strcmp(pLabel->type, "external")) {
            operandWord.value = ext;

            temp.label = *pLabel;
            addToList(externalSymbols, newNode(temp));
        }
        else {
            operandWord.value = reloc;
            operandWord.value |= pLabel->value << 2;
        }
    }
    else
        operandWord.value = MISSING_LABEL;

    return operandWord;
}



