#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gravity.h"
#include "functions.h"



int main(int argc, char * argv[]) {
    clear();
    printf("Hello, World!\n");
    fileGetMatrix();
    printf("Best move is: %d\n", bestMove(1));
    printf("Best cut is %d %d\n", *bestCut(1), *(bestCut(1)+1));
    printGravityMatrix();
    int hey;
    scanf("%d", &hey);


    return (0);
}


// Todo: Write a function to start a terminal-based game!
