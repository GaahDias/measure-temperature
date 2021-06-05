#include "include/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main();

//get the correct package manager
char *getPackageManager() {
    char *package[] = {"pamac", "apt", "pacman", "yum", "dnf"};

    for (int i = 0; i < sizeof(package) / 8; i++) {
        char path[50];

        strcpy(path, "/usr/bin/");
        strcat(path, package[i]);
        FILE *p = fopen(path, "r");

        if (p != NULL) {
            fclose(p);
            return package[i];
        }
    }
}

//command to install lm-sensors
void cmdInstall(char *pm, char *str) {
    char install[50];

    strcpy(install, "sudo ");

    strcat(install, pm);

    if (!strcmp(pm, "pacman")) {
        strcat(install, " -S lm-sensors");
    } else {
        strcat(install, " install lm-sensors");
    }

    strcpy(str, install);
}

//call the two functions
void installSensors(FILE *fpath) {
    fpath = fopen("/usr/bin/sensors", "r");

    if(fpath == NULL) {
        char cmd[50];
        printf("Command failed. Downloading lm-sensors.\n");

        cmdInstall(getPackageManager(), cmd);
        system(cmd);
        
        system("clear");
        printf("Application downloaded successfully. Running the program...\n");
        sleep(2);

        main();
        exit(1);
    }

    fclose(fpath);
}
