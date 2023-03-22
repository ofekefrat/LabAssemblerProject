#include "main.h"

int lineCount=0; /* for error reporting */
char* currentFileName; /* the name of the current file being worked on */
int error; /* to indicate an error has been encountered */

int main(int argc, char** argv) {
    int fileCount;
    FILE* source, *am; /* am: for the file returned from pre-assembly */
    char* fileName = (char*) calloc(MAX_FILE_NAME, sizeof(char));

    if (argc >= 2) {
        for (fileCount=1; fileCount < argc; fileCount++) {
            error=0;
            sprintf(fileName, "%s.as", argv[fileCount]);
            currentFileName = fileName;
            source = fopen(fileName, "r");
            if (source) {
                am = preAssemble(source, argv[fileCount]);
                fclose(source);

                if (error) {
                    printf("Errors found in pre-assembly, stopping..\n");
                    fclose(source);
                    continue;
                }

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