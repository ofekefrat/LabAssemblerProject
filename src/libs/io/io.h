#ifndef io_h
#define io_h

#include "../../root.h"
#define RESERVED_SPACE 100
#define NUM_OF_OPCODES 16
#define ADDRESS_PRINT_LENGTH (4+1)
#define WORD_STR_LENGTH (WORD_LENGTH+1)

/* pre-assembly */
/* isSpread: returns a pointer to a macro if the current line is attempting to spread it, and NULL otherwise. */
Node* isSpread(List, const char*, char* buff);

/* isDef: returns 1 if the line is attempting to define a new macro, and 0 otherwise.*/
int isDef(const char*);

/* isEndmcr: returns 1 if the line is "endmcr", and 0 otherwise */
int isEndmcr(const char* line);

/* getMacroName: read the name of the macro attempting to be defined and copy it to buffer */
void getMacroName(const char* defLine, char* buffer);

/* label related */
/* hasLabel: check if the current line defines a new label.*/
int hasLabel(const char* line);

/* readLabelName: read the label name that the line is attempting to define.*/
int readLabelName(char* buffer, int* ind, const char* line);

/* assembly*/
/* isInstruction: if the line contains an instruction, returns its index in the opcodes array, and 0 otherwise.*/
int isInstruction(const char* word);

/* isDirective: returns 1 if the current line contains a possible directive, and 0 otherwise.*/
int isDirective(const char* line, int* ind);

/* isDataDirective: returns 1 if the directive in the line is the data directive, and 0 otherwise.*/
int isDataDirective(const char* word);

/* isStringDirective: returns 1 if the directive in the line is the string directive, and 0 otherwise.*/
int isStringDirective(const char* word);

/* isExternDirective: returns 1 if the directive in the line is the extern directive, and 0 otherwise.*/
int isExternDirective(const char* word);

/* isEntryDirective: returns 1 if the directive in the line is the entry directive, and 0 otherwise.*/
int isEntryDirective(const char* word);

/* readNextOperand: read the next operand from the current line.*/
void readNextOperand(const char *line, int *ind, char* operand, size_t size);

/* stillInWord: returns 1 if no separating characters are detected at the index, in the line,  and 0 otherwise.*/
int stillInWord(const char* line, int i);

/* isRegisterOperand: returns 1 if the given operand is a register, and 0 otherwise.*/
int isRegisterOperand(const char* operand);

/* isJumpOperand: returns 1 if the given operand is a jump operand (method 2), and 0 otherwise.*/
int isJumpOperand(const char* line, int i);

/* checkWhiteChar: for usage where white characters aren't supposed to be found, report an error if
 * a white character is at the index */
void checkWhiteChar(const char* line, int i);

/* readNextNumber: read the next number from the line, starting at the given index.*/
int readNextNumber(const char* line, int* ind);

/* verifyComma: verify whether a (necessary) comma is present and returns 1 if it is,
 * otherwise reports an error and returns 0.*/
int verifyComma(const char* line, int* ind);

/* printError: prints the given error message preceded by the line number (from lineCount),
 * and updates the error indicator*/
void printError(const char* str);

/* skipWhiteSpaces: updates the index to skip all white characters. */
void skipWhiteSpaces(const char* line, int* ind);

/* skipLabel: updates the index to skip the label name and the colon after it. */
void skipLabel(const char* line, int* ind);

/* skipWord: updates the index to skip the next word from the line. */
void skipWord(const char* line, int* ind);

/* readNextWord: read the next word in line from the index, and save the result in the given buffer.*/
void readNextWord(char* buffer, const char* line, int* ind, size_t size);

/* binTranslator: translate the number from decimal to base 2 and save the result in the given buffer. */
void binTranslator(unsigned int num, char* buffer);

/* reverseWord: reverse the given string. */
void reverseWord(char* buff);

/* makeObLine: produce the required line for the object file. */
void makeObLine(Word word, int i, char* newLine);

#endif
