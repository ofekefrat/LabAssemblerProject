#ifndef assembly_h
#define assembly_h

#include "../libraries.h"
#define MAX_LABEL_LENGTH 30 /* not including colon */
#define MAX_TYPE_LENGTH 9
#define MAX_DATA 666
#define MAX_INT_ARRAY 666
#define MAX_LABELS 666
#define MAX_STR_LENGTH 666
#define NO_ADDRESS 404


extern int dataCounter, instructionCounter;

union value {
    int* arr;
    char* str;
};

typedef struct Data {
    union value val;
}Data;

typedef struct Label {
    char name[MAX_LABEL_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int address;
}Label;


Data* newData(union value val);
Data* addIntArray(char* line, int* ind, Data** data);
Data* addString(char* line, int* ind, Data** data);
void addDataToTable(Data* value, Data** data);


#endif //assembly_h
