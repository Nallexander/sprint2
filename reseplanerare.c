#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseplanerare.h"
#include "filereader.h"

struct node createNode(char * name) 
{
  strdup(name);
  struct node station = { .name = name, .connections = NULL };
  return station;
}

struct line * createLineList (unsigned short newLine) {
  struct line *c = malloc(sizeof (struct line));
  c->number = newLine;
  c->next = NULL;
  return c;
}

void addLine (struct line *lineList, unsigned short newLine) {
  struct line **dp = &(lineList->next);
  while (*dp != NULL) { 
    dp = &((*dp)->next);
  }
  *dp = (createLineList(newLine));
}

struct adjList * createAdjList(struct node * node, unsigned short time, unsigned short line) {
  struct adjList *c = malloc(sizeof (struct adjList));
  c->node = node;
  c->time = time;
  c->lines = createLineList(line);
  c->next = NULL;
  return c;
}



// seperate module
void addToAdjList (struct node *Node, struct node *connectionNode, unsigned short time, unsigned short line){
  
  int write = 1;
  struct adjList **dp = &(Node->connections);
  while (*dp != NULL) { 
    if ((strncmp ((*dp)->node->name, connectionNode->name, 100) == 0)) {
      addLine ((*dp)->lines, line);
      write = 0;
      break;
    }
    dp = &((*dp)->next);
  }
  if (write == 1) {
    *dp = (createAdjList(connectionNode, time, line));
  }
}

void deleteName (struct node *Node, char *name) {
  struct adjList **currentAdjList = &(Node->connections);
  while ((*currentAdjList != NULL)) {
    
    if  ((*currentAdjList)->node->name != name)
      {
	currentAdjList = &((*currentAdjList)->next);
      }
    else {
      struct adjList *dp2 = *currentAdjList;
      *currentAdjList = ((*currentAdjList)->next);
      free(dp2);
    }
  }
}

void deleteNode (char *name, struct node *nodeList, unsigned short *numberOfStations)
{
  for (int i = 0; i <= (*numberOfStations - 1); i++) {

    if (name == nodeList[i].name) {
      nodeList[i] = nodeList[(*numberOfStations)-1];	
      *numberOfStations -= 1;
    }

    else {
      deleteName((nodeList + i), name);
    }
  } 
}


void deleteConnection (struct node *node1, struct node *node2) {
  deleteName(node1, (node2->name));
  deleteName(node2, (node1->name));
}

// Vet att station finns i nodeList
unsigned short findNodeListNumber(struct node * nodeList, char * station)
{
  unsigned short countStation = 0;
  while (strncmp(station,  nodeList[countStation].name, 100))
    {
      countStation +=1;
    }
  return countStation;
}



//printStations
void printConnections(struct node *station)
{
  printf("Connections:\n");
  struct adjList **dp = &(station->connections);
  while ((*dp) != NULL) {
    printf("%s\n", (*dp)->node->name);
    dp = &((*dp)->next);

  }

}

int isInLineList (struct line *lineList, unsigned short line) {
  struct line *currentLine = lineList;
  while (currentLine != NULL) {
    if (currentLine->number == line) {
      return 1;
    }
    else {
      currentLine = currentLine->next;
    }
  }
  return 0;
}
// returns 1 if currentStation is connected with endStation thorugh line line but not thorugh previousStation.
int isConnected (struct node *currentStation, struct node *previousStation, struct node *endStation, unsigned short line) {
  struct adjList **dp = &(currentStation->connections);
  if (currentStation == endStation) { //basfall
    return 1;
  } 
  while ((strncmp((*dp)->node->name, endStation->name, 100) != 0)) /*&& isInLineList((*dp)->lines, line))*/ {
    if (((*dp)->next) != NULL) {
      if (isInLineList ((*dp)->lines, line) == 1) {
	if (strncmp((*dp)->node->name, previousStation->name, 100) == 0) {
	  dp = &((*dp)->next);
	}
	else {
	  previousStation = currentStation; //CHECK NULL
	  currentStation = ((*dp)->node);
	  dp = &((*dp)->node->connections);
	}
      }
      else {
	dp = &((*dp)->next); //CHECK NULL
      }
    }
    else {
      return 0;
    }
  }
  if (isInLineList((*dp)->lines, line)) {
    return 1;
  }
  else {
    return 0;
  }
}




