/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "Eq.h"
Eq::Eq() {
	upd_RX_mode=true;
	upd_RX_63Hz=true;
	upd_RX_125Hz=true;
	upd_RX_250Hz=true;
	upd_RX_500Hz=true;
	upd_RX_1000Hz=true;
	upd_RX_2000Hz=true;
	upd_RX_4000Hz=true;
	upd_RX_8000Hz=true;
	upd_TX_mode=true;
	upd_TX_63Hz=true;
	upd_TX_125Hz=true;
	upd_TX_250Hz=true;
	upd_TX_500Hz=true;
	upd_TX_1000Hz=true;
	upd_TX_2000Hz=true;
	upd_TX_4000Hz=true;
	upd_TX_8000Hz=true;

	updated=false;
}

void Eq::updateStatus(String msg) {
    
	int t=msg.indexOf(' ',0);
	String type=msg.substring(0,t);
	//Serial.println(F("==Eq::updateStatus=="));
	//Serial.println(type);
	msg=msg.substring(t+1);
	//Serial.println(msg);
	updated=true;
	
	int oldi=0;
	int i=msg.indexOf(' ',oldi);
	
	if (type.equals(F("rxsc"))) {
		while (i>0) {
			setRxValue(msg.substring(oldi,i));
			oldi=i+1;
			i=msg.indexOf(' ',oldi+1);
		}
		//get the last element
		i=msg.indexOf('\n',oldi);
		setRxValue(msg.substring(oldi,i));
	}

	if (type.equals(F("txsc"))) {
		while (i>0) {
			setTxValue(msg.substring(oldi,i));
			oldi=i+1;
			i=msg.indexOf(' ',oldi+1);
		}
		//get the last element
		i=msg.indexOf('\n',oldi);
		setTxValue(msg.substring(oldi,i));
	}
	/*
    Serial.println(RX_mode);
	Serial.println(RX_63Hz);
	Serial.println(RX_125Hz);
	Serial.println(RX_250Hz);
	Serial.println(RX_500Hz);
	Serial.println(RX_1000Hz);
	Serial.println(RX_2000Hz);
	Serial.println(RX_4000Hz);
	Serial.println(RX_8000Hz);
	Serial.println(TX_mode);
	Serial.println(TX_63Hz);
	Serial.println(TX_125Hz);
	Serial.println(TX_250Hz);
	Serial.println(TX_500Hz);
	Serial.println(TX_1000Hz);
	Serial.println(TX_2000Hz);
	Serial.println(TX_4000Hz);
	Serial.println(TX_8000Hz);
	*/

}

void Eq::setRxValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.print(var); Serial.print(F("="));Serial.println(msg.substring(i+1));
		if (var.equals(F("mode"))) { 
			set_RX_mode(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("63Hz"))) { 
			set_RX_63Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("125Hz"))) { 
			set_RX_125Hz(msg.substring(i+1).toInt()); 
			return;  
		}

		if (var.equals(F("250Hz"))) { 
			set_RX_250Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("500Hz"))) { 
			set_RX_500Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("1000Hz"))) { 
			set_RX_1000Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("2000Hz"))) { 
			set_RX_2000Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("4000Hz"))) { 
			set_RX_4000Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("8000Hz"))) { 
			set_RX_8000Hz(msg.substring(i+1).toInt()); 
			return;  
		}		
	}	
}



void Eq::setTxValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.print(var); Serial.print(F("="));Serial.println(msg.substring(i+1));
		if (var.equals(F("mode"))) { 
		    set_TX_mode(msg.substring(i+1).toInt());  
			return; 
		}
		if (var.equals(F("63Hz"))) { 
			set_TX_63Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("125Hz"))) { 
			set_TX_125Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("250Hz"))) { 
			set_TX_250Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("500Hz"))) { 
			set_TX_500Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("1000Hz"))) { 
			set_TX_1000Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("2000Hz"))) { 
			set_TX_2000Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("4000Hz"))) { 
			set_TX_4000Hz(msg.substring(i+1).toInt()); 
			return;  
		}
		
		if (var.equals(F("8000Hz"))) { 
			set_TX_8000Hz(msg.substring(i+1).toInt()); 
			return;  
		}
	}	
}

