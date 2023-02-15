#ifndef cell_h
#define cell_h

#include "../libraries.h"

#define CELL_SIZE 14


/* STRUCTURES */

typedef struct cell {
    int value : CELL_SIZE;
}cell;

typedef struct cell* pCell;


/* METHODS */

cell createCell(int);
cell getCellCopy(pCell);
int cellEquals(pCell,pCell);

#endif
