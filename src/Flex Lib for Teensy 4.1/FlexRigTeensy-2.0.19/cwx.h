/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef Cwx_h
#define Cwx_h
#include "Arduino.h"

#define MACRO_INFO_LIST_SIZE 10
extern "C" {
	typedef void (*eventHandlerFunction)(void);
}

extern "C" {
	typedef void (*eventHandlerArrFunction)(const int senderId);
}

typedef struct MacroInfo
{
  int macroId;           //MacroId it can be 1/2/3/.../12
  int commandId;         //Command id to match with
  int from;              //First macro character
  int to;                //Last macro character   
} macroInfoElement;

class Cwx
{
  public:
    //properties
	int wpm;
	int break_in_delay;
	String macro1;
	String macro2;
	String macro3;
	// String macro4;
	// String macro5;
	// String macro6;
	// String macro7;
	// String macro8;
	// String macro9;
	// String macro10;
	// String macro11;
	// String macro12;
	int sent;
	String erase;
	
	
    //methods
    Cwx();
	void updateStatus(String msg);
	void updateObject(int objectId,int value);  //Update specific interlock object	
	//circular list methods
	void printMacroInfoList();
	void addToInfoList(int macroId,int commandId);
	void removeFromInfoList(int commandId);
	void setFromToValues(int commandId, int firstCharId);
	
	//setter methods
	void set_wpm(int newval); 
	void set_break_in_delay(int newval);  
	void set_macro1(String newval); 
	void set_macro2(String newval); 
	void set_macro3(String newval); 
	void set_sent(int newval); 
	void set_erase(String newval); 
	
	//event handler accessor methods
	void attach_wpm_event(eventHandlerFunction _eventHandler); //=0 
	void attach_break_in_delay_event(eventHandlerFunction _eventHandler); 
	void attach_macro1_event(eventHandlerFunction _eventHandler); 
	void attach_macro2_event(eventHandlerFunction _eventHandler); 
	void attach_macro3_event(eventHandlerFunction _eventHandler); 
	void attach_sent_event(eventHandlerFunction _eventHandler); 
	void attach_erase_event(eventHandlerArrFunction _eventHandler);

    void attach_macro_active_event(eventHandlerArrFunction _eventHandler); 
	void attach_macro_stopped_event(eventHandlerArrFunction _eventHandler); 
	
	//
	void fireEvents();
	boolean updated;
	
	//Update Flags
	boolean upd_wpm;
	boolean upd_break_in_delay; 
	boolean upd_macro1; 
	boolean upd_macro2; 
	boolean upd_macro3; 
	boolean upd_sent; 
	boolean upd_erase;
    
	//event handlers
	eventHandlerFunction do_wpm_event=NULL; //=0 
	eventHandlerFunction do_break_in_delay_event=NULL; 
	eventHandlerFunction do_macro1_event=NULL; 
	eventHandlerFunction do_macro2_event=NULL; 
	eventHandlerFunction do_macro3_event=NULL; 
	eventHandlerFunction do_sent_event=NULL; 
	eventHandlerArrFunction do_erase_event=NULL;  
	
	eventHandlerArrFunction do_macro_active_event=NULL; 
	eventHandlerArrFunction do_macro_stopped_event=NULL;  
	
	
  private:
    //properties
	macroInfoElement mInfoElem[MACRO_INFO_LIST_SIZE]; //circular queque
	int front;   //pointer to macro info list array

    //methods	
	void setValue(String msg);
	int getInfoId(int commandId);
	//
};
	
#endif