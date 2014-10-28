#ifndef FILEREADER_H
#define FILEREADER_H

int isUnique (char **list, char *element);
unsigned short countStations(FILE *inputFile);
unsigned short *createBusLineList(FILE *inputFile);
struct node *createNodeList(FILE *inputFile, unsigned short numberOfStations);

#endif
