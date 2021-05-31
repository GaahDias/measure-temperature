#include <stdio.h>

#ifndef util_temperature_h
#define util_temperature_h

void getInstall(char * pm, char * str);
char* getPackageManager();
void installSensors(FILE *fpath);
void sleep(int sec);

#endif