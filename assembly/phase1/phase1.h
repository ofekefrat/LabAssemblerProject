#ifndef phase_1
#define phase_1

#include "../../libraries.h"
#include "../assembly.h"

int hasLabel(const char* line);
int isInstruction(const char* line, int* ind);
int isDirective(const char* line, int* ind);
int isDataDirective(const char* word);
int isStringDirective(const char* word);
int isExternDirective(const char* word);
int isEntryDirective(const char* word);

void getLabelName(char* buffer, int* ind, const char* line);
void addLabel(const char* name, const char* type, Label** labels);
void printError(const char* str);


extern int error;
extern int lineCount;

#endif //phase_1
