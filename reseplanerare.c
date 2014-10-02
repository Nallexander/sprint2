#include <stdio.h>
#include <stdlib.h>

struct edge {
  unsigned short bus_line;
  struct node *station1;
  struct node *station2;
  unsigned short time; 
} edge; 


struct node {
  char * name;
  struct connection * connections; 
  
} node;

struct node createNode(char * name) 
{
  struct node station  = { .name = name };
  return station;
}

struct edge connectNodes(unsigned short bus_line, struct node *station1, struct node *station2, unsigned short time)
{
  struct edge connection = { .bus_line = bus_line, .station1 = station1, .station2 = station2, .time = time };
    return connection;

}


int main ()
{
  struct node * nodeList = malloc(sizeof(struct node)*2);
  struct node a = createNode("Polacksbacken");
  struct node b = createNode("Grindstugan");
  nodeList[0] = a;
  nodeList[1] = b;

  //Lägg till edgeList
  
  struct edge ab = connectNodes(110, &a, &b, 10);

  // test
  printf("Stationsnamn 1: %s\nStationsnamn 2: %s\nTid mellan stationerna: %d\n", nodeList[0].name, nodeList[1].name, ab.time );

  return 0;
} 