void Eq::set_RX_mode(int newval) {
	if (newval!=RX_mode) {
		RX_mode=newval;
		upd_RX_mode=true;
	}
}

void Eq::set_RX_63Hz(int newval) {
	if (newval!=RX_63Hz) {
		RX_63Hz=newval;
		upd_RX_63Hz=true;
	}
}

void Eq::set_RX_125Hz(int newval) {
	if (newval!=RX_125Hz) {
		RX_125Hz=newval;
		upd_RX_125Hz=true;
	}
}

void Eq::set_RX_250Hz(int newval) {
	if (newval!=RX_250Hz) {
		RX_250Hz=newval;
		upd_RX_250Hz=true;
	}
}

void Eq::set_RX_500Hz(int newval) {
	if (newval!=RX_500Hz) {
		RX_500Hz=newval;
		upd_RX_500Hz=true;
	}
}

void Eq::set_RX_1000Hz(int newval) {
	if (newval!=RX_1000Hz) {
		RX_1000Hz=newval;
		upd_RX_1000Hz=true;
	}
}

void Eq::set_RX_2000Hz(int newval) {
	if (newval!=RX_2000Hz) {
		RX_2000Hz=newval;
		upd_RX_2000Hz=true;
	}
}

void Eq::set_RX_4000Hz(int newval) {
	if (newval!=RX_4000Hz) {
		RX_4000Hz=newval;
		upd_RX_4000Hz=true;
	}
}

void Eq::set_RX_8000Hz(int newval) {
	if (newval!=RX_8000Hz) {
		RX_8000Hz=newval;
		upd_RX_8000Hz=true;
	}
}

void Eq::set_TX_mode(int newval) {
	if (newval!=TX_mode) {
		TX_mode=newval;
		upd_TX_mode=true;
	}
}

void Eq::set_TX_63Hz(int newval) {
	if (newval!=TX_63Hz) {
		TX_63Hz=newval;
		upd_TX_63Hz=true;
	}
}

void Eq::set_TX_125Hz(int newval) {
	if (newval!=TX_125Hz) {
		TX_125Hz=newval;
		upd_TX_125Hz=true;
	}
}

void Eq::set_TX_250Hz(int newval) {
	if (newval!=TX_250Hz) {
		TX_250Hz=newval;
		upd_TX_250Hz=true;
	}
}

void Eq::set_TX_500Hz(int newval) {
	if (newval!=TX_500Hz) {
		TX_500Hz=newval;
		upd_TX_500Hz=true;
	}
}

void Eq::set_TX_1000Hz(int newval) {
	if (newval!=TX_1000Hz) {
		TX_1000Hz=newval;
		upd_TX_1000Hz=true;
	}
}

void Eq::set_TX_2000Hz(int newval) {
	if (newval!=TX_2000Hz) {
		TX_2000Hz=newval;
		upd_TX_2000Hz=true;
	}
}

void Eq::set_TX_4000Hz(int newval) {
	if (newval!=TX_4000Hz) {
		TX_4000Hz=newval;
		upd_TX_4000Hz=true;
	}
}

void Eq::set_TX_8000Hz(int newval) {
	if (newval!=TX_8000Hz) {
		TX_8000Hz=newval;
		upd_TX_8000Hz=true;
	}
}

