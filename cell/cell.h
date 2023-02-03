#ifndef LABASSEMBLERPROJECT_CELL_H
#define LABASSEMBLERPROJECT_CELL_H

#include "../libraries.h"

#define CELL_SIZE 14


/* STRUCTURES */

typedef struct cell {
    int value : CELL_SIZE;
}cell;

typedef struct cell* pCell;


/* METHODS */

cell getEmptyCell();
cell getCellCopy(pCell);
cell setBit(pCell,int);
int cellEquals(pCell,pCell);

#endif
