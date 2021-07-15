#ifdef _WIN32
#error Sorry, Windows is not compatible with this application.
#endif

#include <stdio.h>

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RESET "\e[0m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BCYN "\e[1;36m"
#define BYEL "\e[1;33m"
#ifndef util_temperature_h
#define util_temperature_h


void getSensorsInstallCommand(char* command);
char* getPackageManager();
char* getSuAgent();
void installSensors();

#endif
