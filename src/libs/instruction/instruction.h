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

enum AddressingMethod {label=1, jump, reg};

enum LocationType {immediate, ext, reloc}; /*A,R,E*/

/* addInstruction: add an instruction to the memory image. */
void addInstruction(const char *line, int *ind, int opcode, Word *instructionArray);

/* getSourceOperand: handle the coding of the source operand in the instruction. returns the resulting word.*/
Word getSourceOperand(const char* operand, int opcode, Word* instruction);

/* getDestOperand: handle the coding of the destination operand in the instruction. returns the resulting word.*/
Word getDestOperand(const char* operand, int opcode, Word* instruction);

/* completeInstruction: in the second phase of assembly, complete any empty labels mentioned in this line in phase 1.*/
void completeInstruction(const char* line,
                         int* ind,
                         Word* instructionArray,
                         List* symbolTable,
                         List* externalSymbols);

/* isJumper: returns 1 if the given opcode represents an operation that is able to receive a jump operand,
 * and 0 otherwise.*/
int isJumper(int opcode);

/* labelOp: handle a label operand: if the label exists, return the resulting word.
 * otherwise, report an error and return a "MISSING_LABEL" word. */
Word labelOp(const char* operand, List* symbolTable, List* externalSymbols);

/* immediateOp: handle an immediate operand. return the resulting word. */
Word immediateOp(const char* operand, int* ind);

/* twoOps: returns 1 if the opcode represents an operations requiring two operands, and 0 otherwise.*/
int twoOps(int opcode);

#endif
