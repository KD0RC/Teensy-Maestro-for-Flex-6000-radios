/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef Panadapter_h
#define Panadapter_h
#include "Arduino.h"

#define PANADAPTER_AVERAGE 5000
#define PANADAPTER_FPS 5001
#define PAN_BANDWIDTH 5002
#define PAN_MIN_DBM 5003
#define PAN_MAX_DBM 5004

extern "C" {
	typedef void (*eventHandlerArrFunction)(const int senderId);
}

class Panadapter
{
  public:
    //properties
	int pan; // 0x40000000 
	int x_pixels; //=1170 
	int y_pixels; //=187 
	int min_dbm; //=-125 
	int max_dbm; //=-40 
	int fps; //=25
	int average; //=10 
	int weighted_average; //=0 
	int rfgain; //=0 
	int wide; //=0 
	int loopa; //=0 
	int loopb; //=0 
	int band; //=20 
	int daxiq; //=1 
	int daxiq_rate; //=48000 
	int capacity; //=16 
	int available; //=14 
	int waterfall; //=42000000 
	int xvtr; //= 
	int pre; //= 	
	int wnb_updating; //=1
	int wnb; //=0 
	int wnb_level; //=5		
	float min_bw; //=0.004919999957085
	float max_bw; //=7.372800292969 
	float bandwidth; //=0.210171 
	float center; //=14.033201 
	String ant_list; //=ANT1,ANT2,XVTR
    String rxant; //=ANT1 
	
	int previousBand;

    //methods
    Panadapter();
	void updateStatus(String msg);
	void updateObject(int objectId,int value);  //Update specific panadapter object	
	
	//setter methods
	void set_pan(int newval); 
	void set_x_pixels(int newval); 
	void set_y_pixels(int newval); 
	void set_min_dbm(int newval); 
	void set_max_dbm(int newval); 
	void set_fps(int newval); 
	void set_average(int newval); 
	void set_weighted_average(int newval);
	void set_rfgain(int newval); 
	void set_wide(int newval); 
	void set_loopa(int newval); 
	void set_loopb(int newval);  
	void set_band(int newval);  
	void set_daxiq(int newval);  
	void set_daxiq_rate(int newval); 
	void set_capacity(int newval); 
	void set_available(int newval); 
	void set_waterfall(int newval); 
	void set_xvtr(int newval);
	void set_pre(int newval); 
	void set_ant_list(String newval);
	void set_rxant(String newval); 
	void set_min_bw(float newval); 
	void set_max_bw(float newval); 
	void set_bandwidth(float newval); 
	void set_center(float newval); 
	void set_wnb_updating(int newval);
	void set_wnb(int newval); 
	void set_wnb_level(int newval);
		
	//event handler accessor methods
	void attach_pan_event (eventHandlerArrFunction _eventHandler); 
	
	void attach_x_pixels_event (eventHandlerArrFunction _eventHandler); 
	void attach_y_pixels_event (eventHandlerArrFunction _eventHandler); 
	void attach_center_event (eventHandlerArrFunction _eventHandler); 
	void attach_bandwidth_event (eventHandlerArrFunction _eventHandler); 
	void attach_min_dbm_event (eventHandlerArrFunction _eventHandler); 
	void attach_max_dbm_event (eventHandlerArrFunction _eventHandler); 
	void attach_fps_event (eventHandlerArrFunction _eventHandler); 
	void attach_average_event (eventHandlerArrFunction _eventHandler); 
	void attach_weighted_average_event (eventHandlerArrFunction _eventHandler);
	void attach_rfgain_event (eventHandlerArrFunction _eventHandler); 
	void attach_rxant_event (eventHandlerArrFunction _eventHandler); 
	void attach_wide_event (eventHandlerArrFunction _eventHandler); 
	void attach_loopa_event (eventHandlerArrFunction _eventHandler); 
	void attach_loopb_event (eventHandlerArrFunction _eventHandler);  
	void attach_band_event (eventHandlerArrFunction _eventHandler);  
	void attach_daxiq_event (eventHandlerArrFunction _eventHandler);  
	void attach_daxiq_rate_event (eventHandlerArrFunction _eventHandler); 
	void attach_capacity_event (eventHandlerArrFunction _eventHandler); 
	void attach_available_event (eventHandlerArrFunction _eventHandler); 
	void attach_waterfall_event (eventHandlerArrFunction _eventHandler); 
	void attach_min_bw_event (eventHandlerArrFunction _eventHandler); 
	void attach_max_bw_event (eventHandlerArrFunction _eventHandler); 
	void attach_xvtr_event (eventHandlerArrFunction _eventHandler);
	void attach_pre_event (eventHandlerArrFunction _eventHandler); 
	void attach_ant_list_event (eventHandlerArrFunction _eventHandler);
    void attach_wnb_updating_event(eventHandlerArrFunction _eventHandler); 
	void attach_wnb_event(eventHandlerArrFunction _eventHandler); 
	void attach_wnb_level_event(eventHandlerArrFunction _eventHandler); 
	
