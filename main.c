#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "include/util.h"
#include "include/colors.h"

char* measureTemperature();
int getTemperature(char *sensor);
int getHighTemperature(char *sensor);
int getCritTemperature(char *sensor);

int main() {
    printf("CPU Temperature: %d.0°C", getTemperature(measureTemperature()));
    
    return 0;
}

//function to get the temperature (temp, high, crit) from lm-sensors. basically string treatment
char* measureTemperature() {
    //declaring variables
    FILE *fp;
    FILE *fpath;
    char *output;
    char *temp;
    bool flag = false;

    //calling installSensors function (util.c)
    installSensors(fpath);

    //executing sensors, and treating string
    fp = popen("sensors", "r");

    output = malloc(80 * sizeof(char));

    while(fscanf(fp, "%s", output) == 1) {
        strcat(output, " ");

        //start in Package
        if(strstr(output, "Package")) {
            flag = true;
            temp = malloc(80 * sizeof(char));
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

    free(output);

    strtok(temp, ":");
    strcpy(temp, strtok(NULL, ":\n"));

    pclose(fp);

    return temp;
}

int getTemperature(char *sensor) {
    char *temp = malloc(48 * sizeof(char));
    int tempValue;

    strtok(sensor, "(");
    strcpy(temp, sensor);

    free(sensor);

    tempValue = atoi(temp);

    return tempValue;
} 

int getHighTemperature(char *sensor) {
    char *highTemp = malloc(48 * sizeof(char));
    int highTempValue;

    strtok(sensor, "=");
    strcpy(highTemp, strtok(NULL, ""));

    free(sensor);

    strtok(highTemp, ",");

    highTempValue = atoi(highTemp);

    return highTempValue;
}

int getCritTemperature(char *sensor) {
    char *critTemp = malloc(48 * sizeof(char));
    int critTempValue;

    strtok(sensor, "=");
    strcpy(critTemp, strtok(NULL, ""));

    free(sensor);

    strtok(critTemp, "=");
    strcpy(critTemp, strtok(NULL, ""));

    critTempValue = atoi(critTemp);

    return critTempValue;
}