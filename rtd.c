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
		
	   Equations from pages 2 & 4 here :
       http://www.analog.com/media/en/technical-documentation/application-notes/AN709_0.pdf  
*/	

float decodeRtdModbusReading(int modbusReading);

void displayRtdValues(int deviceId, int displayType)
{
	// initialise these to zero or else we'll get nonsense readings 
	// shown if the chan/register is not enabled in the config.
	// You could initialise this to NaN or some other recognisable value to indicate "No reading available" 
	float chanLve[9]={0.0};
	float chanMax[9]={0.0};
	float chanMin[9]={0.0};
	float chanAvg[9]={0.0};
	
	int regId;
	
	for(regId=1 ; regId<(dataSource[deviceId].numRegisters+1) ; regId++)
	{	
		// Deals with chan 1 value registers
		if ( dataSource[deviceId].regAddress[regId] == 9  ) { chanLve[1]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 13 ) { chanAvg[1]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 17 ) { chanMax[1]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 21 ) { chanMin[1]=dataSource[deviceId].value[regId]; }
		
		// Deals with chan 2 value registers
		if ( dataSource[deviceId].regAddress[regId] == 10 ) { chanLve[2]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 14 ) { chanAvg[2]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 18 ) { chanMax[2]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 22 ) { chanMin[2]=dataSource[deviceId].value[regId]; }
		
		// Deals with chan 3 value registers
		if ( dataSource[deviceId].regAddress[regId] == 11 ) { chanLve[3]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 15 ) { chanAvg[3]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 19 ) { chanMax[3]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 23 ) { chanMin[3]=dataSource[deviceId].value[regId]; }

		// Deals with chan 4 value registers
		if ( dataSource[deviceId].regAddress[regId] == 12 ) { chanLve[4]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 16 ) { chanAvg[4]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 20 ) { chanMax[4]=dataSource[deviceId].value[regId]; }
		if ( dataSource[deviceId].regAddress[regId] == 24 ) { chanMin[4]=dataSource[deviceId].value[regId]; }	
	}

	// present the output in the format desired by the command line option
	if (displayType == HUMANREAD)
	{		
	
		printf("_____| RTD4 Modbus Address %i |______________________________________________________________________\n", dataSource[deviceId].modbusId);
		printf("Ch\t\t\tLive\t\tMin\t\tAvg\t\tMax\n");
		printf("1\t\t\t%f\t%f\t%f\t%f\n", chanLve[1],chanMin[1],chanAvg[1],chanMax[1]);
		printf("2\t\t\t%f\t%f\t%f\t%f\n", chanLve[2],chanMin[2],chanAvg[2],chanMax[2]);
		printf("3\t\t\t%f\t%f\t%f\t%f\n", chanLve[3],chanMin[3],chanAvg[3],chanMax[3]);		
		printf("4\t\t\t%f\t%f\t%f\t%f\n", chanLve[4],chanMin[4],chanAvg[4],chanMax[4]);
		printf("\n\n");
	}

	if (displayType == JSONREAD)
	{		
		printf ("      \"name\":\"RTU-RTD4\",\n");
		printf ("      \"type\": %i,\n",dataSource[deviceId].deviceType);
		printf ("      \"deviceId\":\"%i\",\n",deviceId);
		printf ("      \"modbusId\":\"%i\",\n",dataSource[deviceId].modbusId);			
		printf ("      \"channels\": 4,\n");


		for(int chanNo=1 ; chanNo <5 ; chanNo++)
		{				
			printf ("      \"channel %i\": {\n",chanNo);
			printf ("         \"live\": %f,\n",chanLve[chanNo]);
			printf ("         \"min\": %f,\n",chanMin[chanNo]);
			printf ("         \"avg\": %f,\n",chanAvg[chanNo]);
			printf ("         \"max\": %f\n",chanMax[chanNo]);
			if (chanNo <4) { printf ("      },\n"); } else  { printf ("      }\n"); }			
		}
		
	}


	if (displayType == CPUREAD)
	{		

		//deviceId,deviceType,modbusId,chanLve[1],chanMin[1],chanAvg[1],chanMax[1].....chanLve[4],chanMin[4],chanAvg[4],chanMax[4]
		printf("%i,%i,%i,4,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f;\n",
		                    deviceId,dataSource[deviceId].deviceType,dataSource[deviceId].modbusId,
							chanLve[1],chanMin[1],chanAvg[1],chanMax[1],	
							chanLve[2],chanMin[2],chanAvg[2],chanMax[2],
							chanLve[3],chanMin[3],chanAvg[3],chanMax[3],
							chanLve[4],chanMin[4],chanAvg[4],chanMax[4]);	
	}



	
}



void decodeRTD(int deviceId)
{

	int regId;

	// Work our way through the list and diretly amend the values stored in 
	// dataSource[deviceId].value[x] 
	for(regId=1 ; regId<(dataSource[deviceId].numRegisters+1) ; regId++)
	{	
		 // Registers 9-24 are the raw RTD values needing further processing, Registere 1-7 are the internal floats gernerated on chip 
		 if ( dataSource[deviceId].regAddress[regId] >7)
		 {
			dataSource[deviceId].value[regId] = decodeRtdModbusReading((int)dataSource[deviceId].value[regId]);	
		 }
	}	
}


float decodeRtdModbusReading(int modbusReading)
{
        const float RTD_A = 3.9083e-3;
        const float RTD_B = -5.775e-7;
        const float RTDnominal = 1000;   // PT1000
        const float refResistor = 4000;  // PT1000

        float Z1, Z2, Z3, Z4, Rt, temp;

        Rt = modbusReading;
        Rt /= 32768;
        Rt *= refResistor;


        Z1 = -RTD_A;
        Z2 = RTD_A * RTD_A - (4 * RTD_B);
        Z3 = (4 * RTD_B) / RTDnominal;
        Z4 = 2 * RTD_B;

        temp = Z2 + (Z3 * Rt);
        temp = (sqrt(temp) + Z1) / Z4;

        // if temperature is >0degC then return calculated value
        if (temp >= 0) return temp;

        // else re-calculate more accurate value for sub zero temperatures using alternate fifth order polynomial expression
        Rt /= RTDnominal;

        Rt *= 100;      // normalize to 100 ohm regardless of PT100/1000 type

        float rpoly = Rt;

        temp = -242.02;
        temp += 2.2228 * rpoly;
        rpoly *= Rt;  // square
        temp += 2.5859e-3 * rpoly;
        rpoly *= Rt;  // ^3
        temp -= 4.8260e-6 * rpoly;
        rpoly *= Rt;  // ^4
        temp -= 2.8183e-8 * rpoly;
        rpoly *= Rt;  // ^5
        temp += 1.5243e-10 * rpoly;

        // returns reading where temp <0degC
        return temp;
}



