#include <stdio.h>
#include <stdlib.h>

struct node {
  char * name;
  struct adjList *connections;   
};

struct adjList {
  struct node *node;
  unsigned short time;
  struct adjList *next;
};

struct node *createNode(char * name) 
{
  struct node *station = malloc(sizeof (struct node));
  station->name = name;
  station->connections = NULL;
  return station;
}

struct adjList * createAdjList(struct node * node, unsigned short time) {
  struct adjList *c = malloc(sizeof (struct adjList));
  c->node = node;
  c->time = time;
  c->next = NULL;
  return c;
}

// seperate module
void addToAdjList (struct node *Node, struct node *connectionNode, unsigned short time){
    struct adjList **dp = &(Node->connections);
    while (*dp != NULL) { 
      dp = &((*dp)->next);
    }
    *dp = (createAdjList(connectionNode, time));
}


void deleteNode (char *deleteName, struct node *nodeList, int *numberOfStations)
{
  for (int i = 0; i <= (*numberOfStations - 1); i++) {
    if (deleteName == nodeList[i].name) {
      nodeList[i] = nodeList[*numberOfStations];
      nodeList[(*numberOfStations) - 1] = NULL;	
      *numberOfStations -= 1;
    }
    else {
      struct adjList **dp = &(nodeList[i].connections);
      while ((dp->name != deleteName) || (*dp != NULL)) { 
      dp = &((*dp)->next);
      }
      if (dp->name == deleteName) {
	struct adjList **dp2 = &dp;
	*dp = *(dp->next);
	free(dp2);
    }
    }
  }
} 


//int * numberOfStations
int main (int argc, char* argv[])
{
  struct node *nodeList = malloc(sizeof(struct node)*(atoi(argv[1]))); //2 = numberOfStations
  struct node *a = createNode("Polacksbacken");
  struct node *b = createNode("Grindstugan");
  nodeList[0] = *(a);
  nodeList[1] = *(b);

  addToAdjList ((nodeList), (nodeList +1), 14);
  addToAdjList (a, b, 13);
  addToAdjList (a, b, 37);
  addToAdjList (a, b, 50);
  addToAdjList (a, b, 50);

  // skriv ut test
  printf("Stationsnamn 1: %s\nStationsnamn 2: %s\nTid mellan stationerna: %d\nTid till nästa: %d\n och: %d\n och: %d\n", a->name, b->name, a->connections->time, a->connections->next->time, a->connections->next->next->time, a->connections->next->next->next->time);
  printf("nodeList[0]->name: %s\nnodeList[1]->name: %s\n", nodeList->name, (nodeList +1)->name);
  free(a);
  free(b);

  return 0;
} 
