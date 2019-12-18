#define MAXKEYWORD 15
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}

int fgetMatrix(int adMatrix){
    char matrixKeyword[] = "matrix"; //matrix keyword in map file
    char nodeKeyword[] = "nodes"; //node keyword in map file
    char keyword[MAXKEYWORD];
    // Reads Node counts and Matrix from file.
    FILE *map;
    if (map = fopen("/src/map.txt", "r+") != NULL){
        while (!feof(map)){
            if (fscanf(map, "%s", &keyword) == nodeKeyword){
                // if it's node line
                int nodeCounts;
                fscanf(map, "%d", &nodeCounts);
            }
            if (fscanf(map,"%s", keyword ) == matrixKeyword){
                // if it's matrix line
                for (int line=0; line<nodeCounts) //could'nt do it!
            }
        }
    }


}