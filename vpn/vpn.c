/* vpn.c: program to be used in a custom waybar module. 
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

// Needed to check for directory exists
#include <dirent.h>
#include <errno.h>

// Constants
#define PATH_TO_INTERFACES "/sys/devices/virtual/net"
#define STR_BUFFER_LEN 40

int main(int argc, char** argv)
{
	// Variables
	DIR* dir;
	char bufferString[STR_BUFFER_LEN];
	
	// Construct path of VPN interface
	snprintf(bufferString, sizeof(bufferString), "%s/%s", PATH_TO_INTERFACES, argv[1]);
	
	dir = opendir(bufferString);
	
	if (dir) {
		/* Directory exists. */
		printf("{\"text\": \"%s \"}", argv[1]);
		closedir(dir);
	} else if (ENOENT == errno) {
		/* Directory does not exist. */
		printf("{\"text\": \"No VPN \",\"class\": \"down\"}");
	}
	
	return 0;
}
