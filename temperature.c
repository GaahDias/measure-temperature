#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void installSensors(FILE *fpath);

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

    output = malloc(120 * sizeof(char));

    while(fscanf(fp, "%s", output) == 1) {
        strcat(output, " ");

        //start in Package
        if(strstr(output, "Package")) {
            flag = true;
            temp = malloc(120 * sizeof(char));
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

//function that returns an array with current, high, and critical temperature
int* getTemperatures(char *sensor) {
    //declaring array that will receive all the temperatures
    int* tempValues = calloc(3, sizeof(int));

    //current temperature
    char *temp = malloc(85 * sizeof(char));
    int tempValue;

    strcpy(temp, sensor);
    strtok(temp, "(");

    tempValue = atoi(temp);
    free(temp);
    tempValues[0] = tempValue;

    //high temperature
    char *highTemp = malloc(85 * sizeof(char));
    int highTempValue;

    strcpy(highTemp, sensor);
    strtok(highTemp, "=");
    strcpy(highTemp, strtok(NULL, ""));

    highTempValue = atoi(highTemp);
    free(highTemp);
    tempValues[1] = highTempValue;

    //critical temperature
    char *critTemp = malloc(85 * sizeof(char));
    int critTempValue;

    strcpy(critTemp, sensor);
    strtok(critTemp, "=");
    strcpy(critTemp, strtok(NULL, ""));
    strtok(critTemp, "=");
    strcpy(critTemp, strtok(NULL, ""));

    critTempValue = atoi(critTemp);
    free(critTemp);
    tempValues[2] = critTempValue;

    return tempValues;
} 