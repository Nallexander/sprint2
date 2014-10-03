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
} node;

struct adjList {
  struct node *node;
  unsigned short time;
  struct adjList *next;
}

struct node createNode(char * name) 
{
  struct node station  = { .name = name };
  return station;
}

void addToAdjList (struct node *node, struct adjList *adjList, unsigned short time){
  if (adjList->node != NULL){
    addToAdjList (&node, &(adjList + 1), time);
  }
  else adjList->node = node;
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
  struct node * nodeList = malloc(sizeof(struct node));
  struct node a = createNode("Polacksbacken");
  struct node b = createNode("Grindstugan");
  nodeList[0] = a;
  nodeList[1] = b;

  addToAdjList (nodeList[1], &(nodeList->adjList), 14);
  //Lägg till edgeList
  
  struct edge ab = connectNodes(110, &a, &b, 10);

  // test
  printf("Stationsnamn 1: %s\nStationsnamn 2: %s\nTid mellan stationerna: %d\n", nodeList[0].name, nodeList[1].name, ab.time );

  return 0;
} 
