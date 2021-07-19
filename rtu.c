/*
        The MIT License (MIT)

        Copyright (c) 2021 Andrew O'Connell

        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.

        Dependancies :

        apt-get install sqlite3 libsqlite3-dev libmodbus5 libmodbus-dev

        Compile as below or use 'make all' to allow program to use external system (.so) libraries
        gcc log.c -o log -lsqlite3 -lmodbus -lm


*/

// System includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// External Libs
#include <sqlite3.h>       //Public domain
#include <modbus/modbus.h> //LGPL 2.1

#include <math.h> 		   // libm GPL This is needed for the RTD module, it's not a system include so needs to be linked against.
						   // You may wish to substitute this for a more permissive licenced version e.g. openlibm

// Types & Variables
#include "Types.h"

// RTU Module Definitions
#include "rtd.c"
#include "adc.c"
#include "digin.c"
#include "ao.c"
#include "digout.c"

// Functions
#include "config.c"
#include "modbus.c"
#include "rtudecode.c"


int main(int argc, char* argv[])
{
	

	int displayType=HUMANREAD; // default
	int opt;
	
      
	// Command line options 
	//
	// For reference see : https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html
	//
    // The colon after the letter tells getopt to expect an argument after the option
	// To disable the automatic error printing, put a colon as the first character     
	while((opt = getopt(argc, argv, ":hjcda:b:p:r:v:m:w")) != -1) 
    { 
        switch(opt) 
        { 
			case 'h': // Human Readable output
            	displayType = HUMANREAD;
                break; 				
            case 'j': // JSON output
				displayType = JSONREAD;
                break; 				
			case 'c': // comma seperated output
				displayType = CPUREAD;
                break;							
			case 'd': // Print Config
				displayType=HUMANREAD;
				debug=1;						
                break;							
            case '?': 
                printf ("Synapse Multi-RTU Reader - v1.0\n\n");				
				printf ("%s [-h|j|c] [-d]\n\n", argv[0]);
				printf ("Syntax :\n\n");
				printf ("-h = Human readable output (default)\n");
				printf ("-j = JSON readable output\n");
				printf ("-c = Comma delimited minimal output\n");
				printf("\n");			
				printf ("-d = Debug output\n");				
				printf("\n");
				printf("Examples :\n");
				printf ("Read RTUs, output in JSON format :  %s -j \n", argv[0]);
				printf("\n");				
				printf ("Note : Config stored in local SQLite databses db_config.db and db_data.db \n");
				printf("\n");
				exit(1);
                break; 							
        } 
	}
    
	
	if (displayType==HUMANREAD)
	{ 
		printf("\nSynapse RTU IO Reader - v1.0\n\n"); 
	
	}

	if (debug==1) { printf("Config Setup\n"); }

	// Load Config
	if (readConfig() == 0)
	{
		if (debug==1)  { printf("Config Done\n"); }
	}
	else
	{
		printf("Fatal Error : Can't process config\n");
		exit(1);
	}

	if (debug==1) { printConfig(); }
	
	if (debug==1) { printf("Modbus Reads...\n"); }
	

	// Read in Modbus registers
	if (getModbusValues() == 0)
	{
		if (debug==1) 
			printf("Modbus reads OK\n\n");
	}
	else
	{
		printf("..Fatal Error : Error Reading Modbus device(s) \n\n");
		exit(1);
	}
	
	decodeRtuUnits();


	// Presentation 
	for(int deviceId=1 ; deviceId<(config.dsTotal+1) ; deviceId++)
	{	
		if (displayType==JSONREAD)
		{
			if (deviceId == 1) 
				printf("{\n   \"device 1\" : {\n");
			else 
			 	printf("   \"device %i\" : {\n",deviceId);	
		}

		if (dataSource[deviceId].deviceType == RTU_AI8)  { displayAdcValues(deviceId, displayType);    }
 		if (dataSource[deviceId].deviceType == RTU_DI8)  { displayDigInValues(deviceId, displayType);  }
		if (dataSource[deviceId].deviceType == RTU_RTD4) { displayRtdValues(deviceId, displayType);    }
		if (dataSource[deviceId].deviceType == RTU_AO4)  { displayAoValues(deviceId, displayType);     }
		if (dataSource[deviceId].deviceType == RTU_DO8)  { displayDigOutValues(deviceId, displayType); }

		if (displayType==JSONREAD)
		{
			if ( deviceId<(config.dsTotal) )
				printf("   },\n");
			else 
				printf("   }\n}\n",deviceId);	
		}
	}
		

}