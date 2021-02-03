/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/

  The license applies to all part of the library including the
  examples and tools supplied with the library.
*/
#include <FlexRigTeensy.h>
FlexRig::FlexRig() {

	connected=false;
	vfo=false;
	nMaxSlice=2;
	activeSlice=0;
	nMaxPanadapter=2;
	activePanadapter=0;
	nMaxWaterfall=2;
	activeWaterfall=0;
	C=0;
	front=0; rear=-1; size=0;

	//sprintf(handle,"3144B418")); //dummy initialization for offline test
	commandList=CommandList();
	radio=Radio();
	transmit=Transmit();
	interlock=Interlock();
	eq=Eq();
	cwx=Cwx();
	atu=Atu();
	for (int i=0;i<nMaxPanadapter;i++) {
		panadapter[i]=Panadapter();
		panadapter[i].set_pan(i);
	}
	//panadapter[1]=Panadapter();
	for (int i=0;i<nMaxWaterfall;i++) {
		waterfall[i]=Waterfall();
		waterfall[i].set_waterfall(i);
	}
	//waterfall[1]=Waterfall();
	for (int i=0;i<nMaxSlice;i++) {
		slice[i]=Slice();
		slice[i].set_sliceId(i);
	}
	//slice[1]=Slice();

	for (int i=0;i<9;i++) metersId[i]=-1;
}

void FlexRig::ping() {
	send(F("ping"));
}

void FlexRig::process() {
	if (!client.connected()) {
	    client.stop();
		connected=false;
		radio.fire_disconnected_event();
	}
	sendAllCommands();
	readEthernetData();
    readVita49Data();
}

void FlexRig::fireEvents() {
	//run events handlers
	radio.fireEvents();
	eq.fireEvents();
	interlock.fireEvents();
	transmit.fireEvents();
	cwx.fireEvents();
	atu.fireEvents();
	for (int i=0;i<nMaxPanadapter;i++)
		panadapter[i].fireEvents();
	for (int i=0;i<nMaxWaterfall;i++)
		waterfall[i].fireEvents();
	for (int i=0;i<nMaxSlice;i++)
		slice[i].fireEvents();
}

void FlexRig::send(String cmd) {
	send(cmd,0);
}


int FlexRig::send(String cmd, int parserId) {
    char c[200];
	//C++;
	sprintf(c, "C%d|%s\n",C++,cmd.c_str());
	//String cmd2=String(c);
	//cmd2 += cmd + "\n";

	addToResponseList(C-1,parserId);
	//Protect critical section from interrupt events
	noInterrupts();
	  //sending command
	  client.println(c);
	interrupts();
	//Serial.print(F("->"));
	//Serial.print(c);
	//Serial.println(F("<-")); //Debug
	return C-1;
}

void FlexRig::setPreampList(char m){

	if (m=='3') {
		preampListSize=2;
		preampList[0]=0; preampList[1]=20;
	}

	if (m=='5') {
		preampListSize=4;
		preampList[0]=-10; preampList[1]=0; preampList[2]=10; preampList[3]=20;
	}

	if (m=='7') {
		preampListSize=5;
		preampList[0]=-10; preampList[1]=0; preampList[2]=10; preampList[3]=20; preampList[4]=30;
	}

}

void FlexRig::readEthernetData() {

	//reading response
	while (client.available()) {
		//Serial.print(F("numero di byte:"));Serial.println(client.available());
		char c=client.read();
		if (c==0) {
		    //Serial.println(F("0!!!"));
			continue;
		}
		//Serial.print(c);

        if (c=='\n') {

			buffer.trim();

			//Serial.print(F("===Buffer address: ")); Serial.println((long)&buffer,HEX);

			switch (buffer[0]) {
			case 'R':
			  //Serial.println(F("==RESPONSE=="));
			  parseReplay(buffer);
			  break;
			case 'S':
			  //Serial.println(F("==STATUS=="));
			  parseStatus(buffer);
			  break;
			case 'M':
			  //Serial.println(F("==MESSAGE=="));
			  parseMessage(buffer);
			  break;
			default:
			  Serial.println(F("\n==UNKNOWN=="));
			  Serial.print(F("Buffer length:")); Serial.println(buffer.length());
			  unsigned int i=0;
			  for (i=0;i<buffer.length();i++) {
			     Serial.print(buffer[0]); Serial.print(F("-"));Serial.println(buffer[0],DEC);
			  }
			  Serial.print(F(">")); Serial.print(buffer);Serial.println(F("<"));
			}
			buffer="";
		} else {
			buffer+=c;
		}

	}

}

