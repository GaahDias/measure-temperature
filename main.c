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

static GtkWidget *current_temp;

int main(int argc, char *argv[]) {
    GtkWidget *window, *grid, *high_temp, *crit_temp;
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(app_quit), NULL);

    gtk_window_set_title(GTK_WINDOW(window), "Measure Temperature");
    gtk_window_set_default_size(GTK_WINDOW(window), 275, 150);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    current_temp = gtk_label_new(NULL);
    gtk_grid_attach(GTK_GRID(grid), current_temp, 0, 1, 1, 1);

    gtk_widget_show_all(window);

    pthread_t tempThread;
    pthread_create(&tempThread, NULL, print_temperature, NULL);
    pthread_join(tempThread, NULL);

    gtk_main();

    return 0;
}

void *print_temperature() {
    while(1){
        char labelText[] = "CPU Temperature: ";
        char *sensor = measureTemperature();
        char *currentTemp = getCurrentTemp(sensor);
        free(sensor);

        strcat(labelText, currentTemp);

        gtk_label_set_text(GTK_LABEL(current_temp), labelText);     
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