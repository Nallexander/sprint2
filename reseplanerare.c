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


void deleteNode (char *deleteName, struct node *nodeList, unsigned short *numberOfStations)
{
  for (int i = 0; i <= (*numberOfStations - 1); i++) {
    if (deleteName == nodeList[i].name) {
      nodeList[i] = nodeList[(*numberOfStations)-1];	
      *numberOfStations -= 1;
    }
    else {
      struct adjList **dp = &(nodeList[i].connections);
      while (((*dp)->node->name != deleteName) || (*dp != NULL)) { 
      dp = &((*dp)->next);
      }
      if ((*dp)->node->name == deleteName) {
	struct adjList *dp2 = (*dp);
	dp = &((*dp)->next);
	free(dp2);
    }
    }
  }
} 


//printStations
void printConnections(struct node *station)
{
  printf("Connections:\n");
  struct adjList **dp = &station->connections;
  while ((*dp) != NULL) {
    printf("%s\n", (*dp)->node->name);
    dp = &((*dp)->next);
  }

}


//int * numberOfStations
int main (int argc, char* argv[])
{

  unsigned short numberOfStations = 5;
  if (argc == 2)
    {
      numberOfStations = atoi(argv[1]);
    }

  struct node *nodeList = malloc(sizeof(struct node)*numberOfStations); //2 = numberOfStations
  struct node *a = createNode("Polacksbacken");
  struct node *b = createNode("Grindstugan");
  struct node *c = createNode("Storgatan");
  struct node *d = createNode("Wallstreet");
  struct node *e = createNode("Levitinsgatan");
  nodeList[0] = *(a);
  nodeList[1] = *(b);
  nodeList[2] = *(c);
  nodeList[3] = *(d);
  nodeList[4] = *(e);

  addToAdjList ((nodeList), (nodeList +1), 14);
  addToAdjList (a, b, 13);
  addToAdjList (a, c, 37);
  addToAdjList (a, d, 50);
  addToAdjList (a, e, 42);
  

  // skriv ut test
  printf("Stationsnamn 1: %s\nStationsnamn 2: %s\nTid mellan stationerna: %d\nTid till nästa: %d\n och: %d\n och: %d\n", a->name, b->name, a->connections->time, a->connections->next->time, a->connections->next->next->time, a->connections->next->next->next->time);
  printf("nodeList[0]->name: %s\nnodeList[1]->name: %s\n", nodeList->name, (nodeList +1)->name);


  printConnections(a);

  deleteNode("Polacksbacken", a, &numberOfStations);
  //printf("nodeList[0]->name: %s\nnodeList[1]->name: %s\n", nodeList->name, (nodeList +1)->name);

  printConnections(a);

  free(a);
  free(b);

  return 0;
} 
