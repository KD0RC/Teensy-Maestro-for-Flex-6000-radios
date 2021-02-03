/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#ifndef Radio_h
#define Radio_h
#include "Arduino.h"
#include "CommandList.h"

#define RADIO_MIXER_LINEOUT_GAIN 1000
#define RADIO_MIXER_HEADPHONE_GAIN 1001

extern "C" {
	typedef void (*eventHandlerFunction)(void);
}

class Radio
{
  public:
    //properties
	int slices; //=0 
	int panadapters; //=0 
	int lineout_gain; //=86 
	int lineout_mute; //=0 
	int headphone_gain; //=59 
	int headphone_mute; //=1 
	int remote_on_enabled; //=0
	int pll_done; //=0 
	int freq_error_ppb; //=-1
	int cal_freq; //=15.000
	int tnf_enabled; //=1
	int snap_tune_enabled; //=1
	String nickname; //=A201440250079 
	String callsign; //=IW7DMH 
    int binaural_rx; //0;
	
    //methods
    Radio();
	void updateStatus(String msg);  //Update radio objects using status messages 
	void updateObject(int objectId,int value);  //Update specific radio object	
	void fire_disconnected_event();
	
	//setter methods
	void set_slices(int newval);
	void set_panadapters(int newval);
	void set_lineout_gain(int newval); 
	void set_lineout_mute(int newval); 
	void set_headphone_gain(int newval); 
	void set_headphone_mute(int newval); 
	void set_remote_on_enabled(int newval);
	void set_pll_done(int newval); 
	void set_freq_error_ppb(int newval); 
	void set_cal_freq(int newval); 
	void set_tnf_enabled(int newval); 
	void set_snap_tune_enabled(int newval);
	void set_nickname(String newval);
	void set_callsign(String newval);
	void set_binaural_rx(int newval);
	
	//event handler accessor methods
	void attach_slices_event(eventHandlerFunction _eventHandler);
	void attach_panadapters_event(eventHandlerFunction _eventHandler);
	void attach_lineout_gain_event(eventHandlerFunction _eventHandler);   	
	void attach_lineout_mute_event(eventHandlerFunction _eventHandler);   
	void attach_headphone_gain_event(eventHandlerFunction _eventHandler);  
	void attach_headphone_mute_event(eventHandlerFunction _eventHandler);  
	void attach_remote_on_enabled_event(eventHandlerFunction _eventHandler);
	void attach_pll_done_event(eventHandlerFunction _eventHandler); 
	void attach_freq_error_ppb_event(eventHandlerFunction _eventHandler); 
	void attach_cal_freq_event(eventHandlerFunction _eventHandler); 
	void attach_tnf_enabled_event(eventHandlerFunction _eventHandler); 
	void attach_snap_tune_enabled_event(eventHandlerFunction _eventHandler);
	void attach_nickname_event(eventHandlerFunction _eventHandler);
	void attach_callsign_event(eventHandlerFunction _eventHandler);
	void attach_binaural_rx_event(eventHandlerFunction _eventHandler);
	void attach_disconnected_event(eventHandlerFunction _eventHandler);
	
	//
	void fireEvents();
	boolean updated;
  private:
    //properties
		
	//Update Flags
	boolean upd_slices;  
	boolean upd_panadapters; 
	boolean upd_lineout_gain;  
	boolean upd_lineout_mute;  
	boolean upd_headphone_gain;  
	boolean upd_headphone_mute;  
	boolean upd_remote_on_enabled; 
	boolean upd_pll_done; 
	boolean upd_freq_error_ppb; 
	boolean upd_cal_freq; 
	boolean upd_tnf_enabled; 
	boolean upd_snap_tune_enabled; 
	boolean upd_nickname; 
	boolean upd_callsign; 
	boolean upd_binaural_rx;
	//event handlers
	
	eventHandlerFunction do_slices_event=NULL;
	eventHandlerFunction do_panadapters_event=NULL;
	eventHandlerFunction do_lineout_gain_event=NULL;  
	eventHandlerFunction do_lineout_mute_event=NULL;  
	eventHandlerFunction do_headphone_gain_event=NULL;  
	eventHandlerFunction do_headphone_mute_event=NULL;  
	eventHandlerFunction do_remote_on_enabled_event=NULL;
	eventHandlerFunction do_pll_done_event=NULL; 
	eventHandlerFunction do_freq_error_ppb_event=NULL; 
	eventHandlerFunction do_cal_freq_event=NULL; 
	eventHandlerFunction do_tnf_enabled_event=NULL; 
	eventHandlerFunction do_snap_tune_enabled_event=NULL;
	eventHandlerFunction do_nickname_event=NULL; 
	eventHandlerFunction do_callsign_event=NULL; 
	eventHandlerFunction do_binaural_rx_event=NULL;
	eventHandlerFunction do_disconnected_event=NULL;

    //methods
	void setValue(String msg);
};
	
#endif

/* radio - RESPONSE V1.4
S5BD3B994|radio  slices=1 
				 panadapters=1 
				 lineout_gain=70 
				 lineout_mute=1 
				 headphone_gain=70 
				 headphone_mute=1 
				 remote_on_enabled=0 
				 pll_done=0 
				 freq_error_ppb=-1 
				 cal_freq=15.000 
				 tnf_enabled=1 
				 snap_tune_enabled=1
				 nickname=A201440250079 
				 callsign=IW7DMH 
				 binaural_rx=0
*/




 