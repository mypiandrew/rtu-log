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
int readConfig()
{	
	int deviceId;
	int regId;
   
     // sql 
	char * db_config="db_config.db";
	char * db_data="db_data.db";
	sqlite3 * dbhandle;
	sqlite3_stmt *stmt;
	char * sql;
	int result;
	
	result=sqlite3_open(db_config,&dbhandle);
	
	if (result != SQLITE_OK) 
	{
		printf("Failed to open database \n\r");
		sqlite3_close(dbhandle);
		return 1;
	}
	//printf("Opened db %s OK\n\r",db_config);

	
	//***************************************************************
	//********************** CONFIG *********************************
	//***************************************************************
	
	// Count the total number of devices configured and check we're not 
	// about to import more than we're ready for.
	sql = "SELECT COUNT(deviceId) FROM dataSource WHERE enabled=1";
	result = sqlite3_prepare_v2(dbhandle, sql,-1, &stmt, NULL);	

	if (result != SQLITE_OK) 
	{
		printf("Failed to prepare statement main.config %i\n\r",result);
		sqlite3_close(dbhandle);
		return 2;
	}

	do 
	{
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) 
		{ 			
			config.dsTotal = sqlite3_column_int(stmt,0);
		}
		
	} while (result == SQLITE_ROW);
	
	sqlite3_finalize(stmt);
	
	if (config.dsTotal > (MAX_DATASOURCES -1))
	{
		printf("Max DataSources [%i] [%i] Exceeded...Exiting\n",MAX_DATASOURCES,config.dsTotal);
		return 2;
	}
		
	

	//***************************************************************
	//********************** DATA SOURCES ***************************
	//***************************************************************	
	sql = "select deviceType, modbusId, baudRate, dataBits, stopBit, interface, parity, deviceTimeout, modeCH1, modeCH2, modeCH3, modeCH4, modeCH5, modeCH6, modeCH7, modeCH8 from dataSource ORDER BY deviceId";
	result = sqlite3_prepare_v2(dbhandle, sql,-1, &stmt, 0);
	
	if (result != SQLITE_OK) 
	{
		printf("Failed to prepare statement datasources - %i\n\r",result);
		sqlite3_close(dbhandle);
		return 2;
	}
	
	deviceId=1;
	do {		
		result = sqlite3_step(stmt);
		
		if (result == SQLITE_ROW) 
		{ 			
			dataSource[deviceId].deviceType  = sqlite3_column_int(stmt,0);
			dataSource[deviceId].modbusId    = sqlite3_column_int(stmt,1);
			dataSource[deviceId].baudRate    = sqlite3_column_int(stmt,2);
			dataSource[deviceId].dataBits    = sqlite3_column_int(stmt,3);		
			dataSource[deviceId].stopBit     = sqlite3_column_int(stmt,4);
			dataSource[deviceId].timeout     = sqlite3_column_int(stmt,7);	
			
			dataSource[deviceId].ChanMode[1] = sqlite3_column_int(stmt,8);	 
			dataSource[deviceId].ChanMode[2] = sqlite3_column_int(stmt,9);	 
			dataSource[deviceId].ChanMode[3] = sqlite3_column_int(stmt,10);	 
			dataSource[deviceId].ChanMode[4] = sqlite3_column_int(stmt,11);	 
			dataSource[deviceId].ChanMode[5] = sqlite3_column_int(stmt,12);	 
			dataSource[deviceId].ChanMode[6] = sqlite3_column_int(stmt,13);	 
			dataSource[deviceId].ChanMode[7] = sqlite3_column_int(stmt,14);	 
			dataSource[deviceId].ChanMode[8] = sqlite3_column_int(stmt,15);	 

			
			strcpy(dataSource[deviceId].interface, (char *)sqlite3_column_text(stmt,5));
			strcpy(dataSource[deviceId].parity,    (char *)sqlite3_column_text(stmt,6));
	
			deviceId++;
		}
		
	} while (result == SQLITE_ROW);

   sqlite3_finalize(stmt);
   
	//***************************************************************
	//********************** DATA POINTS ****************************
	//***************************************************************
	for(deviceId=1 ; deviceId<(config.dsTotal+1);deviceId++)
	{		
		sql = "SELECT regAddress, regType FROM dataPoint WHERE deviceId=? AND enabled=1 ORDER BY regAddress";
		result = sqlite3_prepare_v2(dbhandle, sql,-1, &stmt, NULL);

		if (result != SQLITE_OK) 
		{
			printf("Failed to prepare statement datapoint - %i\n\r",result);
			sqlite3_close(dbhandle);
			return 2;
		}
		
		if (sqlite3_bind_int(stmt, 1, deviceId) != SQLITE_OK)
		{
			printf("SQL   : Could not bind deviceId [%i]\n", deviceId);
			return 2;
		}   
		

		// we don't need a for loop here as the SQL statement will bring back 
		// only the relevent rows, which we have already counted
		regId=1;

		do {			
			result = sqlite3_step(stmt);
			if (result == SQLITE_ROW) 
			{ 			
				dataSource[deviceId].regAddress[regId]   = sqlite3_column_int(stmt,0);
				dataSource[deviceId].regType[regId]      = sqlite3_column_int(stmt,1);
			
				dataSource[deviceId].numRegisters=regId;

				regId++;
			}
			
		} while (result == SQLITE_ROW);

	}
		
    /* Finish off + Free handle*/
	sqlite3_finalize(stmt);
	sqlite3_close(dbhandle);
	
	return 0;
}

