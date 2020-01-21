#include "funcHeader.h"

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
    for (int i = 0; i < nodeCounts; i++)
        for (int j = 0; j < nodeCounts; j++){
            fscanf(map, "%d", &adMatrix[i][j]);
        }
    fscanf(map, "%d", &spiderCount);
    fscanf(map, "%d", &spiderIndex);
    fscanf(map, "%d", &butterfliesCount);
    for (int x = 0; x < butterfliesCount; x++){
        fscanf(map, "%d", &butterfliesIndex[x]);
    }
    for (int x2 = 0; x2 < nodeCounts; x2++){
        fscanf(map, "%d %d", &coordMatrix[x2][0], &coordMatrix[x2][1]);
    }
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
    /* TXTspiderInHellAsciiArt */ printf(ANSI_COLOR_RED"        (                                (               )\r\n        )\\ )            (                )\\ )         ( /(       (   (\r\n       (()/(       (    )\\ )   (   (    (()/(         )\\())   (  )\\  )\\\r\n        /(_))`  )  )\\  (()/(  ))\\  )(    /(_)) (     ((_)\\   ))\\((_)((_)\r\n       (_))  /(/( ((_)  ((_))/((_)(()\\  (_))   )\\ )   _((_) /((_)_   _   \r\n       / __|((_)_\\ (_)  _| |(_))   ((_) |_ _| _(_/(  | || |(_)) | | | |\r\n       \\__ \\| \'_ \\)| |/ _` |/ -_) | \'_|  | | | \' \\)) | __ |/ -_)| | | |\r\n       |___/| .__/ |_|\\__,_|\\___| |_|   |___||_||_|  |_||_|\\___||_| |_|\r\n            |_|\n"ANSI_COLOR_RESET);
    /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
    /* TXTTerminalSpider */ printf(ANSI_COLOR_CYAN"    ___      _       _                       _              _    \r\n   / __\\__ _| |_ ___| |__     __ _ _ __   __| |   ___  __ _| |_  \r\n  / /  / _` | __/ __| \'_ \\   / _` | \'_ \\ / _` |  / _ \\/ _` | __| \r\n / /__| (_| | || (__| | | | | (_| | | | | (_| | |  __/ (_| | |_  \r\n \\____/\\__,_|\\__\\___|_| |_|  \\__,_|_| |_|\\__,_|  \\___|\\__,_|\\__| \r\n                                                                 \r\n _   _            _           _   _             __ _ _           \r\n| |_| |__   ___  | |__  _   _| |_| |_ ___ _ __ / _| (_) ___  ___ \r\n| __| \'_ \\ / _ \\ | \'_ \\| | | | __| __/ _ \\ \'__| |_| | |/ _ \\/ __|\r\n| |_| | | |  __/ | |_) | |_| | |_| ||  __/ |  |  _| | |  __/\\__ \\\r\n \\__|_| |_|\\___| |_.__/ \\__,_|\\__|\\__\\___|_|  |_| |_|_|\\___||___/\r\n                                                                 \n"ANSI_COLOR_RESET);
    int winStatus = isButterflyIndex(spiderIndex);
    int loseStatus = distToClosestButterfly(spiderIndex) == -1;
    while (!winStatus && !loseStatus){
        // User Turn
        /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
        /* TXTspiderTurn */ printf("🕷  It's Spider's turn.\n");
        /* TXTinputSpiderNode */printf("Please enter an index for spider to move:");
        int newSpiderIndex;
        scanf("%d", &newSpiderIndex);
        while (!isLinkBetween(spiderIndex, newSpiderIndex)){
            printf(ANSI_COLOR_RED"⛔  Bad choice. Please try again:"ANSI_COLOR_RESET);
            scanf("%d", &newSpiderIndex);
        }
        spiderIndex = newSpiderIndex;
        /* TXTniceChoice */printf("✓ Nice choice!\n");

        // Calculate if any wins
        winStatus = isButterflyIndex(spiderIndex);
        loseStatus = distToClosestButterfly(spiderIndex) == -1;
        if (winStatus){
            /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
            printf("        >>  <<,_,>>  <<\r\n       //   _0.-.0_   \\\\\r\n       \\\'._/       \\_.\'/\r\n        \'-.\\.--.--./.-\'\r\n        __/ : :Y: : \\ _\r\n\';,  .-(_| : : | : : |_)-.  ,:\'         You won!\r\n  \\\\/.\'  |: : :|: : :|  `.\\//     A butterfly is caught!\r\n   (/    |: : :|: : :|    \\)\r\n         |: : :|: : :;\r\n        /\\ : : | : : /\\\r\n       (_/\'.: :.: :.\'\\_)\r\n        \\\\  `\"\"`\"\"`  //\r\n         \\\\         //\r\n          \':.     .:\'\n");
            break;
        }
        if (loseStatus){
            /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
            printf("            __,_,\r\n           [_|_/ \r\n            //\r\n          _//    __\r\n         (_|)   |@@|\r\n          \\ \\__ \\--/ __\r\n           \\o__|----|  |   __      All butterflies escaped!\r\n               \\ }{ /\\ )_ / _\\      I\'m smarter than you!\r\n               /\\__/\\ \\__O (__\r\n              (--/\\--)    \\__/\r\n              _)(  )(_\r\n             `---\'\'---`\n");
            break;
        }

        // Computer Turn
        /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
        printf("🐦  It's butterfly's turn.\n");
        printf("🔗 Computer chose the link between %d and %d.\n", *(bestCut(spiderIndex)), *(bestCut(spiderIndex)+1));
        removeLinkBetween(*bestCut(spiderIndex), *(bestCut(spiderIndex)+1));

        // Calculate if any wins
        winStatus = isButterflyIndex(spiderIndex);
        loseStatus = distToClosestButterfly(spiderIndex) == -1;
        if (winStatus){
            /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
            printf("        >>  <<,_,>>  <<\r\n       //   _0.-.0_   \\\\\r\n       \\\'._/       \\_.\'/\r\n        \'-.\\.--.--./.-\'\r\n        __/ : :Y: : \\ _\r\n\';,  .-(_| : : | : : |_)-.  ,:\'         You won!\r\n  \\\\/.\'  |: : :|: : :|  `.\\//     A butterfly is caught!\r\n   (/    |: : :|: : :|    \\)\r\n         |: : :|: : :;\r\n        /\\ : : | : : /\\\r\n       (_/\'.: :.: :.\'\\_)\r\n        \\\\  `\"\"`\"\"`  //\r\n         \\\\         //\r\n          \':.     .:\'\n");
            break;
        }
        if (loseStatus){
            /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
            printf("            __,_,\r\n           [_|_/ \r\n            //\r\n          _//    __\r\n         (_|)   |@@|\r\n          \\ \\__ \\--/ __\r\n           \\o__|----|  |   __      All butterflies escaped!\r\n               \\ }{ /\\ )_ / _\\      I\'m smarter than you!\r\n               /\\__/\\ \\__O (__\r\n              (--/\\--)    \\__/\r\n              _)(  )(_\r\n             `---\'\'---`\n");
            break;
        }
    }
    printf("🆒 Nice game!");
    exit(0);
} // Initialize a terminal-based game in-which you're the spider!

