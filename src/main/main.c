#include "main.h"

int lineCount=0; /* for error reporting */
char* currentFileName; /* the name of the current file being worked on */

int main(int argc, char** argv) {
    int fileCount;
    FILE* source, *am; /* am: for the file returned from pre-assembly */
    char* fileName = (char*) calloc(MAX_FILE_NAME, sizeof(char));

    if (argc >= 2) {
        for (fileCount=1; fileCount < argc; fileCount++) {
            sprintf(fileName, "%s.as", argv[fileCount]);
            currentFileName = fileName;
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

    free(fileName);

    return 0;
}