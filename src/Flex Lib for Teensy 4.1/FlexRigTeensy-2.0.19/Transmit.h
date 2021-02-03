/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef Transmit_h
#define Transmit_h
#include "Arduino.h"

#define TRANSMIT_RF_POWER 3000
#define TRANSMIT_ATU_POWER 3001
#define TRANSMIT_BREAK_IN_DELAY 3002
#define TRANSMIT_MONITOR_GAIN_CW 3003
#define TRANSMIT_MONITOR_PAN_CW 3004
#define TRANSMIT_SPEED 3005
#define TRANSMIT_PITCH 3006
#define TRANSMIT_MIC_LEVEL 3007
#define TRANSMIT_MONITOR_GAIN_SB 3008
#define TRANSMIT_COMPANDER_LEVEL 3009
#define TRANSMIT_VOX_LEVEL 3010
#define TRANSMIT_VOX_DELAY 3011
#define TRANSMIT_AM_CARRIER 3012
#define TRANSMIT_LO 3013
#define TRANSMIT_HI 3014 

extern "C" {
	typedef void (*eventHandlerFunction)(void);
}


class Transmit
{
  public:
    //properties
	int freq;// =14.0366 
	int lo;// =100 
	int hi;// =2900 
	int rfpower;// =3 
	int tunepower;// =10 
	int am_carrier_level;// =100 
	int vox_enable;// =0 
	int vox_level;// =50 
	int vox_delay;// =250 
	int mic_level;// =40 
	int mic_boost;// =1 
	int mic_bias;// =0 
	int mic_acc;// =0 
	int compander;// =1 
	int compander_level;// =70 
	int dax;// =0 
	int pitch;// =540 
	int speed;// =23 
	int iambic;// =1 
	int iambic_mode;// =1 
	int cwl_enabled;// =0 
	int swap_paddles;// =0 
	int break_in;// =1 
	int break_in_delay;// =9 
	int sidetone;// =1 
	int monitor;// =0 
	int sb_monitor; //=0
	int mon_gain_cw;// =76 
	int mon_gain_sb;// =80 
	int mon_pan_cw;// =50 
	int mon_pan_sb;// =50 
	int tune;// =0 
	int met_in_rx;// =0 
	int hwalc_enabled;// =0 
	int inhibit;// =0 
	int speech_processor_enable;// =1
	int speech_processor_level;// =0 
	int show_tx_in_waterfall;// =0
	String mic_selection;// =MIC 
	
	
    //methods
    Transmit();
	void updateStatus(String msg);
	void updateObject(int objectId,int value);  //Update specific transmit object

	//setter methods
	void set_freq(int newval);
	void set_lo(int newval);
	void set_hi(int newval);
	void set_rfpower(int newval);
	void set_tunepower(int newval); 
	void set_am_carrier_level(int newval); 
	void set_vox_enable(int newval);
	void set_vox_level(int newval); 
	void set_vox_delay(int newval); 
	void set_mic_level(int newval);
	void set_mic_boost(int newval); 
	void set_mic_bias(int newval); 
	void set_mic_acc(int newval); 
	void set_compander(int newval); 
	void set_compander_level(int newval); 
	void set_dax(int newval); 
	void set_pitch(int newval); 
	void set_speed(int newval); 
	void set_iambic(int newval);
	void set_iambic_mode(int newval); 
	void set_cwl_enabled(int newval); 
	void set_swap_paddles(int newval); 
	void set_break_in(int newval);
	void set_break_in_delay(int newval);
	void set_sidetone(int newval); 
	void set_monitor(int newval); 
	void set_sb_monitor(int newval); 
	void set_mon_gain_cw(int newval); 
	void set_mon_gain_sb(int newval); 
	void set_mon_pan_cw(int newval);
	void set_mon_pan_sb(int newval); 
	void set_tune(int newval); 
	void set_met_in_rx(int newval);
	void set_hwalc_enabled(int newval); 
	void set_inhibit(int newval);
	void set_speech_processor_enable(int newval);
	void set_speech_processor_level(int newval); 
	void set_show_tx_in_waterfall(int newval);
	void set_mic_selection(String newval);

	//event handler accessor methods
	void attach_freq_event(eventHandlerFunction _eventHandler);
	void attach_lo_event(eventHandlerFunction _eventHandler);
	void attach_hi_event(eventHandlerFunction _eventHandler);
	void attach_rfpower_event(eventHandlerFunction _eventHandler);
	void attach_tunepower_event(eventHandlerFunction _eventHandler); 
	void attach_am_carrier_level_event(eventHandlerFunction _eventHandler); 
	void attach_vox_enable_event(eventHandlerFunction _eventHandler);
	void attach_vox_level_event(eventHandlerFunction _eventHandler); 
	void attach_vox_delay_event(eventHandlerFunction _eventHandler); 
	void attach_mic_level_event(eventHandlerFunction _eventHandler);
	void attach_mic_boost_event(eventHandlerFunction _eventHandler); 
	void attach_mic_bias_event(eventHandlerFunction _eventHandler); 
	void attach_mic_acc_event(eventHandlerFunction _eventHandler); 
	void attach_compander_event(eventHandlerFunction _eventHandler); 
	void attach_compander_level_event(eventHandlerFunction _eventHandler); 
	void attach_dax_event(eventHandlerFunction _eventHandler); 
	void attach_pitch_event(eventHandlerFunction _eventHandler); 
	void attach_speed_event(eventHandlerFunction _eventHandler); 
	void attach_iambic_event(eventHandlerFunction _eventHandler);
	void attach_iambic_mode_event(eventHandlerFunction _eventHandler); 
	void attach_cwl_enabled_event(eventHandlerFunction _eventHandler); 
	void attach_swap_paddles_event(eventHandlerFunction _eventHandler); 
	void attach_break_in_event(eventHandlerFunction _eventHandler);
	void attach_break_in_delay_event(eventHandlerFunction _eventHandler);
	void attach_sidetone_event(eventHandlerFunction _eventHandler); 
	void attach_monitor_event(eventHandlerFunction _eventHandler); 
	void attach_sb_monitor_event(eventHandlerFunction _eventHandler); 
	void attach_mon_gain_cw_event(eventHandlerFunction _eventHandler); 
	void attach_mon_gain_sb_event(eventHandlerFunction _eventHandler); 
	void attach_mon_pan_cw_event(eventHandlerFunction _eventHandler);
	void attach_mon_pan_sb_event(eventHandlerFunction _eventHandler); 
	void attach_tune_event(eventHandlerFunction _eventHandler); 
	void attach_met_in_rx_event(eventHandlerFunction _eventHandler);
	void attach_hwalc_enabled_event(eventHandlerFunction _eventHandler); 
	void attach_inhibit_event(eventHandlerFunction _eventHandler);
	void attach_speech_processor_enable_event(eventHandlerFunction _eventHandler);
	void attach_speech_processor_level_event(eventHandlerFunction _eventHandler); 
	void attach_show_tx_in_waterfall_event(eventHandlerFunction _eventHandler);
	void attach_mic_selection_event(eventHandlerFunction _eventHandler);
	
