/* shit for cells */

#include "cell.h"

cell getEmptyCell() { /* also for resetting */

    cell newCell;
    newCell.value = 0;
    return newCell;
}

cell getCellCopy(pCell target) {
    if (target == NULL) {
        printf("getCellCopy received a null pointer\n");
        exit(0);
    }

    cell temp;
    temp.value = target->value;
    return temp;
}

cell setBit(pCell target, int bit) {
    if (target == NULL) {
        printf("setBit received a null pointer\n");
        exit(0);
    }

    if (bit < 0 || bit > CELL_SIZE-1) {
        printf("bit out of range (1-13)\n");
        exit(0);
    }

    cell temp = getCellCopy(target);
    temp.value |= 1 << bit;

    free(target);
    return temp;
}

int cellEquals(pCell c1, pCell c2) {
    if (c1 == NULL || c2 == NULL) {
        printf("cellEquals received a null pointer\n");
        exit(0);
    }

    return (c1->value == c2->value);
}

