#ifndef RESEPLANERARE_H
#define RESEPLANERARE_H

struct node {
  char * name;
  struct adjList *connections;   
};

struct line {
  unsigned short number;
  struct line *next;
};

struct adjList {
  struct node *node;
  unsigned short time;
  struct line *lines;
  struct adjList *next;
};

struct node createNode(char * name);
struct adjList *createAdjList(struct node * node, unsigned short time, unsigned short line);
void addToAdjList(struct node *Node, struct node *connectionNode, unsigned short time, unsigned short line);
void deleteName(struct node *Node, char *name);
void deleteNode(char *name, struct node *nodeList, unsigned short *numberOfStations);
void deleteConnection(struct node *node1, struct node *node2);
unsigned short findNodeListNumber(struct node * nodeList, char * station);
void printConnections(struct node *station);

#endif
