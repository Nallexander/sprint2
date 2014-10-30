#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reseplanerare.h"
#include "filereader.h"
//#include "interface.h"

int main(void){
  puts("Välkommen!\n\n");

  int choice = -1;
  char *station = malloc(sizeof station);
  while (choice != 0){
    puts("== M E N Y ===============");
    puts("1. Skapa station");
    puts("2. Koppla två stationer");
    puts("3. Ta bort station");
    puts("4. Ta bort koppling");
    puts("5. Finn kortaste sträckan");
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