void FlexRig::parseStatus(String msg){
	//Serial.print(F("FlexRig::parseStatus(msg): "));
	//Serial.println(msg);
	//if (msg.indexOf(handle)) {

	    int s=msg.indexOf(' ');
		int h=msg.indexOf('|')+1;
		String type=msg.substring(h,s);

		//Serial.println(type);

		if (type.equals(F("memory")))
		{
		    //Serial.print("Memory: "); Serial.println(MaxMemNum);

		    int sepIDX = msg.indexOf(" ", s + 1);
			int mIDX;
			int MNum;
			String MFreq;
			String MName;

			MNum = msg.substring(s, sepIDX).toInt();

			if (msg.indexOf("freq=") >= 0)
			{
				mIDX = msg.indexOf("freq=");
				sepIDX = msg.indexOf(" ", mIDX);
				if (sepIDX != -1)
				{
					mIDX += 5;
					MFreq = msg.substring(mIDX, sepIDX);
				}
			}

			if (msg.indexOf("name=") >= 0)
			{
				mIDX = msg.indexOf("name=");
				sepIDX = msg.indexOf(" ", mIDX);
				if (sepIDX != -1)
				{
					mIDX += 5;
					MName = msg.substring(mIDX, sepIDX);
					MName.replace(char(127), " ");
				}
			}

			//Serial.print("Memory: "); Serial.print(MaxMemNum); Serial.print(Mem[MaxMemNum]); Serial.print(" "); Serial.println(MemFreq[MaxMemNum]);
			//Serial.print("Memory (From Flex): "); Serial.print(MaxMemNum); Serial.print(" "); Serial.print(MNum); Serial.print(" "); Serial.print(MFreq); Serial.print(" "); Serial.println(MName);
		    
			for (mIDX = 0; mIDX <= MaxMemNum; mIDX++)
			{
				if (MNum == Mem[mIDX])
				{
					MemFreq[mIDX] = MFreq;
					MemName[mIDX] = MName;
					//Serial.print("Memory (rewritten): "); Serial.print(mIDX); Serial.print(" "); Serial.print(Mem[mIDX]); Serial.print(" "); Serial.print(MemFreq[mIDX]); Serial.print(" "); Serial.println(MemName[mIDX]);

					break;
				}
			}

			if (mIDX > MaxMemNum)
			{
				mIDX -= 1;
				Mem[mIDX] = MNum;
				MemFreq[mIDX] = MFreq;
				MemName[mIDX] = MName;
				MaxMemNum += 1;
				//Serial.print("Memory (initial write): "); Serial.print(mIDX); Serial.print(" "); Serial.print(Mem[mIDX]); Serial.print(" "); Serial.print(MemFreq[mIDX]); Serial.print(" "); Serial.println(MemName[mIDX]);
			}
		    
		}

		if (type.equals(F("profile")))
		{
		    if(msg.indexOf("global current=") >= 0)
		    {
			int glIDX=msg.indexOf("global current=");
			Current_Profile = msg.substring(glIDX + 15);
			//Serial.print("Global Profile: "); Serial.println(msg.substring(glIDX + 15));
		    }

		    int glIDX = msg.indexOf("global list=");
		    if(glIDX !=-1)
		    {
			glIDX +=12;
		        for(int i=0; i<200; i++)
                        {
			    int sepIDX = msg.indexOf("^", glIDX);
			    if(sepIDX !=-1)
			    {
			       Profile[i] = msg.substring(glIDX, sepIDX);
		               glIDX = sepIDX + 1; 
			       //Serial.println(Profile[i]);
    			    }
			    else
			    {
			       return;
			    }
                        }
                    }
		    //radio.updateStatus(msg.substring(s+1));
			return;
		}

		if (type.equals(F("radio"))){
		    radio.updateStatus(msg.substring(s+1));
			return;
		}
		if (type.equals(F("transmit"))){
		    transmit.updateStatus(msg.substring(s+1));
			return;
		}
		if (type.equals(F("interlock"))){
		    interlock.updateStatus(msg.substring(s+1));
			return;
		}
		if (type.equals(F("display"))){
		    //Serial.println(msg);
		    int s1=msg.indexOf(' ',s+1);
			String obj=msg.substring(s+1,s1);
			//Serial.print(F("===")); Serial.print(obj); Serial.println(F("==="));
		    //Serial.print(F("===pan (position) ")); Serial.println(s1);
        	int id=(msg.substring(s1+3,s1+11)).toInt();
			if (obj.equals(F("pan"))) {
				//Serial.print(F("===pan (before) ")); Serial.println(id);
        		id=id % 40000000;
				//Serial.print(F("===pan (after) ")); Serial.println(id);
			    if (id<=1)
					panadapter[id].updateStatus(msg.substring(s1+12));
			}

			if (obj.equals(F("waterfall"))) {
			    //Serial.print(F("===waterfall (before) ")); Serial.println(id);
        		id=id % 42000000;
				//Serial.print(F("===waterfall (after) ")); Serial.println(id);
			    waterfall[id].updateStatus(msg.substring(s1+12));
			}

			return;
		}
		if (type.equals(F("slice"))){
	        //Serial.print(F("msg="));Serial.println(msg);
    		int s1=msg.indexOf(' ',s);
		    //Serial.print(F("s1:")); Serial.println(s1);
			int id=(msg.substring(s1+1,s1+2)).toInt();
			//Serial.print(F("slice id=")); Serial.println(id);
			if (id<nMaxSlice)
				slice[id].updateStatus(msg.substring(s1+1));
			return;
		}

		if (type.equals(F("eq"))){
			//Serial.println(F("============>eq"));
			eq.updateStatus(msg.substring(s+1));
			return;
		}

		if (type.equals(F("waveform"))){
			//Serial.println(F("waveform"));
			return;
		}

		if (type.equals(F("atu"))){
			//Serial.println(F("atu"));
			atu.updateStatus(msg.substring(s+1));
			return;
		}

 		if (type.equals(F("cwx"))){
			//Serial.println(F("cwx"));
			cwx.updateStatus(msg.substring(s+1));
			return;
		}

		if (type.equals(F("meter"))){
			parseMeter(msg.substring(s+1));
			//for (int i=0;i<6;i++) {
			//	Serial.print(F("==> Meter id:"));Serial.print(i);Serial.print(F("-"));Serial.println(metersId[i]);
  		    //}
			return;
		}
		/////////////////////////////////////////////////////////////Serial.print(F("FlexRig::parseStatus() - Unhandled type->")); Serial.println(type + "<"));
	//}
}

void FlexRig::readVita49Data() {
	
	int vitaPktSize = vitaUdp.parsePacket();
	
	//Serial.println(vitaPktSize);
	
	if (vitaPktSize) {

		vitaUdp.read(vitaPacketBuffer,vitaPktSize);

		//Serial.println(vitaPacketBuffer);	
		
		// DEBUG
		/*
	    Serial.print(F("VITA49 PKT - len:")); Serial.println(vitaPktSize);
	    char vb[3];
	    int x=0;
	    for (int i=0; i < vitaPktSize; i++) {
	      sprintf(vb,"0x%02x, ",vitaPacketBuffer[i]);
		  if (x==16) {x=0; Serial.println();}
          Serial.print(vb);
		  x++;
        }
        Serial.println(); */
	    // DEBUG


	    char pattern[24];
        sprintf(pattern,"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
               vitaPacketBuffer[4],vitaPacketBuffer[5],vitaPacketBuffer[6],vitaPacketBuffer[7],
               vitaPacketBuffer[8],vitaPacketBuffer[9],vitaPacketBuffer[10],vitaPacketBuffer[11],
               vitaPacketBuffer[12],vitaPacketBuffer[13],vitaPacketBuffer[14],vitaPacketBuffer[15]);

	    if (! String(pattern).equals(F("0000070000001C2D534C8002"))) {
		                              //0000070000001C2D534C8002
			//Serial.println(pattern);
   	    	//Serial.println(F("NON VITA METERING PACKET !!!!"));
   	    	return;
	    }

	    int packet_size=getUIntValue2Bytes(vitaPacketBuffer[2],vitaPacketBuffer[3]);
		//Serial.print(F("VITA==>packet_size: "));Serial.println(packet_size);

		int payload_bytes=(packet_size - 1) * 4;
		//Serial.print(F("VITA==>payload_bytes: "));Serial.println(payload_bytes);

		int num_meters=(payload_bytes - 24) / 4;
		//Serial.print(F("VITA==>num_meters: "));Serial.println(num_meters);

		int offset=28;
		for (int i=0;i<num_meters;i++) {
			offset=28+i*4;
			int meterId=getUIntValue2Bytes(vitaPacketBuffer[offset],vitaPacketBuffer[offset+1]);
			short meterValue=getMeterValue(vitaPacketBuffer[offset+2],vitaPacketBuffer[offset+3]);

			/*
			if (meterId==12 || meterId==7 || meterId==8) {
				Serial.print(F("Meter id:"));Serial.print(meterId);
				Serial.print(F("-Value:"));Serial.println(meterValue);
			} */

			/*
			if (meterId==15) {
			    Serial.print(F("Meter id:"));Serial.print(meterId);
				Serial.print(F("-Value:"));Serial.println(meterValue);
			}
			*/

			/*
			if (meterId==19 || meterId==20 || meterId==21 || meterId==22 ||
			    meterId==23 || meterId==24 || meterId==25 || meterId==26) {
				Serial.print(F("Meter id:"));Serial.print(meterId);
				Serial.print(F("-Value:"));Serial.println(meterValue);
			}
			*/
			//Serial.print(F("meterId:"));Serial.println(meterId);

			if (meterId==metersId[MET_S_A]) {
				//Serial.print(F(" Meter MET_S_A ")); Serial.println(millis());
				metersValue[MET_S_A]=(float)meterValue/128.0f;
				continue;
			}
			if (meterId==metersId[MET_S_B]) {
				//Serial.println(F(" Meter MET_S_B"));
				metersValue[MET_S_B]=(float)meterValue/128.0f;
				continue;
			}
			if (meterId==metersId[MET_SWR]) {
				//Serial.print(F("meterValue:"));Serial.println(meterValue);
				metersValue[MET_SWR]=(float)meterValue/128.0f;
				//Serial.print(F("metersValue[MET_SWR]:"));Serial.println(metersValue[MET_SWR]);

				continue;
			}
			if (meterId==metersId[MET_FPWR]) {
				//Serial.println(F("Meter MET_FPWR"));
				metersValue[MET_FPWR]=pow(10,(((float)meterValue/128.0f)/10))/1000;
				continue;
			}
			/*
			if (meterId==metersId[MET_MIC_PEAK]) {
				//Serial.println(F("Meter MET_MIC_PEAK"));
				metersValue[MET_MIC_PEAK]=(float)meterValue/128.0f;
				continue;
			}
			if (meterId==metersId[MET_COMP_PEAK]) {
				//Serial.println(F("Meter MET_COMP_PEAK"));
				metersValue[MET_COMP_PEAK]=(float)meterValue/128.0f;
				continue;
			}*/
			if (meterId==metersId[PATEMP]) {
				//Serial.println(F("Meter MET_COMP_PEAK"));
				metersValue[PATEMP]=((float)meterValue/64.0f)/100;
				continue;
			}
			if (meterId==metersId[VOLTAGE_BEFORE]) {
				//Serial.println(F("Meter MET_COMP_PEAK"));
				metersValue[VOLTAGE_BEFORE]=((float)meterValue)/1000;
				continue;
			}

			if (meterId==metersId[VOLTAGE_AFTER]) {
				//Serial.println(F("Meter MET_COMP_PEAK"));
				metersValue[VOLTAGE_AFTER]=((float)meterValue)/1000;
				continue;
			}

		}

	}

}

