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
			
*/	

void displayDigInValues(int deviceId, int displayType)
{
	int regId;
	const char *chMode[4];
				chMode[0] = "Level";
				chMode[1] = "Level";
				chMode[2] = "Pulse";
				chMode[3] = "PWM";


	// initialise these to zero or else we'll get nonsense readings shown if the chan/register 
	// is not enabled in the config.
	// You could initialise this to NaN or some other recognisable value to indicate "No reading available" 
	int chanLvl[9]={0};      // Values from index position 1 onwards
    int chanCount[9]={0};
    int chanPWM[9]={0};
    int chanPWMAvg[9]={0};
	int chanPWMMax[9]={0};
	int chanPWMMin[9]={0};
	

	for(regId=1 ; regId<(dataSource[deviceId].numRegisters+1) ; regId++)
	{	
		// Deals with chan 1 value registers
		if ( dataSource[deviceId].regAddress[regId] == 1  ) { chanLvl[1]   =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 9  ) { chanCount[1] =dataSource[deviceId].value[regId]; }    // Pulse
		if ( dataSource[deviceId].regAddress[regId] == 25 ) { chanPWM[1]   =dataSource[deviceId].value[regId]; }    // PWM
		if ( dataSource[deviceId].regAddress[regId] == 41 ) { chanPWMAvg[1]=dataSource[deviceId].value[regId]; }    // PWM AVG
		if ( dataSource[deviceId].regAddress[regId] == 57 ) { chanPWMMax[1]=dataSource[deviceId].value[regId]; }	   // PWM Max Peek	    
		if ( dataSource[deviceId].regAddress[regId] == 73 ) { chanPWMMin[1]=dataSource[deviceId].value[regId]; }    // PWM Min Peek


		// Deals with chan 2 value registers
		if ( dataSource[deviceId].regAddress[regId] == 2  ) { chanLvl[2]   =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 11 ) { chanCount[2] =dataSource[deviceId].value[regId]; }    // Pulse
		if ( dataSource[deviceId].regAddress[regId] == 27 ) { chanPWM[2]   =dataSource[deviceId].value[regId]; }    // PWM
		if ( dataSource[deviceId].regAddress[regId] == 43 ) { chanPWMAvg[2]=dataSource[deviceId].value[regId]; }    // PWM AVG
		if ( dataSource[deviceId].regAddress[regId] == 59 ) { chanPWMMax[2]=dataSource[deviceId].value[regId]; }	   // PWM Max Peek	    
		if ( dataSource[deviceId].regAddress[regId] == 75 ) { chanPWMMin[2]=dataSource[deviceId].value[regId]; }    // PWM Min Peek
		
		// Deals with chan 3 value registers
		if ( dataSource[deviceId].regAddress[regId] == 3  ) { chanLvl[3]   =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 13 ) { chanCount[3] =dataSource[deviceId].value[regId]; }    // Pulse
		if ( dataSource[deviceId].regAddress[regId] == 29 ) { chanPWM[3]   =dataSource[deviceId].value[regId]; }    // PWM
		if ( dataSource[deviceId].regAddress[regId] == 45 ) { chanPWMAvg[3]=dataSource[deviceId].value[regId]; }    // PWM AVG
		if ( dataSource[deviceId].regAddress[regId] == 61 ) { chanPWMMax[3]=dataSource[deviceId].value[regId]; }	   // PWM Max Peek	    
		if ( dataSource[deviceId].regAddress[regId] == 77 ) { chanPWMMin[3]=dataSource[deviceId].value[regId]; }    // PWM Min Peek

		// Deals with chan 4 value registers
		if ( dataSource[deviceId].regAddress[regId] == 4  ) { chanLvl[4]   =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 15 ) { chanCount[4] =dataSource[deviceId].value[regId]; }    // Pulse
		if ( dataSource[deviceId].regAddress[regId] == 31 ) { chanPWM[4]   =dataSource[deviceId].value[regId]; }    // PWM
		if ( dataSource[deviceId].regAddress[regId] == 47 ) { chanPWMAvg[4]=dataSource[deviceId].value[regId]; }    // PWM AVG
		if ( dataSource[deviceId].regAddress[regId] == 63 ) { chanPWMMax[4]=dataSource[deviceId].value[regId]; }	   // PWM Max Peek	    
		if ( dataSource[deviceId].regAddress[regId] == 79 ) { chanPWMMin[4]=dataSource[deviceId].value[regId]; }    // PWM Min Peek
		
		// Deals with chan 5 value registers
		if ( dataSource[deviceId].regAddress[regId] == 5  ) { chanLvl[5]   =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 17 ) { chanCount[5] =dataSource[deviceId].value[regId]; }    // Pulse
		if ( dataSource[deviceId].regAddress[regId] == 33 ) { chanPWM[5]   =dataSource[deviceId].value[regId]; }    // PWM
		if ( dataSource[deviceId].regAddress[regId] == 49 ) { chanPWMAvg[5]=dataSource[deviceId].value[regId]; }    // PWM AVG
		if ( dataSource[deviceId].regAddress[regId] == 65 ) { chanPWMMax[5]=dataSource[deviceId].value[regId]; }	   // PWM Max Peek	    
		if ( dataSource[deviceId].regAddress[regId] == 81 ) { chanPWMMin[5]=dataSource[deviceId].value[regId]; }    // PWM Min Peek

		// Deals with chan 6 value registers
		if ( dataSource[deviceId].regAddress[regId] == 6  ) { chanLvl[6]   =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 19 ) { chanCount[6] =dataSource[deviceId].value[regId]; }    // Pulse
		if ( dataSource[deviceId].regAddress[regId] == 35 ) { chanPWM[6]   =dataSource[deviceId].value[regId]; }    // PWM
		if ( dataSource[deviceId].regAddress[regId] == 51 ) { chanPWMAvg[6]=dataSource[deviceId].value[regId]; }    // PWM AVG
		if ( dataSource[deviceId].regAddress[regId] == 67 ) { chanPWMMax[6]=dataSource[deviceId].value[regId]; }	   // PWM Max Peek	    
		if ( dataSource[deviceId].regAddress[regId] == 83 ) { chanPWMMin[6]=dataSource[deviceId].value[regId]; }    // PWM Min Peek

		// Deals with chan 7 value registers
		if ( dataSource[deviceId].regAddress[regId] == 7  ) { chanLvl[7]   =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 21 ) { chanCount[7] =dataSource[deviceId].value[regId]; }    // Pulse
		if ( dataSource[deviceId].regAddress[regId] == 37 ) { chanPWM[7]   =dataSource[deviceId].value[regId]; }    // PWM
		if ( dataSource[deviceId].regAddress[regId] == 53 ) { chanPWMAvg[7]=dataSource[deviceId].value[regId]; }    // PWM AVG
		if ( dataSource[deviceId].regAddress[regId] == 69 ) { chanPWMMax[7]=dataSource[deviceId].value[regId]; }	   // PWM Max Peek	    
		if ( dataSource[deviceId].regAddress[regId] == 85 ) { chanPWMMin[7]=dataSource[deviceId].value[regId]; }    // PWM Min Peek

		// Deals with chan 8 value registers
		if ( dataSource[deviceId].regAddress[regId] == 8  ) { chanLvl[8]   =dataSource[deviceId].value[regId]; }    // Level
		if ( dataSource[deviceId].regAddress[regId] == 23 ) { chanCount[8] =dataSource[deviceId].value[regId]; }    // Pulse
		if ( dataSource[deviceId].regAddress[regId] == 39 ) { chanPWM[8]   =dataSource[deviceId].value[regId]; }    // PWM
		if ( dataSource[deviceId].regAddress[regId] == 55 ) { chanPWMAvg[8]=dataSource[deviceId].value[regId]; }    // PWM AVG
		if ( dataSource[deviceId].regAddress[regId] == 71 ) { chanPWMMax[8]=dataSource[deviceId].value[regId]; }	   // PWM Max Peek	    
		if ( dataSource[deviceId].regAddress[regId] == 87 ) { chanPWMMin[8]=dataSource[deviceId].value[regId]; }    // PWM Min Peek
	} 
	
	
	
	// present the output in the format desired by the command line option
	if (displayType == HUMANREAD)
	{			
		printf("_____| DI8 Modbus Address %i |______________________________________________________________________\n", dataSource[deviceId].modbusId);
		printf("Ch\tMode\tLevel\tCount\t\tPWM\t\tMin Pk\t\tAvg\t\tMax Pk\n");

       
        // see https://eecs.wsu.edu/~cs150/reading/printf.htm for futher information on printf formating 


        for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{		
            printf("1\t%s\t", chMode[dataSource[deviceId].ChanMode[chanNo]]);

            if (dataSource[deviceId].ChanMode[chanNo]  < 2 )      // Level 
                printf("%-8i%-16s%-16s%-16s%-16s%-16s",chanLvl[chanNo],"-","-","-","-","-"); 
            else if (dataSource[deviceId].ChanMode[chanNo] == 2 )  // Pulse Count
                printf("%-8s%-16i%-16s%-16s%-16s%-16s","-", chanCount[chanNo],"-","-","-","-"); 
            else if (dataSource[deviceId].ChanMode[chanNo] == 3 )  // PWM
                printf("%-8s%-16s%-16i%-16i%-16i%-16i","-","-",chanPWM[chanNo],chanPWMMin[chanNo],chanPWMAvg[chanNo],chanPWMMax[chanNo]); 

            printf("\n");
        }
        printf("\n");

	}	


	if (displayType == JSONREAD)
	{				
		printf ("      \"name\":\"RTU-DI8\",\n");
		printf ("      \"type\": %i,\n",dataSource[deviceId].deviceType);
		printf ("      \"deviceId\":\"%i\",\n",deviceId);
		printf ("      \"modbusId\":\"%i\",\n",dataSource[deviceId].modbusId);	        
		printf ("      \"channels\": 8,\n");

		for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{				
			printf ("      \"channel %i\": {\n",chanNo);
			printf ("         \"mode\": %i,\n",dataSource[deviceId].ChanMode[chanNo]);
            if (dataSource[deviceId].ChanMode[chanNo]  < 2 )                 
                printf ("         \"Level\": %i\n",chanLvl[chanNo]);
            else if (dataSource[deviceId].ChanMode[chanNo] == 2 )
                printf ("         \"Pulse Count\": %i\n",chanCount[chanNo]);
            else if (dataSource[deviceId].ChanMode[chanNo] == 3 ) 
            {
			    printf ("         \"PWM Live\": %i,\n",chanPWM[chanNo]);
			    printf ("         \"PWM min\": %i,\n",chanPWMMin[chanNo]);
			    printf ("         \"PWM avg\": %i,\n",chanPWMAvg[chanNo]);
			    printf ("         \"PWM max\": %i\n",chanPWMMax[chanNo]);
            }

			if (chanNo <8) { printf ("      },\n"); } else  { printf ("      }\n"); }			
		}
				
	}


	if (displayType == CPUREAD)
	{		

		//deviceId,deviceType,modbusId,ChansTotal,ChanMode[1], chanLvl[1], chanCount[1], chanPWM[1], chanPWMMin[1], chanPWMAvg[1], chanPWMMax[1]....ChansTotal,ChanMode[8], chanLvl[8], chanCount[8], chanPWM[8], chanPWMMin[8], chanPWMAvg[8], chanPWMMax[8] 
		printf("%i,%i,%i,8,",deviceId,dataSource[deviceId].deviceType,dataSource[deviceId].modbusId);
        
        for(int chanNo=1 ; chanNo <9 ; chanNo++)
		{				
		        printf ("%i,", dataSource[deviceId].ChanMode[chanNo]);
                printf ("%i,%i,%i,%i,%i", chanLvl[chanNo], chanCount[chanNo], chanPWM[chanNo], chanPWMMin[chanNo], chanPWMAvg[chanNo], chanPWMMax[chanNo] );
                
		}
        printf(";\n");

	}

}
