/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "Radio.h"
Radio::Radio() {
	
	binaural_rx=0;

    upd_slices=true;  
	upd_panadapters=true; 
	upd_lineout_gain=true;  
	upd_lineout_mute=true;  
	upd_headphone_gain=true;  
	upd_headphone_mute=true;  
	upd_remote_on_enabled=true; 
	upd_pll_done=true; 
	upd_freq_error_ppb=true; 
	upd_cal_freq=true; 
	upd_tnf_enabled=true; 
	upd_snap_tune_enabled=true;
	upd_nickname=true; 
	upd_callsign=true; 
	upd_binaural_rx=true;
	
	updated=false;
}

void Radio::updateStatus(String msg) {
    
	//Serial.println(F("Radio::updateStatus"));
	
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
	Serial.println(slices);
	Serial.println(panadapters);
	Serial.println(lineout_gain);
	Serial.println(lineout_mute);
	Serial.println(headphone_gain);
	Serial.println(headphone_mute);
	Serial.println(remote_on_enabled);
	Serial.println(pll_done);
	Serial.println(freq_error_ppb);
	Serial.println(cal_freq);
	Serial.println(tnf_enabled);
	Serial.println(snap_tune_enabled); 
	*/

}

void Radio::setValue(String msg){
    int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.println(var);
		if (var.equals(F("slices"))) {
			//slices=msg.substring(i+1).toInt();
			set_slices(msg.substring(i+1).toInt());
			return;
		}
		if (var.equals(F("panadapters"))) { 
			//panadapters=msg.substring(i+1).toInt();
			set_panadapters(msg.substring(i+1).toInt());
			return; 
		}
		if (var.equals(F("lineout_gain"))) { 
			//lineout_gain=msg.substring(i+1).toInt();
			set_lineout_gain(msg.substring(i+1).toInt());
			return; 
		}
		if (var.equals(F("lineout_mute"))) { 
			//lineout_mute=msg.substring(i+1).toInt();
			Serial.print("lineout_mute="); Serial.println(msg.substring(i+1));
  	        set_lineout_mute(msg.substring(i+1).toInt());
			return; 
		}
		if (var.equals(F("headphone_gain"))) { 
			//headphone_gain=msg.substring(i+1).toInt();
			set_headphone_gain(msg.substring(i+1).toInt());			
			return; 
		}
		if (var.equals(F("headphone_mute"))) { 
			//headphone_mute=msg.substring(i+1).toInt();
            set_headphone_mute(msg.substring(i+1).toInt());			
			return; 
		}
		
		if (var.equals(F("remote_on_enabled"))) { 
			//remote_on_enabled=msg.substring(i+1).toInt(); 
			set_remote_on_enabled(msg.substring(i+1).toInt());
			return; 
		}
		
		if (var.equals(F("pll_done"))) { 
			//pll_done=msg.substring(i+1).toInt();
			set_pll_done(msg.substring(i+1).toInt());
			return; 
		}
		
		if (var.equals(F("freq_error_ppb"))) { 
			//freq_error_ppb=msg.substring(i+1).toInt();
			set_freq_error_ppb(msg.substring(i+1).toInt());
			return; 
		}
		
		if (var.equals(F("cal_freq"))) { 
			//cal_freq=msg.substring(i+1).toFloat()*1000000;
			set_cal_freq(msg.substring(i+1).toFloat()*1000000);
			return; 
		}
		
		if (var.equals(F("tnf_enabled"))) { 
			//tnf_enabled=msg.substring(i+1).toInt();
			set_tnf_enabled(msg.substring(i+1).toInt());
			return; 
		}
		
		if (var.equals(F("snap_tune_enabled"))) { 
			//snap_tune_enabled=msg.substring(i+1).toInt();
			set_snap_tune_enabled(msg.substring(i+1).toInt());			
			return; 
		}

		if (var.equals(F("nickname"))) { 
			set_nickname(msg.substring(i+1));			
			return; 
		}
		
		if (var.equals(F("callsign"))) { 
			set_callsign(msg.substring(i+1));			
			return; 
		}
		
		if (var.equals(F("binaural_rx"))) { 
			//snap_tune_enabled=msg.substring(i+1).toInt();
			set_binaural_rx(msg.substring(i+1).toInt());			
			return; 
		}
		
	}
}

