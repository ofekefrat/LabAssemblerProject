#ifndef instruction_h
#define instruction_h

#include "../../root.h"
#define MAX_INSTRUCTIONS 666
#define NUM_OF_REGS 7
#define OPCODE_IND 6
#define PAR1_IND 12
#define PAR2_IND 10
#define FULL_OPCODE_BITS 15
#define SOURCE_AM_IND 4
#define DEST_AM_IND 2
#define INST_ERROR 3
#define MISSING_LABEL (1 | (1 << 3))
#define OPCODES {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp", "bne", \
                    "red", "prn", "jsr", "rts", "stop"}

enum opcode {mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne,
    red, prn, jsr, rts, stop};

enum AddressingMethod {label=1, jump, reg=3};

enum LocationType {immediate, ext, reloc}; /*A,R,E*/

void addInstruction(const char *line, int *ind, int opcode, Word *instructionArray);
Word getSourceOperand(const char* operand, int opcode, Word* instruction);
Word getDestOperand(const char* operand, int opcode, Word* instruction);
void completeInstruction(const char* line,
                         int* ind,
                         Word* instructionArray,
                         List* symbolTable,
                         List* externalSymbols);

int isJumper(int opcode);
Word labelOp(const char* operand, List* symbolTable, List* externalSymbols);
Word immediateOp(const char* operand, int* ind);
int twoOps(int opcode);
int labelsInInstruction(Word instruction);

#endif
