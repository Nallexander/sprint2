/**
\author Alexander Lind & Anton Kallbom 

*/
	
#ifndef RESEPLANERARE_H
#define RESEPLANERARE_H

struct node {
  char * name; ///< Name of station
  struct adjList *connections; ///< List of connections
};

struct line {
  unsigned short number; ///< Number of busline.
  struct line *next; ///< Next member of the line list.
};

struct adjList {
  struct node *node; ///< The connected station.
  unsigned short time; ///< The time between the stations.
  struct line *lines; ///< The linest that connect the stations.
  struct adjList *next; ///< The next connection.
};
/** @brief Creates a new node with the name name and an empty list of connections.
 * 
 * 
 * 
 * @param name The name of the node.
 * @return A node with name name.
 */
struct node createNode(char * name); 
/// Creates a new linked list with newLine as the first element and no next element
/// \param newLine - The number of the line.
/// \return A line list with number newline and next NULL.
struct line * createLineList (unsigned short newLine);


struct adjList *createAdjList(struct node * node, unsigned short time, unsigned short line);
void addToAdjList(struct node *Node, struct node *connectionNode, unsigned short time, unsigned short line);
void deleteName(struct node *Node, char *name);
void deleteNode(char *name, struct node *nodeList, unsigned short *numberOfStations);
void deleteConnection(struct node *node1, struct node *node2);
unsigned short findNodeListNumber(struct node * nodeList, char * station);
void printConnections(struct node *station);
struct node* findStation(char* station, struct node* stationList, unsigned short numberOfStations);
void printPossibleTrips(struct node* station1, struct node* station2, unsigned short* lineList);

#endif
