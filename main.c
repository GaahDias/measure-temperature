#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "include/util.h"
#include "include/colors.h"

void measureTemperature();
void installSensors(FILE *fpath);

int main(int argc, char *argv[]) {
    measureTemperature();
    
    return 0;
}

void measureTemperature() {
    FILE *fp;
    FILE *fpath;
    char output[32];
    char temp[150];
    bool flag = false;

    installSensors(fpath);

    fp = popen("sensors", "r");

    while(fscanf(fp, "%s", output) == 1) {
        strcat(output, " ");
        //printf("\n---%s", output);

        if(strstr(output, "Package")) {
            flag = true;
        }

        if(flag == true) {
            if(strstr(output, "(")) {
                flag = false;
                break;
            }
            strcat(temp, output);
        }
    }

    strtok(temp, ":");
    strcpy(temp, strtok(NULL, ":\n"));

    printf(HRED);
    printf("CPU Temperature:%s\n", temp);

    pclose(fp);

}

void installSensors(FILE *fpath) {
    fpath = fopen("/usr/bin/sensors", "r");

    if(fpath == NULL) {
        char cmd[50];
        printf("Command failed. Downloading lm-sensors.\n");

        getInstall(gpm(), cmd);
        system(cmd);
        
        system("clear");
        printf("Application downloaded successfully. Running the program...\n");
        sleep(3);

        measureTemperature();
        exit(0);
    }

    fclose(fpath);
}

