/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/

  The license applies to all part of the library including the
  examples and tools supplied with the library.
  
                 VERSION 2.10  VERSION 2.10  VERSION 2.10  VERSION 2.10  
                 VERSION 2.10  VERSION 2.10  VERSION 2.10  VERSION 2.10
                 VERSION 2.10  VERSION 2.10  VERSION 2.10  VERSION 2.10  
*/
#ifndef FlexRig_h
#define FlexRig_h

#include "Arduino.h"
#include <SPI.h>
#include <NativeEthernet.h>
#include "Radio.h"
#include "Transmit.h"
#include "Interlock.h"
#include "Panadapter.h"
#include "Waterfall.h"
#include "Slice.h"
#include "Eq.h"
#include "CommandList.h"
#include "Cwx.h"
#include "Atu.h"

#define UDP_DISCOVERING_PORT 4992
#define UDP_TX_PACKET_MAX_SIZE 1024	// V3 = 596, V2 = 350
#define UDP_VITA49_PORT 4991
#define UDP_VITA49_PACKET_MAX_SIZE 16384	// V3 = 16384, V2 = 4992
#define RESPONSE_PACKET_LIST_SIZE 1024	// V3 = 1024, V2 = 25

//COMMAND (CIRCULAR) LIST
//#define COMMAND_LIST_SIZE 20
//#define COMMAND_LEGTH 80
#define UPDATE_VFO_TIMER 25  //millis


enum UNITS {dBFS=0, Volts, dBm, SWR, degC};
enum METERS_ID {MET_S_A=0, MET_S_B, MET_SWR, MET_FPWR, MET_MIC_PEAK, 
                MET_COMP_PEAK, PATEMP, VOLTAGE_BEFORE, VOLTAGE_AFTER};


struct rPacket
{
  int id;                //Command id to match with
  int parserId;          //Message parser id
};

struct Meter     //Meters Structure
{
  String name;   //Meter Name
  int id;        //Meter id
  float low;     //Min meter value
  float hi;      //Max meter value
  float value;   //Meter value
  int num;       //Meter source object num
  int unit;      //Meter unit
};

class FlexRig
{
  public:
    //properties
	byte ipAddress[4];       //IP Address

	char modelName[36];      //Model Name
    char serial[36];         //Serial Number
    char nickName[36];       //Nick Name
    char softVersion[32];    //Software Version
	char handle[8];          //Handle assigned to client
	int C;                   //Command id counter
	boolean connected;       //Connection status
	int preampList[5];
	int preampListSize;
	//Embedded objects
	Radio radio;
	Transmit transmit;
	Interlock interlock;
	Cwx cwx;
	Panadapter panadapter[2];
	Waterfall waterfall[2];
	Slice slice[2];
	Eq eq;
	Atu atu;
    boolean vfo;
	int nMaxSlice;
	int activeSlice;
	int nMaxPanadapter;
	int activePanadapter;
	int nMaxWaterfall;
	int activeWaterfall;
	float metersValue[9];       //meters values
	String Current_Profile;
	String Profile[200];
	int MaxMemNum = 0;
	int Mem[200];	// mem num kept in Flex (may not be consecutive)
	String MemName[200];
	String MemFreq[200];

    //methods
    FlexRig();
	void connect();
	void process();
	void fireEvents();
	void ping();
	void setPreampList(char m);
	//void setVFOA(float freq);
	void parseStatus(String msg);
	void initBuffer();
	void send(String cmd);
	static FlexRig findAFlex(const char* serial);
	void startReceiver();
	void stopReceiver();
	void updateObject(int objectId,int value,int activeSlice,int activePanadapter,int activeWaterfall);
	//String removeFromCommandList();
	void addToCommandList(String entry);
	
	//GUI METHODS
	void set_headphone_gain(int val);
	
	void set_sidetone_onoff(int value);
	void set_breakin_onoff(int value);
	void set_iambic_onoff(int value);
	void set_vox_onoff(int value);
	void set_dexp_onoff(int value);
	void set_proc_onoff(int value);
	void set_monitor_onoff(int value);
	
	void setRxAntenna(int sliceId, String value);
	void setTxAntenna(int sliceId, String value);
	void setPreampGain(int panId, int value);
	void setTxEqMode(int value);
	void setRxEqMode(int value);
	
	void setBand(int panId,int value);
	void setMode(int sliceId,String value);
	
	void setTx(int sliceId,int active);
	void setActiveSlice(int sliceId,int active);
	void removeSlice(int sliceId);
	//void createSlice(float freq,String antenna,String mode);
	void createSlice(double freq,String antenna,String mode);
	void removePanadapter(int panId);
	//void createPanadapter(float freq);
	void createPanadapter(double freq);
	void setFreq(int sliceId, int freq);
	
