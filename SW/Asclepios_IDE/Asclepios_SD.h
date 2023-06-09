#include "Asclepios_IDE.h"

#ifndef ASCLEPIOS_SD_H
#define ASCLEPIOS_SD_H


void SD_setup();
void SD_update();
void appendFile(fs::FS &fs, const char * path, const char * message);
void writeFile(fs::FS &fs, const char * path, const char * message);
void readFile(fs::FS &fs, const char * path);
void renameFile(fs::FS &fs, const char * path1, const char * path2);


#endif // #define ASCLEPIOS_SD_H