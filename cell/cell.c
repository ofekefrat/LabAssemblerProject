/* shit for cells */

#include "cell.h"

cell getEmptyCell() { /* also for resetting */
    int i;
    cell newCell;

    for (i = 0; i < CELL_SIZE; i++)
        newCell.bits[i].value = 0;

    return newCell;
}

cell getCellCopy(pCell target) {
    int i;

    cell temp = getEmptyCell();
    for (i = 0; i < CELL_SIZE; i++)
        if (target->bits[i].value)
            temp.bits[i].value = 1;

    if (target != NULL) free(target);
    return temp;
}

cell setBit(pCell target, int bit) {

    cell temp = getCellCopy(target);
    if (!(target->bits[bit].value))
        temp.bits[bit].value = 1;

    if (target != NULL) free(target);
    return temp;
}



int cellEquals(pCell c1, pCell c2);

