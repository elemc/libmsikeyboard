#include <stdio.h>
#include <stdlib.h>
#include "msikeyboard.h"

void printResult(char *what, char **result, int resultSize) {
    if (result == NULL) {
        printf("%s get list function return null pointer!\n", what);
        exit(1);
    }

    printf("%s:\n", what);
    int i;
    for( i=0; i < resultSize; i++ ) {
        printf("\t\"%s\" ok.\n", result[i]);
    }
}

int main(int argc, char const *argv[]) {
    size_t size;
    char **intList = get_intensities(&size);
    printResult("Intensities", intList, size);

    char **colorList = get_colors(&size);
    printResult("Colors", colorList, size);

    char **modeList = get_modes(&size);
    printResult("Modes", modeList, size);

    char **regionList = get_regions(&size);
    printResult("Modes", regionList, size);

    free(intList);
    free(colorList);
    free(modeList);
    free(regionList);

    return 0;
}
