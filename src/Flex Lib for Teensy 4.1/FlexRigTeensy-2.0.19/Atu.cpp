/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "Atu.h"

Atu::Atu() {
	
	upd_atu_enabled=true; 
	upd_memories_enabled=true;  
	upd_using_mem=true; 
	upd_status=true; 
	upd_int_status=true;
	
	updated=false;
	
}


void Atu::updateStatus(String msg) {

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
	Serial.println(atu_enabled);
	Serial.println(memories_enabled);
	Serial.println(using_mem); 
	Serial.println(status);
	*/
	
}

void Atu::setValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.println(var);
		if (var.equals(F("atu_enabled"))) { 
			set_atu_enabled(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("memories_enabled"))) { 
			set_memories_enabled(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("using_mem"))) { 
			set_using_mem(msg.substring(i+1).toInt()); 
			return; 
		} 		
		if (var.equals(F("status"))) { 
			set_status(msg.substring(i+1)); 
			return; 
		}
	}
}

void Atu::set_atu_enabled(int newval) {
	if (newval!=atu_enabled) {
		atu_enabled=newval;
		upd_atu_enabled=true;
	}
}

void Atu::set_memories_enabled(int newval) {
	if (newval!=memories_enabled) {
		memories_enabled=newval;
		upd_memories_enabled=true;
	}
}

void Atu::set_using_mem(int newval) {
	if (newval!=using_mem) {
		using_mem=newval;
		upd_using_mem=true;
	}
}

void Atu::set_status(String newval) {
	if (!newval.equals(status)) {
		//status=newval;
		
		if (newval.equals(F("TUNE_MANUAL_BYPASS"))) {
			int_status=0;
			upd_int_status=true;
			status=" Bypass  ";
		} else if (newval.equals(F("TUNE_IN_PROGRESS"))) {
			int_status=1;
			upd_int_status=true;
			status="Progress";
		} else if (newval.equals(F("TUNE_SUCCESSFUL"))) {
			int_status=2;
			upd_int_status=true;
			status=" Success ";
		}
		
		upd_status=true;		
	}
}


void Atu::fireEvents() {

	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;
		
		- la proprietà updated deve diventare privata
	*/

	if ((upd_atu_enabled) && (do_atu_enabled_event!=NULL)) {
			do_atu_enabled_event(); 
			upd_atu_enabled=false; 
	}
	if ((upd_memories_enabled) && (do_memories_enabled_event!=NULL)) {
			do_memories_enabled_event(); 
			upd_memories_enabled=false; 
	}
	if ((upd_using_mem) && (do_using_mem_event!=NULL)) {
			do_using_mem_event(); 
			upd_using_mem=false; 
	}
	if ((upd_status) && (do_status_event!=NULL)) {
			do_status_event(); 
			upd_status=false; 
	}
	if ((upd_int_status) && (do_int_status_event!=NULL)) {
			do_int_status_event(); 
			upd_int_status=false; 
	}
}


void Atu::attach_atu_enabled_event(eventHandlerFunction _eventHandler) {
	do_atu_enabled_event=_eventHandler;
}

void Atu::attach_memories_enabled_event(eventHandlerFunction _eventHandler) {
	do_memories_enabled_event=_eventHandler;
}

void Atu::attach_using_mem_event(eventHandlerFunction _eventHandler) {
	do_using_mem_event=_eventHandler;
}

void Atu::attach_status_event(eventHandlerFunction _eventHandler) {
	do_status_event=_eventHandler;
}

void Atu::attach_int_status_event(eventHandlerFunction _eventHandler) {
	do_int_status_event=_eventHandler;
}

void Atu::updateObject(int objectId,int value){
	switch(objectId) {
	//	case RADIO_MIXER_LINEOUT_GAIN:
	//		 break;
		default:
			 Serial.print(F("Atu::updateObject - Unhandled id:")); Serial.println(objectId);
	}

}
