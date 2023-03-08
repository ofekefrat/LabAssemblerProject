#ifndef io_h
#define io_h

#include "../../root.h"

Node* isSpread(List, const char*);
int isDef(const char*);

int hasLabel(const char* line);
int readLabelName(char* buffer, int* ind, const char* line);

int isInstruction(const char* word, char** ops);
int isDirective(const char* line, int* ind);
int isDataDirective(const char* word);
int isStringDirective(const char* word);
int isExternDirective(const char* word);
int isEntryDirective(const char* word);

void readNextOperand(const char *line, int *ind, char* operand);
int stillInWord(const char* line, const int* ind);
int isRegisterOperand(const char* operand);

void readNextNumber(const char* line, int* ind, int* pInt);
int verifyComma(const char* line, int* ind);

void printError(const char* str);
void skipWhiteSpaces(const char* line, int* ind);

extern int lineCount;

#endif //io_h
