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


//TODO: Write a function to add gravity to all routes to butterfly with n length.
//TODO: Write a function to delete the link with most gravity.

//TODO: Write a function to change the index of spider to the adjacent node by the link with most gravity.

