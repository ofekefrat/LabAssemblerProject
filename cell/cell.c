/* shit for cells */

#include "cell.h"

cell createCell(int value) {

    cell temp;
    temp.value = value;

    return temp;
}

cell getCellCopy(pCell target) {

    cell temp;

    if (target == NULL) {
        printf("getCellCopy received a null pointer\n");
        exit(0);
    }

    temp.value = target->value;
    return temp;
}

int cellEquals(pCell c1, pCell c2) {

    if (c1 == NULL || c2 == NULL) {
        printf("cellEquals received a null pointer\n");
        exit(0);
    }

    return (c1->value == c2->value);
}

