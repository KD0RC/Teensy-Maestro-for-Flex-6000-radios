/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef Waterfall_h
#define Waterfall_h
#include "Arduino.h"

#define WATERFALL_BLACK_LEVEL 4000
#define WATERFALL_GRADIENT_INDEX 4001
#define WATERFALL_LINE_DURATION 4002
#define WATERFALL_COLOR_GAIN 4003

extern "C" {
	typedef void (*eventHandlerArrFunction)(const int senderId);
}

class Waterfall
{
  public:
    //properties
	int waterfall; // 0x42000000 
	int x_pixels; //=1170 
	float center; //=14.033201 
	float bandwidth; //=0.210171 
	int line_duration; //=100 
	int rfgain; //=0 
	String rxant; //=ANT1 
	int wide; //=0 
	int loopa; //=0 
	int loopb; //=0 
	int band; //=20 
	int daxiq; //=0 
	int daxiq_rate; //=0 
	int capacity; //=16 
	int available; //=14 
	int panadapter; //=40000000 
	int color_gain; //=31 
	int auto_black; //=1 
	int black_level; //=0 
	int gradient_index; //=0 
	int xvtr; //=

    //methods
    Waterfall();
	void updateStatus(String msg);
	void updateObject(int objectId,int value);  //Update specific waterfall object	
	
	//setter methods
	void set_waterfall(int newval); 
	void set_x_pixels(int newval);
	void set_line_duration(int newval); 
	void set_rfgain(int newval); 
	void set_wide(int newval);
	void set_loopa(int newval); 
	void set_loopb(int newval); 
	void set_band(int newval); 
	void set_daxiq(int newval);
	void set_daxiq_rate(int newval); 
	void set_capacity(int newval); 
	void set_available(int newval); 
	void set_panadapter(int newval);
	void set_color_gain(int newval);
	void set_auto_black(int newval);
	void set_black_level(int newval); 
	void set_gradient_index(int newval); 
	void set_xvtr(int newval); 
	void set_center(float newval);
	void set_bandwidth(float newval);  
	void set_rxant(String newval);
	
	//event handler accessor methods
	void attach_waterfall_event(eventHandlerArrFunction _eventHandler); 
	void attach_x_pixels_event(eventHandlerArrFunction _eventHandler);
	void attach_line_duration_event(eventHandlerArrFunction _eventHandler); 
	void attach_rfgain_event(eventHandlerArrFunction _eventHandler); 
	void attach_wide_event(eventHandlerArrFunction _eventHandler);
	void attach_loopa_event(eventHandlerArrFunction _eventHandler); 
	void attach_loopb_event(eventHandlerArrFunction _eventHandler); 
	void attach_band_event(eventHandlerArrFunction _eventHandler); 
	void attach_daxiq_event(eventHandlerArrFunction _eventHandler);
	void attach_daxiq_rate_event(eventHandlerArrFunction _eventHandler); 
	void attach_capacity_event(eventHandlerArrFunction _eventHandler); 
	void attach_available_event(eventHandlerArrFunction _eventHandler); 
	void attach_panadapter_event(eventHandlerArrFunction _eventHandler);
	void attach_color_gain_event(eventHandlerArrFunction _eventHandler);
	void attach_auto_black_event(eventHandlerArrFunction _eventHandler);
	void attach_black_level_event(eventHandlerArrFunction _eventHandler); 
	void attach_gradient_index_event(eventHandlerArrFunction _eventHandler); 
	void attach_xvtr_event(eventHandlerArrFunction _eventHandler); 
	void attach_center_event(eventHandlerArrFunction _eventHandler);
	void attach_bandwidth_event(eventHandlerArrFunction _eventHandler);  
	void attach_rxant_event(eventHandlerArrFunction _eventHandler);
	
	//
	void fireEvents();
	boolean updated;
	
	
  private:
    //properties
	
	//Update flags
	boolean upd_waterfall; 
	boolean upd_x_pixels;
	boolean upd_line_duration; 
	boolean upd_rfgain; 
	boolean upd_wide;
	boolean upd_loopa; 
	boolean upd_loopb; 
	boolean upd_band; 
	boolean upd_daxiq;
	boolean upd_daxiq_rate; 
	boolean upd_capacity; 
	boolean upd_available; 
	boolean upd_panadapter;
	boolean upd_color_gain;
	boolean upd_auto_black;
	boolean upd_black_level; 
	boolean upd_gradient_index; 
	boolean upd_xvtr; 
	boolean upd_center;
	boolean upd_bandwidth;  
	boolean upd_rxant;
	
	//Event handlers
	eventHandlerArrFunction do_waterfall_event=NULL; 
	eventHandlerArrFunction do_x_pixels_event=NULL;
	eventHandlerArrFunction do_line_duration_event=NULL; 
	eventHandlerArrFunction do_rfgain_event=NULL; 
	eventHandlerArrFunction do_wide_event=NULL;
	eventHandlerArrFunction do_loopa_event=NULL; 
	eventHandlerArrFunction do_loopb_event=NULL; 
	eventHandlerArrFunction do_band_event=NULL; 
	eventHandlerArrFunction do_daxiq_event=NULL;
	eventHandlerArrFunction do_daxiq_rate_event=NULL; 
	eventHandlerArrFunction do_capacity_event=NULL; 
	eventHandlerArrFunction do_available_event=NULL; 
	eventHandlerArrFunction do_panadapter_event=NULL;
	eventHandlerArrFunction do_color_gain_event=NULL;
	eventHandlerArrFunction do_auto_black_event=NULL;
	eventHandlerArrFunction do_black_level_event=NULL; 
	eventHandlerArrFunction do_gradient_index_event=NULL; 
	eventHandlerArrFunction do_xvtr_event=NULL; 
	eventHandlerArrFunction do_center_event=NULL;
	eventHandlerArrFunction do_bandwidth_event=NULL;  
	eventHandlerArrFunction do_rxant_event=NULL;	
	
    //methods	
	void setValue(String msg);
};
	
#endif