void FlexRig::parseMessage(String msg){
	Serial.println(msg);
}


void FlexRig::connect() {

  Serial.print(F("connecting to Flex rig: "));
  Serial.print(ipAddress[0]); Serial.print(F("."));
  Serial.print(ipAddress[1]); Serial.print(F("."));
  Serial.print(ipAddress[2]); Serial.print(F("."));
  Serial.print(ipAddress[3]);  Serial.println(F("."));

  if (client.connect(ipAddress, UDP_DISCOVERING_PORT)) {
    connected=true;
    Serial.println("Connected");
	//ping();
	//String buffer;

	delay(1000);
	while (client.available()) {
		char c=client.read();
	    if (c=='\n') {
			switch (buffer[0]) {
//			case 'V':
//			  Serial.println(F("==VERSION (connect)=="));
//			  for (int i=1;i<buffer.length();i++) {
//				softVersion[i-1]=buffer[i];
//				Serial.print(softVersion[i-1]);
//			  }
//			  Serial.println();
//			  break;
			case 'H':
			  //Serial.println(F("==HANDLE (connect)=="));
			  for (unsigned int i=1;i<buffer.length();i++) {
				handle[i-1]=buffer[i];
				Serial.print(handle[i-1]);
			  }
			  Serial.println();
			  break;
            case 'S':
			  //Serial.println(F("==STATUS (connect)=="));
			  parseStatus(buffer);
			  break;
			case 'M':
			  //Serial.println(F("==MESSAGE(connect)=="));
			  parseMessage(buffer);
			  break;

		}
			buffer="";
		} else {
			buffer+=c;
		}
	}
	//Listening on port 4991 for VITA-49 protocol
	vitaUdp.begin(UDP_VITA49_PORT);
	Serial.println(F("==>LISTENING FOR VITA49 PACKETS"));
	configureClient();

	//
	//startReceiver();
	//
  } else {
    Serial.println(F("failed"));
  }

}

void FlexRig::initBuffer(){
    //dummy initializazion with 1024 bytes
	/*
	buffer="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	buffer+="                                                                ";
	*/
}

boolean FlexRig::isAFlex(const char* model, const char* serial, const char* serialKey) {
  boolean found=true;
  char pattern[7] = "FLEX-6";

  for (int i=0;i<6;i++) {
    if (pattern[i]!=model[i]) {
		//Serial.print(model[i]); Serial.print(F("-")); Serial.println(pattern[i]);
      found=false;
      break;
    }
  }

  if (found && serialKey!=NULL) {  //looking for a specific rig
	for (int i=0;i<19;i++) {
		if (serial[i]!=serialKey[i]) {
			//Serial.print(serial[i]); Serial.print(F("-")); Serial.println(serialKey[i]);
		  found=false;
		  break;
		}
    }
  }
  //Serial.print(F("FlexRig::isAFlex():")); Serial.println(found);

  return found;
}

FlexRig FlexRig::findAFlex(const char* serialKey) {

  EthernetUDP Udp;
  char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
  Udp.begin(UDP_DISCOVERING_PORT);
  FlexRig f=FlexRig();
  f.initBuffer();

  Serial.println(F("===Looking for Flex Rig (UDP)==="));

  unsigned long TimeIt = millis();
  boolean found=false;
  while (!found) {

      int packetSize = Udp.parsePacket();

      //Serial.print(F("Received packet - size "));
      //Serial.println(packetSize);

      //if ((packetSize==UDP_TX_PACKET_MAX_SIZE) || (packetSize==228))
      //if (packetSize>=228)
	  if (packetSize>0)
      {

		// read the packet into packetBufffer
        Udp.read(packetBuffer,packetSize);

//***

	Serial.print("packetSize: ");
	Serial.println(packetSize);

	for (int i=28; i<UDP_TX_PACKET_MAX_SIZE; i++)
	  {
	    if(packetBuffer[i] == ' ')
	      {
//		  Serial.println();
		}
	    else
		{
//		  Serial.print(packetBuffer[i]);
		}
	  }

	 Serial.println(" ");

			  
//***


		if (charIndexOf(packetBuffer,"discovery_protocol_version")) {
			//int k=strstr(packetBuffer,"discovery_protocol_version");
			//Serial.println(k);
			//Serial.println("UDP_DISCOVERING_PROTOCOL_PKT!!!");
			//Serial.println(packetBuffer[k+27]);
			
			//Serial.print("pkt>");
			//for (int i=28;i<packetSize;i++)
			//	Serial.print(packetBuffer[i]);
			//Serial.println("<pkt");
			

			// if (k>0) {      //it is a Discovering protocol pkt
			char model[10];
			Serial.println("");
			for (int i =0; i < 9; i++) {
			  model[i]=packetBuffer[69+i];
			  Serial.print(model[i]);
			}
			Serial.println("");
			
			char serialTmpVal[20];
			//Serial.print(F("=====>"));
			for (int i=0; i < 19; i++) {
				serialTmpVal[i]=packetBuffer[86+i];
				Serial.print(packetBuffer[86+i]);
			}
			Serial.println("");

			if (isAFlex(model,serialTmpVal,serialKey)) {

			  Serial.println(F("===========Flex Rig============="));

			  Serial.print(F("IP Address:"));
			  IPAddress remote = Udp.remoteIP();
			  for (int i =0; i < 4; i++) {
				Serial.print(remote[i], DEC);
				f.ipAddress[i]=remote[i];       //Storing data into Flex Struct
				if (i < 3) Serial.print(F("."));
			  }
			  Serial.println("<");


			  Serial.print(F("Model Name:"));
//***
			  for (int i=0; i < 32; i++)	// clean up garbage
			    {
				f.modelName[i]=0x0;
			    }
//***

			  for (int i=69; i < 78; i++) {
				f.modelName[i-69]=packetBuffer[i]; //Storing data into Flex Struct
				Serial.print(packetBuffer[i]);
			  }

			  Serial.println("<");

			  Serial.print(F("Serial:"));
//***
			  for (int i=0; i < 32; i++)	// clean up garbage
			    {
				f.serial[i]=0x0;
			    }
//***

			  for (int i=86; i < 105; i++) {
				f.serial[i-86]=packetBuffer[i]; //Storing data into Flex Struct
				Serial.print(packetBuffer[i]);
			  }

			  Serial.println("<");

			  Serial.print(F("Version:"));
//***
			  for (int i=0; i < 32; i++)	// clean up garbage
			    {
				f.softVersion[i]=0x0;
			    }
//***

			  for (int i=114; i < 123; i++) {
				f.softVersion[i-114]=packetBuffer[i]; //Storing data into Flex Struct
				Serial.print(packetBuffer[i]);
			  }

			  Serial.println("<");

			  Serial.print(F("NickName:"));
//***
			  for (int i=0; i < 32; i++)	// clean up garbage
			    {
				f.nickName[i]=0x0;
			    }
//***

			  for (int i=133; i < 141; i++) {
				f.nickName[i-133]=packetBuffer[i]; //Storing data into Flex Struct
				Serial.print(packetBuffer[i]);
			  }


			  Serial.println("<");

			  //Serial.println(f.modelName[6]);
			  f.setPreampList(f.modelName[6]);

			  found=true;
			}
		}  //Protocol_version packet
      }  //packetsize
	
      if(millis() - TimeIt > 10000)
      {
	return f;
      }

      delay(100);
  } //main loop simulation - it is executed only once until a Flex rig is not found

   Serial.println();
   Serial.println(f.modelName);
   Serial.println(f.serial);
   Serial.println(f.nickName);
   Serial.println(f.softVersion);
   Serial.println(long(f.handle));
   
   Serial.println("Found");
   
   return f;
}