void printConfig()
{
	int deviceId;
	int regId;
	
	printf("--------- Config Imported ----------\n\n");

	// i = device  n = register
   for(deviceId=1 ; deviceId<(config.dsTotal+1) ; deviceId++)
   {	
	
		printf("dataSource [%i] deviceType  = [%i]  \n", deviceId, dataSource[deviceId].deviceType);
		printf("dataSource [%i] modbusId    = [%i]  \n", deviceId, dataSource[deviceId].modbusId);
		printf("dataSource [%i] interface   = [%s]  \n", deviceId, dataSource[deviceId].interface);
		printf("dataSource [%i] baudRate    = [%i]  \n", deviceId, dataSource[deviceId].baudRate);
		printf("dataSource [%i] dataBits    = [%i]  \n", deviceId, dataSource[deviceId].dataBits);
		printf("dataSource [%i] parity      = [%s]  \n", deviceId, dataSource[deviceId].parity);	
		printf("dataSource [%i] stopBit     = [%i]  \n", deviceId, dataSource[deviceId].stopBit);
		printf("dataSource [%i] timeout     = [%i]  \n", deviceId, dataSource[deviceId].timeout);
		printf("dataSource [%i] DataPoints  = [%i] \n",  deviceId, dataSource[deviceId].numRegisters);
		printf("dataSource [%i] Chan 1 Mode = [%i] \n",  deviceId, dataSource[deviceId].ChanMode[1]);
		printf("dataSource [%i] Chan 2 Mode = [%i] \n",  deviceId, dataSource[deviceId].ChanMode[2]);
		printf("dataSource [%i] Chan 3 Mode = [%i] \n",  deviceId, dataSource[deviceId].ChanMode[3]);
		printf("dataSource [%i] Chan 4 Mode = [%i] \n",  deviceId, dataSource[deviceId].ChanMode[4]);
		printf("dataSource [%i] Chan 5 Mode = [%i] \n",  deviceId, dataSource[deviceId].ChanMode[5]);
		printf("dataSource [%i] Chan 6 Mode = [%i] \n",  deviceId, dataSource[deviceId].ChanMode[6]);
		printf("dataSource [%i] Chan 7 Mode = [%i] \n",  deviceId, dataSource[deviceId].ChanMode[7]);
		printf("dataSource [%i] Chan 8 Mode = [%i] \n",  deviceId, dataSource[deviceId].ChanMode[8]);
		
		for(regId=1 ; regId<(dataSource[deviceId].numRegisters+1) ; regId++)
		{	
			printf("[%i]\tregAddress  = [%i]  regType     = [%i]    ",regId, dataSource[deviceId].regAddress[regId],dataSource[deviceId].regType[regId]);
			printf("\n");
		}
		
	}
	printf("\n");
	printf("------------------------------------\n");
	printf("\n");
	
}