/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "Panadapter.h"

Panadapter::Panadapter() {
	upd_pan=true; 
	upd_x_pixels=true; 
	upd_y_pixels=true; 
	upd_center=true; 
	upd_bandwidth=true; 
	upd_min_dbm=true; 
	upd_max_dbm=true; 
	upd_fps=true; 
	upd_average=true; 
	upd_weighted_average=true;
	upd_rfgain=true; 
	upd_wide=true; 
	upd_loopa=true; 
	upd_loopb=true;  
	upd_band=true;  
	upd_daxiq=true;  
	upd_daxiq_rate=true; 
	upd_capacity=true; 
	upd_available=true; 
	upd_waterfall=true; 
	upd_xvtr=true;
	upd_pre=true; 
	upd_ant_list=true;
	upd_rxant=true;
	upd_min_bw=true; 
	upd_max_bw=true; 
	upd_wnb_updating=true; 
	upd_wnb=true; 
	upd_wnb_level=true; 	
	updated=false;
	previousBand=-1;
}


void Panadapter::updateStatus(String msg) {
	
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
	Serial.println(pan); 
	Serial.println(x_pixels); 
	Serial.println(y_pixels);
	Serial.println(center);
	Serial.println(bandwidth);
	Serial.println(min_dbm); 
	Serial.println(max_dbm);
	Serial.println(fps);
	Serial.println(average);
	Serial.println(weighted_average);
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
	Serial.println(waterfall);
	Serial.println(min_bw);
	Serial.println(max_bw);
	Serial.println(xvtr); 
	Serial.println(pre); 
	Serial.println(ant_list);
	Serial.println(upd_wnb_updating); 
	Serial.println(upd_wnb); 
	Serial.println(upd_wnb_level); 	

	*/
}

void Panadapter::setValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.println(var);
		
		if (var.equals(F("pan"))) {
		    set_pan(msg.substring(i+3).toInt()); 
			return;
		} 
		if (var.equals(F("x_pixels"))) {
			set_x_pixels(msg.substring(i+1).toInt()); 
			return; 
		} 
		if (var.equals(F("y_pixels"))) {
			set_y_pixels(msg.substring(i+1).toInt()); 
			return; 
		} 
		if (var.equals(F("min_dbm"))) {
			set_min_dbm(msg.substring(i+1).toFloat());
			return; 
		} 
		if (var.equals(F("max_dbm"))) {
			set_max_dbm(msg.substring(i+1).toFloat()); 
			return; 
		} 
		if (var.equals(F("fps"))) {
			set_fps(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("average"))) {
			set_average(msg.substring(i+1).toInt()); 
			return; 
		} 
		if (var.equals(F("weighted_average"))) {
			set_weighted_average(msg.substring(i+1).toInt()); 
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
		if (var.equals(F("waterfall"))) {
			set_waterfall(msg.substring(i+1).toInt()); 
			return; 
		} 
		if (var.equals(F("xvtr"))) {
			set_xvtr(msg.substring(i+1).toInt()); 
			return; 
		} 
		if (var.equals(F("pre"))) {
			set_pre(msg.substring(i+1).toInt()); 
			return; 
		} 
		if (var.equals(F("min_bw"))) {
			set_min_bw(msg.substring(i+1).toFloat()); 
			return; 
		}
		if (var.equals(F("max_bw"))) {
			set_max_bw(msg.substring(i+1).toFloat()); 
			return; 
		}
		if (var.equals(F("center"))) {
			set_center(msg.substring(i+1).toFloat()*1000000); 
			return; 
		} 
		if (var.equals(F("bandwidth"))) {
			set_bandwidth(msg.substring(i+1).toFloat()*1000000); 
			return; 
		} 
		if (var.equals(F("ant_list"))) {
			set_ant_list(msg.substring(i+1)); 
			return; 
		}
		if (var.equals(F("rxant"))) {
			set_rxant(msg.substring(i+1)); 
			return; 
		} 
		if (var.equals(F("wnb_updating"))) {
			set_wnb_updating(msg.substring(i+1).toInt()); 
			return;
		}		
		if (var.equals(F("wnb"))) {
			set_wnb(msg.substring(i+1).toInt()); 
			return;
		}
		if (var.equals(F("wnb_level"))) {
			set_wnb_level(msg.substring(i+1).toInt()); 
			return;
		}

		
	}
}

void Panadapter::set_pan(int newval) {
    if (newval!=pan) {
		pan=newval;
		upd_pan=true;
	}
}

