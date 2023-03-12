#ifndef io_h
#define io_h

#include "../../root.h"
#define RESERVED_SPACE 100
#define NUM_OF_OPCODES 16
#define ADDRESS_PRINT_LENGTH (4+1)
#define WORD_STR_LENGTH (WORD_LENGTH+1)

Node* isSpread(List, const char*, char* buff);
int isDef(const char*);

int hasLabel(const char* line);
int readLabelName(char* buffer, int* ind, const char* line);

int isInstruction(const char* word);
int isDirective(const char* line, int* ind);
int isDataDirective(const char* word);
int isStringDirective(const char* word);
int isExternDirective(const char* word);
int isEntryDirective(const char* word);

void readNextOperand(const char *line, int *ind, char* operand);
int stillInWord(const char* line, int i);
int isRegisterOperand(const char* operand);
int isJumpOperand(const char* line, int i);
void checkWhiteChar(const char* line, int i);

int readNextNumber(const char* line, int* ind);
int verifyComma(const char* line, int* ind);

void printError(const char* str);
void skipWhiteSpaces(const char* line, int* ind);
int skipLabel(const char* line, int* ind);
void skipWord(const char* line, int* ind);
void readNextWord(char* buffer, const char* line, int* ind);

void binTranslator(unsigned int num, char* buff);
void reverseWord(char* buff);
void makeObFile(FILE* file, Word* instructionArray, Word* dataArray);
void makeObLine(Word word, int i, char* newLine);
void printFileContent(FILE*);

#endif
