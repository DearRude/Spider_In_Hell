#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gravity.h"
#include "functions.h"



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
    printf("Best move is: %d\n", bestMove(1));
    printf("Best cut is %d %d\n", *bestCut(1), *(bestCut(1)+1));
    printGravityMatrix();

    return (0);
}


// Todo: Write a function to start a terminal-based game!
