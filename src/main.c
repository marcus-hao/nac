#include "include/nac.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Please include an input file\n");
        return 1;
    }

    compile_file(argv[1]);

    return 0;
}