void Panadapter::set_x_pixels(int newval) {
	if (newval!=x_pixels) {
		x_pixels=newval;
		upd_x_pixels=true;
	}
}

void Panadapter::set_y_pixels(int newval) {
	if (newval!=y_pixels) {
		y_pixels=newval;
		upd_y_pixels=true;
	}
}

void Panadapter::set_min_dbm(int newval) {
	if (newval!=min_dbm) {
		min_dbm=newval;
		upd_min_dbm=true;
	}
}

void Panadapter::set_max_dbm(int newval) {
	if (newval!=max_dbm) {
		max_dbm=newval;
		upd_max_dbm=true;
	}
}

void Panadapter::set_fps(int newval) {
	if (newval!=fps) {
		fps=newval;
		upd_fps=true;
	}
}

void Panadapter::set_average(int newval) {
	if (newval!=average) {
		average=newval;
		upd_average=true;
	}
}

void Panadapter::set_weighted_average(int newval) {
	if (newval!=weighted_average) {
		weighted_average=newval;
		upd_weighted_average=true;
	}
}

void Panadapter::set_rfgain(int newval) {
	if (newval!=rfgain) {
		rfgain=newval;
		upd_rfgain=true;
	}
}

void Panadapter::set_wide(int newval) {
	if (newval!=wide) {
		wide=newval;
		upd_wide=true;
	}
}

void Panadapter::set_loopa(int newval) {
	if (newval!=loopa) {
		loopa=newval;
		upd_loopa=true;
	}
}

void Panadapter::set_loopb(int newval) {
	if (newval!=loopb) {
		loopb=newval;
		upd_loopb=true;
	}
}

void Panadapter::set_band(int newval) {
	if (newval!=band) {
		previousBand=band;
		band=newval;
		upd_band=true;
	}
}

void Panadapter::set_daxiq(int newval) {
	if (newval!=daxiq) {
		daxiq=newval;
		upd_daxiq=true;
	}
}

void Panadapter::set_daxiq_rate(int newval) {
	if (newval!=daxiq_rate) {
		daxiq_rate=newval;
		upd_daxiq_rate=true;
	}
}

void Panadapter::set_capacity(int newval) {
	if (newval!=capacity) {
		capacity=newval;
		upd_capacity=true;
	}
}

void Panadapter::set_available(int newval) {
	if (newval!=available) {
		available=newval;
		upd_available=true;
	}
}

void Panadapter::set_waterfall(int newval) {
	if (newval!=waterfall) {
		waterfall=newval;
		upd_waterfall=true;
	}
}

void Panadapter::set_xvtr(int newval) {
	if (newval!=xvtr) {
		xvtr=newval;
		upd_xvtr=true;
	}
}

void Panadapter::set_pre(int newval) {
	if (newval!=pre) {
		pre=newval;
		upd_pre=true;
	}
}

void Panadapter::set_min_bw(float newval) {
	if (newval!=min_bw) {
		min_bw=newval;
		upd_min_bw=true;
	}
}

void Panadapter::set_max_bw(float newval) {
	if (newval!=max_bw) {
		max_bw=newval;
		upd_max_bw=true;
	}
}

void Panadapter::set_bandwidth(float newval) {
	if (newval!=bandwidth) {
		bandwidth=newval;
		upd_bandwidth=true;
	}
}

void Panadapter::set_center(float newval) {
	if (newval!=center) {
		center=newval;
		upd_center=true;
	}
}

void Panadapter::set_ant_list(String newval) {
	if (!newval.equals(ant_list)) {
		ant_list=newval;
		upd_ant_list=true;
	}
}

void Panadapter::set_rxant(String newval) {
	if (!newval.equals(rxant)) {
		rxant=newval;
		upd_rxant=true;
	}
}

void Panadapter::set_wnb_updating(int newval) {
	if (newval!=wnb_updating) {
		wnb_updating=newval;
		upd_wnb_updating=true;
	}
}

void Panadapter::set_wnb(int newval) {
	if (newval!=wnb) {
		wnb=newval;
		upd_wnb=true;
	}
}

void Panadapter::set_wnb_level(int newval) {
	if (newval!=wnb_level) {
		wnb_level=newval;
		upd_wnb_level=true;
	}
}

