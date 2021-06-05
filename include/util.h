#ifdef _WIN32
#error Sorry, Windows is not compatible with this application.
#endif

#include <stdio.h>

#ifndef util_temperature_h
#define util_temperature_h

void cmdInstall(char * pm, char * str);
char* getPackageManager();
void installSensors();

#endif
