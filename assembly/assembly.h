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
#define OPCODE_POS 6
#define MAX_STR_LENGTH 666
#define NO_ADDRESS 404
extern int dataCounter, instructionCounter;

enum opcode {mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne,
    red, prn, jsr, rts, stop};

typedef struct Cell {
    int value : 14;
}Cell;

typedef struct Label {
    char name[MAX_LABEL_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int value;
}Label;

FILE* phase1(FILE* source,
            Cell* dataArray,
            Cell* instructionArray,
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
void addInstruction(const char* line, int* ind, int opcode, Cell** instructionArray);
Cell* getSourceOperand(const char* line, int* ind, int opcode, Cell* instruction);
Cell* getDestOperand(const char* line, int* ind, int opcode, Cell* instruction);

void addIntArray(char* line, int* ind, Cell* dataArray);
void addString(char* line, int* ind, Cell* dataArray);
void insertNumber(char* digits, int* j, Cell* dataArray);
void resetDigitArray(char* arr, int* j);
void readNextNumber(const char* line, int* ind, int* pInt);
int verifyComma(const char* line, int* ind);

void printError(const char* str);
void skipWhiteSpaces(const char* line, int* ind);

Cell (*opFunc)(const char* line, int* ind);
#endif //assembly_h
