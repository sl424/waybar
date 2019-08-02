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

// Constants
#define mW_TO_WATTS_FACTOR 1000000
#define STR_BUFFER_LEN 15

// Battery paths
#define PATH_POWER_NOW "/sys/class/power_supply/BAT0/power_now"
#define PATH_ENERGY_FULL "/sys/class/power_supply/BAT0/energy_full"
#define PATH_ENERGY_NOW "/sys/class/power_supply/BAT0/energy_now"
#define PATH_STATE "/sys/class/power_supply/BAT0/status"

// Functions
float read_float_from_file(char fileToOpen[]);
void read_string_from_file(char fileToOpen[], char contentOfFile[]);

int main()
{	
	// Variables to fill
	float currentDischarge; 
	float batteryPercentage;
	char wattDisplayString[STR_BUFFER_LEN];
	char batteryState[STR_BUFFER_LEN];
	char *batteryIcon;
	char *batteryStateIcon;
	char finalOutput[STR_BUFFER_LEN];
	
	// 1. Current discharge
	currentDischarge = read_float_from_file(PATH_POWER_NOW) / mW_TO_WATTS_FACTOR;
	
	// 2. Battery percentage
	batteryPercentage = read_float_from_file(PATH_ENERGY_NOW) / 
	read_float_from_file(PATH_ENERGY_FULL) * 100;
	
	// 3. Watt display string
	snprintf(wattDisplayString, sizeof(wattDisplayString), "%0.0fW ", 
	currentDischarge); 
	
	// 4. Battery state
	read_string_from_file(PATH_STATE, batteryState);
	
	// Convert batteryState to lowercase as CSS expects a lowercase value
	for(int i = 0; batteryState[i]; i++){
		batteryState[i] = tolower(batteryState[i]);
	}
	
	// 5. Battery icon
	if (batteryPercentage >= 90)
		batteryIcon = "";
	else if (batteryPercentage >= 80)
		batteryIcon = "";
	else if (batteryPercentage >= 60)
		batteryIcon = "";
	else if (batteryPercentage >= 50)
		batteryIcon = "";
	else if (batteryPercentage >= 40)
		batteryIcon = "";
	else if (batteryPercentage >= 20)
		batteryIcon = "";
	else 
		batteryIcon = "";
	
	// 6. Battery state icon
	batteryStateIcon = "";
	
	if (strcmp(batteryState, "charging") == 0) {
		batteryStateIcon = "";
		
		// Also set watts to null, it means nothing when charging
		strcpy(wattDisplayString, "");
	}
	
	// 7. Final output
	snprintf(finalOutput, sizeof(finalOutput), "%0.0f%% %s%s%s", 
	batteryPercentage, wattDisplayString, batteryIcon, batteryStateIcon);
	
	printf("{\"text\": \"%s\", \"class\": \"%s\"}", finalOutput, batteryState);
	
	return 0;
}

float read_float_from_file(char fileToOpen[])
{
	float toReturn;
	FILE *fileToRead;
	char *mode = "r";
	
	fileToRead = fopen(fileToOpen, mode);
	
	fscanf(fileToRead, "%f", &toReturn);
	
	fclose(fileToRead);
	
	return toReturn;
}

void read_string_from_file(char fileToOpen[], char contentOfFile[])
{
	FILE *fileToRead;
	char *mode = "r";
	
	fileToRead = fopen(fileToOpen, mode);
	
	fscanf(fileToRead, "%s", contentOfFile);
	
	fclose(fileToRead);
}