	//
	void fireEvents();
	boolean updated;	
	
  private:
    //properties
	
	//Update Flags
	boolean upd_freq;
	boolean upd_lo;
	boolean upd_hi;
	boolean upd_rfpower;
	boolean upd_tunepower; 
	boolean upd_am_carrier_level; 
	boolean upd_vox_enable;
	boolean upd_vox_level; 
	boolean upd_vox_delay; 
	boolean upd_mic_level;
	boolean upd_mic_boost; 
	boolean upd_mic_bias; 
	boolean upd_mic_acc; 
	boolean upd_compander; 
	boolean upd_compander_level; 
	boolean upd_dax; 
	boolean upd_pitch; 
	boolean upd_speed; 
	boolean upd_iambic;
	boolean upd_iambic_mode; 
	boolean upd_cwl_enabled; 
	boolean upd_swap_paddles; 
	boolean upd_break_in;
	boolean upd_break_in_delay;
	boolean upd_sidetone; 
	boolean upd_monitor; 
	boolean upd_sb_monitor; 
	boolean upd_mon_gain_cw; 
	boolean upd_mon_gain_sb; 
	boolean upd_mon_pan_cw;
	boolean upd_mon_pan_sb; 
	boolean upd_tune; 
	boolean upd_met_in_rx;
	boolean upd_hwalc_enabled; 
	boolean upd_inhibit;
	boolean upd_speech_processor_enable;
	boolean upd_speech_processor_level; 
	boolean upd_show_tx_in_waterfall;
	boolean upd_mic_selection;
	
	//event handlers
	eventHandlerFunction do_freq_event=NULL;
	eventHandlerFunction do_lo_event=NULL;
	eventHandlerFunction do_hi_event=NULL;
	eventHandlerFunction do_rfpower_event=NULL;
	eventHandlerFunction do_tunepower_event=NULL; 
	eventHandlerFunction do_am_carrier_level_event=NULL; 
	eventHandlerFunction do_vox_enable_event=NULL;
	eventHandlerFunction do_vox_level_event=NULL; 
	eventHandlerFunction do_vox_delay_event=NULL; 
	eventHandlerFunction do_mic_level_event=NULL;
	eventHandlerFunction do_mic_boost_event=NULL; 
	eventHandlerFunction do_mic_bias_event=NULL; 
	eventHandlerFunction do_mic_acc_event=NULL; 
	eventHandlerFunction do_compander_event=NULL; 
	eventHandlerFunction do_compander_level_event=NULL; 
	eventHandlerFunction do_dax_event=NULL; 
	eventHandlerFunction do_pitch_event=NULL; 
	eventHandlerFunction do_speed_event=NULL; 
	eventHandlerFunction do_iambic_event=NULL;
	eventHandlerFunction do_iambic_mode_event=NULL; 
	eventHandlerFunction do_cwl_enabled_event=NULL; 
	eventHandlerFunction do_swap_paddles_event=NULL; 
	eventHandlerFunction do_break_in_event=NULL;
	eventHandlerFunction do_break_in_delay_event=NULL;
	eventHandlerFunction do_sidetone_event=NULL; 
	eventHandlerFunction do_monitor_event=NULL; 
	eventHandlerFunction do_sb_monitor_event=NULL; 
	eventHandlerFunction do_mon_gain_cw_event=NULL; 
	eventHandlerFunction do_mon_gain_sb_event=NULL; 
	eventHandlerFunction do_mon_pan_cw_event=NULL;
	eventHandlerFunction do_mon_pan_sb_event=NULL; 
	eventHandlerFunction do_tune_event=NULL; 
	eventHandlerFunction do_met_in_rx_event=NULL;
	eventHandlerFunction do_hwalc_enabled_event=NULL; 
	eventHandlerFunction do_inhibit_event=NULL;
	eventHandlerFunction do_speech_processor_enable_event=NULL;
	eventHandlerFunction do_speech_processor_level_event=NULL; 
	eventHandlerFunction do_show_tx_in_waterfall_event=NULL;
	eventHandlerFunction do_mic_selection_event=NULL;
	
    //methods	
	void setValue(String msg);
};
	
#endif