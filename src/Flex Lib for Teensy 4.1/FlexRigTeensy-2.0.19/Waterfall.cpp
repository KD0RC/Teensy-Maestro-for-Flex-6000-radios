/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "Waterfall.h"

Waterfall::Waterfall() {
	upd_waterfall=true; 
	upd_x_pixels=true;
	upd_line_duration=true; 
	upd_rfgain=true; 
	upd_wide=true;
	upd_loopa=true; 
	upd_loopb=true; 
	upd_band=true; 
	upd_daxiq=true;
	upd_daxiq_rate=true; 
	upd_capacity=true; 
	upd_available=true; 
	upd_panadapter=true;
	upd_color_gain=true;
	upd_auto_black=true;
	upd_black_level=true; 
	upd_gradient_index=true; 
	upd_xvtr=true; 
	upd_center=true;
	upd_bandwidth=true;  
	upd_rxant=true;
	
	updated=false;
}


void Waterfall::updateStatus(String msg) {
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
	Serial.println(waterfall);
	Serial.println(x_pixels);
	Serial.println(center);
	Serial.println(bandwidth);
	Serial.println(line_duration);
	Serial.println(rfgain);
	Serial.println(rxant);
	Serial.println(wide); 
	Serial.println(loopa);
	Serial.println(loopb);
	Serial.println(band);
	Serial.println(daxiq);
	Serial.println(daxiq_rate);
	Serial.println(capacity);
	Serial.println(available);
	Serial.println(panadapter);
	Serial.println(color_gain);
	Serial.println(auto_black);
	Serial.println(black_level);
	Serial.println(gradient_index);
	Serial.println(xvtr);
	*/
}

void Waterfall::setValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.println(var);
		
		if (var.equals(F("waterfall"))) {
			set_waterfall(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("x_pixels"))) {
			set_x_pixels(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("line_duration"))) {
			set_line_duration(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("rfgain"))) {
			set_rfgain(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("wide"))) {
			set_wide(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("loopa"))) {
			set_loopa(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("loopb"))) {
			set_loopb(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("band"))) {
			set_band(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("daxiq"))) {
			set_daxiq(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("daxiq_rate"))) {
			set_daxiq_rate(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("capacity"))) {
			set_capacity(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("available"))) {
			set_available(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("panadapter"))) {
			set_panadapter(msg.substring(i+1).toInt()); 
			return;  
		}  
		if (var.equals(F("color_gain"))) {
			set_color_gain(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("auto_black"))) {
			set_auto_black(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("black_level"))) {
			set_black_level(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("gradient_index"))) {
			set_gradient_index(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("xvtr"))) {
			set_xvtr(msg.substring(i+1).toInt()); 
			return;  
		}
		if (var.equals(F("center"))) {
			set_center(msg.substring(i+1).toFloat()); 
			return;  
		}
		if (var.equals(F("bandwidth"))) {
			set_bandwidth(msg.substring(i+1).toFloat()); 
			return;  
		}
		if (var.equals(F("rxant"))) {
			set_rxant(msg.substring(i+1)); 
			return;  
		}
		
	}
}

void Waterfall::set_waterfall(int newval) {
	if (newval!=waterfall) {
		waterfall=newval;
		upd_waterfall=true;
	}
}

void Waterfall::set_x_pixels(int newval) {
	if (newval!=x_pixels) {
		x_pixels=newval;
		upd_x_pixels=true;
	}
}

void Waterfall::set_center(float newval) {
	if (newval!=center) {
		center=newval;
		upd_center=true;
	}
}

void Waterfall::set_bandwidth(float newval) {
	if (newval!=bandwidth) {
		bandwidth=newval;
		upd_bandwidth=true;
	}
}

void Waterfall::set_line_duration(int newval) {
	if (newval!=line_duration) {
		line_duration=newval;
		upd_line_duration=true;
	}
}

void Waterfall::set_rfgain(int newval) {
	if (newval!=rfgain) {
		rfgain=newval;
		upd_rfgain=true;
	}
}

void Waterfall::set_rxant(String newval) {
	if (!newval.equals(rxant)) {
		rxant=newval;
		upd_rxant=true;
	}
}

void Waterfall::set_wide(int newval) {
	if (newval!=wide) {
		wide=newval;
		upd_wide=true;
	}
}

void Waterfall::set_loopa(int newval) {
	if (newval!=loopa) {
		loopa=newval;
		upd_loopa=true;
	}
}

