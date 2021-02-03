/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef Slice_h
#define Slice_h
#include "Arduino.h"

#define SLICE_AUDIO_GAIN 6000
#define SLICE_AUDIO_PAN 6001
#define SLICE_AGC_THRESHOLD 6003
#define SLICE_NB_LEVEL 6004
#define SLICE_NR_LEVEL 6005
#define SLICE_APF_LEVEL 6006
#define SLICE_RIT_FREQ 6007
#define SLICE_XIT_FREQ 6008
#define SLICE_FILTER_LOW 6009
#define SLICE_FILTER_HIGH 6010
#define SLICE_FILTER_SHIFT 6011
#define SLICE_FILTER_WIDTH 6012
#define SLICE_AGC_OFF_LEVEL 6013				 
#define SLICE_ANF_LEVEL 6014
#define SLICE_WNB_LEVEL 6015

extern "C" {
	typedef void (*eventHandlerArrFunction)(const int senderId);
}

enum SLICE_MODES {LSB=0,USB,AM,CW,DIGL,DIGU,FM,NFM,DFM,SAM_,RTTY};

class Slice
{
  public:
    //properties
	int in_use; //=1 
	int RF_frequency; //=14.036600 
	int rit_on; //=0 
	int rit_freq; //=0 
	int xit_on; //=0 
	int xit_freq; //=0 
	int wide; //=0 
	int filter_lo; //=-200
	int filter_hi; //=200
	int step; //=10 
	int agc_threshold; //=65 
	int agc_off_level; //=10 
	int pan; //=0x40000000 
	int loopa; //=0 
	int loopb; //=0 
	int qsk; //=1 
	int dax; //=1 
	int dax_clients; //=0 
	int lock; //=0 
	int tx; //=1 
	int dax_tx; //=0 
	int active; //=0 
	int audio_gain; //=50 
	int audio_pan; //=50 
	int audio_mute; //=0 
	int record; //=0 
	int record_time; //=0.0 
	int anf; //=0 
	int anf_level; //=0 
	int nr; //=0 
	int nr_level; //=50 
	int wnb; //=0 
	int wnb_level; //=50 
	int nb; //=0 
	int nb_level; //=50 
	int apf; //=0 
	int apf_level; //=7 
	int diversity; //=0 
	int diversity_parent; //=0 
	int diversity_child; //=0 
	int diversity_index; //=1342177293 
	int filter_shift;
	int filter_width; 
	String rxant; //=ANT1 
	String mode; //=CW 
	String step_list; //=1,5,10,50,100,200,400
	String agc_mode; //=med 
	String txant; //=ANT1 
	String play; //=disabled 
	String ant_list; //=ANT1,ANT2,XVTR
	
	//int intMode; //Numeric value that identifies one of the SLICE_MODES
	//int oldIntMode;
    String previousMode;


    //methods
    Slice();
	void updateStatus(String msg);
	void updateObject(int objectId,int value);  //Update specific slice object	
	
	//setter methods
	void set_in_use(int newval);
	void set_RF_frequency(int newval); 
	void set_rit_on(int newval); 
	void set_rit_freq(int newval); 
	void set_xit_on(int newval); 
	void set_xit_freq(int newval);
	void set_wide(int newval);  
	void set_filter_lo(int newval);
	void set_filter_hi(int newval);
	void set_step(int newval); 
	void set_agc_threshold(int newval); 
	void set_agc_off_level(int newval); 
	void set_pan(int newval);
	void set_loopa(int newval); 
	void set_loopb(int newval); 
	void set_qsk(int newval); 
	void set_dax(int newval); 
	void set_dax_clients(int newval); 
	void set_lock(int newval); 
	void set_tx(int newval); 
	void set_dax_tx(int newval);
	void set_active(int newval);
	void set_audio_gain(int newval); 
	void set_audio_pan(int newval);
	void set_audio_mute(int newval); 
	void set_record(int newval);  
	void set_record_time(int newval); 
	void set_anf(int newval);  
	void set_anf_level(int newval); 
	void set_nr(int newval); 
	void set_nr_level(int newval);
	void set_nb(int newval); 
	void set_nb_level(int newval); 
	void set_wnb(int newval); 
	void set_wnb_level(int newval); 
	void set_apf(int newval); 
	void set_apf_level(int newval); 
	void set_diversity(int newval); 
	void set_diversity_parent(int newval); 
	void set_diversity_child(int newval); 
	void set_diversity_index(int newval); 
	void set_filter_shift(int newval);
	void set_filter_width(int newval); 
	void set_rxant(String newval); 
	void set_mode(String newval); 
	void set_step_list(String newval); 
	void set_agc_mode(String newval); 
	void set_txant(String newval); 
	void set_play(String newval); 
	void set_ant_list(String newval);
	
	void set_sliceId(int newval);
	