struct node *findNextStation (struct node *currentStation, struct node *endStation, unsigned short line) {
  
  struct adjList **dp = &(currentStation->connections);
  if (isInLineList((*dp)->lines, line) == 1) {
    if (isConnected((*dp)->node, currentStation, endStation, line)) {
      return (*dp)->node;
    }
  }
    while ((*dp)->next != NULL) { //tar med basfallet
    if (isInLineList((*dp)->lines, line) == 1) {
      if (isConnected((*dp)->node, currentStation, endStation, line)) {
	return (*dp)->node;
      }
      else {
	dp = &((*dp)->next);
      }
    }
    else {
      dp = &((*dp)->next);
    }
  } 


  return NULL; 
}

//find which lines that connects two nodes
unsigned short *linesConnectingStations(struct node* station1, struct node* station2, unsigned short *busLineList) {
  int i= 0;
  int j=0;
  unsigned short *connectionList = malloc(sizeof(unsigned short)*50); 
  struct node* nextStation;
  
  for (int k = 0; k < 50; k++) {
    connectionList[k] = 0;
  }

  while (busLineList[i] != 0) {
    
    nextStation = findNextStation(station1, station2, busLineList[i]);
    if (nextStation == NULL) { i++;}
    else { 
      if (isConnected(nextStation, station1, station2, busLineList[i]) == 1) {
	while (connectionList[j] != 0) {
	  j++;
	}
      }
      connectionList[j] = busLineList[i]; 
      j = 0;
      i++;
    }
    
    
  }
  return connectionList;
}

unsigned short findTimeAdjacentStation (struct node *station1, struct node *station2) {
  struct adjList **dp = &(station1->connections);
  while (strncmp((*dp)->node->name, station2->name, 100) != 0) {
    dp = &(*dp)->next;
  } 
  return (*dp)->time;
}


void printTrip (struct node *startStation, struct node *endStation, unsigned short line) {
  int time = 0;
  struct node * currentStation = startStation;
  struct node * nextStation;
  printf("Busslinje: %d\n", line);
  printf("Start: %s\n", startStation->name);
  while ((currentStation != NULL) && ((strncmp(currentStation->name, endStation->name, 100)) != 0)) {
    nextStation = findNextStation(currentStation, endStation, line);
    if (nextStation == NULL) { break; }
    time += findTimeAdjacentStation(currentStation, nextStation);
    currentStation = findNextStation(currentStation, endStation, line);
    printf("%s\n", currentStation->name); 
  }
  if (nextStation == NULL) {
    printf("ERROR - stations not connected\n");
  }
  else {
    printf("Time: %d\n", time);
    
  }
}

struct node* findStation(char * station, struct node* stationList, unsigned short numberOfStations) { //Se upp för segfault om man försöker skriva NULL
  int i = 0;
  while (strncmp(station, stationList[i].name, 100) != 0) {
    i++;
    if (i == numberOfStations) {
      return NULL;
    }
  }
  return (stationList + i);
}

void printPossibleTrips(struct node* station1, struct node* station2, unsigned short* lineList) {
  if ((station1 == NULL) || (station2 == NULL)) { 
    printf("There is no station with this name.\n");
  }
  else {
    unsigned short* busLineList = linesConnectingStations(station1, station2, lineList);
    int i = 0;
    while (busLineList[i] != 0) {
      printTrip(station1, station2, busLineList[i]);
      i++;
    }
  }
}
  

