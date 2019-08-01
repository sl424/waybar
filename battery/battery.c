#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Needed to convert strings to lowercase
#include <ctype.h>

// Constants
#define mW_TO_WATTS_FACTOR 1000000

// Functions
void construct_path(char endOfPath[], char finalPath[]);
float read_float_from_file(char fileToOpen[]);
void read_string_from_file(char fileToOpen[], char contentOfFile[]);

int main()
{	
	// 1. Get current discharge in milliwatts
	float currentDischarge = read_float_from_file("/sys/class/power_supply/BAT0/power_now");
	
	// 1a. Convert to watts
	currentDischarge = currentDischarge / mW_TO_WATTS_FACTOR;
	
	// 1b. Make watt display string
	char wattDisplayString[10];
	
	snprintf(wattDisplayString, sizeof(wattDisplayString), "%0.1fW ", 
	currentDischarge); 
	
	// 2. Get current battery state and percentage
	char batteryState[25];
	
	read_string_from_file("/sys/class/power_supply/BAT0/status", batteryState);
	
	// 2a. Convert batteryState to lowercase as CSS expects a lowercase value
	for(int i = 0; batteryState[i]; i++){
		batteryState[i] = tolower(batteryState[i]);
	}
	
	float batteryPercentage = read_float_from_file("/sys/class/power_supply/BAT0/energy_now") 
	/ read_float_from_file("/sys/class/power_supply/BAT0/energy_full") * 100;
	
	// 3. Determine battery icon to use based on battery state and percentage
	char *batteryIcon;
	
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
		
	char *batteryStateIcon = "";
	
	if (strcmp(batteryState, "charging") == 0) {
		batteryStateIcon = "";
		
		// Also set watts to null, it means nothing when charging
		strcpy(wattDisplayString, "");
	}
	
	// Print final output
	char finalOutput[15];
	
	snprintf(finalOutput, sizeof(finalOutput), "%0.0f%% %s%s%s", 
	batteryPercentage, wattDisplayString, batteryIcon, batteryStateIcon);
	
	printf("{\"text\": \"%s\", \"class\": \"%s\"}", finalOutput, batteryState);
	
	return 0;
}

void construct_path(char endOfPath[], char finalPath[])
{
	
}

float read_float_from_file(char fileToOpen[])
{
	FILE *fileToRead;
	char *mode = "r";
	fileToRead = fopen(fileToOpen, mode);
	
	float toReturn;
	fscanf(fileToRead, "%f", &toReturn);
	
	return toReturn;
}

void read_string_from_file(char fileToOpen[], char contentOfFile[])
{
	FILE *fileToRead;
	char *mode = "r";
	fileToRead = fopen(fileToOpen, mode);
	
	fscanf(fileToRead, "%s", contentOfFile);
}