void Waterfall::set_loopb(int newval) {
	if (newval!=loopb) {
		loopb=newval;
		upd_loopb=true;
	}
}

void Waterfall::set_band(int newval) {
	if (newval!=band) {
		band=newval;
		upd_band=true;
	}
}

void Waterfall::set_daxiq(int newval) {
	if (newval!=daxiq) {
		daxiq=newval;
		upd_daxiq=true;
	}
}

void Waterfall::set_daxiq_rate(int newval) {
	if (newval!=daxiq_rate) {
		daxiq_rate=newval;
		upd_daxiq_rate=true;
	}
}

void Waterfall::set_capacity(int newval) {
	if (newval!=capacity) {
		capacity=newval;
		upd_capacity=true;
	}
}

void Waterfall::set_available(int newval) {
	if (newval!=available) {
		available=newval;
		upd_available=true;
	}
}

void Waterfall::set_panadapter(int newval) {
	if (newval!=panadapter) {
		panadapter=newval;
		upd_panadapter=true;
	}
}

void Waterfall::set_color_gain(int newval) {
	if (newval!=color_gain) {
		color_gain=newval;
		upd_color_gain=true;
	}
}

void Waterfall::set_auto_black(int newval) {
	if (newval!=auto_black) {
		auto_black=newval;
		upd_auto_black=true;
	}
}

void Waterfall::set_black_level(int newval) {
	if (newval!=black_level) {
		black_level=newval;
		upd_black_level=true;
	}
}

void Waterfall::set_gradient_index(int newval) {
	if (newval!=gradient_index) {
		gradient_index=newval;
		upd_gradient_index=true;
	}
}

void Waterfall::set_xvtr(int newval) {
	if (newval!=xvtr) {
		xvtr=newval;
		upd_xvtr=true;
	}
}

void Waterfall::fireEvents() {

	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;
		
		- la proprietà updated deve diventare privata
	*/
	
	if ((upd_waterfall) && (do_waterfall_event!=NULL)) {
			do_waterfall_event(waterfall); 
			upd_waterfall=false; 
	}

	if ((upd_x_pixels) && (do_x_pixels_event!=NULL)) {
			do_x_pixels_event(waterfall); 
			upd_x_pixels=false; 
	}
	
	if ((upd_center) && (do_center_event!=NULL)) {
			do_center_event(waterfall); 
			upd_center=false; 
	}
	
	if ((upd_bandwidth) && (do_bandwidth_event!=NULL)) {
			do_bandwidth_event(waterfall); 
			upd_bandwidth=false; 
	}
	
	if ((upd_line_duration) && (do_line_duration_event!=NULL)) {
			do_line_duration_event(waterfall); 
			upd_line_duration=false; 
	}
	
	if ((upd_rfgain) && (do_rfgain_event!=NULL)) {
			do_rfgain_event(waterfall); 
			upd_rfgain=false; 
	}
	
	if ((upd_rxant) && (do_rxant_event!=NULL)) {
			do_rxant_event(waterfall); 
			upd_rxant=false; 
	}
	
	if ((upd_wide) && (do_wide_event!=NULL)) {
			do_wide_event(waterfall); 
			upd_wide=false; 
	}
	
	if ((upd_loopa) && (do_loopa_event!=NULL)) {
			do_loopa_event(waterfall); 
			upd_loopa=false; 
	}
	
	if ((upd_loopb) && (do_loopb_event!=NULL)) {
			do_loopb_event(waterfall); 
			upd_loopb=false; 
	}
	
	if ((upd_band) && (do_band_event!=NULL)) {
			do_band_event(waterfall); 
			upd_band=false; 
	}
	
	if ((upd_daxiq) && (do_daxiq_event!=NULL)) {
			do_daxiq_event(waterfall); 
			upd_daxiq=false; 
	}
	
	if ((upd_daxiq_rate) && (do_daxiq_rate_event!=NULL)) {
			do_daxiq_rate_event(waterfall); 
			upd_daxiq_rate=false; 
	}
	
	if ((upd_capacity) && (do_capacity_event!=NULL)) {
			do_capacity_event(waterfall); 
			upd_capacity=false; 
	}
	
	if ((upd_available) && (do_available_event!=NULL)) {
			do_available_event(waterfall); 
			upd_available=false; 
	}
	
	if ((upd_panadapter) && (do_panadapter_event!=NULL)) {
			do_panadapter_event(waterfall); 
			upd_panadapter=false; 
	}
	
	if ((upd_color_gain) && (do_color_gain_event!=NULL)) {
			do_color_gain_event(waterfall); 
			upd_color_gain=false; 
	}
	
	if ((upd_auto_black) && (do_auto_black_event!=NULL)) {
			do_auto_black_event(waterfall); 
			upd_auto_black=false; 
	}
	
	if ((upd_black_level) && (do_black_level_event!=NULL)) {
			do_black_level_event(waterfall); 
			upd_black_level=false; 
	}
	
	if ((upd_gradient_index) && (do_gradient_index_event!=NULL)) {
			do_gradient_index_event(waterfall); 
			upd_gradient_index=false; 
	}
	
	if ((upd_xvtr) && (do_xvtr_event!=NULL)) {
			do_xvtr_event(waterfall); 
			upd_xvtr=false; 
	}
	
	
}

