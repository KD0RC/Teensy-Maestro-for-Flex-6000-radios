/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef Interlock_h
#define Interlock_h
#include "Arduino.h"

extern "C" {
	typedef void (*eventHandlerFunction)(void);
}

class Interlock
{
  public:
    //properties
	int timeout; //=0 
	int acc_txreq_enable; //=0 
	int rca_txreq_enable; //=0 
	int acc_txreq_polarity; //=0
	int rca_txreq_polarity; //=0
	int tx1_enabled; //=1 
	int tx1_delay; //=0 
	int tx2_enabled; //=1 
	int tx2_delay; //=0 
	int tx3_enabled; //=1 
	int tx3_delay; //=0 
	int acc_tx_enabled; //=1 
	int acc_tx_delay; //=0 
	int tx_delay; //=0
	String state; //TRANSMITTING
	String reason; //
	String source;  //SW

    //methods
    Interlock();
	void updateStatus(String msg);
	void updateObject(int objectId,int value);  //Update specific interlock object	
	
	//setter methods
	void set_timeout(int newval); //=0 
	void set_acc_txreq_enable(int newval); 
	void set_rca_txreq_enable(int newval); 
	void set_acc_txreq_polarity(int newval); 
	void set_rca_txreq_polarity(int newval); 
	void set_tx1_enabled(int newval); 
	void set_tx1_delay(int newval);  
	void set_tx2_enabled(int newval); 
	void set_tx2_delay(int newval);  
	void set_tx3_enabled(int newval); 
	void set_tx3_delay(int newval); 
	void set_acc_tx_enabled(int newval); 
	void set_acc_tx_delay(int newval);  
	void set_tx_delay(int newval); 
	void set_state(String newval); 
	void set_reason(String newval); 
	void set_source(String newval); 
	
	//event handler accessor methods
	void attach_timeout_event(eventHandlerFunction _eventHandler); //=0 
	void attach_acc_txreq_enable_event(eventHandlerFunction _eventHandler); 
	void attach_rca_txreq_enable_event(eventHandlerFunction _eventHandler); 
	void attach_acc_txreq_polarity_event(eventHandlerFunction _eventHandler); 
	void attach_rca_txreq_polarity_event(eventHandlerFunction _eventHandler); 
	void attach_tx1_enabled_event(eventHandlerFunction _eventHandler); 
	void attach_tx1_delay_event(eventHandlerFunction _eventHandler);  
	void attach_tx2_enabled_event(eventHandlerFunction _eventHandler); 
	void attach_tx2_delay_event(eventHandlerFunction _eventHandler);  
	void attach_tx3_enabled_event(eventHandlerFunction _eventHandler); 
	void attach_tx3_delay_event(eventHandlerFunction _eventHandler); 
	void attach_acc_tx_enabled_event(eventHandlerFunction _eventHandler); 
	void attach_acc_tx_delay_event(eventHandlerFunction _eventHandler);  
	void attach_tx_delay_event(eventHandlerFunction _eventHandler); 
	void attach_state_event(eventHandlerFunction _eventHandler); 
	void attach_reason_event(eventHandlerFunction _eventHandler); 
	void attach_source_event(eventHandlerFunction _eventHandler);
	
	//
	void fireEvents();
	boolean updated;
	boolean isInTransmit;
	
	//Update Flags
	boolean upd_timeout;
	boolean upd_acc_txreq_enable; 
	boolean upd_rca_txreq_enable; 
	boolean upd_acc_txreq_polarity; 
	boolean upd_rca_txreq_polarity; 
	boolean upd_tx1_enabled; 
	boolean upd_tx1_delay;  
	boolean upd_tx2_enabled; 
	boolean upd_tx2_delay;  
	boolean upd_tx3_enabled; 
	boolean upd_tx3_delay; 
	boolean upd_acc_tx_enabled; 
	boolean upd_acc_tx_delay;  
	boolean upd_tx_delay; 
	boolean upd_state; 
	boolean upd_reason; 
	boolean upd_source; 
	
	//event handlers
	eventHandlerFunction do_timeout_event=NULL; //=0 
	eventHandlerFunction do_acc_txreq_enable_event=NULL; 
	eventHandlerFunction do_rca_txreq_enable_event=NULL; 
	eventHandlerFunction do_acc_txreq_polarity_event=NULL; 
	eventHandlerFunction do_rca_txreq_polarity_event=NULL; 
	eventHandlerFunction do_tx1_enabled_event=NULL; 
	eventHandlerFunction do_tx1_delay_event=NULL;  
	eventHandlerFunction do_tx2_enabled_event=NULL; 
	eventHandlerFunction do_tx2_delay_event=NULL;  
	eventHandlerFunction do_tx3_enabled_event=NULL; 
	eventHandlerFunction do_tx3_delay_event=NULL; 
	eventHandlerFunction do_acc_tx_enabled_event=NULL; 
	eventHandlerFunction do_acc_tx_delay_event=NULL;  
	eventHandlerFunction do_tx_delay_event=NULL; 
	eventHandlerFunction do_state_event=NULL; 
	eventHandlerFunction do_reason_event=NULL; 
	eventHandlerFunction do_source_event=NULL; 

  private:
    //properties
	
    //methods	
	void setValue(String msg);
};
	
#endif