int FlexRig::charIndexOf(const char *string, const char *key) {
  int val=-1;
  char *test;
  test=strstr(string,key);
  if (test) {
    val=test-string;
    Serial.print("test:"); Serial.println(test);
  }
  return val;
}

char *FlexRig::valueOf(char *string, char *key) {
  char *ret;

  char * pch;
  pch = strtok (string," ");
  while (pch != NULL)
  {
    //Serial.print(">"); Serial.print(pch); Serial.println("<");
    int pos=charIndexOf(pch,"=");
    int i=charIndexOf(pch,key);
    //Serial.print(pos);Serial.print(" # ");Serial.println(i);
    if (i==0) {
      Serial.print("  found key:"); Serial.println(key);
      char * tmp=strstr(pch,"=");
      Serial.println(tmp);
      ret=tmp+1;
      break;
    }
    /*if (charIndexOf(pch,key)) {
      char *tmp=strstr(pch,"=");
      ret=tmp+1;
      Serial.print("  ret: ");Serial.println(ret);
    }*/
    pch = strtok (NULL, " ");
  }
  return (char *)ret;
}



void FlexRig::configureClient() {
	delay(500);
	
	commandList.add(F("client ip"));
	//send(F("client program DMH_CONTROLLER"));
	send(F("client program TeensyMaestro"));
    commandList.add(F("sub radio all"));

	commandList.add(F("sub tx all"));
	//S69A3CDEB|transmit freq=14.03619 lo=100 hi=2900 rfpower=3 tunepower=10 am_carrier_level=100 vox_enable=0 vox_level=50 vox_delay=250 mic_level=40 mic_selection=MIC mic_boost=1 mic_bias=0 mic_acc=0 compander=1 compander_level=70 dax=0 pitch=540 speed=23 iambic=1 iambic_mode=1 cwl_enabled=0 swap_paddles=0 break_in=1 break_in_delay=9 sidetone=1 monitor=0 mon_gain_cw=76 mon_gain_sb=80 mon_pan_cw=50 mon_pan_sb=50 tune=0 met_in_rx=0 hwalc_enabled=0 inhibit=0 speech_processor_enable=1 speech_processor_level=0 show_tx_in_waterfall=0
	commandList.add(F("sub atu all"));
	//S69A3CDEB|atu status=NONE atu atu_enabled=0
	commandList.add(F("sub meter all"));
	//elenco dei meter disponibili
	commandList.add(F("sub pan all"));
	//S69A3CDEB|display pan 0x40000000 x_pixels=1170 y_pixels=449 center=14.03499 bandwidth=0.00984 min_dbm=-143.75 max_dbm=-58.75 fps=23 average=10 weighted_average=0 rfgain=0 rxant=ANT1 wide=0 loopa=0 loopb=0 band=20 daxiq=1 daxiq_rate=48000 capacity=16 available=14 waterfall=42000000 min_bw=0.004919999957085 max_bw=7.372800292969 xvtr= pre= ant_list=ANT1,ANT2,XVTR
    //S69A3CDEB|display waterfall 0x42000000 x_pixels=1170 center=14.03499 bandwidth=0.00984 line_duration=100 rfgain=0 rxant=ANT1 wide=0 loopa=0 loopb=0 band=20 daxiq=0 daxiq_rate=0 capacity=16 available=14 panadapter=40000000 color_gain=27 auto_black=1 black_level=0 gradient_index=0 xvtr=
	commandList.add(F("sub slice all"));
	//S69A3CDEB|slice 0 in_use=1 RF_frequency=14.036190 rit_on=0 rit_freq=0 xit_on=0 xit_freq=0 rxant=ANT1 mode=CW wide=0 filter_lo=-200 filter_hi=200 step=10 step_list=1,5,10,50,100,200,400 agc_mode=med agc_threshold=65 agc_off_level=10 pan=0x40000000 txant=ANT1 loopa=0 loopb=0 qsk=1 dax=1 dax_clients=0 lock=0 tx=1 dax_tx=0 active=1 audio_gain=50 audio_pan=50 audio_mute=0 record=0 play=disabled record_time=0.0 anf=0 anf_level=0 nr=0 nr_level=50 nb=0 nb_level=50 apf=0 apf_level=0 diversity=0 diversity_parent=0 diversity_child=0 diversity_index=1342177293 ant_list=ANT1,ANT2,XVTR
	//send(F("sub gps all"));
	//send(F("sub audio_stream all"));
	commandList.add(F("sub cwx all"));
	//send(F("sub xvtr all"));
	//send(F("info"));
	//send(F("version"));
	//commandList.add(F("ant list",1);
	//commandList.add(F("mic list",2);
	send(F("profile global info"));
	send(F("sub memories all"));
	//send(F("profile tx info"));
	//send(F("profile mic info"));
	//send(F("profile display info"));
	//send(F("client udpport 4991"));
	commandList.add(F("eq RXsc info"));
	commandList.add(F("eq TXsc info"));
	commandList.add(F("client udpport 4991"));
	commandList.add(F("keepalive disable"));
    delay(500);
}

