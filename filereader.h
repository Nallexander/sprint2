#ifndef FILEREADER_H
#define FILEREADER_H
#include <stdio.h>

/***
Return true (1) and inserts element at the first free slot in list iff element is not in list. Returns false (0) otherwise. 
\param list An array of stations in the system, an empty slot is represented by the string "NOTASTATION". 
\param element The string that will be sought for in list. Can not be "NOTASTATION".
\return 1 (true) if element is not in list, 0 (false) otherwise. 
 */
int isUnique (char **list, char *element);
/***
Returns the number of unique strings (inbetween commas, see nätverk.txt) in inputFile.
\param inputFile A file containing the stations for the system.
\return The number of unique stations in inputFile.
*/
unsigned short countStations(FILE *inputFile);
/***
Returns a list of the different ints (before the first comma on every line, see nätverk.txt) in inputFile.
\param inputFile The file containing the buslines.
\return A list of all different ints before the first comma on every line in inputLine.
*/
unsigned short *createBusLineList(FILE *inputFile);
/***
Creates a list of nodes with one node for every unique string inbetween commas (again, see nätverk.txt) in inputFile
\param inputFile A file containing all stations for the system.
\param numberOfStations The number of unique stations in inputFile.
*/
struct node *createNodeList(FILE *inputFile, unsigned short numberOfStations);

#endif