void Waterfall::attach_waterfall_event(eventHandlerArrFunction _eventHandler) {
	do_waterfall_event=_eventHandler;
}

void Waterfall::attach_x_pixels_event(eventHandlerArrFunction _eventHandler) {
	do_x_pixels_event=_eventHandler;
}

void Waterfall::attach_center_event(eventHandlerArrFunction _eventHandler) {
	do_center_event=_eventHandler;
}

void Waterfall::attach_bandwidth_event(eventHandlerArrFunction _eventHandler) {
	do_bandwidth_event=_eventHandler;
}

void Waterfall::attach_line_duration_event(eventHandlerArrFunction _eventHandler) {
	do_line_duration_event=_eventHandler;
}

void Waterfall::attach_rfgain_event(eventHandlerArrFunction _eventHandler) {
	do_rfgain_event=_eventHandler;
}

void Waterfall::attach_rxant_event(eventHandlerArrFunction _eventHandler) {
	do_rxant_event=_eventHandler;
}

void Waterfall::attach_wide_event(eventHandlerArrFunction _eventHandler) {
	do_wide_event=_eventHandler;
}

void Waterfall::attach_loopa_event(eventHandlerArrFunction _eventHandler) {
	do_loopa_event=_eventHandler;
}

void Waterfall::attach_loopb_event(eventHandlerArrFunction _eventHandler) {
	do_loopb_event=_eventHandler;
}

void Waterfall::attach_band_event(eventHandlerArrFunction _eventHandler) {
	do_band_event=_eventHandler;
}

void Waterfall::attach_daxiq_event(eventHandlerArrFunction _eventHandler) {
	do_daxiq_event=_eventHandler;
}

void Waterfall::attach_daxiq_rate_event(eventHandlerArrFunction _eventHandler) {
	do_daxiq_rate_event=_eventHandler;
}

void Waterfall::attach_capacity_event(eventHandlerArrFunction _eventHandler) {
	do_capacity_event=_eventHandler;
}

void Waterfall::attach_available_event(eventHandlerArrFunction _eventHandler) {
	do_available_event=_eventHandler;
}

void Waterfall::attach_panadapter_event(eventHandlerArrFunction _eventHandler) {
	do_panadapter_event=_eventHandler;
}

void Waterfall::attach_color_gain_event(eventHandlerArrFunction _eventHandler) {
	do_color_gain_event=_eventHandler;
}

void Waterfall::attach_auto_black_event(eventHandlerArrFunction _eventHandler) {
	do_auto_black_event=_eventHandler;
}

void Waterfall::attach_black_level_event(eventHandlerArrFunction _eventHandler) {
	do_black_level_event=_eventHandler;
}

void Waterfall::attach_gradient_index_event(eventHandlerArrFunction _eventHandler) {
	do_gradient_index_event=_eventHandler;
}

void Waterfall::attach_xvtr_event(eventHandlerArrFunction _eventHandler) {
	do_xvtr_event=_eventHandler;
}


void Waterfall::updateObject(int objectId,int value){
	switch(objectId) {
 		case WATERFALL_BLACK_LEVEL:
		    black_level=value;
			break;
		case WATERFALL_GRADIENT_INDEX:
		    gradient_index=value;
			break;
		case WATERFALL_LINE_DURATION:
		    line_duration=value;
			break;
		case WATERFALL_COLOR_GAIN:
		    color_gain=value;
			break;
		default:
			 Serial.print(F("Waterfall::updateObject - Unhandled id:")); Serial.println(objectId);
	}

}