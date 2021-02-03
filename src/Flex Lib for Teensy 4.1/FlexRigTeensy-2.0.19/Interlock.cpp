/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "Interlock.h"

Interlock::Interlock() {
	
    upd_timeout=true;
    upd_acc_txreq_enable=true; 
    upd_rca_txreq_enable=true; 
    upd_acc_txreq_polarity=true; 
    upd_rca_txreq_polarity=true; 
    upd_tx1_enabled=true; 
    upd_tx1_delay=true;  
    upd_tx2_enabled=true; 
    upd_tx2_delay=true;  
    upd_tx3_enabled=true; 
    upd_tx3_delay=true; 
    upd_acc_tx_enabled=true; 
    upd_acc_tx_delay=true;  
    upd_tx_delay=true; 
    upd_state=true; 
    upd_reason=true; 
    upd_source=true; 	
	
	isInTransmit=false;
	updated=false;
	
}


void Interlock::updateStatus(String msg) {

	//Serial.println(msg);
	updated=true;
	int oldi=0;
	int i=msg.indexOf(' ',oldi);
	while (i>0) {
		setValue(msg.substring(oldi,i));
		oldi=i+1;
		i=msg.indexOf(' ',oldi+1);
	}	
	//get the last element
	i=msg.indexOf('\n',oldi);
	setValue(msg.substring(oldi,i));
	/*
	Serial.println(timeout);
	Serial.println(acc_txreq_enable);
	Serial.println(rca_txreq_enable); 
	Serial.println(acc_txreq_polarity);
	Serial.println(rca_txreq_polarity);
	Serial.println(tx1_enabled);
	Serial.println(tx1_delay);
	Serial.println(tx2_enabled);
	Serial.println(tx2_delay); 
	Serial.println(tx3_enabled);
	Serial.println(tx3_delay);
	Serial.println(acc_tx_enabled);
	Serial.println(acc_tx_delay);
	Serial.println(tx_delay);
	Serial.println(state);
	Serial.println(reason); 
	Serial.println(source); */
	
}

void Interlock::setValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.println(var);
		
		if (var.equals(F("timeout"))) { 
			set_timeout(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("acc_txreq_enable"))) { 
			set_acc_txreq_enable(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("rca_txreq_enable"))) { 
			set_rca_txreq_enable(msg.substring(i+1).toInt()); 
			return; 
		} 
		if (var.equals(F("acc_txreq_polarity"))) { 
			set_acc_txreq_polarity(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("rca_txreq_polarity"))) { 
			set_rca_txreq_polarity(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("tx1_enabled"))) { 
			set_tx1_enabled(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("tx1_delay"))) { 
			set_tx1_delay(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("tx2_enabled"))) { 
			set_tx2_enabled(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("tx2_delay"))) { 
			set_tx2_delay(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("tx3_enabled"))) { 
			set_tx3_enabled(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("tx3_delay"))) { 
			set_tx3_delay(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("acc_tx_enabled"))) { 
			set_acc_tx_enabled(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("acc_tx_delay"))) { 
			set_acc_tx_delay(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("tx_delay"))) { 
			set_tx_delay(msg.substring(i+1).toInt()); 
			return; 
		}		
		
		if (var.equals(F("state"))) { 
			set_state(msg.substring(i+1)); 
			if (state.equals(F("TRANSMITTING"))) 
				isInTransmit=true;
			else
				isInTransmit=false;
			return; 
		}
		if (var.equals(F("reason"))) { 
			set_reason(msg.substring(i+1)); 
			return; 
		}
		if (var.equals(F("source"))) { 
			set_source(msg.substring(i+1)); 
			return; 
		}
		
	}
}

void Interlock::set_timeout(int newval) {
	if (newval!=timeout) {
		timeout=newval;
		upd_timeout=true;
	}
}

void Interlock::set_acc_txreq_enable(int newval) {
	if (newval!=acc_txreq_enable) {
		acc_txreq_enable=newval;
		upd_acc_txreq_enable=true;
	}
}

void Interlock::set_rca_txreq_enable(int newval) {
	if (newval!=rca_txreq_enable) {
		rca_txreq_enable=newval;
		upd_rca_txreq_enable=true;
	}
}