void initTerminalButterfly(){
    clear();
    /* TXTspiderInHellAsciiArt */ printf(ANSI_COLOR_RED"        (                                (               )\r\n        )\\ )            (                )\\ )         ( /(       (   (\r\n       (()/(       (    )\\ )   (   (    (()/(         )\\())   (  )\\  )\\\r\n        /(_))`  )  )\\  (()/(  ))\\  )(    /(_)) (     ((_)\\   ))\\((_)((_)\r\n       (_))  /(/( ((_)  ((_))/((_)(()\\  (_))   )\\ )   _((_) /((_)_   _   \r\n       / __|((_)_\\ (_)  _| |(_))   ((_) |_ _| _(_/(  | || |(_)) | | | |\r\n       \\__ \\| \'_ \\)| |/ _` |/ -_) | \'_|  | | | \' \\)) | __ |/ -_)| | | |\r\n       |___/| .__/ |_|\\__,_|\\___| |_|   |___||_||_|  |_||_|\\___||_| |_|\r\n            |_|\n"ANSI_COLOR_RESET);
    /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
    /* TXTYou're Butterfly */ printf(ANSI_COLOR_CYAN"              __ _ _                    _                        \r\n             / /(_) |__   ___ _ __ __ _| |_ ___                  \r\n            / / | | \'_ \\ / _ \\ \'__/ _` | __/ _ \\                 \r\n           / /__| | |_) |  __/ | | (_| | ||  __/                 \r\n           \\____/_|_.__/ \\___|_|  \\__,_|\\__\\___|                 \r\n                                                                 \r\n _   _            _           _   _             __ _ _           \r\n| |_| |__   ___  | |__  _   _| |_| |_ ___ _ __ / _| (_) ___  ___ \r\n| __| \'_ \\ / _ \\ | \'_ \\| | | | __| __/ _ \\ \'__| |_| | |/ _ \\/ __|\r\n| |_| | | |  __/ | |_) | |_| | |_| ||  __/ |  |  _| | |  __/\\__ \\\r\n \\__|_| |_|\\___| |_.__/ \\__,_|\\__|\\__\\___|_|  |_| |_|_|\\___||___/\r\n                                                                 \n"ANSI_COLOR_RESET);
    int loseStatus = isButterflyIndex(spiderIndex);
    int winStatus = distToClosestButterfly(spiderIndex) == -1;
    while (!winStatus && !loseStatus){
        // Computer's Turn
        /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
        /* TXTspiderTurn */ printf("🕷  It's Spider's turn.\n");
        spiderIndex = bestMove(spiderIndex);
        printf("Computer chose the node [%d] for spider to move.\n", spiderIndex);

        // Calculate if any wins
        loseStatus = isButterflyIndex(spiderIndex);
        winStatus = distToClosestButterfly(spiderIndex) == -1;

        if (winStatus){
            /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
            printf("     _               _\r\n    (o\\             /o)        You won!\r\n    /::\\  o     o  /::\\\r\n   /:\'\':\\  \\___/  /:\'\':\\    Butterflies are\r\n  /:\'  \':\\/6 . 6\\/:\'  \':\\     liberated!\r\n (o:.   \'(  ._.  )\'   .:o)      _.-\'\'\'-.\r\n  `\\:.    \\     /    .:/`     .\'        \'.\r\n    `\\:.  /`---\'\\  .:/`       :           :\r\n      `)://`===`\\\\:(`          \'.        .\'\r\n      /:(/\\-===-/\\):\\            \'.    .\'\r\n     /:\'.,/ /^\\ \\,.\':\\             \'..\'\r\n    /:.:/(_/   \\_)\\:.:\\            .\'\'._\r\n   (::/`     :     `\\::)         .\'     `-....-\'`\r\n    \\o)       \'.    (o/        .\'\r\n     ^          \'.   ^       .\'\r\n                  `\'\'\'\'\'\'\'\'\'`\r\n\n");
            break;
        }

        if (loseStatus){
            /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
            printf("        >>  <<,_,>>  <<\r\n       //   _0.-.0_   \\\\\r\n       \\\'._/       \\_.\'/\r\n        \'-.\\.--.--./.-\'\r\n        __/ : :Y: : \\ _\r\n\';,  .-(_| : : | : : |_)-.  ,:\'         You lost!\r\n  \\\\/.\'  |: : :|: : :|  `.\\//     A butterfly is caught!\r\n   (/    |: : :|: : :|    \\)\r\n         |: : :|: : :;\r\n        /\\ : : | : : /\\\r\n       (_/\'.: :.: :.\'\\_)\r\n        \\\\  `\"\"`\"\"`  //\r\n         \\\\         //\r\n          \':.     .:\'\n");
            break;
        }

        // User Turn
        /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
        printf("🐦  It's butterfly's turn.\n");
        int startnode, finishnode;
        printf("Input two nodes to cut the link in between:");
        scanf("%d %d", &startnode, &finishnode);
        while(!isLinkBetween(startnode, finishnode)){
            printf(ANSI_COLOR_RED"⛔  Bad choice. Please try again:"ANSI_COLOR_RESET);
            scanf("%d %d", &startnode, &finishnode);
        }
        removeLinkBetween(startnode, finishnode);

        // Calculate if any wins
        loseStatus = isButterflyIndex(spiderIndex);
        winStatus = distToClosestButterfly(spiderIndex) == -1;

        if (winStatus){
            /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
            printf("     _               _\r\n    (o\\             /o)        You won!\r\n    /::\\  o     o  /::\\\r\n   /:\'\':\\  \\___/  /:\'\':\\    Butterflies are\r\n  /:\'  \':\\/6 . 6\\/:\'  \':\\     liberated!\r\n (o:.   \'(  ._.  )\'   .:o)      _.-\'\'\'-.\r\n  `\\:.    \\     /    .:/`     .\'        \'.\r\n    `\\:.  /`---\'\\  .:/`       :           :\r\n      `)://`===`\\\\:(`          \'.        .\'\r\n      /:(/\\-===-/\\):\\            \'.    .\'\r\n     /:\'.,/ /^\\ \\,.\':\\             \'..\'\r\n    /:.:/(_/   \\_)\\:.:\\            .\'\'._\r\n   (::/`     :     `\\::)         .\'     `-....-\'`\r\n    \\o)       \'.    (o/        .\'\r\n     ^          \'.   ^       .\'\r\n                  `\'\'\'\'\'\'\'\'\'`\r\n\n");
            break;
        }

        if (loseStatus){
            /* TXTdevider */ printf(ANSI_COLOR_YELLOW".-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-.-.   .-..-.   .-.-.   .-.\r\n / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \\ \\ / / \r\n`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'   `-`-\'    `-`-\'   `-`-\'\n"ANSI_COLOR_RESET);
            printf("        >>  <<,_,>>  <<\r\n       //   _0.-.0_   \\\\\r\n       \\\'._/       \\_.\'/\r\n        \'-.\\.--.--./.-\'\r\n        __/ : :Y: : \\ _\r\n\';,  .-(_| : : | : : |_)-.  ,:\'         You lost!\r\n  \\\\/.\'  |: : :|: : :|  `.\\//     A butterfly is caught!\r\n   (/    |: : :|: : :|    \\)\r\n         |: : :|: : :;\r\n        /\\ : : | : : /\\\r\n       (_/\'.: :.: :.\'\\_)\r\n        \\\\  `\"\"`\"\"`  //\r\n         \\\\         //\r\n          \':.     .:\'\n");
            break;
        }

    }
    printf("🆒 Nice game!");
    exit(0);
} // Initialize a terminal-based game in-which you liberate butterflies.
