//TODO: FIX VISITED PROBLEM FOR LOOPS.
//TODO: REMINDER: Routes less that 2 length (including 1 and 0) should not use 3procGravity algorithm because they have definite answers.
#include "funcHeader.h"

int isButterflyIndex(int index);

void resetGravityMatrix(){
    for (int i = 0; i < nodeCounts; i++)
        for (int j = 0; j < nodeCounts; j++){
            linkGravity[i][j] = 0;
        }
} // Set Gravity Matrix to 0.

void makeGravitySymmetric(){
    int sum = 0;
    for (int i = 0; i < nodeCounts; i++)
        for (int j = 0; j < nodeCounts; j++) {
            if (i>=j) {
                sum = linkGravity[i][j] + linkGravity[j][i];
                // printf("%d,%d: %d ", i, j, sum);
                linkGravity[i][j] = sum;
                linkGravity[j][i] = sum;
                sum = 0;
                // printf("%d\n", sum);
            }
        }
} // Makes the Gravity Matrix symmetric.

void printGravityMatrix(){
    for (int i = 0; i < nodeCounts; i++) {
        for (int j = 0; j < nodeCounts; j++) {
            printf("%2d\t", linkGravity[i][j]);
        }
        printf("\n");
    }
} // Prints the Gravity Matrix.

void add2lengthRoutes(int startNode, int weight) {
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2] && isButterflyIndex(ad2)) {
                    printf("%d %d %d\n", startNode, ad1, ad2);
                    linkGravity[startNode][ad1] += weight;
                    linkGravity[ad1][ad2] += weight;
                }
} // Add gravity for 2-lengths.

void add3lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3] && isButterflyIndex(ad3)){
                            printf("%d %d %d %d\n", startNode, ad1, ad2, ad3);
                            linkGravity[startNode][ad1] += weight;
                            linkGravity[ad1][ad2] += weight;
                            linkGravity[ad2][ad3] += weight;
                        }

} // Add gravity for 3-lengths.

void add4lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4] && isButterflyIndex(ad4)){
                                    //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                    linkGravity[startNode][ad1] += weight;
                                    linkGravity[ad1][ad2] += weight;
                                    linkGravity[ad2][ad3] += weight;
                                    linkGravity[ad3][ad4] += weight;
                                }

} // Add gravity for 4-lengths.

void add5lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5] && isButterflyIndex(ad5)){
                                            //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                            linkGravity[startNode][ad1] += weight;
                                            linkGravity[ad1][ad2] += weight;
                                            linkGravity[ad2][ad3] += weight;
                                            linkGravity[ad3][ad4] += weight;
                                            linkGravity[ad4][ad5] += weight;
                                }

} // Add gravity for 5-lengths.

void add6lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6] && isButterflyIndex(ad6)){
                                                    //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                    linkGravity[startNode][ad1] += weight;
                                                    linkGravity[ad1][ad2] += weight;
                                                    linkGravity[ad2][ad3] += weight;
                                                    linkGravity[ad3][ad4] += weight;
                                                    linkGravity[ad4][ad5] += weight;
                                                    linkGravity[ad5][ad6] += weight;
                                                }

} // Add gravity for 6-lengths.

void add7lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6])
                                                    for (int ad7 = 0; ad7 < nodeCounts; ad7++)
                                                        if (adMatrix[ad6][ad7]&& isButterflyIndex(ad7)){
                                                            //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                            linkGravity[startNode][ad1] += weight;
                                                            linkGravity[ad1][ad2] += weight;
                                                            linkGravity[ad2][ad3] += weight;
                                                            linkGravity[ad3][ad4] += weight;
                                                            linkGravity[ad4][ad5] += weight;
                                                            linkGravity[ad5][ad6] += weight;
                                                            linkGravity[ad6][ad7] += weight;
                                                        }

} // Add gravity for 7-lengths.

void add8lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6])
                                                    for (int ad7 = 0; ad7 < nodeCounts; ad7++)
                                                        if (adMatrix[ad6][ad7])
                                                            for (int ad8 = 0; ad8 < nodeCounts; ad8++)
                                                                if (adMatrix[ad7][ad8] && isButterflyIndex(ad8)) {
                                                                    //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                                    linkGravity[startNode][ad1] += weight;
                                                                    linkGravity[ad1][ad2] += weight;
                                                                    linkGravity[ad2][ad3] += weight;
                                                                    linkGravity[ad3][ad4] += weight;
                                                                    linkGravity[ad4][ad5] += weight;
                                                                    linkGravity[ad5][ad6] += weight;
                                                                    linkGravity[ad6][ad7] += weight;
                                                                    linkGravity[ad7][ad8] += weight;
                                                                }

} // Add gravity for 8-lengths.