	//old setter methods
	//void setFilterLow(int value);
    //void setFilterHigh(int value);
    //void setFilterShift(int value);
	//void setFilterWidth(int value);
	
	//specific getter methods
	//int getBand();
	int getParentPan();
	String getAgcTMode();
	String getFilterWidthStr();
	void calcShiftWidthValue();
	void calcHighLowValues();
	
	//event handler accessor methods
	void attach_in_use_event(eventHandlerArrFunction _eventHandler);
	void attach_RF_frequency_event(eventHandlerArrFunction _eventHandler); 
	void attach_rit_on_event(eventHandlerArrFunction _eventHandler); 
	void attach_rit_freq_event(eventHandlerArrFunction _eventHandler); 
	void attach_xit_on_event(eventHandlerArrFunction _eventHandler); 
	void attach_xit_freq_event(eventHandlerArrFunction _eventHandler);
	void attach_wide_event(eventHandlerArrFunction _eventHandler);  
	void attach_filter_lo_event(eventHandlerArrFunction _eventHandler);
	void attach_filter_hi_event(eventHandlerArrFunction _eventHandler);
	void attach_step_event(eventHandlerArrFunction _eventHandler); 
	void attach_agc_threshold_event(eventHandlerArrFunction _eventHandler); 
	void attach_agc_off_level_event(eventHandlerArrFunction _eventHandler); 
	void attach_pan_event(eventHandlerArrFunction _eventHandler);
	void attach_loopa_event(eventHandlerArrFunction _eventHandler); 
	void attach_loopb_event(eventHandlerArrFunction _eventHandler); 
	void attach_qsk_event(eventHandlerArrFunction _eventHandler); 
	void attach_dax_event(eventHandlerArrFunction _eventHandler); 
	void attach_dax_clients_event(eventHandlerArrFunction _eventHandler); 
	void attach_lock_event(eventHandlerArrFunction _eventHandler); 
	void attach_tx_event(eventHandlerArrFunction _eventHandler); 
	void attach_dax_tx_event(eventHandlerArrFunction _eventHandler);
	void attach_active_event(eventHandlerArrFunction _eventHandler);
	void attach_audio_gain_event(eventHandlerArrFunction _eventHandler); 
	void attach_audio_pan_event(eventHandlerArrFunction _eventHandler);
	void attach_audio_mute_event(eventHandlerArrFunction _eventHandler); 
	void attach_record_event(eventHandlerArrFunction _eventHandler);  
	void attach_record_time_event(eventHandlerArrFunction _eventHandler); 
	void attach_anf_event(eventHandlerArrFunction _eventHandler);  
	void attach_anf_level_event(eventHandlerArrFunction _eventHandler); 
	void attach_nr_event(eventHandlerArrFunction _eventHandler); 
	void attach_nr_level_event(eventHandlerArrFunction _eventHandler);
	void attach_wnb_event(eventHandlerArrFunction _eventHandler); 
	void attach_wnb_level_event(eventHandlerArrFunction _eventHandler); 
	void attach_nb_event(eventHandlerArrFunction _eventHandler); 
	void attach_nb_level_event(eventHandlerArrFunction _eventHandler); 
	void attach_apf_event(eventHandlerArrFunction _eventHandler); 
	void attach_apf_level_event(eventHandlerArrFunction _eventHandler); 
	void attach_diversity_event(eventHandlerArrFunction _eventHandler); 
	void attach_diversity_parent_event(eventHandlerArrFunction _eventHandler); 
	void attach_diversity_child_event(eventHandlerArrFunction _eventHandler); 
	void attach_diversity_index_event(eventHandlerArrFunction _eventHandler); 
	void attach_filter_shift_event(eventHandlerArrFunction _eventHandler);
	void attach_filter_width_event(eventHandlerArrFunction _eventHandler); 
	void attach_rxant_event(eventHandlerArrFunction _eventHandler); 
	void attach_mode_event(eventHandlerArrFunction _eventHandler); 
	void attach_step_list_event(eventHandlerArrFunction _eventHandler); 
	void attach_agc_mode_event(eventHandlerArrFunction _eventHandler); 
	void attach_txant_event(eventHandlerArrFunction _eventHandler); 
	void attach_play_event(eventHandlerArrFunction _eventHandler); 
	void attach_ant_list_event(eventHandlerArrFunction _eventHandler);
	
	//
	void fireEvents();
	boolean updated;
	 
  private:
    //properties
	int sliceId;
	