void FlexRig::startReceiver() {
    commandList.add(F("display pan c 7.020000 1 800 400"));
	commandList.add(F("slice C 7.020000 ant1 cw"));
}

void FlexRig::stopReceiver() {
    send(F("slice r 0"));
	send(F("slice r 1"));
	send(F("display pan r 0x40000000"));
	send(F("display pan r 1x40000000"));
}

void FlexRig::addToResponseList(int id, int parserId) {

  if((front==0&&rear==RESPONSE_PACKET_LIST_SIZE-1)||(front>0&&rear==front-1)) {
    Serial.println(F("\nResponse List overflow"));
    return;
  } else {
    if(rear==RESPONSE_PACKET_LIST_SIZE-1&&front>0) {
      rear=0;
    } else {
      if((front==0&&rear==-1)||(rear!=front-1))
      rear++;
    }
  }
  packetElement[rear].id=id;
  packetElement[rear].parserId=parserId;
  size++;

}

rPacket FlexRig::removeFromResponseList()
{
  rPacket element;
  if((front==0)&&(rear==-1)) {
      Serial.println(F("Response List underflow\n"));
      return element;
  }
  if(front==rear){
      element=packetElement[front];
      rear=-1;
      front=0;
  } else {
      if(front==RESPONSE_PACKET_LIST_SIZE-1) {
           element=packetElement[front];
           front=0;
      } else {
        element=packetElement[front];
        front++;
      }
  }
  size--;
  return element;
}

void FlexRig::parseReplay(String msg) {

  //Serial.println(msg);
  int id = msg.substring(1, msg.indexOf(F("|"))).toInt();
  //Serial.println(id);
  //Serial.print("size:"); Serial.println(size);

  while (size>0) {
     rPacket tmp = removeFromResponseList();
     //Serial.print(tmp.id); Serial.print(" - "); Serial.print(tmp.parserId);
	 if (tmp.id==id) {
        switch (tmp.parserId) {
			case 0:
			  //parseDummy(msg.substring(msg.lastIndexOf(F("|"))+1));
			  break;
			case 1:
			  //parseAntennaList(msg.substring(msg.lastIndexOf(F("|"))+1));
			  break;
			case 2:
			  //parseMicList();
			  break;
			case 3:
			  //Serial.print("First Cwx CharId:");
			  //Serial.println(msg.substring(msg.lastIndexOf(F("|"))+1));
			  String t=msg.substring(msg.lastIndexOf(F("|"))+1);
			  //Serial.print("ParseReplay - commandId"); Serial.print(tmp.id);
			  //Serial.print(" - FirstCharId:" );
			  //Serial.println(t.toInt());
			  cwx.setFromToValues(tmp.id,t.toInt());   //commandId, firstCharId
	   }
       break;
     }
  }

}

void FlexRig::parseDummy(String msg) {
  //Serial.println(F("=== Dummy ==="));
  //Serial.println(msg+"<"));
  //Serial.print(F("===front:")); Serial.print(front);Serial.print(F(" - rear:")); Serial.print(rear);Serial.print(F(" - size:")); Serial.print(size);
  //Serial.println();
}

void FlexRig::parseAntennaList(String msg) {
  //Serial.println(F("=== Antenna List ==="));
  Serial.println(msg);
}

void FlexRig::parseMicList(String msg) {
  //Serial.println(F("=== Mic List ==="));
  Serial.println(msg);
}


void FlexRig::updateObject(int objectId,int value,int activeSlice,int activePanadapter,int activeWaterfall) {

	int i=(int)objectId/1000;
	/* do not use this code - it locks the console!!!!
	Serial.print(F("updateStatus id="));Serial.print(objectId);
	Serial.print(F(" - value="));Serial.print(value);
	Serial.print(F(" - activeSlice="));Serial.println(activeId);
	*/
	switch(i) {
		case 1: //Radio
		        this->radio.updateObject(objectId,value);
				break;
		case 2: //Interlock
		        this->interlock.updateObject(objectId,value);
				break;
		case 3: //Transmit
		        this->transmit.updateObject(objectId,value);
				break;
		case 4: //Waterfall (0/1)
				this->waterfall[activeWaterfall].updateObject(objectId,value);
				break;
		case 5: //Panadapter (0/1)
		        this->panadapter[activePanadapter].updateObject(objectId,value);
				break;
		case 6: //Slice (0/1)
		        this->slice[activeSlice].updateObject(objectId,value);
				break;
		case 7: //Eq
		        this->eq.updateObject(objectId,value);
				break;
		default:
			    Serial.print(F("FlexRig::updateObject - Unhandled Status:"));Serial.println(i);
	}

}

void  FlexRig::sendAllCommands() {
    while (commandList.getCount()>0) {
		send(commandList.remove());
	}
}

//DA cancellare
void FlexRig::addToCommandList(String entry) {
		commandList.add(entry);
}

/*
 * Return (and remove) the first command in the list
 */
 /*
String FlexRig::removeFromCommandList()
{
	return commandList.remove();

 String element;
  if((cFront==0)&&(cRear==-1)) {
      Serial.println(F("\nCommand List underflow"));
      return element;
  }
  if(cFront==cRear){
      element=CommandEntry[cFront];
      cRear=-1;
      cFront=0;
  } else {
      if(cFront==COMMAND_LIST_SIZE-1) {
           element=CommandEntry[cFront];
           cFront=0;
      } else {
        element=CommandEntry[cFront];
        cFront++;
      }
  }
  cSize--;
  //Serial.print(F("->")); Serial.println(element);
  return element;
}
*/

unsigned int FlexRig::getUIntValue2Bytes(char nb1, char nb2) {

  return nb2 | nb1 << 8;

}

short FlexRig::getMeterValue(char nb1, char nb2) {

  short var=nb2 | nb1 << 8;
  return var;

}

void FlexRig::setMeterField(Meter *m, String fld) {

  // Serial.println(fld);

  int s=fld.indexOf('.',0);
  int e=fld.indexOf('=',0);
  String var=fld.substring(s+1,e);

  if (var.equals(F("src"))) {
    m->id=fld.substring(0,s).toInt();
  }


  if (var.equals(F("nam"))) m->name=fld.substring(e+1,fld.length());
  if (var.equals(F("low"))) m->low=fld.substring(e+1,fld.length()).toFloat();
  if (var.equals(F("hi"))) m->hi=fld.substring(e+1,fld.length()).toFloat();
  if (var.equals(F("num"))) m->num=fld.substring(e+1,fld.length()).toInt();
  if (var.equals(F("unit"))) {
    String val=fld.substring(e+1,fld.length());
    if (val.equals(F("dBFS"))) m->unit=dBFS;
    if (val.equals(F("Volts"))) m->unit=Volts;
    if (val.equals(F("dBm"))) m->unit=dBm;
    if (val.equals(F("SWR"))) m->unit=SWR;
    if (val.equals(F("degC"))) m->unit=degC;
  }

}

