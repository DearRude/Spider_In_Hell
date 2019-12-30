#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNODES 100

int nodeCounts;
int adMatrix[MAXNODES][MAXNODES];
int spiderCount;
int spiderIndex[];
int butterfliesCount;
int butterfliesIndex[MAXNODES];

int fileGetMatrix(void);


int main() {
    printf("Hello, World!\n");
    fileGetMatrix();

    return (0);
}

int fileGetMatrix(void){
    // Reads Node counts and Matrix from file.
    FILE *map;
    map = fopen("/home/dearrude/CLionProjects/Spider-In-Hell/graphData", "r+");
    if (map == NULL){
        perror("Error finding adMatrix map file. ");
        return (-1);
    }
    nodeCounts = fgetc(map) - '0';
    //printf("%d", nodeCounts);
    char chara;
    int iMatrix = 0, jMatrix = 0;
    while (!feof(map)){
        chara = fgetc(map);
        if (!(chara >= '0' && chara <= '9')) continue; // Pass non-integer numbers.

        if (iMatrix == nodeCounts){ // Go to next line in the adMatrix
            iMatrix = 0;
            jMatrix++;
        }
        if (jMatrix < nodeCounts - 1) adMatrix[iMatrix++][jMatrix] = chara - '0';

    }
    for(int i=0; i<nodeCounts; i++) {
        for (int j = 0; j < nodeCounts; j++) {
            printf("%d ", adMatrix[i][j]);
        }
        printf("\n");
    }
    fclose(map);
    return (0);
}