void Radio::set_slices(int newval) {
	if (newval!=slices) {
		slices=newval;
		upd_slices=true;
	}
}

void Radio::set_panadapters(int newval) {
	if (newval!=panadapters) {
		panadapters=newval;
		upd_panadapters=true;
	}
}

void Radio::set_lineout_gain(int newval) {
	if (newval!=lineout_gain) {
		lineout_gain=newval;
		upd_lineout_gain=true;
	}
}
 
void Radio::set_lineout_mute(int newval) {
	if (newval!=lineout_mute) {
		lineout_mute=newval;
		upd_lineout_mute=true;
	}
} 

void Radio::set_headphone_gain(int newval) {
	if (newval!=headphone_gain) {
		headphone_gain=newval;
		upd_headphone_gain=true;
	}
}
 
void Radio::set_headphone_mute(int newval) {
	if (newval!=headphone_mute) {
		headphone_mute=newval;
		upd_headphone_mute=true;
	}
} 

void Radio::set_remote_on_enabled(int newval) {
	if (newval!=remote_on_enabled) {
		remote_on_enabled=newval;
		upd_remote_on_enabled=true;
	}
}

void Radio::set_pll_done(int newval) {
	if (newval!=pll_done) {
		pll_done=newval;
		upd_pll_done=true;
	}
} 

void Radio::set_freq_error_ppb(int newval) {
	if (newval!=freq_error_ppb) {
		freq_error_ppb=newval;
		upd_freq_error_ppb=true;
	}
} 

void Radio::set_cal_freq(int newval) {
	if (newval!=cal_freq) {
		cal_freq=newval;
		upd_cal_freq=true;
	}
}
 
void Radio::set_tnf_enabled(int newval) {
	if (newval!=tnf_enabled) {
		tnf_enabled=newval;
		upd_tnf_enabled=true;
	}
}
 
void Radio::set_snap_tune_enabled(int newval) {
	if (newval!=snap_tune_enabled) {
		snap_tune_enabled=newval;
		upd_snap_tune_enabled=true;
	}
}

void Radio::set_nickname(String newval) {
	if (!newval.equals(nickname)) {
		nickname=newval;
		upd_nickname=true;
	}
}

void Radio::set_callsign(String newval) {
	if (!newval.equals(callsign)) {
		callsign=newval;
		upd_callsign=true;
	}
}

void Radio::set_binaural_rx(int newval) {
	if (newval!=binaural_rx) {
		binaural_rx=newval;
		upd_binaural_rx=true;
	}
}

void Radio::fireEvents() {

	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;
		
		- la proprietà updated deve diventare privata
	*/
	
	if ((upd_slices) && (do_slices_event!=NULL)) { 
		do_slices_event();
		upd_slices=false; 
	}  
	
	if ((upd_panadapters) && (do_panadapters_event!=NULL)) {
		do_panadapters_event(); 
		upd_panadapters=false; 
	}

	if ((upd_lineout_gain) && (do_lineout_gain_event!=NULL)) {
		do_lineout_gain_event(); 
		upd_lineout_gain=false; 
	}
	
	if ((upd_lineout_mute) && (do_lineout_mute_event!=NULL)) {
		do_lineout_mute_event(); 
		upd_lineout_mute=false; 
	}
	
	if ((upd_headphone_gain) && (do_headphone_gain_event!=NULL)) {
		do_headphone_gain_event(); 
		upd_headphone_gain=false; 
	}
	
	if ((upd_headphone_mute) && (do_headphone_mute_event!=NULL)) {
		do_headphone_mute_event(); 
		upd_headphone_mute=false; 
	}
	
	if ((upd_remote_on_enabled) && (do_remote_on_enabled_event!=NULL)) {
		do_remote_on_enabled_event(); 
		upd_remote_on_enabled=false; 
	}
	
	if ((upd_pll_done) && (do_pll_done_event!=NULL)) {
		do_pll_done_event(); 
		upd_pll_done=false; 
	}
	
	if ((upd_freq_error_ppb) && (do_freq_error_ppb_event!=NULL)) {
		do_freq_error_ppb_event(); 
		upd_freq_error_ppb=false; 
	}
	
	if ((upd_cal_freq) && (do_cal_freq_event!=NULL)) {
		do_cal_freq_event(); 
		upd_cal_freq=false; 
	}
	
	if ((upd_tnf_enabled) && (do_tnf_enabled_event!=NULL)) {
		do_tnf_enabled_event(); 
		upd_tnf_enabled=false; 
	}
	
	if ((upd_snap_tune_enabled) && (do_snap_tune_enabled_event!=NULL)) {
		do_snap_tune_enabled_event(); 
		upd_snap_tune_enabled=false; 
	}
	
	if ((upd_nickname) && (do_nickname_event!=NULL)) {
		do_nickname_event(); 
		upd_nickname=false; 
	}
	
	if ((upd_callsign) && (do_callsign_event!=NULL)) {
		do_callsign_event(); 
		upd_callsign=false; 
	}

	if ((upd_binaural_rx) && (do_binaural_rx_event!=NULL)) {
		do_binaural_rx_event(); 
		upd_binaural_rx=false; 
	}
	
}