void FlexRig::parseMeter(String msg) {

  Meter met;
  //Serial.println(msg);
  int oldi=0;
  int i=msg.indexOf('#',oldi);
  while (i>0) {
    setMeterField(&met, msg.substring(oldi,i));
    oldi=i+1;
    i=msg.indexOf('#',oldi+1);
  }

  if (met.name.equals(F("LEVEL")) && met.num==0) met.name="LEVEL-0";
  if (met.name.equals(F("LEVEL")) && met.num==1) met.name="LEVEL-1";

  /*Serial.print(F("Meter name: ")); Serial.println(met.name);
  Serial.print(F("Meter id  : ")); Serial.println(met.id);
  Serial.print(F("Meter low : ")); Serial.println(met.low);
  Serial.print(F("Meter hi  : ")); Serial.println(met.hi);
  Serial.print(F("Meter num : ")); Serial.println(met.num);
  Serial.print(F("Meter unit : ")); Serial.println(met.unit);*/

  //Inserire codice che registra gli ID dei meter che si vuole monitorare
  int index=-1;
  if (met.name.equals(F("MICPEAK")))  index=MET_MIC_PEAK;
  if (met.name.equals(F("COMPPEAK"))) index=MET_COMP_PEAK;
  if (met.name.equals(F("SWR")))      index=MET_SWR;
  if (met.name.equals(F("FWDPWR")))   index=MET_FPWR;
  if (met.name.equals(F("LEVEL-0")))  index=MET_S_A;
  if (met.name.equals(F("LEVEL-1")))  index=MET_S_B;
  if (met.name.equals(F("PATEMP")))   index=PATEMP;
  if (met.name.equals(F("+13.8A")))   index=VOLTAGE_BEFORE;
  if (met.name.equals(F("+13.8B")))   index=VOLTAGE_AFTER;

  metersId[index]=met.id;
}

//GUI METHODS IMPLEMENTATION
/************************************ SLICE ****************************************/

/************************************ RADIO ****************************************/
void FlexRig::set_headphone_gain(int val){
	char cmd[30];
	sprintf(cmd,"mixer headphone gain %d",val);
	//sprintf(cmd,"audio client 0 slice 0 gain %d",val);

	addToCommandList(cmd);
	radio.set_headphone_gain(val);
}


/************************************ RADIO ****************************************/
void FlexRig::set_sidetone_onoff(int value) {
	char cmd[40];
	sprintf(cmd,"cw sidetone %d",value);
	addToCommandList(cmd);
	transmit.set_sidetone(value);
}

void FlexRig::set_breakin_onoff(int value){
	char cmd[40];
	sprintf(cmd,"cw break_in %d",value);
	addToCommandList(cmd);
	transmit.set_break_in(value);
}

void FlexRig::set_iambic_onoff(int value){
	char cmd[40];
	sprintf(cmd,"cw iambic %d",value);
	addToCommandList(cmd);
	transmit.set_iambic(value);
}

void FlexRig::set_vox_onoff(int value){
	char cmd[40];
	sprintf(cmd,"transmit set vox_enable=%d",value);
	addToCommandList(cmd);
	transmit.set_vox_enable(value);
}

void FlexRig::set_dexp_onoff(int value){
	char cmd[40];
	sprintf(cmd,"transmit set compander=%d",value);
	addToCommandList(cmd);
	transmit.set_compander(value);
}

void FlexRig::set_proc_onoff(int value){
	char cmd[40];
	sprintf(cmd,"transmit set speech_processor_enable=%d",value);
	addToCommandList(cmd);
	transmit.set_speech_processor_enable(value);
}

void FlexRig::set_monitor_onoff(int value){
	char cmd[40];
	sprintf(cmd,"transmit set mon=%d",value);
	addToCommandList(cmd);
	transmit.set_sb_monitor(value);
}

void FlexRig::setRxAntenna(int sliceId, String value){
	char cmd[40];
	sprintf(cmd,"slice set %d rxant=%s",sliceId,value.c_str());
	addToCommandList(cmd);
	slice[sliceId].set_rxant(value);
}

void FlexRig::setTxAntenna(int sliceId, String value){
	char cmd[40];
	sprintf(cmd,"slice set %d txant=%s",sliceId,value.c_str());
	addToCommandList(cmd);
	slice[sliceId].set_txant(value);
}

void FlexRig::setPreampGain(int panId, int value){
	char cmd[50];
	sprintf(cmd,"display pan set 0x%d rfgain=%d.0",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_rfgain(value);
}

void FlexRig::setTxEqMode(int value){
	char cmd[40];
	if (value)
		sprintf(cmd,"eq TXsc mode=True");
    else
		sprintf(cmd,"eq TXsc mode=False");
	addToCommandList(cmd);
	eq.set_TX_mode(value);
}

void FlexRig::setRxEqMode(int value){
	char cmd[40];
	if (value)
		sprintf(cmd,"eq RXsc mode=True");
    else
		sprintf(cmd,"eq RXsc mode=False");
	addToCommandList(cmd);
	eq.set_RX_mode(value);
}

void FlexRig::setBand(int panId,int value){
	char cmd[50];
	//Serial.println(panId+40000000);
	//Serial.println(panId+value);
	sprintf(cmd,"display pan set 0x%d band=%d",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_band(value);
}

void FlexRig::setMode(int sliceId,String value){
	char cmd[40];
	sprintf(cmd,"slice set %d mode=%s",sliceId,value.c_str());
	addToCommandList(cmd);
	slice[sliceId].set_mode(value);
}

void FlexRig::setTx(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d tx=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_tx(active);
}

void FlexRig::setActiveSlice(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d active=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_active(active);
}

void FlexRig::removeSlice(int sliceId){
	char cmd[30];
	sprintf(cmd,"slice r %d",sliceId);
	addToCommandList(cmd);
	slice[sliceId].set_in_use(0);
}

void FlexRig::createSlice(double freq,String antenna,String mode){
	char cmd[50];
	sprintf(cmd,"slice c %f %s %s",freq,antenna.c_str(),mode.c_str());
	addToCommandList(cmd);
}

void FlexRig::removePanadapter(int panId){
	char cmd[30];
	//sprintf(cmd,"display pan r %dx40000000",panId);
	//addToCommandList(cmd);
}


void FlexRig::createPanadapter(double freq){
	char cmd[50];
	//sprintf(cmd,"display pan c %f 1 800 400",freq);
	//addToCommandList(cmd);
}

void FlexRig::setFreq(int sliceId, int freq) {
	char cmd[40];
	sprintf(cmd, "slice t %d %f\n",sliceId,(double)freq/1000000);
    addToCommandList(String(cmd));
	slice[sliceId].RF_frequency=freq;
}

void FlexRig::setAgcMode(int sliceId, String value) {
	char cmd[40];
	sprintf(cmd,"slice set %d agc_mode=%s",sliceId,value.c_str());
	addToCommandList(cmd);
	slice[sliceId].set_agc_mode(value);
}

void FlexRig::setDisplayPanWeightAverage(int panId,int value){
    char cmd[60];
	sprintf(cmd,"display pan set 0x%d weighted_average=%d",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_weighted_average(value);
}

void FlexRig::setPanafallAutoBlack(int panFallId,int value){
    char cmd[60];
	sprintf(cmd,"display panafall set 0x%d auto_black=%d",panFallId+42000000,value);
	addToCommandList(cmd);
	waterfall[panFallId].set_auto_black(value);
}

void FlexRig::setNr(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d nr=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_nr(active);
}

void FlexRig::setWnb(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d wnb=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_wnb(active);
}

void FlexRig::setNb(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d nb=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_nb(active);
}

void FlexRig::setApf(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d apf=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_apf(active);
}

void FlexRig::setAnf(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d anf=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_anf(active);
}

void FlexRig::setRit(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d rit_on=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_rit_on(active);
}

void FlexRig::setXit(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d xit_on=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_xit_on(active);
}

void FlexRig::setAudioMute(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"audio client 0 slice %d mute %d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_audio_mute(active);
}

void FlexRig::setAgcOffLevel(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d agc_off_level=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_agc_off_level(active);
}

void FlexRig::setAgcThreshold(int sliceId,int active){
	char cmd[40];
	sprintf(cmd,"slice set %d agc_threshold=%d",sliceId,active);
	addToCommandList(cmd);
	slice[sliceId].set_agc_threshold(active);
}

void FlexRig::setLineoutMute(int active){
	char cmd[40];
	sprintf(cmd,"mixer lineout mute %d",active);
	addToCommandList(cmd);
	radio.set_lineout_mute(active);
}

void FlexRig::setHeadphoneMute(int active){
	char cmd[40];
	sprintf(cmd,"mixer headphone mute %d",active);
	addToCommandList(cmd);
	radio.set_headphone_mute(active);
}

void FlexRig::setBandWidth(int sliceId,int low,int high){
	char cmd[40];
	sprintf(cmd,"filt %d %d %d",sliceId, low, high);
	addToCommandList(cmd);
	slice[sliceId].set_filter_lo(low);
	slice[sliceId].set_filter_hi(high);
	slice[sliceId].calcShiftWidthValue();
}

void FlexRig::setWnbLevel(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"slice set %d wnb_level=%d",sliceId,value);
	addToCommandList(cmd);
	slice[sliceId].set_wnb_level(value);
}

void FlexRig::setNbLevel(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"slice set %d nb_level=%d",sliceId,value);
	addToCommandList(cmd);
	slice[sliceId].set_nb_level(value);
}

void FlexRig::setNrLevel(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"slice set %d nr_level=%d",sliceId,value);
	addToCommandList(cmd);
	slice[sliceId].set_nr_level(value);
}

