#include <stdio.h>
#include <stdlib.h>
/*
struct edge {
  unsigned short bus_line;
  struct node *station1;
  struct node *station2;
  unsigned short time; 
} edge; 
*/

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

void addToAdjList (struct node *node1, struct node *node2, unsigned short time){
  if (node2->connections == NULL){
    node2->connections = createAdjList(node1, time);
  }
  else {
    if (node2->connections->next == NULL){ // Något fel här!]
      node2->connections->next = createAdjList(node1, time);
    }
    else {
      struct adjList **dp = &(node2->connections->next);
	while (*dp != NULL) { 
	  dp = &((*dp)->next);
	}
      *dp = (createAdjList(node1, time));


    }

  }
}
/*
void connectNodes(struct node *station1, struct node *station2, unsigned short time)
{
  station1->adjList->node
  struct edge connection = { .station1 = station1, .station2 = station2, .time = time };
    return connection;

}
*/

int main ()
{
  //  struct node *nodeList = malloc(sizeof(struct node));
  struct node *a = createNode("Polacksbacken");
  struct node *b = createNode("Grindstugan");

  addToAdjList (b, a, 14);
  addToAdjList (b, a, 13);
  addToAdjList (b, a, 37);
  addToAdjList (b, a, 50);

  // test
  printf("Stationsnamn 1: %s\nStationsnamn 2: %s\nTid mellan stationerna: %d\nTid till nästa: %d\n och: %d\n och: %d\n", a->name, b->name, a->connections->time, a->connections->next->time, a->connections->next->next->time, a->connections->next->next->next->time);
  free(a);
  free(b);

  return 0;
} 
