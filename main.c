#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "include/util.h"
#include "include/colors.h"

void measureTemperature(char * argv[]) {
    FILE *fp;
    FILE *fpath;
    char output[32];
    char temp[150];
    bool flag = false;

    fpath = fopen("/usr/bin/sensors", "r");

    if(fpath == NULL) {
        printf("Command failed. Downloading lm-sensors.\n");

        char cmd[50];
        getInstall(gpm(), cmd);
        system(cmd);
        
        sleep(2);
        system("clear");

        printf("Application downloaded successfully. Running the program...\n");
        sleep(2);

        system(argv[0]);
        exit(0);
    }

    fclose(fpath);

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

int main(int argc, char * argv[]) {
    measureTemperature(argv);
    
    return 0;
}