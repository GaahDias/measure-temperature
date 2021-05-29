#include "include/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void getInstall(char * pm, char * str) {
    char install[50];

    strcpy(install, "sudo ");

    strcat(install, pm);

    if(!strcmp(pm, "pacman")) {
        strcat(install, " -S lm-sensors");
    } else {
        strcat(install, " install lm-sensors");
    }

    strcpy(str, install);
}

char * gpm() {
  char * package[] = {
    "apt",
    "pamac",
    "pacman",
    "yum",
    "dnf" 
  };

  for (int i = 0; i < sizeof(package) / 8; i++) {
    char path[50];

    strcpy(path, "/usr/bin/");
    strcat(path, package[i]);
    FILE * p = fopen(path, "r");

    if (p != NULL) {
      fclose(p);
      return package[i];
    }
    fclose(p);
  }
  
  return NULL;
}

void sleep(int sec) {
    time_t end = time(NULL) + sec;

    while(time(NULL) < end);
}
