/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef Atu_h
#define Atu_h
#include "Arduino.h"

extern "C" {
	typedef void (*eventHandlerFunction)(void);
}

class Atu
{
  public:
    //properties
	int atu_enabled; //=0 
	int memories_enabled; //=0 
	int using_mem; //=0
	String status; //TRANSMITTING
	int int_status; //0=TUNE_MAUNAL_BYPASS - 1=TUNE_IN_PROGRESS - 2=TUNE_SUCCESSFUL
	
    //methods
    Atu();
	void updateStatus(String msg);
	void updateObject(int objectId,int value);  //Update specific interlock object	
	
	//setter methods
	void set_atu_enabled(int newval); //=0 
	void set_memories_enabled(int newval); 
	void set_using_mem(int newval); 
	void set_status(String newval); 
	void set_int_status(int newval); 
	
	
	//event handler accessor methods
	void attach_atu_enabled_event(eventHandlerFunction _eventHandler); //=0 
	void attach_memories_enabled_event(eventHandlerFunction _eventHandler); 
	void attach_using_mem_event(eventHandlerFunction _eventHandler); 
	void attach_status_event(eventHandlerFunction _eventHandler); 
	void attach_int_status_event(eventHandlerFunction _eventHandler); 
	
	//
	void fireEvents();
	boolean updated;
	
	//Update Flags
	boolean upd_atu_enabled;
	boolean upd_memories_enabled; 
	boolean upd_using_mem; 
	boolean upd_status;
	boolean upd_int_status;
	
	
	//event handlers
	eventHandlerFunction do_atu_enabled_event=NULL; //=0 
	eventHandlerFunction do_memories_enabled_event=NULL; 
	eventHandlerFunction do_using_mem_event=NULL; 
	eventHandlerFunction do_status_event=NULL; 
	eventHandlerFunction do_int_status_event=NULL; 

  private:
    //properties
	
    //methods	
	void setValue(String msg);
};
	
#endif