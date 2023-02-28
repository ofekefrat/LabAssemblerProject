#include "libraries.h"
#include "preassemble.h"

int main() {

    FILE *input, *output;
    char* name = "C:\\Users\\ofeke\\CLionProjects\\LabAssemblerProject\\src\\input.txt";
    input = fopen(name, "r");
    if (input == NULL) {
        printf("error opening input file\n");
        exit(1);
    }

    output = preAssemble(input);

//    if (output == NULL) {
//        printf("preassembly returned null file pointer\n");
//        exit(1);
//    }

    printFileContent(output);
    return 0;
}