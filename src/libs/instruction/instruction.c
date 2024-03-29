#include "instruction.h"


/* addInstruction: add an instruction to the memory image. */
void addInstruction(const char *line,
                    int *ind,
                    int opcode,
                    Word* instructionArray) {

    Word sourceOperand, destOperand, jmpLabelOperand, instruction;
    char operand1[MAX_LABEL_LENGTH], operand2[MAX_LABEL_LENGTH], operand0[MAX_LABEL_LENGTH];
    int i = *ind;
    const int regSrc = reg << SOURCE_AM_IND , regDest = reg << DEST_AM_IND
            , regPar1 = reg << PAR1_IND, regPar2 = reg << PAR2_IND; /* constants for clearer code */

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

            readNextOperand(line, &i, operand1, sizeof(operand1));
            sourceOperand = getSourceOperand(operand1, opcode, &instruction);

            checkWhiteChar(line, i);
            verifyComma(line, &i);

            checkWhiteChar(line, i);
            readNextOperand(line, &i, operand2, sizeof(operand2));
            destOperand = getDestOperand(operand2, opcode+stop, &instruction);
            checkWhiteChar(line, i);
            skipWhiteSpaces(line, &i);
            if (i < strlen(line)) {
                if (line[i] != ')')
                    printError("Missing closing bracket");
                else
                    i++;
            }
        }
        else {
            readNextOperand(line, &i, operand2, sizeof(operand2));
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
            readNextOperand(line, &i, operand1, sizeof(operand1));
            sourceOperand = getSourceOperand(operand1, opcode, &instruction);

            verifyComma(line, &i);
        }

        /* destination operand */
        if (opcode < rts) {
            skipWhiteSpaces(line, &i);
            readNextOperand(line, &i, operand2, sizeof(operand2));
            destOperand = getDestOperand(operand2, opcode, &instruction);
        }

        skipWhiteSpaces(line, &i);
        if (i < strlen(line) && line[i] != '\n')
            printError("Too many operands for this instruction");

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

/* completeInstruction: in the second phase of assembly, complete any empty labels mentioned in this line in phase 1.*/
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
    readNextOperand(line, &i, operand, sizeof(operand));

    if ((currentOperand->value & MISSING_LABEL) == MISSING_LABEL) {
        *currentOperand = labelOp(operand, symbolTable, externalSymbols);
    }

    if (twoOps(opcode) || r) {
        verifyComma(line, &i);
        memset(operand2, 0, MAX_LABEL_LENGTH);
        readNextOperand(line, &i, operand2, sizeof(operand2));
        if (!(isRegisterOperand(operand) && isRegisterOperand(operand2))) {
            currentOperand = &instructionArray[instructionCounter++];
            if ((currentOperand->value & MISSING_LABEL) == MISSING_LABEL)
                *currentOperand = labelOp(operand2, symbolTable, externalSymbols);
        }
    }
    *ind = i;
}

/* twoOps: returns 1 if the opcode represents an operations requiring two operands, and 0 otherwise.*/
int twoOps(int opcode) {
    return ((opcode >= mov && opcode <= sub) || opcode == lea);
}

/* getSourceOperand: handle the coding of the source operand in the instruction. returns the resulting word.*/
Word getSourceOperand(const char* operand, int opcode, Word* instruction) {
    Word sourceOperand = { INST_ERROR };
    int i=1, r;

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
            if (r >= 0 && r <= NUM_OF_REGS) {
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

/* isJumper: returns 1 if the given opcode represents an operation that is able to receive a jump operand,
 * and 0 otherwise.*/
int isJumper(int opcode) {
    return (opcode == bne || opcode == jmp || opcode == jsr);
}


/* getDestOperand: handle the coding of the destination operand in the instruction. returns the resulting word.*/
Word getDestOperand(const char* operand, int opcode, Word* instruction) {
    Word destOperand = { INST_ERROR };

    int i=1, r;

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
        if (r >= 0 && r <= NUM_OF_REGS) {
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

/* immediateOp: handle an immediate operand. return the resulting word. */
Word immediateOp(const char* operand, int* ind) {
    Word operandWord = { INST_ERROR };
    int num;

    if (*ind >= strlen(operand) || operand[*ind] == '\n') {
        printError("missing number after #");
        return operandWord;
    }

    num = readNextNumber(operand, ind);
    if (num != INT_MIN) {
        if (num < (1 << (WORD_LENGTH-2)) && num > (-(1 << (WORD_LENGTH-2)))) {
            operandWord.value = immediate;
            operandWord.value |= (num << 2);
        }
        else printError("number is too big");
    }
    return operandWord;
}

/* labelOp: handle a label operand: if the label exists, return the resulting word.
 * otherwise, report an error and return a "MISSING_LABEL" word. */
Word labelOp(const char* operand, List* symbolTable, List* externalSymbols) {
    Word operandWord;
    Item temp;

    Label* pLabel = getLabel(operand, *symbolTable);

    if (pLabel != NULL) {
        if (!strcmp(pLabel->type, "external")) {
            operandWord.value = ext;

            temp.label = *pLabel;
            temp.label.value = instructionCounter-1 + RESERVED_SPACE;
            addToList(externalSymbols, newNode(temp));
        }
        else {
            operandWord.value = reloc;
            operandWord.value |= pLabel->value << 2;
        }
    }
    else {
        printError("Usage of undefined label");
        operandWord.value = MISSING_LABEL;
    }

    return operandWord;
}
