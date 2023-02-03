#ifndef LABASSEMBLERPROJECT_CELL_H
#define LABASSEMBLERPROJECT_CELL_H

#include "../main.h"

#define CELL_SIZE 14

struct bit {
    unsigned int value : 1;
};

typedef struct cell {
    struct bit bits[CELL_SIZE];
}cell;

typedef struct cell* pCell;

cell getEmptyCell();
cell getCellCopy(pCell);
cell setBit(pCell,int);


#endif