void add9lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6])
                                                    for (int ad7 = 0; ad7 < nodeCounts; ad7++)
                                                        if (adMatrix[ad6][ad7])
                                                            for (int ad8 = 0; ad8 < nodeCounts; ad8++)
                                                                if (adMatrix[ad7][ad8])
                                                                    for (int ad9 = 0; ad9 < nodeCounts; ad9++)
                                                                        if (adMatrix[ad8][ad9] && isButterflyIndex(ad9)){
                                                                            //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                                            linkGravity[startNode][ad1] += weight;
                                                                            linkGravity[ad1][ad2] += weight;
                                                                            linkGravity[ad2][ad3] += weight;
                                                                            linkGravity[ad3][ad4] += weight;
                                                                            linkGravity[ad4][ad5] += weight;
                                                                            linkGravity[ad5][ad6] += weight;
                                                                            linkGravity[ad6][ad7] += weight;
                                                                            linkGravity[ad7][ad8] += weight;
                                                                            linkGravity[ad8][ad9] += weight;
                                                                        }

} // Add gravity for 9-lengths.

void add10lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6])
                                                    for (int ad7 = 0; ad7 < nodeCounts; ad7++)
                                                        if (adMatrix[ad6][ad7])
                                                            for (int ad8 = 0; ad8 < nodeCounts; ad8++)
                                                                if (adMatrix[ad7][ad8])
                                                                    for (int ad9 = 0; ad9 < nodeCounts; ad9++)
                                                                        if (adMatrix[ad8][ad9])
                                                                            for (int ad10 = 0; ad10 < nodeCounts; ad10++)
                                                                                if (adMatrix[ad9][ad10] && isButterflyIndex(ad10)){
                                                                                    //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                                                    linkGravity[startNode][ad1] += weight;
                                                                                    linkGravity[ad1][ad2] += weight;
                                                                                    linkGravity[ad2][ad3] += weight;
                                                                                    linkGravity[ad3][ad4] += weight;
                                                                                    linkGravity[ad4][ad5] += weight;
                                                                                    linkGravity[ad5][ad6] += weight;
                                                                                    linkGravity[ad6][ad7] += weight;
                                                                                    linkGravity[ad7][ad8] += weight;
                                                                                    linkGravity[ad8][ad9] += weight;
                                                                                    linkGravity[ad9][ad10] += weight;
                                                                                }

} // Add gravity for 10-lengths.

void add11lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6])
                                                    for (int ad7 = 0; ad7 < nodeCounts; ad7++)
                                                        if (adMatrix[ad6][ad7])
                                                            for (int ad8 = 0; ad8 < nodeCounts; ad8++)
                                                                if (adMatrix[ad7][ad8])
                                                                    for (int ad9 = 0; ad9 < nodeCounts; ad9++)
                                                                        if (adMatrix[ad8][ad9])
                                                                            for (int ad10 = 0; ad10 < nodeCounts; ad10++)
                                                                                if (adMatrix[ad9][ad10])
                                                                                    for (int ad11 = 0; ad11 < nodeCounts; ad11++)
                                                                                        if (adMatrix[ad10][ad11] && isButterflyIndex(ad11)){
                                                                                            //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                                                            linkGravity[startNode][ad1] += weight;
                                                                                            linkGravity[ad1][ad2] += weight;
                                                                                            linkGravity[ad2][ad3] += weight;
                                                                                            linkGravity[ad3][ad4] += weight;
                                                                                            linkGravity[ad4][ad5] += weight;
                                                                                            linkGravity[ad5][ad6] += weight;
                                                                                            linkGravity[ad6][ad7] += weight;
                                                                                            linkGravity[ad7][ad8] += weight;
                                                                                            linkGravity[ad8][ad9] += weight;
                                                                                            linkGravity[ad9][ad10] += weight;
                                                                                            linkGravity[ad10][ad11] += weight;
                                                                                        }

} // Add gravity for 11-lengths.

