#ifndef instruction_h
#define instruction_h

#include "../../root.h"
#define MAX_INSTRUCTIONS 666
#define NUM_OF_REGS 7
#define OPCODE_IND 6
#define SOURCE_AM_IND 4
#define DEST_AM_IND 2
#define INST_ERROR (1 << (WORD_LENGTH-1))

const char* ops[] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne",
               "red", "prn", "jsr", "rts", "stop"};

enum opcode {mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne,
    red, prn, jsr, rts, stop};

enum AddressingMethod {label=1, jump, reg};

enum LocationType {immediate, ext, reloc};


void addInstruction(const char *line, int *ind, int opcode, Word *instructionArray, Label **symbolTable, Label** externalSymbols);
Word getSourceOperand(const char* operand, int opcode, Word instruction, Label** symbolTable, Label** externalSymbols);
int twoOps(int opcode);

#endif //instruction_h