//int * numberOfStations
/*
int main (int argc, char* argv[])
{
 
  unsigned short numberOfStations = 5;
  if (argc == 2)
    {
      numberOfStations = atoi(argv[1]);
    }
  
  struct node *nodeList = malloc(sizeof(struct node)*numberOfStations); //2 = numberOfStations
  struct node a = createNode("Polacksbacken");
  struct node b = createNode("Grindstugan");
  struct node c = createNode("Storgatan");
  struct node d = createNode("Wallstreet");
  struct node e = createNode("Levertinsgatan");
  nodeList[0] = (a);
  nodeList[1] = (b);
  nodeList[2] = (c);
  nodeList[3] = (d);
  nodeList[4] = (e);

  //addToAdjList ((*nodeList), (*(nodeList +1)), 14);
  addToAdjList (nodeList, nodeList + 1, 13);
  addToAdjList (nodeList, nodeList + 2, 37);
  addToAdjList (nodeList, nodeList + 3, 50);
  addToAdjList (nodeList, nodeList + 4, 42);
  
  */
  //FILEREADER
  //char buffer[1024];
  //FILE *inputFile;
/*
  inputFile = fopen("nätverk.txt", "r");
  if (inputFile == NULL) {
    perror("\"nätverk.txt\" ");
    return (-1);
  } 
  unsigned short numberOfStations2 = countStations(inputFile);
  //printf("%d\n", numberOfStations2);
  rewind(inputFile);
  unsigned short *busLineList = createBusLineList(inputFile);
  printf("%d\n", busLineList[0]);

  rewind(inputFile);
  
  struct node *nodeList = createNodeList(inputFile, numberOfStations2);
  
  printf("\nNamn: %s\n", nodeList[90].name);
  //printConnections(&nodeList[2]);
  //printf("%s connects with %s through line %d\n", nodeList[2].name, nodeList[2].connections->node->name, nodeList[2].connections->lines->next->number);
  //unsigned short *lineList1 = linesConnectingStations(&nodeList[1], &nodeList[2], busLineList);
  //printf("\nDet här ska va 10:%d\n", lineList1[1]);

  printTrip(&(nodeList[1]), &(nodeList[2]), 20);
  struct node* testStation = findStation("Prastgardsgatan", nodeList, numberOfStations2);
  if (testStation != NULL) {
    printf("Station Bio: %s\n", (testStation)->name);
  }
  */
  //printTrip(&nodeList[3], &nodeList[4], 2);

  //TEST AV NYA FUNKTIONERNA ------------------------------------------------------------------------------

  //Bugg när man söker med Centralstationen och Grindstugan//
/*
  struct node* station1 = findStation("Centralstationen", nodeList, numberOfStations2);
  struct node* station2 = findStation("Lingonvagen", nodeList, numberOfStations2);
  printPossibleTrips(station1, station2, busLineList);
*/
  //TEST AV NYA FUNKTIONERNA ------------------------------------------------------------------------------

  // skriv ut test
  /* printf("Stationsnamn 1: %s\nStationsnamn 2: %s\nTid mellan stationerna: %d\nTid till nästa: %d\n och: %d\n och: %d\n", a->name, b->name, a->connections->time, a->connections->next->time, a->connections->next->next->time, a->connections->next->next->next->time);
     printf("nodeList[0]->name: %s\nnodeList[1]->name: %s\n", ((*nodeList)->name), (*(nodeList + 1))->name);

  */
  /*
  printConnections(nodeList);
 
  deleteNode("Grindstugan", nodeList, &numberOfStations);
  //printf("nodeList[0]->name: %s\nnodeList[1]->name: %s\n", nodeList->name, (nodeList +1)->name);

  printConnections(nodeList);
  printf("NumberOfStations: %d\n", numberOfStations);

  deleteConnection(nodeList, nodeList + 2);
  printConnections(nodeList);

  free(nodeList);
  */
  // return 0;
// } 
