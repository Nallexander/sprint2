#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filereader.h"


#ifndef _INCL_GUARD_RESE
#include "reseplanerare.c"
#endif



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


struct node *createNodeList(FILE *inputFile, unsigned short numberOfStations)
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