void add12lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6])
                                                    for (int ad7 = 0; ad7 < nodeCounts; ad7++)
                                                        if (adMatrix[ad6][ad7])
                                                            for (int ad8 = 0; ad8 < nodeCounts; ad8++)
                                                                if (adMatrix[ad7][ad8])
                                                                    for (int ad9 = 0; ad9 < nodeCounts; ad9++)
                                                                        if (adMatrix[ad8][ad9])
                                                                            for (int ad10 = 0; ad10 < nodeCounts; ad10++)
                                                                                if (adMatrix[ad9][ad10])
                                                                                    for (int ad11 = 0; ad11 < nodeCounts; ad11++)
                                                                                        if (adMatrix[ad10][ad11])
                                                                                            for (int ad12 = 0; ad12 < nodeCounts; ad12++)
                                                                                                if (adMatrix[ad11][ad12] && isButterflyIndex(ad12)){
                                                                                                    //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                                                                    linkGravity[startNode][ad1] += weight;
                                                                                                    linkGravity[ad1][ad2] += weight;
                                                                                                    linkGravity[ad2][ad3] += weight;
                                                                                                    linkGravity[ad3][ad4] += weight;
                                                                                                    linkGravity[ad4][ad5] += weight;
                                                                                                    linkGravity[ad5][ad6] += weight;
                                                                                                    linkGravity[ad6][ad7] += weight;
                                                                                                    linkGravity[ad7][ad8] += weight;
                                                                                                    linkGravity[ad8][ad9] += weight;
                                                                                                    linkGravity[ad9][ad10] += weight;
                                                                                                    linkGravity[ad10][ad11] += weight;
                                                                                                    linkGravity[ad11][ad12] += weight;
                                                                                                }

} // Add gravity for 12-lengths.

void add13lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6])
                                                    for (int ad7 = 0; ad7 < nodeCounts; ad7++)
                                                        if (adMatrix[ad6][ad7])
                                                            for (int ad8 = 0; ad8 < nodeCounts; ad8++)
                                                                if (adMatrix[ad7][ad8])
                                                                    for (int ad9 = 0; ad9 < nodeCounts; ad9++)
                                                                        if (adMatrix[ad8][ad9])
                                                                            for (int ad10 = 0; ad10 < nodeCounts; ad10++)
                                                                                if (adMatrix[ad9][ad10])
                                                                                    for (int ad11 = 0; ad11 < nodeCounts; ad11++)
                                                                                        if (adMatrix[ad10][ad11])
                                                                                            for (int ad12 = 0; ad12 < nodeCounts; ad12++)
                                                                                                if (adMatrix[ad11][ad12])
                                                                                                    for (int ad13 = 0; ad13 < nodeCounts; ad13++)
                                                                                                        if (adMatrix[ad12][ad13] && isButterflyIndex(ad13)){
                                                                                                            //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                                                                            linkGravity[startNode][ad1] += weight;
                                                                                                            linkGravity[ad1][ad2] += weight;
                                                                                                            linkGravity[ad2][ad3] += weight;
                                                                                                            linkGravity[ad3][ad4] += weight;
                                                                                                            linkGravity[ad4][ad5] += weight;
                                                                                                            linkGravity[ad5][ad6] += weight;
                                                                                                            linkGravity[ad6][ad7] += weight;
                                                                                                            linkGravity[ad7][ad8] += weight;
                                                                                                            linkGravity[ad8][ad9] += weight;
                                                                                                            linkGravity[ad9][ad10] += weight;
                                                                                                            linkGravity[ad10][ad11] += weight;
                                                                                                            linkGravity[ad11][ad12] += weight;
                                                                                                            linkGravity[ad12][ad13] += weight;
                                                                                                        }

} // Add gravity for 13-lengths.

