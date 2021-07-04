#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "include/util.h"
#include "include/temperature.h"
#include <gtk/gtk.h>
#include "include/macros.h"
void print_temp(GtkWidget *temperature);
void temp_color(GtkWidget *temperature);
void app_load_css();
void app_quit(GtkWidget *widget, gpointer data);

int main(int argc, char *argv[]) {
    measureTemperature();

    GtkWidget *window, *grid, *cpu_temp_label, *current_temp_label, *info_label;
    gtk_init(&argc, &argv);

    app_load_css();

    //create window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Measure Temperature");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 150);
    g_signal_connect(window, "destroy", G_CALLBACK(app_quit), NULL);

    //create grid
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    //create labels
    cpu_temp_label = gtk_label_new("CPU Temperature: ");
    gtk_grid_attach(GTK_GRID(grid), cpu_temp_label, 0, 0, 1, 1);

    current_temp_label = gtk_label_new(NULL);
    gtk_grid_attach_next_to(GTK_GRID(grid), current_temp_label, cpu_temp_label, GTK_POS_RIGHT, 1, 1);

    info_label = gtk_label_new("High Temperature: 70°C    |    Critical Temperature: 90°C");
    gtk_widget_set_name(info_label, "info-temp-label");
    gtk_grid_attach_next_to(GTK_GRID(grid), info_label, cpu_temp_label, GTK_POS_BOTTOM, 50, 50);

    gtk_widget_show_all(window);

    //call print_temp function every 500ms
    g_timeout_add(500, G_SOURCE_FUNC(print_temp), current_temp_label);

    gtk_main();

    return 0;
}

//update the current_temp_label
void print_temp(GtkWidget *temperature) {
    message("Updating temperature\n");
    char *sensor = measureTemperature();
    char *currentTemp = getCurrentTemp(sensor);

    temp_color(temperature); 

    gtk_label_set_text(GTK_LABEL(temperature), currentTemp); 
}

//change the color depending on cpu temperature
void temp_color(GtkWidget *temperature) {

    char *sensor = measureTemperature();
    char *currentTemp = getCurrentTemp(sensor);

    int currentTempValue = atoi(currentTemp);
    int highTempValue = 70;
    int critTempValue = 90;

    //switch the css color classes
    gtk_style_context_remove_class(gtk_widget_get_style_context(temperature), "normal-temp");
    gtk_style_context_remove_class(gtk_widget_get_style_context(temperature), "high-temp");
    gtk_style_context_remove_class(gtk_widget_get_style_context(temperature), "crit-temp");

    if(currentTempValue >= highTempValue && currentTempValue < critTempValue) {
        gtk_style_context_add_class(gtk_widget_get_style_context(temperature), "high-temp");
    }
    else if(currentTempValue >= critTempValue) {
        gtk_style_context_add_class(gtk_widget_get_style_context(temperature), "crit-temp");
    } else {
        gtk_style_context_add_class(gtk_widget_get_style_context(temperature), "normal-temp");
    }
}

//load css
void app_load_css() {
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    GFile *cssfp = g_file_new_for_path("style/style.css");

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, cssfp, NULL);

    g_object_unref(provider);
}

//quit the application
void app_quit(GtkWidget *widget, gpointer data) {
    exit(1);
}