void Panadapter::fireEvents() {

	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;
		
		- la proprietà updated deve diventare privata
	*/
	
	if ((upd_pan) && (do_pan_event!=NULL)) {
		do_pan_event(pan); 
		upd_pan=false; 
	}

	if ((upd_x_pixels) && (do_x_pixels_event!=NULL)) {
			do_x_pixels_event(pan); 
			upd_x_pixels=false; 
	}

	if ((upd_y_pixels) && (do_y_pixels_event!=NULL)) {
			do_y_pixels_event(pan); 
			upd_y_pixels=false; 
	}

	if ((upd_min_dbm) && (do_min_dbm_event!=NULL)) {
			do_min_dbm_event(pan); 
			upd_min_dbm=false; 
	}

	if ((upd_max_dbm) && (do_max_dbm_event!=NULL)) {
			do_max_dbm_event(pan); 
			upd_max_dbm=false; 
	}

	if ((upd_fps) && (do_fps_event!=NULL)) {
			do_fps_event(pan); 
			upd_fps=false; 
	}

	if ((upd_average) && (do_average_event!=NULL)) {
			do_average_event(pan); 
			upd_average=false; 
	}

	if ((upd_weighted_average) && (do_weighted_average_event!=NULL)) {
			do_weighted_average_event(pan); 
			upd_weighted_average=false; 
	}

	if ((upd_rfgain) && (do_rfgain_event!=NULL)) {
			do_rfgain_event(pan); 
			upd_rfgain=false; 
	}

	if ((upd_wide) && (do_wide_event!=NULL)) {
			do_wide_event(pan); 
			upd_wide=false; 
	}

	if ((upd_loopa) && (do_loopa_event!=NULL)) {
			do_loopa_event(pan); 
			upd_loopa=false; 
	}

	if ((upd_loopb) && (do_loopb_event!=NULL)) {
			do_loopb_event(pan); 
			upd_loopb=false; 
	}

	if ((upd_band) && (do_band_event!=NULL)) {
			do_band_event(pan); 
			upd_band=false; 
	}

	if ((upd_daxiq) && (do_daxiq_event!=NULL)) {
			do_daxiq_event(pan); 
			upd_daxiq=false; 
	}

	if ((upd_daxiq_rate) && (do_daxiq_rate_event!=NULL)) {
			do_daxiq_rate_event(pan); 
			upd_daxiq_rate=false; 
	}

	if ((upd_capacity) && (do_capacity_event!=NULL)) {
			do_capacity_event(pan); 
			upd_capacity=false; 
	}

	if ((upd_available) && (do_available_event!=NULL)) {
			do_available_event(pan); 
			upd_available=false; 
	}

	if ((upd_waterfall) && (do_waterfall_event!=NULL)) {
			do_waterfall_event(pan); 
			upd_waterfall=false; 
	}

	if ((upd_xvtr) && (do_xvtr_event!=NULL)) {
			do_xvtr_event(pan); 
			upd_xvtr=false; 
	}

	if ((upd_pre) && (do_pre_event!=NULL)) {
			do_pre_event(pan); 
			upd_pre=false; 
	}

	if ((upd_min_bw) && (do_min_bw_event!=NULL)) {
			do_min_bw_event(pan); 
			upd_min_bw=false; 
	}

	if ((upd_max_bw) && (do_max_bw_event!=NULL)) {
			do_max_bw_event(pan); 
			upd_max_bw=false; 
	}

	if ((upd_bandwidth) && (do_bandwidth_event!=NULL)) {
			do_bandwidth_event(pan); 
			upd_bandwidth=false; 
	}

	if ((upd_center) && (do_center_event!=NULL)) {
			do_center_event(pan); 
			upd_center=false; 
	}

	if ((upd_ant_list) && (do_ant_list_event!=NULL)) {
			do_ant_list_event(pan); 
			upd_ant_list=false; 
	}

	if ((upd_rxant) && (do_rxant_event!=NULL)) {
			do_rxant_event(pan); 
			upd_rxant=false; 
	}

	if ((upd_wnb_updating) && (do_wnb_updating_event!=NULL)) {
			do_wnb_updating_event(pan); 
			upd_wnb_updating=false; 
	}
	
	if ((upd_wnb) && (do_wnb_event!=NULL)) {
			do_wnb_event(pan); 
			upd_wnb=false; 
	}
	
	if ((upd_wnb_level) && (do_wnb_level_event!=NULL)) {
			do_wnb_level_event(pan); 
			upd_wnb_level=false; 
	}

}

void Panadapter::attach_pan_event(eventHandlerArrFunction _eventHandler) {
	do_pan_event=_eventHandler;
}


void Panadapter::attach_x_pixels_event(eventHandlerArrFunction _eventHandler) {
	do_x_pixels_event=_eventHandler;
}

