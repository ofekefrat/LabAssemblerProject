#include "assembly.h"

// ERRORS:
//TODO confusion about cell size
//TODO unrecognized action
//TODO oger lo kayam
//TODO labels are defined no more than once

int dataCounter=0, instructionCounter=0;

FILE* assembly(FILE* source, const char* oldFileName) {
    char newFileName[MAX_FILE_NAME];
    FILE* objectFile, *postPhase1;
    Word memoryImage[MAX_DATA + MAX_INSTRUCTIONS + RESERVED_SPACE];
    Word dataArray[MAX_DATA];
    Word instructionArray[MAX_INSTRUCTIONS];

    List symbolTable = { NULL, NULL };
    List externalSymbols = { NULL, NULL };
    List entrySymbols = { NULL, NULL };



    sprintf(newFileName, "%s.ob", oldFileName);

    postPhase1 = phase1(source,
           dataArray,
           instructionArray,
           symbolTable,
           externalSymbols,
           entrySymbols,
           ops);

//    phase2(source,
//           dataArray,
//           instructionArray,
//           symbolTable,
//           externalSymbols,
//           entrySymbols);

    objectFile = fopen(newFileName, "w");

    if (error) {
        printf("Errors found, stopping..\n");
        exit(1);
    }
}