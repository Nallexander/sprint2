#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filereader.h"
#include "reseplanerare.h"



/***
Return true (1) and inserts element at the first free slot in list iff element is not in list. Returns false (0) otherwise. 
\param list An array of stations in the system, an empty slot is represented by the string "NOTASTATION". 
\param element The string that will be sought for in list. Can not be "NOTASTATION".
\return 1 (true) if element is not in list, 0 (false) otherwise. 

 */
int isUnique (char **list, char *element) {
  int counter = 0;
  while ((strncmp(list[counter], "NOTASTATION", 100)) != 0) {
    if (strncmp(list[counter], element, 100) == 0) {
      return 0;
    } 
    counter += 1;    
  }
  strdup(element);
  list[counter] = element;
  return 1;
}

/***
Returns the number of unique strings (inbetween commas, see nätverk.txt) in inputFile.
\param inputFile A file containing the stations for the system.
\return The number of unique stations in inputFile.
*/

unsigned short countStations(FILE *inputFile) {
  int counter = 0;
  char *uniqueNodes[1024];
  char number[1024];
  char node[1024];
  char connection[1024];
  char time[1024];
  for (int i = 0; i != 1024; i++) {
    uniqueNodes[i] = "NOTASTATION";
  }
  while (!feof(inputFile)) {
    fscanf(inputFile, "%[^,], %[^,], %[^,], %[^\n]", number, node, connection, time);
    if (isUnique(uniqueNodes, strdup(node))) {
      counter += 1;
    }
    if (isUnique(uniqueNodes, strdup(connection))) {
      counter += 1;
    }
  }
  return counter;
}

/***
Returns a list of the different ints (before the first comma on every line, see nätverk.txt) in inputFile.
\param inputFile The file containing the buslines.
\return A list of all different ints before the first comma on every line in inputLine.
*/

unsigned short *createBusLineList(FILE *inputFile) {
  unsigned short *lineList = malloc(sizeof(unsigned int)*100);
  char number[1024];
  char node[1024];
  char connection[1024];
  char time[1024];

  for (int i = 0; i < 100; i++) {
    lineList[i] = 0;
  }
  while (!feof(inputFile)) {
    fscanf(inputFile, "%[^,], %[^,], %[^,], %[^\n]", number, node, connection, time);
    for (int i = 0; i < 100; i++) {
      if (lineList[i] == 0) {
	lineList[i] = atoi(number);
	break;
      }
      if (atoi(number) == lineList[i]) {	
	break;
      }
    }
    
  }
  
  return lineList;
}
/***
Creates a list of nodes with one node for every unique string inbetween commas (again, see nätverk.txt) in inputFile
\param inputFile A file containing all stations for the system.
\param numberOfStations The number of unique stations in inputFile.
*/
struct node *createNodeList(FILE *inputFile, unsigned short numberOfStations) //numberOfStations statiskt i hela programmet
{
  int counter = 0;
  char *uniqueNodes[numberOfStations];
  char number[1024];
  char node[1024];
  char connection[1024];
  char time[1024];
  struct node *nodeList = malloc(sizeof(struct node)*numberOfStations+1);
  for (int i = 0; i != numberOfStations; i++) {
    uniqueNodes[i] = "NOTASTATION";
  }
  while (!feof(inputFile)) 
    {
      fscanf(inputFile, "%[^,], %[^,], %[^,], %[^\n]", number, node, connection, time);
      if (isUnique(uniqueNodes, strdup(node))) 
	{
	  if (isUnique(uniqueNodes, strdup(connection)))
	    {
	      nodeList[counter] = createNode(strdup(node));
	      counter += 1;
	      nodeList[counter] = createNode(strdup(connection));
	      counter += 1;
	      addToAdjList(&nodeList[counter-2], &nodeList[counter-1], atoi(time), atoi(number));
	      addToAdjList(&nodeList[counter-1], &nodeList[counter-2], atoi(time), atoi(number));
	    }
	  else
	    {
	      nodeList[counter] = createNode(strdup(node));
	      counter += 1;
	      addToAdjList(&nodeList[counter-1], &nodeList[findNodeListNumber(nodeList, strdup(connection))], atoi(time), atoi(number));
	      addToAdjList(&nodeList[findNodeListNumber(nodeList, strdup(connection))], &nodeList[counter-1], atoi(time), atoi(number));
	    }

	}
      else 
	{
	  if (isUnique(uniqueNodes, strdup(connection)))
	    {
	      nodeList[counter] = createNode(strdup(connection));
	      counter += 1;
	      addToAdjList(&nodeList[counter-1], &nodeList[findNodeListNumber(nodeList, strdup(node))], atoi(time), atoi(number));
	      addToAdjList(&nodeList[findNodeListNumber(nodeList, strdup(node))], &nodeList[counter-1], atoi(time), atoi(number));
	    }
	  else 
	    {
	      addToAdjList(&nodeList[findNodeListNumber(nodeList, strdup(node))], &nodeList[findNodeListNumber(nodeList, strdup(connection))], atoi(time), atoi(number));
	      addToAdjList(&nodeList[findNodeListNumber(nodeList, strdup(connection))], &nodeList[findNodeListNumber(nodeList, strdup(node))], atoi(time), atoi(number));
	    }
	}
    }
  

  return nodeList;
}
/*
int main() {
  char buffer[1024];
  FILE *inputFile;

  inputFile = fopen("nätverk.txt", "r");
  if (inputFile == NULL) {
    perror("\"nätverk.txt\" ");
    return (-1);
  }   
  char number[1024];
  char node[1024];
  char connection[1024];
  char time[1024];

  char *testList[3];
  testList[0] = "Test1";
  testList[1] = "Test2";
  testList[2] = "Test3";

 printf("%d\n", countStations(inputFile));

  while (!feof(inputFile)) {
    if(fgets(buffer, 1024, inputFile) != NULL) {
      fscanf(inputFile, "%[^,], %[^,], %[^,], %[^\n]", number, node, connection, time);
      //  printf("Number: %s\nNode: %s\nConnection: %s\nTime: %s\n", number, node, connection, time);
    }
  }
  
  fclose(inputFile);
  
  return 0;
}
*/