void add14lengthRoutes(int startNode, int weight){
    for (int ad1 = 0; ad1 < nodeCounts; ad1++)
        if (adMatrix[startNode][ad1])
            for (int ad2 = 0; ad2 < nodeCounts; ad2++)
                if (adMatrix[ad1][ad2])
                    for (int ad3 = 0; ad3 < nodeCounts; ad3++)
                        if (adMatrix[ad2][ad3])
                            for (int ad4 = 0; ad4 < nodeCounts; ad4++)
                                if (adMatrix[ad3][ad4])
                                    for (int ad5 = 0; ad5 < nodeCounts; ad5++)
                                        if (adMatrix[ad4][ad5])
                                            for (int ad6 = 0; ad6 < nodeCounts; ad6++)
                                                if (adMatrix[ad5][ad6])
                                                    for (int ad7 = 0; ad7 < nodeCounts; ad7++)
                                                        if (adMatrix[ad6][ad7])
                                                            for (int ad8 = 0; ad8 < nodeCounts; ad8++)
                                                                if (adMatrix[ad7][ad8])
                                                                    for (int ad9 = 0; ad9 < nodeCounts; ad9++)
                                                                        if (adMatrix[ad8][ad9])
                                                                            for (int ad10 = 0; ad10 < nodeCounts; ad10++)
                                                                                if (adMatrix[ad9][ad10])
                                                                                    for (int ad11 = 0; ad11 < nodeCounts; ad11++)
                                                                                        if (adMatrix[ad10][ad11])
                                                                                            for (int ad12 = 0; ad12 < nodeCounts; ad12++)
                                                                                                if (adMatrix[ad11][ad12])
                                                                                                    for (int ad13 = 0; ad13 < nodeCounts; ad13++)
                                                                                                        if (adMatrix[ad12][ad13])
                                                                                                            for (int ad14 = 0; ad14 < nodeCounts; ad14++)
                                                                                                                if (adMatrix[ad13][ad14]  && isButterflyIndex(ad14)){
                                                                                                                    //printf("%d %d %d %d %d\n", startNode, ad1, ad2, ad3, ad4);
                                                                                                                    linkGravity[startNode][ad1] += weight;
                                                                                                                    linkGravity[ad1][ad2] += weight;
                                                                                                                    linkGravity[ad2][ad3] += weight;
                                                                                                                    linkGravity[ad3][ad4] += weight;
                                                                                                                    linkGravity[ad4][ad5] += weight;
                                                                                                                    linkGravity[ad5][ad6] += weight;
                                                                                                                    linkGravity[ad6][ad7] += weight;
                                                                                                                    linkGravity[ad7][ad8] += weight;
                                                                                                                    linkGravity[ad8][ad9] += weight;
                                                                                                                    linkGravity[ad9][ad10] += weight;
                                                                                                                    linkGravity[ad10][ad11] += weight;
                                                                                                                    linkGravity[ad11][ad12] += weight;
                                                                                                                    linkGravity[ad12][ad13] += weight;
                                                                                                                    linkGravity[ad13][ad14] += weight;
                                                                                                        }

} // Add gravity for 14-lengths.

void proc3stepGravity(int startNode, int minLength){
    if (minLength == 2){
        resetGravityMatrix();
        add2lengthRoutes(startNode, PrimaryWeight);
        add3lengthRoutes(startNode, SecondaryWeight);
        //add4lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }

    if (minLength == 3){
        resetGravityMatrix();
        add3lengthRoutes(startNode, PrimaryWeight);
        add4lengthRoutes(startNode, SecondaryWeight);
        add5lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }

    if (minLength == 4){
        resetGravityMatrix();
        add4lengthRoutes(startNode, PrimaryWeight);
        add5lengthRoutes(startNode, SecondaryWeight);
        add6lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }

    if (minLength == 5){
        resetGravityMatrix();
        add5lengthRoutes(startNode, PrimaryWeight);
        add6lengthRoutes(startNode, SecondaryWeight);
        add7lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }

    if (minLength == 6){
        resetGravityMatrix();
        add6lengthRoutes(startNode, PrimaryWeight);
        add7lengthRoutes(startNode, SecondaryWeight);
        add8lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }

    if (minLength == 7){
        resetGravityMatrix();
        add7lengthRoutes(startNode, PrimaryWeight);
        add8lengthRoutes(startNode, SecondaryWeight);
        add9lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }

    if (minLength == 8){
        resetGravityMatrix();
        add8lengthRoutes(startNode, PrimaryWeight);
        add9lengthRoutes(startNode, SecondaryWeight);
        add10lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }

    if (minLength == 9){
        resetGravityMatrix();
        add9lengthRoutes(startNode, PrimaryWeight);
        add10lengthRoutes(startNode, SecondaryWeight);
        add11lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }

    if (minLength == 10){
        resetGravityMatrix();
        add10lengthRoutes(startNode, PrimaryWeight);
        add11lengthRoutes(startNode, SecondaryWeight);
        add12lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }


    if (minLength == 11){
        resetGravityMatrix();
        add11lengthRoutes(startNode, PrimaryWeight);
        add12lengthRoutes(startNode, SecondaryWeight);
        add13lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }


    if (minLength == 12){
        resetGravityMatrix();
        add12lengthRoutes(startNode, PrimaryWeight);
        add13lengthRoutes(startNode, SecondaryWeight);
        add14lengthRoutes(startNode, TertiaryWeight);
        makeGravitySymmetric();
    }
} // A function to automate 3-step processing.


void addNlengthRoutes(int startNode, int length, int weight){
    int path[length];
    path[0] = startNode;
    for (int iter = 1; iter <= length; iter++) {
        for (int adj = 0; adj < nodeCounts; adj++) {
            if (adMatrix[startNode][adj]) {
                path[iter] = adj;
                startNode = adj;
                break;
            }
        }
    }
    for (int i = 0; i < length; i++){
        printf("%d ", path[i]);
    }
}

#endif // Endif define gravity header.