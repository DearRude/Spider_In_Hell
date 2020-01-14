#include <stdlib.h>
#include <stdio.h>

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

void clear(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
} // Clears the screen. (Works on Linux and Windows.)

int fileGetMatrix(void){
    // Reads Node counts and Matrix from file.
    FILE *map;
    map = fopen("/home/dearrude/CLionProjects/Spider-In-Hell/graphData", "r+");
    if (map == NULL){
        perror("Error finding adMatrix map file. ");
        return (-1);
    }
    fscanf(map, "%d", &nodeCounts);
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
    printf("Link between %d and %d removed.\n", from, to);
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
    pAppendQueue = (int *) &queue; pCurrentQueue = (int *) &queue; // Starts two queue. One for current. One for appending.
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
        if (adMatrix[spiderNode][adjancy] && isButterflyIndex(adjancy)) return adjancy; // Return the definite if there is.
        if (linkGravity[spiderNode][bestNode] < linkGravity[spiderNode][adjancy]){
            bestNode = adjancy;
        }
    }
    return bestNode;
} // Returns the best move for spider.

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
    for (int adjan = 0; adjan < nodeCounts; adjan++){
        if (isButterflyIndex(adjan) && adMatrix[spiderNode][adjan]){
            bestLink[0] = spiderNode;
            bestLink[1] = adjan;
        }
    }
    return pBestLink;
} // Returns a pointer to array of best cut link.

void initTerminalSpider(){
    clear();
    /* TXTspiderInHellAsciiArt */ printf("        (                                (               )\r\n        )\\ )            (                )\\ )         ( /(       (   (\r\n       (()/(       (    )\\ )   (   (    (()/(         )\\())   (  )\\  )\\\r\n        /(_))`  )  )\\  (()/(  ))\\  )(    /(_)) (     ((_)\\   ))\\((_)((_)\r\n       (_))  /(/( ((_)  ((_))/((_)(()\\  (_))   )\\ )   _((_) /((_)_   _   \r\n       / __|((_)_\\ (_)  _| |(_))   ((_) |_ _| _(_/(  | || |(_)) | | | |\r\n       \\__ \\| \'_ \\)| |/ _` |/ -_) | \'_|  | | | \' \\)) | __ |/ -_)| | | |\r\n       |___/| .__/ |_|\\__,_|\\___| |_|   |___||_||_|  |_||_|\\___||_| |_|\r\n            |_|\n");
    /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
    /* TXTTerminalSpider */ printf("    ___      _       _                       _              _    \r\n   / __\\__ _| |_ ___| |__     __ _ _ __   __| |   ___  __ _| |_  \r\n  / /  / _` | __/ __| \'_ \\   / _` | \'_ \\ / _` |  / _ \\/ _` | __| \r\n / /__| (_| | || (__| | | | | (_| | | | | (_| | |  __/ (_| | |_  \r\n \\____/\\__,_|\\__\\___|_| |_|  \\__,_|_| |_|\\__,_|  \\___|\\__,_|\\__| \r\n                                                                 \r\n _   _            _           _   _             __ _ _           \r\n| |_| |__   ___  | |__  _   _| |_| |_ ___ _ __ / _| (_) ___  ___ \r\n| __| \'_ \\ / _ \\ | \'_ \\| | | | __| __/ _ \\ \'__| |_| | |/ _ \\/ __|\r\n| |_| | | |  __/ | |_) | |_| | |_| ||  __/ |  |  _| | |  __/\\__ \\\r\n \\__|_| |_|\\___| |_.__/ \\__,_|\\__|\\__\\___|_|  |_| |_|_|\\___||___/\r\n                                                                 \n");
    int winStatus = isButterflyIndex(spiderIndex);
    int loseStatus = distToClosestButterfly(spiderIndex) == -1;
    while (!winStatus && !loseStatus){
        // User Turn
        /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
        /* TXTspiderTurn */ printf("🕷  It's Spider's turn.\n");
        /* TXTinputSpiderNode */printf("Please enter an index for spider to move:");
        int newSpiderIndex;
        scanf("%d", &newSpiderIndex);
        while (!isLinkBetween(spiderIndex, newSpiderIndex)){
            printf("⛔  Bad choice. Please try again:");
            scanf("%d", &newSpiderIndex);
        }
        spiderIndex = newSpiderIndex;
        /* TXTniceChoice */printf("✓ Nice choice!\n");

        // Calculate if any wins
        winStatus = isButterflyIndex(spiderIndex);
        loseStatus = distToClosestButterfly(spiderIndex) == -1;
        if (winStatus){
            /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n\n");
            printf("        >>  <<,_,>>  <<\r\n       //   _0.-.0_   \\\\\r\n       \\\'._/       \\_.\'/\r\n        \'-.\\.--.--./.-\'\r\n        __/ : :Y: : \\ _\r\n\';,  .-(_| : : | : : |_)-.  ,:\'         You won!\r\n  \\\\/.\'  |: : :|: : :|  `.\\//     A butterfly is caught!\r\n   (/    |: : :|: : :|    \\)\r\n         |: : :|: : :;\r\n        /\\ : : | : : /\\\r\n       (_/\'.: :.: :.\'\\_)\r\n        \\\\  `\"\"`\"\"`  //\r\n         \\\\         //\r\n          \':.     .:\'\n");
            break;
        }
        if (loseStatus){
            /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n\n");
            printf("            __,_,\r\n           [_|_/ \r\n            //\r\n          _//    __\r\n         (_|)   |@@|\r\n          \\ \\__ \\--/ __\r\n           \\o__|----|  |   __      All butterflies escaped!\r\n               \\ }{ /\\ )_ / _\\      I\'m smarter than you!\r\n               /\\__/\\ \\__O (__\r\n              (--/\\--)    \\__/\r\n              _)(  )(_\r\n             `---\'\'---`\n");
            break;
        }

        // Computer Turn
        /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
        printf("🐦  It's butterfly's turn.\n");
        printf("🔗 Computer chose the link between %d and %d.\n", *(bestCut(spiderIndex)), *(bestCut(spiderIndex)+1));
        removeLinkBetween(*bestCut(spiderIndex), *(bestCut(spiderIndex)+1));

        // Calculate if any wins
        winStatus = isButterflyIndex(spiderIndex);
        loseStatus = distToClosestButterfly(spiderIndex) == -1;
        if (winStatus){
            /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n\n");
            printf("        >>  <<,_,>>  <<\r\n       //   _0.-.0_   \\\\\r\n       \\\'._/       \\_.\'/\r\n        \'-.\\.--.--./.-\'\r\n        __/ : :Y: : \\ _\r\n\';,  .-(_| : : | : : |_)-.  ,:\'         You won!\r\n  \\\\/.\'  |: : :|: : :|  `.\\//     A butterfly is caught!\r\n   (/    |: : :|: : :|    \\)\r\n         |: : :|: : :;\r\n        /\\ : : | : : /\\\r\n       (_/\'.: :.: :.\'\\_)\r\n        \\\\  `\"\"`\"\"`  //\r\n         \\\\         //\r\n          \':.     .:\'\n");
            break;
        }
        if (loseStatus){
            /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n\n");
            printf("            __,_,\r\n           [_|_/ \r\n            //\r\n          _//    __\r\n         (_|)   |@@|\r\n          \\ \\__ \\--/ __\r\n           \\o__|----|  |   __      All butterflies escaped!\r\n               \\ }{ /\\ )_ / _\\      I\'m smarter than you!\r\n               /\\__/\\ \\__O (__\r\n              (--/\\--)    \\__/\r\n              _)(  )(_\r\n             `---\'\'---`\n");
            break;
        }
    }
    printf("🆒 Nice game!");
    exit(0);
} // Initialize a terminal-based game in-which you're the spider!

