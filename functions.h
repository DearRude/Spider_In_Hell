#ifndef SPIDER_IN_HELL_FUNCTIONS_H
#define SPIDER_IN_HELL_FUNCTIONS_H

#endif //SPIDER_IN_HELL_FUNCTIONS_H
#define MAXNODES 100
int nodeCounts;
int adMatrix[MAXNODES][MAXNODES];
int spiderCount;
int spiderIndex;
int butterfliesCount;
int butterfliesIndex[MAXNODES];
int coordMatrix[MAXNODES][2]; // lat and lan × number of the nodes × digits of the pixels
int linkGravity[MAXNODES][MAXNODES];


int fileGetMatrix(void){
    // Reads Node counts and Matrix from file.
    FILE *map;
    map = fopen("/home/dearrude/CLionProjects/Spider-In-Hell/graphData", "r+");
    if (map == NULL){
        perror("Error finding adMatrix map file. ");
        return (-1);
    }
    nodeCounts = fgetc(map) - '0';

    char chara;
    int iMatrix = 0, jMatrix = 0, iButter = 0, iCoord = 0;
    int statMatrix = 0, statNumSpider = 0, statPosSpider = 0, statNumButterflies = 0, statPosButterflies = 0;

    while (!feof(map)){
        fscanf(map, "%c", &chara);

        if (!(chara >= '0' && chara <= '9')) continue; // Pass non-integer numbers.

        if (!statMatrix){ // Get Matrix section.
            if (iMatrix == nodeCounts){ // Go to next line in the adMatrix
                iMatrix = 0;
                jMatrix++;
            }
            if (jMatrix == nodeCounts - 1 && iMatrix == nodeCounts - 1) statMatrix = 1;
            adMatrix[iMatrix++][jMatrix] = chara - '0';} // Get Matrix.

        else if (!statNumSpider){
            spiderCount = chara - '0';
            statNumSpider = 1;
        } // Get number of spiders.

        else if (!statPosSpider){
            spiderIndex = chara - '0';
            statPosSpider = 1;
        } // Get position of the spiders.

        else if (!statNumButterflies){
            butterfliesCount = chara - '0';
            statNumButterflies = 1;
        } // Get the Number of the butterflies.

        else if (!statPosButterflies){
            butterfliesIndex[iButter++] = chara - '0';
            if (iButter == butterfliesCount - 1) {statPosButterflies = 1;}
        } // Get the position of the butterflies.

        else {
            while (iCoord < nodeCounts){
                fscanf(map, "%d %d", &coordMatrix[iCoord][0], &coordMatrix[iCoord][1]);
                iCoord++;
                butterfliesIndex[iButter] = chara - '0';
            }
        } // Get the coordinates of the nodes.
    }

//    for(int i=0; i<nodeCounts; i++) {
//        for (int j = 0; j < nodeCounts; j++) {
//            printf("%d ", adMatrix[i][j]);
//        }
//        printf("\n");
//    }
//    printf("%d %d\n", spiderCount, spiderIndex);
//    printf("%d\n", butterfliesCount);
//    for (int ii=0; ii<butterfliesCount; ii++){
//        printf("%d\n", butterfliesIndex[ii]);
//    }
//
//    for(int i=0; i<nodeCounts; i++) {
//        for (int j = 0; j <2; j++) {
//            printf("%d ", coordMatrix[i][j]);
//        }
//        printf("\n");
//    }
    fclose(map);
    printf("Graph data was imported successfully.\n");
    return (0);
} // A function to get info from graphData file.

void removeLinkBetween(int from, int to){
    adMatrix[from][to] = 0;
    adMatrix[to][from] = 0;
    printf("Link between %d and %d removed.", from, to);
} // Remove the link between from and to.

int isLinkBetween(int from, int to){
    if (adMatrix[from][to]==1 && adMatrix[to][from]==1) return (1);
    return (0);
} // Checks if there is a links between from and to.

int isButterflyIndex(int index){
    for (int numButter = 0; numButter < butterfliesCount; numButter++){
        if (index == butterfliesIndex[numButter]) return (1);
    }
    return (0);
} // Checks if the given node is in butterfly index.

int distToClosestButterfly(int nodeIndex){
    int visited[MAXNODES], distance = 0, queue[MAXNODES];
    for (int iVisited = 0; iVisited < MAXNODES; iVisited++) visited[iVisited] = 0;
    for (int iQueue = 0; iQueue < MAXNODES; iQueue++) queue[iQueue] = -2;
    int * pAppendQueue, * pCurrentQueue;
    pAppendQueue = &queue; pCurrentQueue = &queue; // Starts two queue. One for current. One for appending.
    *(pAppendQueue++) = nodeIndex; *(pAppendQueue++) = -1;
    visited[*pCurrentQueue] = 1;
    if (isButterflyIndex(*pCurrentQueue)) return (0); // Checks if the current node is butterfly before going to into the loop.
    while (*pCurrentQueue != -2){
        if (*pCurrentQueue == -1) distance++; // If it's queue interval.
        else if (*pCurrentQueue != -2 && *pCurrentQueue != -1){ // If it's not queue interval or empty queue.
            for (int iAdjan = 0; iAdjan < nodeCounts; iAdjan++){
                if (adMatrix[iAdjan][*pCurrentQueue]== 1 && !visited[iAdjan] ){
                    if (isButterflyIndex(iAdjan)) return (distance+1); // Finish the loop if the butterfly node is founded.
                    else {
                        *pAppendQueue++ = iAdjan; // Add to the queue.
                        visited[iAdjan] = 1; // Mark the node as visited.
                    }
                }
            }
            if (*(pCurrentQueue+1) == -1) *pAppendQueue++ = -1; // Add queue interval if the next queue is an interval.
        }
        *pCurrentQueue++; // Go for the next queue.
    }
    return (-1); // No butterfly is found.
} // Calculate the shortest path to butterflies.

int bestMove (int spiderNode){
    int bestNode = 0;
    proc3stepGravity(spiderNode, distToClosestButterfly(spiderNode));
    for (int adjancy = 0; adjancy < nodeCounts; adjancy++){
        if (linkGravity[spiderNode][bestNode] < linkGravity[spiderNode][adjancy]){
            bestNode = adjancy;
        }
    }
    return bestNode;
}

int * bestCut(int spiderNode){
    int bestLink[2] = {0, 0};
    int * pBestLink;
    pBestLink = (int *) &bestLink;

    proc3stepGravity(spiderNode, distToClosestButterfly(spiderNode));
    for (int i = 0; i < nodeCounts; i++)
        for (int j = 0; j < nodeCounts; j++){
            if (linkGravity[bestLink[0]][bestLink[1]] < linkGravity[i][j]){
                bestLink[0] = i;
                bestLink[1] = j;
                //printf("%d %d\n", bestLink[0], bestLink[1]);
            }
        }
    return pBestLink;
}