void FlexRig::setApfLevel(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"slice set %d apf_level=%d",sliceId,value);
	addToCommandList(cmd);
	slice[sliceId].set_apf_level(value);
}

void FlexRig::setAnfLevel(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"slice set %d anf_level=%d",sliceId,value);
	addToCommandList(cmd);
	slice[sliceId].set_anf_level(value);
}

void FlexRig::setPanAverage(int panId,int value){
	char cmd[40];
	sprintf(cmd,"display pan set 0x%d average=%d",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_average(value);
}

void FlexRig::setRitFreq(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"slice set %d rit_freq=%d",sliceId,value);
	addToCommandList(cmd);
	slice[sliceId].set_rit_freq(value);
}

void FlexRig::setXitFreq(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"slice set %d xit_freq=%d",sliceId,value);
	addToCommandList(cmd);
	slice[sliceId].set_xit_freq(value);
}

void FlexRig::setPanFps(int panId,int value){
	char cmd[50];
	sprintf(cmd,"display pan set 0x%d fps=%d",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_fps(value);
}

void FlexRig::setRxFiltLow(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"filt %d %d %d",sliceId,value,slice[sliceId].filter_hi);
    addToCommandList(cmd);
	slice[sliceId].set_filter_lo(value);
	slice[sliceId].calcShiftWidthValue();
}

void FlexRig::setRxFiltShift(int sliceId,int value){
	char cmd[40];
	slice[sliceId].set_filter_shift(value);
	slice[sliceId].calcHighLowValues();
    sprintf(cmd,"filt %d %d %d",sliceId,slice[sliceId].filter_lo,slice[sliceId].filter_hi);
    addToCommandList(cmd);
}

void FlexRig::setWatBlackLevel(int watId,int value){
	char cmd[60];
	sprintf(cmd,"display panafall set 0x%d black_level=%d",watId+42000000,value);
	addToCommandList(cmd);
	waterfall[watId].set_black_level(value);
}

void FlexRig::setRxFiltHigh(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"filt %d %d %d",sliceId,slice[sliceId].filter_lo,value);
    addToCommandList(cmd);
	slice[sliceId].set_filter_hi(value);
	slice[sliceId].calcShiftWidthValue();
}

void FlexRig::setRxFiltWidth(int sliceId,int value){
	char cmd[40];
	slice[sliceId].set_filter_width(value);
	slice[sliceId].calcHighLowValues();
    sprintf(cmd,"filt %d %d %d",sliceId,slice[sliceId].filter_lo,slice[sliceId].filter_hi);
    addToCommandList(cmd);
}

void FlexRig::setWatGradientId(int watId,int value){
	char cmd[60];
	sprintf(cmd,"display panafall set 0x%d gradient_index=%d",watId+42000000,value);
	addToCommandList(cmd);
	waterfall[watId].set_gradient_index(value);
}

void FlexRig::setAudioGain(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"audio client 0 slice %d gain %d",sliceId,value);
    addToCommandList(cmd);
	slice[sliceId].set_audio_gain(value);
}

void FlexRig::setAudioPan(int sliceId,int value){
	char cmd[40];
	sprintf(cmd,"audio client 0 slice %d pan %d",sliceId,value);
    addToCommandList(cmd);
	slice[sliceId].set_audio_pan(value);
}

void FlexRig::setWatLineDuration(int watId,int value){
	char cmd[60];
	sprintf(cmd,"display panafall set 0x%d line_duration=%d",watId+42000000,value);
	addToCommandList(cmd);
	waterfall[watId].set_line_duration(value);
}

void FlexRig::setWatColorGain(int watId,int value){
	char cmd[60];
	sprintf(cmd,"display panafall set 0x%d color_gain=%d",watId+42000000,value);
	addToCommandList(cmd);
	waterfall[watId].set_color_gain(value);
}

void FlexRig::setCwSpeed(int value){
	char cmd[30];
	sprintf(cmd,"cw wpm %d",value);
    addToCommandList(cmd);
	transmit.set_speed(value);
}

void FlexRig::setCwPitch(int value){
	char cmd[30];
	sprintf(cmd,"cw pitch %d",value);
    addToCommandList(cmd);
	transmit.set_pitch(value);
}

void FlexRig::setCwBreakinInDelay(int value){
	char cmd[30];
	sprintf(cmd,"cw break_in_delay %d",value);
    addToCommandList(cmd);
	transmit.set_break_in_delay(value);
}

void FlexRig::setCwMonitorGain(int value){
	char cmd[30];
	sprintf(cmd,"transmit set mon_gain_cw=%d",value);
    addToCommandList(cmd);
	transmit.set_mon_gain_cw(value);
}

void FlexRig::setCwMonitorPan(int value){
	char cmd[30];
	sprintf(cmd,"transmit set mon_pan_cw=%d",value);
    addToCommandList(cmd);
	transmit.set_mon_pan_cw(value);
}