void Panadapter::attach_y_pixels_event(eventHandlerArrFunction _eventHandler) {
	do_y_pixels_event=_eventHandler;
}

void Panadapter::attach_min_dbm_event(eventHandlerArrFunction _eventHandler) {
	do_min_dbm_event=_eventHandler;
}

void Panadapter::attach_max_dbm_event(eventHandlerArrFunction _eventHandler) {
	do_max_dbm_event=_eventHandler;
}

void Panadapter::attach_fps_event(eventHandlerArrFunction _eventHandler) {
	do_fps_event=_eventHandler;
}

void Panadapter::attach_average_event(eventHandlerArrFunction _eventHandler) {
	do_average_event=_eventHandler;
}

void Panadapter::attach_weighted_average_event(eventHandlerArrFunction _eventHandler) {
	do_weighted_average_event=_eventHandler;
}

void Panadapter::attach_rfgain_event(eventHandlerArrFunction _eventHandler) {
	do_rfgain_event=_eventHandler;
}

void Panadapter::attach_wide_event(eventHandlerArrFunction _eventHandler) {
	do_wide_event=_eventHandler;
}

void Panadapter::attach_loopa_event(eventHandlerArrFunction _eventHandler) {
	do_loopa_event=_eventHandler;
}

void Panadapter::attach_loopb_event(eventHandlerArrFunction _eventHandler) {
	do_loopb_event=_eventHandler;
}

void Panadapter::attach_band_event(eventHandlerArrFunction _eventHandler) {
	do_band_event=_eventHandler;
}

void Panadapter::attach_daxiq_event(eventHandlerArrFunction _eventHandler) {
	do_daxiq_event=_eventHandler;
}

void Panadapter::attach_daxiq_rate_event(eventHandlerArrFunction _eventHandler) {
	do_daxiq_rate_event=_eventHandler;
}

void Panadapter::attach_capacity_event(eventHandlerArrFunction _eventHandler) {
	do_capacity_event=_eventHandler;
}

void Panadapter::attach_available_event(eventHandlerArrFunction _eventHandler) {
	do_available_event=_eventHandler;
}

void Panadapter::attach_waterfall_event(eventHandlerArrFunction _eventHandler) {
	do_waterfall_event=_eventHandler;
}

void Panadapter::attach_xvtr_event(eventHandlerArrFunction _eventHandler) {
	do_xvtr_event=_eventHandler;
}

void Panadapter::attach_pre_event(eventHandlerArrFunction _eventHandler) {
	do_pre_event=_eventHandler;
}

void Panadapter::attach_min_bw_event(eventHandlerArrFunction _eventHandler) {
	do_min_bw_event=_eventHandler;
}

void Panadapter::attach_max_bw_event(eventHandlerArrFunction _eventHandler) {
	do_max_bw_event=_eventHandler;
}

void Panadapter::attach_bandwidth_event(eventHandlerArrFunction _eventHandler) {
	do_bandwidth_event=_eventHandler;
}

void Panadapter::attach_center_event(eventHandlerArrFunction _eventHandler) {
	do_center_event=_eventHandler;
}

void Panadapter::attach_ant_list_event(eventHandlerArrFunction _eventHandler) {
	do_ant_list_event=_eventHandler;
}

void Panadapter::attach_rxant_event(eventHandlerArrFunction _eventHandler) {
	do_rxant_event=_eventHandler;
}

void Panadapter::attach_wnb_updating_event(eventHandlerArrFunction _eventHandler) {
	do_wnb_updating_event=_eventHandler;
}

void Panadapter::attach_wnb_event(eventHandlerArrFunction _eventHandler) {
	do_wnb_event=_eventHandler;
}

void Panadapter::attach_wnb_level_event(eventHandlerArrFunction _eventHandler) {
	do_wnb_level_event=_eventHandler;
}

void Panadapter::updateObject(int objectId,int value){
	//Serial.print(F("==Panadapter::updateObject()=="));
    switch(objectId) {
		case PANADAPTER_AVERAGE:
		    average=value;
			break;
		case PANADAPTER_FPS:
		    fps=value;
			break;
		case PAN_BANDWIDTH:
		    bandwidth=value;
			break;
		case PAN_MIN_DBM:
		    min_dbm=value;
			break;
		case PAN_MAX_DBM:
		    max_dbm=value;
			break;
		default:
			 Serial.print(F("Panadapter::updateObject - Unhandled id:")); Serial.println(objectId);
	}

}