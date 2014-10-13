#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isUnique (char **list, char *element) {
  int counter = 0;
  while ((strncmp (list[counter], "NOTASTATION", 100)) != 0) {
    if (strncmp (list[counter], element, 100) == 0) {
      return 0;
    } 
    
    counter += 1;
  }
  list[counter] = element;
  return 1;
}

unsigned short countStations(FILE *inputFile) {
  int counter = 0;
  char buffer[1024];
  char *uniqueNodes[1024];
  char number[1024];
  char node[1024];
  char connection[1024];
  char time[1024];
  uniqueNodes[0] = "FIRST";
  for (int i = 1; i != 1024; i++) {
    uniqueNodes[i] = "NOTASTATION";
  }
  while (!feof(inputFile)) {
    if(fgets(buffer, 1024, inputFile) != NULL) {
      fscanf(inputFile, "%[^,], %[^,], %[^,], %[^\n]", number, node, connection, time);
      if (isUnique(uniqueNodes, node)) {
	counter += 1;
      }
      if (isUnique(uniqueNodes, connection)) {
	counter += 1;
      }
    }
  }
  return counter;
}

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
