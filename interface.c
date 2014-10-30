#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseplanerare.h"
#include "filereader.h"
//#include "interface.h"

int main(void){

  FILE *inputFile;
  inputFile = fopen("nätverk.txt", "r");
  if (inputFile == NULL) {
    perror("\"nätverk.txt\" ");
    return (-1);
  } 
  unsigned short numberOfStations = countStations(inputFile);
  rewind(inputFile);
  unsigned short *busLineList = createBusLineList(inputFile);
  printf("%d\n", busLineList[0]);
  rewind(inputFile);
  struct node *nodeList = createNodeList(inputFile, numberOfStations);

  puts("Välkommen!\n\n");

  char station1[50];
  char station2[50];
  strcpy(station1, "NOTASTATION");
  strcpy(station2, "NOTASTATION");  
      
  int choice = -1;
  char *station = malloc(sizeof station);
  while (choice != 0){
    puts("== M E N Y ===============");
    puts("1. Skapa station");
    puts("2. Koppla två stationer");
    puts("3. Ta bort station");
    puts("4. Ta bort koppling");
    puts("5. Finn kortaste sträckan");
    puts("6. Skriv ut möjliga resvägar mellan två stationer");
    puts("0. Avsluta");
    puts("");
    puts("Välj ett alternativ:");

    scanf("%d", &choice);
 
    switch(choice){
    case 1:
      
      puts("\nSkriv in namnet på den station du vill skapa:");
      scanf("%s", station);
      struct node a = createNode(station);
      printf("\n%s är nu skapad.\n\n", a.name);
      return 0;
    case 2:
      puts("\nDu valde 2.");
      return 0;
    case 3:
      puts("\nDu valde 3.");
      return 0;
    case 4:
      puts("\nDu valde 4.");
      return 0;
    case 5:
      puts("\nDu valde 5.");
      return 0;
    case 6:
      while (strncmp(station1, "NOTASTATION", 50) == 0) { //"NOTASTATION bytes mot alla stationsnamn?
	puts("Skriv namnet på station 1:");
	scanf("%s", station1);
      }
      while (strncmp(station2, "NOTASTATION", 50) == 0) {
	puts("Skriv namnet på station 2:");
	scanf("%s", station2);
      }   
      puts("Alternativ för din resa:");
      struct node* Station1 = findStation(station1, nodeList, numberOfStations);
      struct node* Station2 = findStation(station2, nodeList, numberOfStations);
      printPossibleTrips(Station1, Station2, busLineList);
      return 0;

    case 0:
      puts("\nDu valde att avsluta.");
      return 0;
    default:
      puts("\nVänligen använd endast 1-5 alternativt 0.");
    }
    puts("");
  }
  return 0;
}
