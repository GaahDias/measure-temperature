#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


#ifndef util_temperature_h
#define util_temperature_h

void getInstall(char * pm, char * str);
char* getPackageManager();
void installSensors(FILE *fpath);
#ifdef _WIN32
void sleep(int seconds);
#endif

#endif
