#include "main.h"


int main(int argc, char** argv) {
    int fileCount;
    FILE* source, *am; /* am: for the file returned from pre-assembly */
    char fileName[MAX_FILE_NAME];

    if (argc >= 2) {
        for (fileCount=1; fileCount < argc; fileCount++) {
            sprintf(fileName, "%s.as", argv[fileCount]);
            source = fopen(fileName, "r");
            if (source) {
                am = preAssemble(source, argv[fileCount]);
                fclose(source);
                compile(am, argv[fileCount]);
            }
            else
                printf("File pointer is null\n");
        }
    }
    else
        printf("not enough arguments\n");

    return 0;
}