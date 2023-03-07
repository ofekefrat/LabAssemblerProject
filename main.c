#include "main.h"

// DON'T FORGET TO CLOSE THE ORIGINAL UNEDITED SOURCE FILE BEFORE ASSEMBLY

int main(int argc, char** argv) {
    int fileCount;
    FILE* source, *am, *ob;
    char fileName[MAX_FILE_NAME];
    printf("Program starts\n");

    if (argc >= 2) printf("File name: %s\n", argv[1]);
    else printf("Problem with argument\n");

    for (fileCount=1; fileCount < argc; fileCount++) {
        sprintf(fileName, "%s.as", argv[fileCount]);
        source = fopen(fileName, "r");
        if (source == NULL) printf("File pointer is null\n");

        am = preAssemble(source, argv[fileCount]);
        fclose(source);


    }

    return 0;
}