	//
	void fireEvents();
	boolean updated;
  private:
    //properties
	
	//Update flags
	boolean upd_pan; 
	boolean upd_x_pixels; 
	boolean upd_y_pixels; 
	boolean upd_center; 
	boolean upd_bandwidth; 
	boolean upd_min_dbm; 
	boolean upd_max_dbm; 
	boolean upd_fps; 
	boolean upd_average; 
	boolean upd_weighted_average;
	boolean upd_rfgain; 
	boolean upd_wide; 
	boolean upd_loopa; 
	boolean upd_loopb;  
	boolean upd_band;  
	boolean upd_daxiq;  
	boolean upd_daxiq_rate; 
	boolean upd_capacity; 
	boolean upd_available; 
	boolean upd_waterfall; 
	boolean upd_xvtr;
	boolean upd_pre; 
	boolean upd_ant_list;
	boolean upd_rxant;
	boolean upd_min_bw; 
	boolean upd_max_bw; 
	boolean upd_wnb_updating; 
	boolean upd_wnb; 
	boolean upd_wnb_level; 
	
	//event handlers
	eventHandlerArrFunction do_pan_event=NULL; 
	eventHandlerArrFunction do_x_pixels_event=NULL; 
	eventHandlerArrFunction do_y_pixels_event=NULL; 
	eventHandlerArrFunction do_center_event=NULL; 
	eventHandlerArrFunction do_bandwidth_event=NULL; 
	eventHandlerArrFunction do_min_dbm_event=NULL; 
	eventHandlerArrFunction do_max_dbm_event=NULL; 
	eventHandlerArrFunction do_fps_event=NULL; 
	eventHandlerArrFunction do_average_event=NULL; 
	eventHandlerArrFunction do_weighted_average_event=NULL;
	eventHandlerArrFunction do_rfgain_event=NULL; 
	eventHandlerArrFunction do_wide_event=NULL; 
	eventHandlerArrFunction do_loopa_event=NULL; 
	eventHandlerArrFunction do_loopb_event=NULL;  
	eventHandlerArrFunction do_band_event=NULL;  
	eventHandlerArrFunction do_daxiq_event=NULL;  
	eventHandlerArrFunction do_daxiq_rate_event=NULL; 
	eventHandlerArrFunction do_capacity_event=NULL; 
	eventHandlerArrFunction do_available_event=NULL; 
	eventHandlerArrFunction do_waterfall_event=NULL; 
	eventHandlerArrFunction do_xvtr_event=NULL;
	eventHandlerArrFunction do_pre_event=NULL; 
	eventHandlerArrFunction do_ant_list_event=NULL;
	eventHandlerArrFunction do_rxant_event=NULL;
	eventHandlerArrFunction do_min_bw_event=NULL; 
	eventHandlerArrFunction do_max_bw_event=NULL;
	eventHandlerArrFunction do_wnb_updating_event=NULL; 	
	eventHandlerArrFunction do_wnb_event=NULL; 
	eventHandlerArrFunction do_wnb_level_event=NULL; 
	
    //methods	
	void setValue(String msg);
};
	
#endif