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

void deleteName (struct node *Node, char *name) {
  struct adjList **currentAdjList = &(Node->connections);
  while ((*currentAdjList != NULL)) {
    
    if  ((*currentAdjList)->node->name != name)
      {
	currentAdjList = &((*currentAdjList)->next);
      }
    else {
      struct adjList *dp2 = *currentAdjList;
      currentAdjList = &((*currentAdjList)->next);
      //free(dp2);
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

  struct node *e = createNode("Levertinsgatan");
  nodeList[0] = (*a);
  nodeList[1] = (*b);
  nodeList[2] = (*c);
  nodeList[3] = (*d);
  nodeList[4] = (*e);

  //addToAdjList ((*nodeList), (*(nodeList +1)), 14);
  addToAdjList (nodeList, nodeList + 1, 13);
  addToAdjList (nodeList, c, 37);
  addToAdjList (nodeList, d, 50);
  addToAdjList (nodeList, e, 42);
  

  // skriv ut test
  /* printf("Stationsnamn 1: %s\nStationsnamn 2: %s\nTid mellan stationerna: %d\nTid till nästa: %d\n och: %d\n och: %d\n", a->name, b->name, a->connections->time, a->connections->next->time, a->connections->next->next->time, a->connections->next->next->next->time);
  printf("nodeList[0]->name: %s\nnodeList[1]->name: %s\n", ((*nodeList)->name), (*(nodeList + 1))->name);

  */
  printConnections(nodeList);
 
  deleteNode("Grindstugan", nodeList, &numberOfStations);
  //printf("nodeList[0]->name: %s\nnodeList[1]->name: %s\n", nodeList->name, (nodeList +1)->name);

  printConnections(nodeList);
  
  free(a);
  free(b);
  free(c);
  free(d);
  free(e);
  free(nodeList);

  return 0;
} 