	//Update Flags
	boolean upd_in_use;
	boolean upd_RF_frequency; 
	boolean upd_rit_on; 
	boolean upd_rit_freq; 
	boolean upd_xit_on; 
	boolean upd_xit_freq;
	boolean upd_wide;  
	boolean upd_filter_lo;
	boolean upd_filter_hi;
	boolean upd_step; 
	boolean upd_agc_threshold; 
	boolean upd_agc_off_level; 
	boolean upd_pan;
	boolean upd_loopa; 
	boolean upd_loopb; 
	boolean upd_qsk; 
	boolean upd_dax; 
	boolean upd_dax_clients; 
	boolean upd_lock; 
	boolean upd_tx; 
	boolean upd_dax_tx;
	boolean upd_active;
	boolean upd_audio_gain; 
	boolean upd_audio_pan;
	boolean upd_audio_mute; 
	boolean upd_record;  
	boolean upd_record_time; 
	boolean upd_anf;  
	boolean upd_anf_level; 
	boolean upd_nr; 
	boolean upd_nr_level;
	boolean upd_wnb; 
	boolean upd_wnb_level; 
	boolean upd_nb; 
	boolean upd_nb_level; 
	boolean upd_apf; 
	boolean upd_apf_level; 
	boolean upd_diversity; 
	boolean upd_diversity_parent; 
	boolean upd_diversity_child; 
	boolean upd_diversity_index; 
	boolean upd_filter_shift;
	boolean upd_filter_width; 
	boolean upd_rxant; 
	boolean upd_mode; 
	boolean upd_step_list; 
	boolean upd_agc_mode; 
	boolean upd_txant; 
	boolean upd_play; 
	boolean upd_ant_list;
		
	//event handlers
    eventHandlerArrFunction do_in_use_event=NULL;
	eventHandlerArrFunction do_RF_frequency_event=NULL; 
	eventHandlerArrFunction do_rit_on_event=NULL; 
	eventHandlerArrFunction do_rit_freq_event=NULL; 
	eventHandlerArrFunction do_xit_on_event=NULL; 
	eventHandlerArrFunction do_xit_freq_event=NULL;
	eventHandlerArrFunction do_wide_event=NULL;  
	eventHandlerArrFunction do_filter_lo_event=NULL;
	eventHandlerArrFunction do_filter_hi_event=NULL;
	eventHandlerArrFunction do_step_event=NULL; 
	eventHandlerArrFunction do_agc_threshold_event=NULL; 
	eventHandlerArrFunction do_agc_off_level_event=NULL; 
	eventHandlerArrFunction do_pan_event=NULL;
	eventHandlerArrFunction do_loopa_event=NULL; 
	eventHandlerArrFunction do_loopb_event=NULL; 
	eventHandlerArrFunction do_qsk_event=NULL; 
	eventHandlerArrFunction do_dax_event=NULL; 
	eventHandlerArrFunction do_dax_clients_event=NULL; 
	eventHandlerArrFunction do_lock_event=NULL; 
	eventHandlerArrFunction do_tx_event=NULL; 
	eventHandlerArrFunction do_dax_tx_event=NULL;
	eventHandlerArrFunction do_active_event=NULL;
	eventHandlerArrFunction do_audio_gain_event=NULL; 
	eventHandlerArrFunction do_audio_pan_event=NULL;
	eventHandlerArrFunction do_audio_mute_event=NULL; 
	eventHandlerArrFunction do_record_event=NULL;  
	eventHandlerArrFunction do_record_time_event=NULL; 
	eventHandlerArrFunction do_anf_event=NULL;  
	eventHandlerArrFunction do_anf_level_event=NULL; 
	eventHandlerArrFunction do_nr_event=NULL; 
	eventHandlerArrFunction do_nr_level_event=NULL;
	eventHandlerArrFunction do_wnb_event=NULL; 
	eventHandlerArrFunction do_wnb_level_event=NULL; 
	eventHandlerArrFunction do_nb_event=NULL; 
	eventHandlerArrFunction do_nb_level_event=NULL; 
	eventHandlerArrFunction do_apf_event=NULL; 
	eventHandlerArrFunction do_apf_level_event=NULL; 
	eventHandlerArrFunction do_diversity_event=NULL; 
	eventHandlerArrFunction do_diversity_parent_event=NULL; 
	eventHandlerArrFunction do_diversity_child_event=NULL; 
	eventHandlerArrFunction do_diversity_index_event=NULL; 
	eventHandlerArrFunction do_filter_shift_event=NULL;
	eventHandlerArrFunction do_filter_width_event=NULL; 
	eventHandlerArrFunction do_rxant_event=NULL; 
	eventHandlerArrFunction do_mode_event=NULL; 
	eventHandlerArrFunction do_step_list_event=NULL; 
	eventHandlerArrFunction do_agc_mode_event=NULL; 
	eventHandlerArrFunction do_txant_event=NULL; 
	eventHandlerArrFunction do_play_event=NULL; 
	eventHandlerArrFunction do_ant_list_event=NULL;	
		
    //methods	
	void setValue(String msg);
	//void setIntMode(String m);
	
};
	
#endif