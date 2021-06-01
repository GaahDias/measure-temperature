#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "include/util.h"
#include "include/colors.h"
#include "include/temperature.h"

int main() {
    int *allTemps = calloc(3, sizeof(int));
    allTemps = getTemperatures(measureTemperature());
  
    printf("CPU Temperature: ");
    printf(BHGRN);

    if(allTemps[0] >= allTemps[2]) {
        printf(BHRED);
    } else if(allTemps[0] >= allTemps[1] && allTemps[0] < allTemps[2]) {
        printf(BHYEL);
    }

    printf("%d.0°C\n", allTemps[0]);
    free(allTemps);
    
    return 0;
}