void initTerminalButterfly(){
    clear();
    /* TXTspiderInHellAsciiArt */ printf("        (                                (               )\r\n        )\\ )            (                )\\ )         ( /(       (   (\r\n       (()/(       (    )\\ )   (   (    (()/(         )\\())   (  )\\  )\\\r\n        /(_))`  )  )\\  (()/(  ))\\  )(    /(_)) (     ((_)\\   ))\\((_)((_)\r\n       (_))  /(/( ((_)  ((_))/((_)(()\\  (_))   )\\ )   _((_) /((_)_   _   \r\n       / __|((_)_\\ (_)  _| |(_))   ((_) |_ _| _(_/(  | || |(_)) | | | |\r\n       \\__ \\| \'_ \\)| |/ _` |/ -_) | \'_|  | | | \' \\)) | __ |/ -_)| | | |\r\n       |___/| .__/ |_|\\__,_|\\___| |_|   |___||_||_|  |_||_|\\___||_| |_|\r\n            |_|\n");
    /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
    /* TXTYou're Butterfly */ printf("              __ _ _                    _                        \r\n             / /(_) |__   ___ _ __ __ _| |_ ___                  \r\n            / / | | \'_ \\ / _ \\ \'__/ _` | __/ _ \\                 \r\n           / /__| | |_) |  __/ | | (_| | ||  __/                 \r\n           \\____/_|_.__/ \\___|_|  \\__,_|\\__\\___|                 \r\n                                                                 \r\n _   _            _           _   _             __ _ _           \r\n| |_| |__   ___  | |__  _   _| |_| |_ ___ _ __ / _| (_) ___  ___ \r\n| __| \'_ \\ / _ \\ | \'_ \\| | | | __| __/ _ \\ \'__| |_| | |/ _ \\/ __|\r\n| |_| | | |  __/ | |_) | |_| | |_| ||  __/ |  |  _| | |  __/\\__ \\\r\n \\__|_| |_|\\___| |_.__/ \\__,_|\\__|\\__\\___|_|  |_| |_|_|\\___||___/\r\n                                                                 \n");
    int loseStatus = isButterflyIndex(spiderIndex);
    int winStatus = distToClosestButterfly(spiderIndex) == -1;
    while (!winStatus && !loseStatus){
        // Computer's Turn
        /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
        /* TXTspiderTurn */ printf("🕷  It's Spider's turn.\n");
        spiderIndex = bestMove(spiderIndex);
        printf("Computer chose the node [%d] for spider to move.\n", spiderIndex);

        // Calculate if any wins
        loseStatus = isButterflyIndex(spiderIndex);
        winStatus = distToClosestButterfly(spiderIndex) == -1;

        if (winStatus){
            /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
            printf("     _               _\r\n    (o\\             /o)        You won!\r\n    /::\\  o     o  /::\\\r\n   /:\'\':\\  \\___/  /:\'\':\\    Butterflies are\r\n  /:\'  \':\\/6 . 6\\/:\'  \':\\     liberated!\r\n (o:.   \'(  ._.  )\'   .:o)      _.-\'\'\'-.\r\n  `\\:.    \\     /    .:/`     .\'        \'.\r\n    `\\:.  /`---\'\\  .:/`       :           :\r\n      `)://`===`\\\\:(`          \'.        .\'\r\n      /:(/\\-===-/\\):\\            \'.    .\'\r\n     /:\'.,/ /^\\ \\,.\':\\             \'..\'\r\n    /:.:/(_/   \\_)\\:.:\\            .\'\'._\r\n   (::/`     :     `\\::)         .\'     `-....-\'`\r\n    \\o)       \'.    (o/        .\'\r\n     ^          \'.   ^       .\'\r\n                  `\'\'\'\'\'\'\'\'\'`\r\n\n");
            break;
        }

        if (loseStatus){
            /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
            printf("        >>  <<,_,>>  <<\r\n       //   _0.-.0_   \\\\\r\n       \\\'._/       \\_.\'/\r\n        \'-.\\.--.--./.-\'\r\n        __/ : :Y: : \\ _\r\n\';,  .-(_| : : | : : |_)-.  ,:\'         You lost!\r\n  \\\\/.\'  |: : :|: : :|  `.\\//     A butterfly is caught!\r\n   (/    |: : :|: : :|    \\)\r\n         |: : :|: : :;\r\n        /\\ : : | : : /\\\r\n       (_/\'.: :.: :.\'\\_)\r\n        \\\\  `\"\"`\"\"`  //\r\n         \\\\         //\r\n          \':.     .:\'\n");
            break;
        }

        // User Turn
        /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
        printf("🐦  It's butterfly's turn.\n");
        int startnode, finishnode;
        printf("Input two nodes to cut the link in between:");
        scanf("%d %d", &startnode, &finishnode);
        while(!isLinkBetween(startnode, finishnode)){
            printf("⛔  Bad choice. Please try again:");
            scanf("%d %d", &startnode, &finishnode);
        }
        removeLinkBetween(startnode, finishnode);

        // Calculate if any wins
        loseStatus = isButterflyIndex(spiderIndex);
        winStatus = distToClosestButterfly(spiderIndex) == -1;

        if (winStatus){
            /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
            printf("     _               _\r\n    (o\\             /o)        You won!\r\n    /::\\  o     o  /::\\\r\n   /:\'\':\\  \\___/  /:\'\':\\    Butterflies are\r\n  /:\'  \':\\/6 . 6\\/:\'  \':\\     liberated!\r\n (o:.   \'(  ._.  )\'   .:o)      _.-\'\'\'-.\r\n  `\\:.    \\     /    .:/`     .\'        \'.\r\n    `\\:.  /`---\'\\  .:/`       :           :\r\n      `)://`===`\\\\:(`          \'.        .\'\r\n      /:(/\\-===-/\\):\\            \'.    .\'\r\n     /:\'.,/ /^\\ \\,.\':\\             \'..\'\r\n    /:.:/(_/   \\_)\\:.:\\            .\'\'._\r\n   (::/`     :     `\\::)         .\'     `-....-\'`\r\n    \\o)       \'.    (o/        .\'\r\n     ^          \'.   ^       .\'\r\n                  `\'\'\'\'\'\'\'\'\'`\r\n\n");
            break;
        }

        if (loseStatus){
            /* TXTdevider */ printf(".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n");
            printf("        >>  <<,_,>>  <<\r\n       //   _0.-.0_   \\\\\r\n       \\\'._/       \\_.\'/\r\n        \'-.\\.--.--./.-\'\r\n        __/ : :Y: : \\ _\r\n\';,  .-(_| : : | : : |_)-.  ,:\'         You lost!\r\n  \\\\/.\'  |: : :|: : :|  `.\\//     A butterfly is caught!\r\n   (/    |: : :|: : :|    \\)\r\n         |: : :|: : :;\r\n        /\\ : : | : : /\\\r\n       (_/\'.: :.: :.\'\\_)\r\n        \\\\  `\"\"`\"\"`  //\r\n         \\\\         //\r\n          \':.     .:\'\n");
            break;
        }

    }
    printf("🆒 Nice game!");
    exit(0);
} // Initialize a terminal-based game in-which you liberate butterflies.