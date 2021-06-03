#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "include/util.h"
#include "include/colors.h"
#include "include/temperature.h"
#include <gtk/gtk.h>
#include <pthread.h>

void app_quit(GtkWidget *widget, gpointer data);
void *print_temperature();

static GtkWidget *cpu_temp;

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(app_quit), NULL);

    gtk_window_set_title(GTK_WINDOW(window), "Measure CPU Temperature");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    cpu_temp = gtk_label_new(NULL);
    gtk_grid_attach(GTK_GRID(grid), cpu_temp, 0, 0, 1, 1);

    gtk_widget_show_all(window);

    pthread_t tempThread;
    pthread_create(&tempThread, NULL, print_temperature, NULL);
    pthread_join(tempThread, NULL);

    gtk_main();

    return 0;
}

void *print_temperature() {
    while(1){
        char *sensor = measureTemperature();
        int *allTemps = getTemperatures(sensor);
        free(sensor);

        char *currentTemp = malloc(8 * sizeof(char));
        sprintf(currentTemp, "%d.0°C", allTemps[0]);
        free(allTemps); 
        
        gtk_label_set_text(GTK_LABEL(cpu_temp), currentTemp);     
        free(currentTemp);
        while(gtk_events_pending()) {
            gtk_main_iteration();
        }
    }
}

void app_quit(GtkWidget *widget, gpointer data) {
    exit(1);
    gtk_main_quit();
}