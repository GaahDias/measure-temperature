#include <stdio.h>

#ifndef terminal_temperatura_h
#define terminal_temperatura_h

void getInstall(char * pm, char * str);
char* getPackageManager();
void installSensors(FILE *fpath);
void sleep(int sec);

#endif