void Eq::fireEvents() {
	
	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;
		
		- la proprietà updated deve diventare privata
	*/
	

	if ((upd_RX_mode) && (do_RX_mode_event!=NULL)) {
			do_RX_mode_event(); 
			upd_RX_mode=false; 
	}

	if ((upd_RX_63Hz) && (do_RX_63Hz_event!=NULL)) {
			do_RX_63Hz_event(); 
			upd_RX_63Hz=false; 
	}
	
	if ((upd_RX_125Hz) && (do_RX_125Hz_event!=NULL)) {
			do_RX_125Hz_event(); 
			upd_RX_125Hz=false; 
	}
	
	if ((upd_RX_250Hz) && (do_RX_250Hz_event!=NULL)) {
			do_RX_250Hz_event(); 
			upd_RX_250Hz=false; 
	}
	
	if ((upd_RX_500Hz) && (do_RX_500Hz_event!=NULL)) {
			do_RX_500Hz_event(); 
			upd_RX_500Hz=false; 
	}
	
	if ((upd_RX_1000Hz) && (do_RX_1000Hz_event!=NULL)) {
			do_RX_1000Hz_event(); 
			upd_RX_1000Hz=false; 
	}
	
	if ((upd_RX_2000Hz) && (do_RX_2000Hz_event!=NULL)) {
			do_RX_2000Hz_event(); 
			upd_RX_2000Hz=false; 
	}
	
	if ((upd_RX_4000Hz) && (do_RX_4000Hz_event!=NULL)) {
			do_RX_4000Hz_event(); 
			upd_RX_4000Hz=false; 
	}
	
	if ((upd_RX_8000Hz) && (do_RX_8000Hz_event!=NULL)) {
			do_RX_8000Hz_event(); 
			upd_RX_8000Hz=false; 
	}
	
	if ((upd_TX_mode) && (do_TX_mode_event!=NULL)) {
			do_TX_mode_event(); 
			upd_TX_mode=false; 
	}
	
	if ((upd_TX_63Hz) && (do_TX_63Hz_event!=NULL)) {
			do_TX_63Hz_event(); 
			upd_TX_63Hz=false; 
	}
	
	if ((upd_TX_125Hz) && (do_TX_125Hz_event!=NULL)) {
			do_TX_125Hz_event(); 
			upd_TX_125Hz=false; 
	}
	
	if ((upd_TX_250Hz) && (do_TX_250Hz_event!=NULL)) {
			do_TX_250Hz_event(); 
			upd_TX_250Hz=false; 
	}
	
	if ((upd_TX_500Hz) && (do_TX_500Hz_event!=NULL)) {
			do_TX_500Hz_event(); 
			upd_TX_500Hz=false; 
	}
	
	if ((upd_TX_1000Hz) && (do_TX_1000Hz_event!=NULL)) {
			do_TX_1000Hz_event(); 
			upd_TX_1000Hz=false; 
	}
	
	if ((upd_TX_2000Hz) && (do_TX_2000Hz_event!=NULL)) {
			do_TX_2000Hz_event(); 
			upd_TX_2000Hz=false; 
	}
	
	if ((upd_TX_4000Hz) && (do_TX_4000Hz_event!=NULL)) {
			do_TX_4000Hz_event(); 
			upd_TX_4000Hz=false; 
	}
	
	if ((upd_TX_8000Hz) && (do_TX_8000Hz_event!=NULL)) {
			do_TX_8000Hz_event(); 
			upd_TX_8000Hz=false; 
	}
	
}

void Eq::attach_RX_mode_event(eventHandlerFunction _eventHandler) {
	do_RX_mode_event=_eventHandler;
}

void Eq::attach_RX_63Hz_event(eventHandlerFunction _eventHandler) {
	do_RX_63Hz_event=_eventHandler;
}	

void Eq::attach_RX_125Hz_event(eventHandlerFunction _eventHandler) {
	do_RX_125Hz_event=_eventHandler;
}	

void Eq::attach_RX_250Hz_event(eventHandlerFunction _eventHandler) {
	do_RX_250Hz_event=_eventHandler;
}	

void Eq::attach_RX_500Hz_event(eventHandlerFunction _eventHandler) {
	do_RX_500Hz_event=_eventHandler;
}	

void Eq::attach_RX_1000Hz_event(eventHandlerFunction _eventHandler) {
	do_RX_1000Hz_event=_eventHandler;
}	

