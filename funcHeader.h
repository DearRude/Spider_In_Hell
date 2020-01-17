#ifndef SPIDER_IN_HELL_FUNCHEADER_H
#define SPIDER_IN_HELL_FUNCHEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXNODES 100
int nodeCounts;
int adMatrix[MAXNODES][MAXNODES];
int spiderCount;
int spiderIndex;
int butterfliesCount;
int butterfliesIndex[MAXNODES];
int coordMatrix[MAXNODES][2]; // lat and lan × number of the nodes × digits of the pixels
int linkGravity[MAXNODES][MAXNODES];

//Declaring Weights
#define PrimaryWeight 5
#define SecondaryWeight 3
#define TertiaryWeight 1

void clear();// Clears the screen. (Works on Linux and Windows.)

int fileGetMatrix(void); // A function to get info from graphData file.

void removeLinkBetween(int from, int to); // Remove the link between from and to.

int isLinkBetween(int from, int to); // Checks if there is a links between from and to.

int isButterflyIndex(int index); // Checks if the given node is in butterfly index.

int distToClosestButterfly(int nodeIndex); // Calculate the shortest path to butterflies.

int bestMove (int spiderNode); // Returns the best move for spider.

int * bestCut(int spiderNode); // Returns a pointer to array of best cut link.

void initTerminalSpider(); // Initialize a terminal-based game in-which you're the spider!

void initTerminalButterfly(); // Initialize a terminal-based game in-which you liberate butterflies.

// --------- Gravity Functions ----------------
void resetGravityMatrix(); // Set Gravity Matrix to 0.

void makeGravitySymmetric(); // Makes the Gravity Matrix symmetric.

void printGravityMatrix(); // Prints the Gravity Matrix.

void add2lengthRoutes(int startNode, int weight); // Add gravity for 2-lengths.

void add3lengthRoutes(int startNode, int weight); // Add gravity for 3-lengths.

void add4lengthRoutes(int startNode, int weight); // Add gravity for 4-lengths.

void add5lengthRoutes(int startNode, int weight); // Add gravity for 5-lengths.

void add6lengthRoutes(int startNode, int weight); // Add gravity for 6-lengths.

void add7lengthRoutes(int startNode, int weight); // Add gravity for 7-lengths.

void add8lengthRoutes(int startNode, int weight); // Add gravity for 8-lengths.

void add9lengthRoutes(int startNode, int weight); // Add gravity for 9-lengths.

void add10lengthRoutes(int startNode, int weight); // Add gravity for 10-lengths.

void add11lengthRoutes(int startNode, int weight); // Add gravity for 11-lengths.

void add12lengthRoutes(int startNode, int weight); // Add gravity for 12-lengths.

void add13lengthRoutes(int startNode, int weight); // Add gravity for 13-lengths.

void add14lengthRoutes(int startNode, int weight); // Add gravity for 14-lengths.

void proc3stepGravity(int startNode, int minLength); // A function to automate 3-step processing.

void addNlengthRoutes(int startNode, int length, int weight);

#endif //SPIDER_IN_HELL_FUNCHEADER_H