	void setAgcMode(int sliceId, String value);
	
	void setDisplayPanWeightAverage(int panId,int value);
	void setPanafallAutoBlack(int panFallId,int value);
	
	void setNb(int sliceId,int active);
	void setNr(int sliceId,int active);
	void setWnb(int sliceId,int active);
	void setApf(int sliceId,int active);
	void setAnf(int sliceId,int active);
	
	void setRit(int sliceId,int active);
	void setXit(int sliceId,int active);
	
	void setAudioMute(int sliceId,int active);
	
	void setAgcOffLevel(int sliceId,int active);
	void setAgcThreshold(int sliceId,int active);
	
	void setLineoutMute(int active);
	void setHeadphoneMute(int active);
	
	void setBandWidth(int sliceId,int low,int high);
	
	//Encoders methods
	void setWnbLevel(int sliceId,int value);
	void setNbLevel(int sliceId,int value);
	void setNrLevel(int sliceId,int value);
	void setApfLevel(int sliceId,int value);
	void setAnfLevel(int sliceId,int value);
	void setPanAverage(int panId,int value);
	void setRitFreq(int sliceId,int value);
	void setXitFreq(int sliceId,int value);
	void setPanFps(int panId,int value);
	void setRxFiltLow(int sliceId,int value);
	void setRxFiltShift(int sliceId,int value);
	void setWatBlackLevel(int watId,int value);
	void setRxFiltHigh(int sliceId,int value);
	void setRxFiltWidth(int sliceId,int value);
	void setWatGradientId(int watId,int value);
	void setAudioGain(int sliceId,int value);
	void setAudioPan(int sliceId,int value);
	void setWatLineDuration(int watId,int value);	
	void setWatColorGain(int watId,int value);	
	void setCwSpeed(int value);
	void setCwPitch(int value);
	void setCwBreakinInDelay(int value);
	void setCwMonitorGain(int value);
	void setCwMonitorPan(int value);	
	void setMicLevel(int value);
	void setSbMonitorGain(int value);
	void setCompanderLevel(int value);
	void setVoxLevel(int value);
	void setVoxDelay(int value);
	void setAmCarrier(int value);
	void setTransmitLow(int value);
	void setTransmitHigh(int value);
	void setPanBandwidth(int panId,float value);
	void setLineoutGain(int value);
	void setHeadphoneGain(int value);
	void setRfPower(int value);
	void setTunePower(int value);
	void setPanMinDbm(int panId,float value);
	void setPanMaxDbm(int panId,float value);	
	void setPanCenter(int panId,float value);	
	void setEqControl(String type,String freq,int value);
	void setMoxState(int value);
	void setTuneState(int value);
	void enableAtu(int value);
	void setAtuMemMode(int value);
	void setStep(int sliceId,int value);
	int sendCwxMsg(String value);
	int sendCwxMacro(int value);
	void clearCwx();
	
	
  private:
    //properties
	EthernetClient client;
	String buffer;             //tcp-ip buffer
	
	CommandList commandList;
	void sendAllCommands();

	int metersId[9];           //meters id
	
	//Vita-49 variables
	EthernetClient vitaClient;
	EthernetUDP vitaUdp;
    char vitaPacketBuffer[UDP_TX_PACKET_MAX_SIZE];

	rPacket packetElement [RESPONSE_PACKET_LIST_SIZE]; //circular queque
	int front;
	int rear;
	int size;   //pointers to response list array

	
	//String CommandEntry[COMMAND_LIST_SIZE];
	//int cFront=0, cRear=-1,cSize=0;   //pointers to commands circular list
    
	//accessory methods
	static int charIndexOf(const char *string, const char *key);
	static char *valueOf(char *string, char *key);

	//methods
	void readEthernetData();
	void readVita49Data();
	void parseMessage(String msg);
	int send(String cmd, int parserId);
	//void send(String cmd);
	void configureClient();
	void addToResponseList(int id, int parserId);
	rPacket removeFromResponseList();
	//void ping();
    static boolean isAFlex(const char* model,const char* serial,const char* serialKey);
	unsigned int getUIntValue2Bytes(char nb1, char nb2);
    short getMeterValue(char nb1, char nb2) ;
	void setMeterField(Meter *m, String fld);
	void parseMeter(String msg);

	//Parser Methods
	void parseReplay(String msg);
	void parseDummy(String msg);        //0
 	void parseAntennaList(String msg);  //1
    void parseMicList(String msg);	    //2

};

#endif