void Interlock::set_acc_txreq_polarity(int newval) {
	if (newval!=acc_txreq_polarity) {
		acc_txreq_polarity=newval;
		upd_acc_txreq_polarity=true;
	}
}

void Interlock::set_rca_txreq_polarity(int newval) {
	if (newval!=rca_txreq_polarity) {
		rca_txreq_polarity=newval;
		upd_rca_txreq_polarity=true;
	}
}

void Interlock::set_tx1_enabled(int newval) {
	if (newval!=tx1_enabled) {
		tx1_enabled=newval;
		upd_tx1_enabled=true;
	}
}

void Interlock::set_tx1_delay(int newval) {
	if (newval!=tx1_delay) {
		tx1_delay=newval;
		upd_tx1_delay=true;
	}
}

void Interlock::set_tx2_enabled(int newval) {
	if (newval!=tx2_enabled) {
		tx2_enabled=newval;
		upd_tx2_enabled=true;
	}
}

void Interlock::set_tx2_delay(int newval) {
	if (newval!=tx2_delay) {
		tx2_delay=newval;
		upd_tx2_delay=true;
	}
}

void Interlock::set_tx3_enabled(int newval) {
	if (newval!=tx3_enabled) {
		tx3_enabled=newval;
		upd_tx3_enabled=true;
	}
}

void Interlock::set_tx3_delay(int newval) {
	if (newval!=tx3_delay) {
		tx3_delay=newval;
		upd_tx3_delay=true;
	}
}

void Interlock::set_acc_tx_enabled(int newval) {
	if (newval!=acc_tx_enabled) {
		acc_tx_enabled=newval;
		upd_acc_tx_enabled=true;
	}
}

void Interlock::set_acc_tx_delay(int newval) {
	if (newval!=acc_tx_delay) {
		acc_tx_delay=newval;
		upd_acc_tx_delay=true;
	}
}

void Interlock::set_tx_delay(int newval) {
	if (newval!=tx_delay) {
		tx_delay=newval;
		upd_tx_delay=true;
	}
}

void Interlock::set_state(String newval) {
	if (!newval.equals(state)) {
			state=newval;
			upd_state=true;
	}
}

void Interlock::set_reason(String newval) {
	if (!newval.equals(reason)) {
			reason=newval;
			upd_reason=true;
	}
}


void Interlock::set_source(String newval) {
	if (!newval.equals(source)) {
			source=newval;
			upd_source=true;
	}
}


void Interlock::fireEvents() {

	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;
		
		- la proprietà updated deve diventare privata
	*/

	if ((upd_timeout) && (do_timeout_event!=NULL)) {
			do_timeout_event(); 
			upd_timeout=false; 
	}
		
	if ((upd_acc_txreq_enable) && (do_acc_txreq_enable_event!=NULL)) {
			do_acc_txreq_enable_event(); 
			upd_acc_txreq_enable=false; 
	}
		
	if ((upd_rca_txreq_enable) && (do_rca_txreq_enable_event!=NULL)) {
			do_rca_txreq_enable_event(); 
			upd_rca_txreq_enable=false; 
	}
		
	if ((upd_acc_txreq_polarity) && (do_acc_txreq_polarity_event!=NULL)) {
			do_acc_txreq_polarity_event(); 
			upd_acc_txreq_polarity=false; 
	}
		
	if ((upd_rca_txreq_polarity) && (do_rca_txreq_polarity_event!=NULL)) {
			do_rca_txreq_polarity_event(); 
			upd_rca_txreq_polarity=false; 
	}
		
	if ((upd_tx1_enabled) && (do_tx1_enabled_event!=NULL)) {
			do_tx1_enabled_event(); 
			upd_tx1_enabled=false; 
	}
		
	if ((upd_tx1_delay) && (do_tx1_delay_event!=NULL)) {
			do_tx1_delay_event(); 
			upd_tx1_delay=false; 
	}
		
	if ((upd_tx2_enabled) && (do_tx2_enabled_event!=NULL)) {
			do_tx2_enabled_event(); 
			upd_tx2_enabled=false; 
	}
		
	if ((upd_tx2_delay) && (do_tx2_delay_event!=NULL)) {
			do_tx2_delay_event(); 
			upd_tx2_delay=false; 
	}
		
	if ((upd_tx3_enabled) && (do_tx3_enabled_event!=NULL)) {
			do_tx3_enabled_event(); 
			upd_tx3_enabled=false; 
	}
	
	if ((upd_tx3_delay) && (do_tx3_delay_event!=NULL)) {
			do_tx3_delay_event(); 
			upd_tx3_delay=false; 
	}
		
	if ((upd_acc_tx_enabled) && (do_acc_tx_enabled_event!=NULL)) {
			do_acc_tx_enabled_event(); 
			upd_acc_tx_enabled=false; 
	}
		
	if ((upd_acc_tx_delay) && (do_acc_tx_delay_event!=NULL)) {
			do_acc_tx_delay_event(); 
			upd_acc_tx_delay=false; 
	}
		
	if ((upd_tx_delay) && (do_tx_delay_event!=NULL)) {
			do_tx_delay_event(); 
			upd_tx_delay=false; 
	}
		
	if ((upd_state) && (do_state_event!=NULL)) {
			do_state_event(); 
			upd_state=false; 
	}
		
	if ((upd_reason) && (do_reason_event!=NULL)) {
			do_reason_event(); 
			upd_reason=false; 
	}
		
	if ((upd_source) && (do_source_event!=NULL)) {
			do_source_event(); 
			upd_source=false; 
	}
		
	
	
}

