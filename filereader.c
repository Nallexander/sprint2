#include <stdio.h>
#include <stdlib.h>

int main() {
  char buffer[1024];
  FILE *inputFile;

  inputFile = fopen("nätverk.txt", "r");
  if (inputFile == NULL){
    perror("\"nätverk.txt\" ");
    return (-1);
  }
  
  char number[1024];
  char node[1024];
  char connection[1024];
  char time[1024];

  while (!feof(inputFile)) {
    if(fgets(buffer, 1024, inputFile) != NULL) {
      fscanf(inputFile, "%[^,], %[^,], %[^,], %[^\n]", number, node, connection, time);
      //  printf("Number: %s\nNode: %s\nConnection: %s\nTime: %s\n", number, node, connection, time);
    }
  }
  
  fclose(inputFile);
  
  return 0;
}