void Eq::attach_RX_2000Hz_event(eventHandlerFunction _eventHandler) {
	do_RX_2000Hz_event=_eventHandler;
}	

void Eq::attach_RX_4000Hz_event(eventHandlerFunction _eventHandler) {
	do_RX_4000Hz_event=_eventHandler;
}	

void Eq::attach_RX_8000Hz_event(eventHandlerFunction _eventHandler) {
	do_RX_8000Hz_event=_eventHandler;
}	

void Eq::attach_TX_mode_event(eventHandlerFunction _eventHandler) {
	do_TX_mode_event=_eventHandler;
}	

void Eq::attach_TX_63Hz_event(eventHandlerFunction _eventHandler) {
	do_TX_63Hz_event=_eventHandler;
}	

void Eq::attach_TX_125Hz_event(eventHandlerFunction _eventHandler) {
	do_TX_125Hz_event=_eventHandler;
}	

void Eq::attach_TX_250Hz_event(eventHandlerFunction _eventHandler) {
	do_TX_250Hz_event=_eventHandler;
}	

void Eq::attach_TX_500Hz_event(eventHandlerFunction _eventHandler) {
	do_TX_500Hz_event=_eventHandler;
}	

void Eq::attach_TX_1000Hz_event(eventHandlerFunction _eventHandler) {
	do_TX_1000Hz_event=_eventHandler;
}	

void Eq::attach_TX_2000Hz_event(eventHandlerFunction _eventHandler) {
	do_TX_2000Hz_event=_eventHandler;
}	

void Eq::attach_TX_4000Hz_event(eventHandlerFunction _eventHandler) {
	do_TX_4000Hz_event=_eventHandler;
}	

void Eq::attach_TX_8000Hz_event(eventHandlerFunction _eventHandler) {
	do_TX_8000Hz_event=_eventHandler;
}	

void Eq::updateObject(int objectId,int value){
	switch(objectId) {
	    
		case  EQ_RX_MODE:
			  RX_mode=value;
			  break;
		case  EQ_RX_63HZ: 
			  RX_63Hz=value;
			  break;
		case  EQ_RX_125HZ:
              RX_125Hz=value;
			  break;
		case  EQ_RX_250HZ:
			  RX_250Hz=value;
			  break;
		case  EQ_RX_500HZ:
			  RX_500Hz=value;
			  break;
		case  EQ_RX_1000HZ:
			  RX_1000Hz=value;
			  break;
		case  EQ_RX_2000HZ:
			  RX_2000Hz=value;
			  break;
		case  EQ_RX_4000HZ:
			  RX_4000Hz=value;
			  break;
		case  EQ_RX_8000HZ:
			  RX_8000Hz=value;
			  break;
		case  EQ_TX_MODE:
		      //Serial.print(F("fRig.eq.TX_mode(before) UPDATE OBJECT=")); Serial.println(TX_mode);
			  //Serial.print(F("value=")); Serial.println(value);
			  TX_mode=value;
			  //Serial.print(F("fRig.eq.TX_mode(after) UPDATE OBJECT=")); Serial.println(TX_mode);
			  break;
		case  EQ_TX_63HZ:
			  TX_63Hz=value;	
			  break;
		case  EQ_TX_125HZ:
              TX_125Hz=value;
			  break;
		case  EQ_TX_250HZ:
			  TX_250Hz=value;
			  break;
		case  EQ_TX_500HZ:
			  TX_500Hz=value;
			  break;
		case  EQ_TX_1000HZ:
			  TX_1000Hz=value;
			  break;
		case  EQ_TX_2000HZ:
			  TX_2000Hz=value;
			  break;
		case  EQ_TX_4000HZ:
			  TX_4000Hz=value;
			  break;
		case  EQ_TX_8000HZ:
			  TX_8000Hz=value;
			  break;
		default:
			  Serial.print(F("Eq::updateObject - Unhandled id:")); Serial.println(objectId);
	}
}			  