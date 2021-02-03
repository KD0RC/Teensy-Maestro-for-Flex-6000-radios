/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef Eq_h
#define Eq_h
#include "Arduino.h"

#define EQ_RX_MODE 7000 
#define EQ_TX_MODE 7001

#define EQ_RX_63HZ 7002
#define EQ_RX_125HZ 7003
#define EQ_RX_250HZ 7004
#define EQ_RX_500HZ 7005
#define EQ_RX_1000HZ 7006
#define EQ_RX_2000HZ 7007
#define EQ_RX_4000HZ 7008
#define EQ_RX_8000HZ 7009

#define EQ_TX_63HZ 7010
#define EQ_TX_125HZ 7011
#define EQ_TX_250HZ 7012
#define EQ_TX_500HZ 7013
#define EQ_TX_1000HZ 7014
#define EQ_TX_2000HZ 7015
#define EQ_TX_4000HZ 7016
#define EQ_TX_8000HZ 7017

extern "C" {
	typedef void (*eventHandlerFunction)(void);
}

class Eq
{
  public:
    //properties
	
	int RX_mode;
	int RX_63Hz;
	int RX_125Hz;
	int RX_250Hz;
	int RX_500Hz;
	int RX_1000Hz;
	int RX_2000Hz;
	int RX_4000Hz;
	int RX_8000Hz;
	int TX_mode;
	int TX_63Hz;
	int TX_125Hz;
	int TX_250Hz;
	int TX_500Hz;
	int TX_1000Hz;
	int TX_2000Hz;
	int TX_4000Hz;
	int TX_8000Hz;
	
	//methods
    Eq();
	void updateStatus(String msg);
	void updateObject(int objectId,int value);  //Update specific transmit object	
	
	//setter methods
	void set_RX_mode(int newval);
	void set_RX_63Hz(int newval);
	void set_RX_125Hz(int newval);
	void set_RX_250Hz(int newval);
	void set_RX_500Hz(int newval);
	void set_RX_1000Hz(int newval);
	void set_RX_2000Hz(int newval);
	void set_RX_4000Hz(int newval);
	void set_RX_8000Hz(int newval);
	void set_TX_mode(int newval);
	void set_TX_63Hz(int newval);
	void set_TX_125Hz(int newval);
	void set_TX_250Hz(int newval);
	void set_TX_500Hz(int newval);
	void set_TX_1000Hz(int newval);
	void set_TX_2000Hz(int newval);
	void set_TX_4000Hz(int newval);
	void set_TX_8000Hz(int newval);
	
	//event handler accessor methods
	void attach_RX_mode_event(eventHandlerFunction _eventHandler);
	void attach_RX_63Hz_event(eventHandlerFunction _eventHandler);
	void attach_RX_125Hz_event(eventHandlerFunction _eventHandler);
	void attach_RX_250Hz_event(eventHandlerFunction _eventHandler);
	void attach_RX_500Hz_event(eventHandlerFunction _eventHandler);
	void attach_RX_1000Hz_event(eventHandlerFunction _eventHandler);
	void attach_RX_2000Hz_event(eventHandlerFunction _eventHandler);
	void attach_RX_4000Hz_event(eventHandlerFunction _eventHandler);
	void attach_RX_8000Hz_event(eventHandlerFunction _eventHandler);

	void attach_TX_mode_event(eventHandlerFunction _eventHandler);
	void attach_TX_63Hz_event(eventHandlerFunction _eventHandler);
	void attach_TX_125Hz_event(eventHandlerFunction _eventHandler);
	void attach_TX_250Hz_event(eventHandlerFunction _eventHandler);
	void attach_TX_500Hz_event(eventHandlerFunction _eventHandler);
	void attach_TX_1000Hz_event(eventHandlerFunction _eventHandler);
	void attach_TX_2000Hz_event(eventHandlerFunction _eventHandler);
	void attach_TX_4000Hz_event(eventHandlerFunction _eventHandler);
	void attach_TX_8000Hz_event(eventHandlerFunction _eventHandler);
	
	//
	void fireEvents();
	boolean updated;
    
	//update flags
	boolean upd_RX_mode;
	boolean upd_RX_63Hz;
	boolean upd_RX_125Hz;
	boolean upd_RX_250Hz;
	boolean upd_RX_500Hz;
	boolean upd_RX_1000Hz;
	boolean upd_RX_2000Hz;
	boolean upd_RX_4000Hz;
	boolean upd_RX_8000Hz;
	boolean upd_TX_mode;
	boolean upd_TX_63Hz;
	boolean upd_TX_125Hz;
	boolean upd_TX_250Hz;
	boolean upd_TX_500Hz;
	boolean upd_TX_1000Hz;
	boolean upd_TX_2000Hz;
	boolean upd_TX_4000Hz;
	boolean upd_TX_8000Hz;
	
	//event handlers
	eventHandlerFunction do_RX_mode_event=NULL;
	eventHandlerFunction do_RX_63Hz_event=NULL;
	eventHandlerFunction do_RX_125Hz_event=NULL;
	eventHandlerFunction do_RX_250Hz_event=NULL;
	eventHandlerFunction do_RX_500Hz_event=NULL;
	eventHandlerFunction do_RX_1000Hz_event=NULL;
	eventHandlerFunction do_RX_2000Hz_event=NULL;
	eventHandlerFunction do_RX_4000Hz_event=NULL;
	eventHandlerFunction do_RX_8000Hz_event=NULL;
	eventHandlerFunction do_TX_mode_event=NULL;
	eventHandlerFunction do_TX_63Hz_event=NULL;
	eventHandlerFunction do_TX_125Hz_event=NULL;
	eventHandlerFunction do_TX_250Hz_event=NULL;
	eventHandlerFunction do_TX_500Hz_event=NULL;
	eventHandlerFunction do_TX_1000Hz_event=NULL;
	eventHandlerFunction do_TX_2000Hz_event=NULL;
	eventHandlerFunction do_TX_4000Hz_event=NULL;
	eventHandlerFunction do_TX_8000Hz_event=NULL;
	
	
  private:
    //properties
	
    //methods	
	void setRxValue(String msg);
	void setTxValue(String msg);
};
	
#endif