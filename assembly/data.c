#include "assembly.h"

Data* newData(union value val) {
    Data* temp = (Data*) malloc(sizeof(Data));

    Data new;
    new.val = val;

    *temp = new;
    return temp;
}

Data* addIntArray(char* line, int* ind, Data** dataTable) {
    int arr[MAX_INT_ARRAY];

    union value val;
    val.arr = arr;
//    dataCounter +=
    addDataToTable(newData(val), dataTable);
}

Data* addString(char* line, int* ind, Data** dataTable) {
    char str[MAX_STR_LENGTH];

    union value val;
    val.str = str;
    addDataToTable(newData(val), dataTable);
}

void addDataToTable(Data* value, Data** dataTable) {
    int i=0;
    while(dataTable[i] != NULL) i++;
    dataTable[i] = value;
}
