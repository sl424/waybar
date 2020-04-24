/* battery.c: program to be used in a custom waybar module.
 * Homepage: https://gitlab.com/krathalan/waybar-modules
 *
 * Copyright (C) 2019 Hunter Peavey
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>

// Needed to convert strings to lowercase
#include <ctype.h>

// Needed to exit when a directory cannot be found
#include <stdlib.h>

// Constants
#define MICROWATT_TO_WATT_FACTOR 1000000
#define STR_BUFFER_LEN 15
#define LARGE_STR_BUFFER_LEN 20

// Battery paths
#define PATH_POWER_NOW "/sys/class/power_supply/BAT1/power_now"
#define PATH_ENERGY_FULL "/sys/class/power_supply/BAT1/energy_full"
#define PATH_ENERGY_NOW "/sys/class/power_supply/BAT1/energy_now"
#define PATH_STATE "/sys/class/power_supply/BAT1/status"

// Functions
float read_float_from_file(char fileToOpen[]);
void read_string_from_file(char fileToOpen[], char contentOfFile[]);

int main(void) {
  // Variables to fill
  float currentDischarge;
  float batteryPercentage;
  char wattDisplayString[STR_BUFFER_LEN];
  char batteryState[STR_BUFFER_LEN];
  char *batteryStateIcon;
  char finalOutput[LARGE_STR_BUFFER_LEN];

  // 1. Current discharge
  currentDischarge =
      read_float_from_file(PATH_POWER_NOW) / MICROWATT_TO_WATT_FACTOR;

  // 2. Battery percentage
  batteryPercentage = read_float_from_file(PATH_ENERGY_NOW) /
                      read_float_from_file(PATH_ENERGY_FULL) * 100;

  // 3. Watt display string
  snprintf(wattDisplayString, sizeof(wattDisplayString), "%0.2fW",
           currentDischarge);

  // 4. Battery state
  read_string_from_file(PATH_STATE, batteryState);

  // Convert batteryState to lowercase as CSS expects a lowercase value
  for (int i = 0; batteryState[i]; i++) {
    batteryState[i] = tolower(batteryState[i]);
  }

  // 5. Battery state icon
  batteryStateIcon = "";

  if (strcmp(batteryState, "charging") == 0 ) {
    batteryStateIcon = "";

    // Assert batteryState to charging if we got here through currentDischarge=0
    snprintf(batteryState, sizeof(batteryState), "charging");

    // Also set watts to null, it means nothing when charging
    strcpy(wattDisplayString, "");
  } else if (currentDischarge == 0) {
    batteryStateIcon = "☉";
    snprintf(batteryState, sizeof(batteryState), "idle");
    strcpy(wattDisplayString, "");

  }

  // 6. Final output
  snprintf(finalOutput, sizeof(finalOutput), "%s%s", wattDisplayString,
           batteryStateIcon);

  printf("{\"text\": \"%s\", \"class\": \"%s\", \"percentage\": %0.0f}",
         finalOutput, batteryState, batteryPercentage);

  return 0;
}

float read_float_from_file(char fileToOpen[]) {
  float toReturn;
  FILE *fileToRead;

  fileToRead = fopen(fileToOpen, "r");

  if (fileToRead == NULL) {
    printf("Error reading file %s", fileToOpen);
    exit(0);
  }

  fscanf(fileToRead, "%f", &toReturn);

  fclose(fileToRead);

  return toReturn;
}

void read_string_from_file(char fileToOpen[], char contentOfFile[]) {
  FILE *fileToRead;

  fileToRead = fopen(fileToOpen, "r");

  if (fileToRead == NULL) {
    printf("Error reading file %s", fileToOpen);
    exit(0);
  }

  fscanf(fileToRead, "%s", contentOfFile);

  fclose(fileToRead);
}