void Interlock::attach_timeout_event(eventHandlerFunction _eventHandler) {
	do_timeout_event=_eventHandler;
}

void Interlock::attach_acc_txreq_enable_event(eventHandlerFunction _eventHandler) {
	do_acc_txreq_enable_event=_eventHandler;
}

void Interlock::attach_rca_txreq_enable_event(eventHandlerFunction _eventHandler) {
	do_rca_txreq_enable_event=_eventHandler;
}

void Interlock::attach_acc_txreq_polarity_event(eventHandlerFunction _eventHandler) {
	do_acc_txreq_polarity_event=_eventHandler;
}

void Interlock::attach_rca_txreq_polarity_event(eventHandlerFunction _eventHandler) {
	do_rca_txreq_polarity_event=_eventHandler;
}

void Interlock::attach_tx1_enabled_event(eventHandlerFunction _eventHandler) {
	do_tx1_enabled_event=_eventHandler;
}

void Interlock::attach_tx1_delay_event(eventHandlerFunction _eventHandler) {
	do_tx1_delay_event=_eventHandler;
}

void Interlock::attach_tx2_enabled_event(eventHandlerFunction _eventHandler) {
	do_tx2_enabled_event=_eventHandler;
}

void Interlock::attach_tx2_delay_event(eventHandlerFunction _eventHandler) {
	do_tx2_delay_event=_eventHandler;
}

void Interlock::attach_tx3_enabled_event(eventHandlerFunction _eventHandler) {
	do_tx3_enabled_event=_eventHandler;
}

void Interlock::attach_tx3_delay_event(eventHandlerFunction _eventHandler) {
	do_tx3_delay_event=_eventHandler;
}

void Interlock::attach_acc_tx_enabled_event(eventHandlerFunction _eventHandler) {
	do_acc_tx_enabled_event=_eventHandler;
}

void Interlock::attach_acc_tx_delay_event(eventHandlerFunction _eventHandler) {
	do_acc_tx_delay_event=_eventHandler;
}

void Interlock::attach_tx_delay_event(eventHandlerFunction _eventHandler) {
	do_tx_delay_event=_eventHandler;
}

void Interlock::attach_state_event(eventHandlerFunction _eventHandler) {
	do_state_event=_eventHandler;
}

void Interlock::attach_reason_event(eventHandlerFunction _eventHandler) {
	do_reason_event=_eventHandler;
}

void Interlock::attach_source_event(eventHandlerFunction _eventHandler) {
	do_source_event=_eventHandler;
}




void Interlock::updateObject(int objectId,int value){
	switch(objectId) {
	//	case RADIO_MIXER_LINEOUT_GAIN:
	//		 break;
		default:
			 Serial.print(F("Interlock::updateObject - Unhandled id:")); Serial.println(objectId);
	}

}
