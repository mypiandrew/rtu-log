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


void displayAoValues(int deviceId, int displayType)
{
	// initialise these to zero or else we'll get nonsense readings 
	// shown if the chan/register is not enabled in the config.
	// You could initialise this to NaN or some other recognisable value to indicate "No reading available" 
	float chanLve[5]={0.0};
	
	int regId;
	
	for(regId=1 ; regId<(dataSource[deviceId].numRegisters+1) ; regId++)
	{	
		
		if ( dataSource[deviceId].regAddress[regId] == 1 ) { chanLve[1]=dataSource[deviceId].value[regId]; }
				
		if ( dataSource[deviceId].regAddress[regId] == 2 ) { chanLve[2]=dataSource[deviceId].value[regId]; }
		
		if ( dataSource[deviceId].regAddress[regId] == 3 ) { chanLve[3]=dataSource[deviceId].value[regId]; }

		if ( dataSource[deviceId].regAddress[regId] == 4 ) { chanLve[4]=dataSource[deviceId].value[regId]; }
	}

	// present the output in the format desired by the command line option
	if (displayType == HUMANREAD)
	{		
	
		printf("_____| AO4 Modbus Address %i |______________________________________________________________________\n", dataSource[deviceId].modbusId);
		printf("Ch\t\t\tOutput setting mA\n");
		printf("1\t\t\t%2.2f\n", (chanLve[1]/100) );  // divide current register value by 100 to get setting in mA 
		printf("2\t\t\t%2.2f\n", (chanLve[2]/100) );
		printf("3\t\t\t%2.2f\n", (chanLve[3]/100) );
		printf("4\t\t\t%2.2f\n", (chanLve[4]/100) );
		printf("\n\n");
	}

	if (displayType == JSONREAD)
	{		
		printf ("      \"name\":\"RTU-AO4\",\n");
		printf ("      \"type\": %i,\n",dataSource[deviceId].deviceType);
		printf ("      \"deviceId\":\"%i\",\n",deviceId);
		printf ("      \"modbusId\":\"%i\",\n",dataSource[deviceId].modbusId);			
		printf ("      \"channels\": 4,\n");
		printf ("      \"channel 1\": {\n");
		printf ("         \"live\": %2.2f\n",(chanLve[1]/100));
		printf ("      },\n");
		printf ("      \"channel 2\": {\n");
		printf ("         \"live\": %2.2f\n",(chanLve[2]/100));
		printf ("      },\n");
		printf ("      \"channel 3\": {\n");
		printf ("         \"live\": %2.2f\n",(chanLve[3]/100));
		printf ("      },\n");
		printf ("      \"channel 4\": {\n");
		printf ("         \"live\": %2.2f\n",(chanLve[4]/100));
		printf ("      }\n");
	}

	if (displayType == CPUREAD)
	{		

		//deviceId,deviceType,modbusId,chanLve[1],chanLve[2],chanLve[3],chanLve[4] 
		printf("%i,%i,%i,4,%2.2f,%2.2f,%2.2f,%2.2f;\n",
		                    deviceId,dataSource[deviceId].deviceType,dataSource[deviceId].modbusId,
							(chanLve[1]/100),(chanLve[2]/100),(chanLve[3]/100),(chanLve[4]/100) );	
	}
	
}