void FlexRig::setMicLevel(int value){
	char cmd[40];
	sprintf(cmd,"transmit set miclevel=%d",value);
    addToCommandList(cmd);
	transmit.set_mic_level(value);
}

void FlexRig::setSbMonitorGain(int value){
	char cmd[40];
	sprintf(cmd,"transmit set mon_gain_sb=%d",value);
    addToCommandList(cmd);
	transmit.set_mon_gain_sb(value);
}

void FlexRig::setCompanderLevel(int value){
	char cmd[40];
	sprintf(cmd,"transmit set compander_level=%d",value);
    addToCommandList(cmd);
	transmit.set_compander_level(value);
}

void FlexRig::setVoxLevel(int value){
	char cmd[40];
	sprintf(cmd,"transmit set vox_level=%d",value);
    addToCommandList(cmd);
	transmit.set_vox_level(value);
}

void FlexRig::setVoxDelay(int value){
	char cmd[40];
	sprintf(cmd,"transmit set vox_delay=%d",value);
    addToCommandList(cmd);
	transmit.set_vox_delay(value);
}

void FlexRig::setAmCarrier(int value){
	char cmd[40];
	sprintf(cmd,"transmit set am_carrier=%d",value);
    addToCommandList(cmd);
	transmit.set_am_carrier_level(value);
}

void FlexRig::setTransmitLow(int value){
	char cmd[40];
	sprintf(cmd,"transmit set filter_low=%d filter_high=%d",value,transmit.hi);
    addToCommandList(cmd);
	transmit.set_lo(value);
}

void FlexRig::setTransmitHigh(int value){
	char cmd[40];
	sprintf(cmd,"transmit set filter_low=%d filter_high=%d",transmit.lo,value);
    addToCommandList(cmd);
	transmit.set_hi(value);
}

void FlexRig::setPanBandwidth(int panId,float value){
	char cmd[70];
	sprintf(cmd,"display pan set 0x%d bandwidth=%f autocenter=1",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_bandwidth(value*1000000);
}

void FlexRig::setLineoutGain(int value){
	char cmd[40];
	sprintf(cmd,"mixer lineout gain %d",value);
    addToCommandList(cmd);
	radio.set_lineout_gain(value);
}

void FlexRig::setHeadphoneGain(int value){
	char cmd[40];
	sprintf(cmd,"mixer headphone gain %d",value);
    addToCommandList(cmd);
	radio.set_headphone_gain(value);
}

void FlexRig::setRfPower(int value){
	char cmd[40];
	sprintf(cmd,"transmit set rfpower=%d",value);
    addToCommandList(cmd);
	transmit.set_rfpower(value);
}

void FlexRig::setTunePower(int value){
	char cmd[40];
	sprintf(cmd,"transmit set tunepower=%d",value);
    addToCommandList(cmd);
	transmit.set_tunepower(value);
}

void FlexRig::setPanMinDbm(int panId,float value){
	char cmd[50];
	sprintf(cmd,"display pan set 0x%d min_dbm=%f",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_min_dbm(value);
}

void FlexRig::setPanMaxDbm(int panId,float value){
	char cmd[50];
	sprintf(cmd,"display pan set 0x%d max_dbm=%f",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_max_dbm(value);
}

void FlexRig::setPanCenter(int panId,float value){
	char cmd[50];
	sprintf(cmd,"display pan set 0x%d center=%f",panId+40000000,value);
	addToCommandList(cmd);
	panadapter[panId].set_center(value);
}

void FlexRig::setEqControl(String type,String freq,int value){
	char cmd[30];
	sprintf(cmd,"eq %ssc %s=%d",type.c_str(),freq.c_str(),value);
	addToCommandList(cmd);
	if (type.equals(F("RX"))) {
		if (freq.equals(F("63Hz")))   { eq.set_RX_63Hz(value);   return; }
		if (freq.equals(F("125Hz")))  { eq.set_RX_125Hz(value);  return; }
		if (freq.equals(F("250Hz")))  { eq.set_RX_250Hz(value);  return; }
		if (freq.equals(F("500Hz")))  { eq.set_RX_500Hz(value);  return; }
		if (freq.equals(F("1000Hz"))) { eq.set_RX_1000Hz(value); return; }
		if (freq.equals(F("2000Hz"))) { eq.set_RX_2000Hz(value); return; }
		if (freq.equals(F("4000Hz"))) { eq.set_RX_4000Hz(value); return; }
		if (freq.equals(F("8000Hz"))) { eq.set_RX_8000Hz(value); return; }
	} else {
		if (freq.equals(F("63Hz")))   { eq.set_TX_63Hz(value);   return; }
		if (freq.equals(F("125Hz")))  { eq.set_TX_125Hz(value);  return; }
		if (freq.equals(F("250Hz")))  { eq.set_TX_250Hz(value);  return; }
		if (freq.equals(F("500Hz")))  { eq.set_TX_500Hz(value);  return; }
		if (freq.equals(F("1000Hz"))) { eq.set_TX_1000Hz(value); return; }
		if (freq.equals(F("2000Hz"))) { eq.set_TX_2000Hz(value); return; }
		if (freq.equals(F("4000Hz"))) { eq.set_TX_4000Hz(value); return; }
		if (freq.equals(F("8000Hz"))) { eq.set_TX_8000Hz(value); return; }
	}
}

void FlexRig::setMoxState(int value){
	char cmd[30];
	sprintf(cmd,"xmit %d",value);
	addToCommandList(cmd);
}

void FlexRig::setTuneState(int value){
    char cmd[30];
	sprintf(cmd,"transmit tune %d",value);
	addToCommandList(cmd);
	transmit.set_tune(value);
}

void FlexRig::enableAtu(int value) {
	char cmd[30];
	if (value==0)
		sprintf(cmd,"atu bypass");
    else
        sprintf(cmd,"atu start");
	addToCommandList(cmd);
}
void FlexRig::setAtuMemMode(int value) {
	char cmd[40];
	sprintf(cmd,"atu set memories_enabled=%d",value);
	addToCommandList(cmd);
}


void FlexRig::setStep(int sliceId,int value){
    char cmd[40];
	sprintf(cmd,"slice set %d step=%d",sliceId,value);
    addToCommandList(cmd);
	slice[sliceId].set_step(value);
}

int FlexRig::sendCwxMsg(String value){
	char cmd[250];
	sprintf(cmd,"cwx send \"%s\"",value.c_str());
	//addToCommandList(cmd);
	int c=send(cmd, 3);
	//Serial.print("Cwx Response command:");Serial.println(c);
	return c;
}

int FlexRig::sendCwxMacro(int value) {
	char cmd[250];
	switch (value) {
		case 1:
			sprintf(cmd,"cwx send \"%s\"",cwx.macro1.c_str());
			break;
		case 2:
			sprintf(cmd,"cwx send \"%s\"",cwx.macro2.c_str());
			break;
		case 3:
			sprintf(cmd,"cwx send \"%s\"",cwx.macro3.c_str());
			break;
	}
	int c=send(cmd, 3);
	cwx.addToInfoList(value,c);
	//Serial.print("Cwx Response command:");Serial.println(c);
	return c;
}

void FlexRig::clearCwx(){
	char *cmd=(char*)"cwx clear";
	addToCommandList(cmd);
}