void Radio::fire_disconnected_event() {
    if (do_disconnected_event!=NULL) do_disconnected_event;
}


void Radio::attach_slices_event(eventHandlerFunction _eventHandler) {
	do_slices_event=_eventHandler;
}

void Radio::attach_panadapters_event(eventHandlerFunction _eventHandler) {
	do_panadapters_event=_eventHandler;
}	

void Radio::attach_lineout_gain_event(eventHandlerFunction _eventHandler) {
	do_lineout_gain_event=_eventHandler;
}	
   	
void Radio::attach_lineout_mute_event(eventHandlerFunction _eventHandler) {
	do_lineout_mute_event=_eventHandler;
}	
     
void Radio::attach_headphone_gain_event(eventHandlerFunction _eventHandler) {
	do_headphone_gain_event=_eventHandler;
}	
 
void Radio::attach_headphone_mute_event(eventHandlerFunction _eventHandler) {
	do_headphone_mute_event=_eventHandler;
}	
  
void Radio::attach_remote_on_enabled_event(eventHandlerFunction _eventHandler) {
	do_remote_on_enabled_event=_eventHandler;
}	

void Radio::attach_pll_done_event(eventHandlerFunction _eventHandler) {
	do_pll_done_event=_eventHandler;
}	
 
void Radio::attach_freq_error_ppb_event(eventHandlerFunction _eventHandler) {
	do_freq_error_ppb_event=_eventHandler;
}	 

void Radio::attach_cal_freq_event(eventHandlerFunction _eventHandler) {
	do_cal_freq_event=_eventHandler;
}	
 
void Radio::attach_tnf_enabled_event(eventHandlerFunction _eventHandler) {
	do_tnf_enabled_event=_eventHandler;
}	 

void Radio::attach_snap_tune_enabled_event(eventHandlerFunction _eventHandler) {
	do_snap_tune_enabled_event=_eventHandler;
}	

void Radio::attach_nickname_event(eventHandlerFunction _eventHandler) {
	do_nickname_event=_eventHandler;
}

void Radio::attach_callsign_event(eventHandlerFunction _eventHandler) {
	do_callsign_event=_eventHandler;
}

void Radio::attach_binaural_rx_event(eventHandlerFunction _eventHandler) {
	do_binaural_rx_event=_eventHandler;
}

void Radio::attach_disconnected_event(eventHandlerFunction _eventHandler) {
	do_disconnected_event=_eventHandler;
}

void Radio::updateObject(int objectId,int value){
	switch(objectId) {
		case RADIO_MIXER_LINEOUT_GAIN:
		     this->lineout_gain=value;
			 break;
			 
		case RADIO_MIXER_HEADPHONE_GAIN:
		     this->headphone_gain=value;
			 break;
		default:
			 Serial.print(F("Radio::updateObject - Unhandled id:")); Serial.println(objectId);
	}

}














