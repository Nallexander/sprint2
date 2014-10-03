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

void addToAdjList (struct node *node1, struct node *node2, unsigned short time){
  if (node2->connections == NULL){
    struct adjList *c = malloc(sizeof (struct adjList));
    c->node = node1;
    c->time = time;
    c->next = NULL;
    node2->connections = c;
  }
  else {
    if (node2->connections->next != NULL){ // Något fel här!]
    addToAdjList (node1, node2->connections->node, time);
  }
  else {
    struct adjList *d = malloc(sizeof (struct adjList));
    d->node = node1;
    d->time = time;
    d->next = NULL;
    node2->connections->next = d;
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

  // test
  printf("Stationsnamn 1: %s\nStationsnamn 2: %s\nTid mellan stationerna: %d\nTid till nästa: %d\n och: %d\n", a->name, b->name, a->connections->time, a->connections->next->time, a->connections->next->next->time);
  free(a);
  free(b);

  return 0;
} 
