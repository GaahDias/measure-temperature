#include "include/util.h"
#include "include/macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


const char* UBIN = "/usr/bin/";
const char* SBIN = "/sbin/";

char* getPackageManager() {
  char* package_managers[] = {
      "pacman",      // Arch Linux
      "pamac",      // Manjaro
      "apt",       // Debian
      "yum",      // OpenSuse
      "dnf",     // Fedora
      "apk"     // Alpine
  };
  forEach(char **package_manager, package_managers) {
    char path[60];
    strcpy(path, UBIN);
    strcat(path, *package_manager);
    FILE *file = fopen(path, "r");
    try(file) {
      fclose(file);
      return *package_manager;
    }
    strcpy(path, SBIN);
    strcat(path, *package_manager);
    file = fopen(path, "r");
    try(file) {
      fclose(file);
      return *package_manager;
    }
  }
  return NULL;
}
char* getSuAgent() {
  char* agents[] = {"sudo", "doas"};
  forEach(char* * agent, agents) {
    char path[60];
    strcpy(path, UBIN);
    strcat(path, *agent);
    FILE *file = fopen(path, "r");
    try(file) {
      fclose(file);
      return *agent;
    }

    strcpy(path, SBIN);
    strcat(path, *agent);
    file = fopen(path, "r");
    try(file) {
      fclose(file);
      return *agent;
    }
  }
  warn("Failed to get a suitable agent. Using fallback agent.\n");
  return "su -c";
}

void getSensorsInstallCommand(char *command) {
  char* package_manager = getPackageManager();
  char* root_agent = getSuAgent();

  try(package_manager) {
    success("Package Manager: %s\n", package_manager);
    strcpy(command, root_agent);
    sprintf(command, "%s %s ", root_agent, package_manager);
    if (!strcmp(package_manager, "pacman")) {
      strcat(command, "-S lm_sensors");
    } else if (!strcmp(package_manager, "apk")) {
      strcat(command, "add lm-sensors");
    } else {
      strcat(command, "install lm-sensors");
    }
  }
  else {
    panic("Failed to get package manager.\n");
  }
}
void installSensors() {
  if (system("sensors > /dev/null 2> /dev/null") != 0) {
    message("Sensors command not found. Trying install sensors...\n");
    char* sensors_install_command = malloc(8);
    getSensorsInstallCommand(sensors_install_command);
    try(sensors_install_command) {
      message("Executing: %s\n", sensors_install_command);
      system(sensors_install_command);
      free(sensors_install_command);
    }
    else {
      panic("Failed to get lm-sensors install command.\n");
    }
  }
}
