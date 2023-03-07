#ifndef assembly_h
#define assembly_h

#include "../libraries.h"
#define MAX_LABEL_LENGTH 30 /* not including colon */
#define MAX_TYPE_LENGTH 9
#define MAX_DATA 666
#define MAX_LABELS 666
#define MAX_INSTRUCTIONS 666
#define RESERVED_SPACE 100
#define MAX_DIGITS 666
#define LABEL_ERROR (-1)
#define PRE_DEF_OPS 16
#define WORD_LENGTH 14
#define NUM_OF_REGS 7
#define OPCODE_IND 6
#define SOURCE_AM_IND 4
#define DEST_AM_IND 2
#define INST_ERROR (1 << (WORD_LENGTH-1))
extern int dataCounter, instructionCounter;

enum opcode {mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne,
    red, prn, jsr, rts, stop};

enum AddressingMethod {label=1, jump, reg};

enum LocationType {immediate, ext, reloc};

typedef struct Word {
    unsigned int value : WORD_LENGTH;
}Word;

typedef struct Label {
    char name[MAX_LABEL_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int value;
}Label;

FILE* phase1(FILE* source,
             Word* dataArray,
             Word* instructionArray,
             Label** symbolTable,
             Label** externalSymbols,
             Label** entrySymbols,
             char** ops);

int hasLabel(const char* line);
int isDirective(const char* line, int* ind);
int isDataDirective(const char* word);
int isStringDirective(const char* word);
int isExternDirective(const char* word);
int isEntryDirective(const char* word);

void addInstructionLabel(const char* name, Label** symbolTable);
Label* getLabel(const char* name, Label** symbolTable);

void addInstruction(const char *line, int *ind, int opcode, Word *instructionArray, Label **symbolTable, Label** externalSymbols);
Word getSourceOperand(const char* operand, int opcode, Word instruction, Label** symbolTable, Label** externalSymbols);
void readNextOperand(const char *line, int *ind, char* operand);
int stillInWord(const char* line, const int* ind);
int isRegisterOperand(const char* operand);
int twoOps(int opcode);

void addIntArray(char* line, int* ind, Word* dataArray);
void addString(char* line, int* ind, Word* dataArray);
void insertNumber(char* digits, int* j, Word* dataArray);
void resetDigitArray(char* arr, int* j);
void readNextNumber(const char* line, int* ind, int* pInt);
int verifyComma(const char* line, int* ind);

void printError(const char* str);
void skipWhiteSpaces(const char* line, int* ind);

#endif //assembly_h
