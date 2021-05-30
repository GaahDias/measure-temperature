#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "include/util.h"
#include "include/colors.h"

char* measureTemperature();
char* getTemperature(char *sensor);
char* getHighTemperature(char *sensor);
char* getCritTemperature(char *sensor);

int main(int argc, char *argv[]) {
    printf("CPU Temperature:%s", getTemperature(measureTemperature()));

    return 0;
}

//function to get the temperature (temp, high, crit) from lm-sensors. basically string treatment
char* measureTemperature() {
    //declaring variables
    FILE *fp;
    FILE *fpath;
    char output[32];
    char *temp;
    bool flag = false;

    //calling installSensors function (util.c)
    installSensors(fpath);

    //executing sensors, and treating string
    fp = popen("sensors", "r");

    while(fscanf(fp, "%s", output) == 1) {
        strcat(output, " ");

        //start in Package
        if(strstr(output, "Package")) {
            flag = true;
            temp = malloc(64 * sizeof(char));
        }

        if(flag == true) {
            //end in Core
            if(strstr(output, "Core")) {
                flag = false;
                break;
            }
            strcat(temp, output);
        }
    }

    strtok(temp, ":");
    strcpy(temp, strtok(NULL, ":\n"));

    pclose(fp);

    return temp;
}

char* getTemperature(char *sensor) {
    char *temp = malloc(32 * sizeof(char));

    strtok(sensor, "(");
    strcpy(temp, sensor);

    return temp;
} 

char* getHighTemperature(char *sensor) {
    char *highTemp = malloc(32 * sizeof(char));

    strtok(sensor, "=");
    strcpy(highTemp, strtok(NULL, ""));
    strtok(highTemp, ",");

    return highTemp;
}

char* getCritTemperature(char *sensor) {
    char *critTemp = malloc(32 * sizeof(char));

    strtok(sensor, "=");
    strcpy(critTemp, strtok(NULL, ""));

    strtok(critTemp, "=");
    strcpy(critTemp, strtok(NULL, ""));

    strtok(critTemp, ")");

    return critTemp;
}