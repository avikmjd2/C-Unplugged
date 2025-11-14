#ifndef SONG_H
#define SONG_H

#include "structures.h"


int addSong(char* name, char* singer, char* date, char* path, char* lyrics, int duration);
int deleteSong(char* name);


Lib* loadAllSong(char* filePath);
Song* findSong(char name[200], Lib* head);

#endif