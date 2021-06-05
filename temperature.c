#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void installSensors(FILE *fpath);

//function to get the only the cpu temperature from lm-sensors. basically string treatment
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

//function that will be called in main.c to update the temperature
char* getCurrentTemp(char *sensor) {
    char *temp = malloc(85 * sizeof(char));

    strcpy(temp, sensor);

    strtok(temp, "(");
    strtok(temp, "+");
    strcpy(temp, strtok(NULL, ""));

    return temp;
}