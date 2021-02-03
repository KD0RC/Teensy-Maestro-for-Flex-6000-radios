/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "Slice.h"

Slice::Slice() {
	upd_in_use=true;
	upd_RF_frequency=true; 
	upd_rit_on=true; 
	upd_rit_freq=true; 
	upd_xit_on=true; 
	upd_xit_freq=true;
	upd_wide=true;  
	upd_filter_lo=true;
	upd_filter_hi=true;
	upd_step=true; 
	upd_agc_threshold=true; 
	upd_agc_off_level=true; 
	upd_pan=true;
	upd_loopa=true; 
	upd_loopb=true; 
	upd_qsk=true; 
	upd_dax=true; 
	upd_dax_clients=true; 
	upd_lock=true; 
	upd_tx=true; 
	upd_dax_tx=true;
	upd_active=true;
	upd_audio_gain=true; 
	upd_audio_pan=true;
	upd_audio_mute=true; 
	upd_record=true;  
	upd_record_time=true; 
	upd_anf=true;  
	upd_anf_level=true; 
	upd_nr=true; 
	upd_nr_level=true;
	upd_wnb=true; 
	upd_wnb_level=true; 
	upd_nb=true; 
	upd_nb_level=true; 
	upd_apf=true; 
	upd_apf_level=true; 
	upd_diversity=true; 
	upd_diversity_parent=true; 
	upd_diversity_child=true; 
	upd_diversity_index=true; 
	upd_filter_shift=true;
	upd_filter_width=true; 
	upd_rxant=true; 
	upd_mode=true; 
	upd_step_list=true; 
	upd_agc_mode=true; 
	upd_txant=true; 
	upd_play=true; 
	upd_ant_list=true;
    in_use=0;
	active=0;
	updated=true;
	previousMode="";
}


void Slice::updateStatus(String msg) {
	
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
	Serial.println(in_use);
	Serial.println(RF_frequency);
	Serial.println(rit_on);
	Serial.println(rit_freq);
	Serial.println(xit_on); 
	Serial.println(xit_freq);
	Serial.println(rxant);
	Serial.println(mode);
	Serial.println(wide);
	Serial.println(filter_lo);
	Serial.println(filter_hi);
	Serial.println(step);
	Serial.println(step_list);
	Serial.println(agc_mode);
	Serial.println(agc_threshold);
	Serial.println(agc_off_level);
	Serial.println(pan);
	Serial.println(txant);
	Serial.println(loopa);
	Serial.println(loopb);
	Serial.println(qsk);
	Serial.println(dax);
	Serial.println(dax_clients);
	Serial.println(lock);
	Serial.println(tx); 
	Serial.println(dax_tx); 
	Serial.println(active); 
	Serial.println(audio_gain);
	Serial.println(audio_pan);
	Serial.println(audio_mute);
	Serial.println(record);
	Serial.println(play); 
	Serial.println(record_time);
	Serial.println(anf);
	Serial.println(anf_level); 
	Serial.println(nr);
	Serial.println(nr_level);
	Serial.println(nb);
	Serial.println(nb_level);
	Serial.println(wnb);
	Serial.println(wnb_level);
	Serial.println(apf); 
	Serial.println(apf_level);
	Serial.println(diversity);
	Serial.println(diversity_parent);
	Serial.println(diversity_child);
	Serial.println(diversity_index);
	Serial.println(ant_list);
	*/

}

void Slice::setValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.println(var);
		
		if (var.equals(F("in_use"))) {set_in_use(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("RF_frequency"))) {set_RF_frequency(msg.substring(i+1).toFloat()*1000000); return;}
		if (var.equals(F("rit_on"))) {set_rit_on(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("rit_freq"))) {set_rit_freq(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("xit_on"))) {set_xit_on(msg.substring(i+1).toInt()); return;} 
		if (var.equals(F("xit_freq"))) {set_xit_freq(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("wide"))) {set_wide(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("filter_lo"))) {set_filter_lo(msg.substring(i+1).toInt()); 
			calcShiftWidthValue();
			//set_filter_width(filter_hi-filter_lo);
			//set_filter_shift(filter_lo+filter_width/2);
			return; 
		}
		if (var.equals(F("filter_hi"))) {set_filter_hi(msg.substring(i+1).toInt());
			calcShiftWidthValue();
			//set_filter_width(filter_hi-filter_lo);
			//set_filter_shift(filter_lo+filter_width/2);
			return; 
		}
		if (var.equals(F("step"))) {set_step(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("agc_threshold"))) {set_agc_threshold(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("agc_off_level"))) {set_agc_off_level(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("pan"))) {set_pan(msg.substring(i+3).toInt()); return;}
		if (var.equals(F("loopa"))) {set_loopa(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("loopb"))) {set_loopb(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("qsk"))) {set_qsk(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("dax"))) {set_dax(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("dax_clients"))) {set_dax_clients(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("lock"))) {set_lock(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("tx"))) {set_tx(msg.substring(i+1).toInt()); return;} 
		if (var.equals(F("dax_tx"))) {set_dax_tx(msg.substring(i+1).toInt()); return;} 
		if (var.equals(F("active"))) {set_active(msg.substring(i+1).toInt()); return;} 
		if (var.equals(F("audio_level"))) {set_audio_gain(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("audio_gain"))) {set_audio_gain(msg.substring(i+1).toInt()); return;}	// V2 compatibility
		if (var.equals(F("audio_pan"))) {set_audio_pan(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("audio_mute"))) {set_audio_mute(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("record"))) {set_record(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("record_time"))) {set_record_time(msg.substring(i+1).toInt()*10); return;}
		if (var.equals(F("anf"))) {set_anf(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("anf_level"))) {set_anf_level(msg.substring(i+1).toInt()); return;} 
		if (var.equals(F("nr"))) {set_nr(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("nr_level"))) {set_nr_level(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("nb"))) {set_nb(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("nb_level"))) {set_nb_level(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("wnb"))) {set_wnb(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("wnb_level"))) {set_wnb_level(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("apf"))) {set_apf(msg.substring(i+1).toInt()); return;} 
		if (var.equals(F("apf_level"))) {set_apf_level(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("diversity"))) {set_diversity(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("diversity_parent"))) {set_diversity_parent(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("diversity_child"))) {set_diversity_child(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("diversity_index"))) {set_diversity_index(msg.substring(i+1).toInt()); return;}
		if (var.equals(F("ant_list"))) {set_ant_list(msg.substring(i+1)); return;}
		if (var.equals(F("rxant"))) {set_rxant(msg.substring(i+1)); return;}
		if (var.equals(F("mode"))) {set_mode(msg.substring(i+1)); return; }
		if (var.equals(F("step_list"))) {set_step_list(msg.substring(i+1)); return;}
		if (var.equals(F("agc_mode"))) {set_agc_mode(msg.substring(i+1)); return;}
		if (var.equals(F("txant"))) {set_txant(msg.substring(i+1)); return;}
		if (var.equals(F("play"))) {set_play(msg.substring(i+1)); return;} 

	}
}

void Slice::set_sliceId(int newval) {
	sliceId=newval;
}

void Slice::set_in_use(int newval) {
	if (newval!=in_use) {
		in_use=newval;
		upd_in_use=true;
	}
}

void Slice::set_RF_frequency(int newval) {
	if (newval!=RF_frequency) {
		RF_frequency=newval;
		upd_RF_frequency=true;
	}
}

void Slice::set_rit_on(int newval) {
	if (newval!=rit_on) {
		rit_on=newval;
		upd_rit_on=true;
	}
}

void Slice::set_rit_freq(int newval) {
	if (newval!=rit_freq) {
		rit_freq=newval;
		upd_rit_freq=true;
	}
}

void Slice::set_xit_on(int newval) {
	if (newval!=xit_on) {
		xit_on=newval;
		upd_xit_on=true;
	}
}

void Slice::set_xit_freq(int newval) {
	if (newval!=xit_freq) {
		xit_freq=newval;
		upd_xit_freq=true;
	}
}

void Slice::set_wide(int newval) {
	if (newval!=wide) {
		wide=newval;
		upd_wide=true;
	}
}

void Slice::set_filter_lo(int newval) {
	if (newval!=filter_lo) {
		filter_lo=newval;
		upd_filter_lo=true;
	}
}

void Slice::set_filter_hi(int newval) {
	if (newval!=filter_hi) {
		filter_hi=newval;
		upd_filter_hi=true;
	}
}

void Slice::set_step(int newval) {
    if (newval!=step) {
		step=newval;
		upd_step=true;
	}
}

void Slice::set_agc_threshold(int newval) {
	if (newval!=agc_threshold) {
		agc_threshold=newval;
		upd_agc_threshold=true;
	}
}

void Slice::set_agc_off_level(int newval) {
	if (newval!=agc_off_level) {
		agc_off_level=newval;
		upd_agc_off_level=true;
	}
}

void Slice::set_pan(int newval) {
	if (newval!=pan) {
		pan=newval;
		upd_pan=true;
	}
}

void Slice::set_loopa(int newval) {
	if (newval!=loopa) {
		loopa=newval;
		upd_loopa=true;
	}
}

void Slice::set_loopb(int newval) {
	if (newval!=loopb) {
		loopb=newval;
		upd_loopb=true;
	}
}

void Slice::set_qsk(int newval) {
	if (newval!=qsk) {
		qsk=newval;
		upd_qsk=true;
	}
}

void Slice::set_dax(int newval) {
	if (newval!=dax) {
		dax=newval;
		upd_dax=true;
	}
}

void Slice::set_dax_clients(int newval) {
	if (newval!=dax_clients) {
		dax_clients=newval;
		upd_dax_clients=true;
	}
}

void Slice::set_lock(int newval) {
	if (newval!=lock) {
		lock=newval;
		upd_lock=true;
	}
}

void Slice::set_tx(int newval) {
	if (newval!=tx) {
		tx=newval;
		upd_tx=true;
	}
}

void Slice::set_dax_tx(int newval) {
	if (newval!=dax_tx) {
		dax_tx=newval;
		upd_dax_tx=true;
	}
}

void Slice::set_active(int newval) {
	if (newval!=active) {
		active=newval;
		upd_active=true;
	}
}

void Slice::set_audio_gain(int newval) {
	if (newval!=audio_gain) {
		audio_gain=newval;
		upd_audio_gain=true;
	}
}

void Slice::set_audio_pan(int newval) {
	if (newval!=audio_pan) {
		audio_pan=newval;
		upd_audio_pan=true;
	}
}

void Slice::set_audio_mute(int newval) {
	if (newval!=audio_mute) {
		audio_mute=newval;
		upd_audio_mute=true;
	}
}

void Slice::set_record(int newval) {
	if (newval!=record) {
		record=newval;
		upd_record=true;
	}
}

void Slice::set_record_time(int newval) {
	if (newval!=record_time) {
		record_time=newval;
		upd_record_time=true;
	}
}

void Slice::set_anf(int newval) {
	if (newval!=anf) {
		anf=newval;
		upd_anf=true;
	}
}

void Slice::set_anf_level(int newval) {
	if (newval!=anf_level) {
		anf_level=newval;
		upd_anf_level=true;
	}
}

void Slice::set_nr(int newval) {
	if (newval!=nr) {
		nr=newval;
		upd_nr=true;
	}
}

void Slice::set_nr_level(int newval) {
	if (newval!=nr_level) {
		nr_level=newval;
		upd_nr_level=true;
	}
}

void Slice::set_nb(int newval) {
	if (newval!=nb) {
		nb=newval;
		upd_nb=true;
	}
}

void Slice::set_nb_level(int newval) {
	if (newval!=nb_level) {
		nb_level=newval;
		upd_nb_level=true;
	}
}

void Slice::set_wnb(int newval) {
	if (newval!=wnb) {
		wnb=newval;
		upd_wnb=true;
	}
}

void Slice::set_wnb_level(int newval) {
	if (newval!=wnb_level) {
		wnb_level=newval;
		upd_wnb_level=true;
	}
}

void Slice::set_apf(int newval) {
	if (newval!=apf) {
		apf=newval;
		upd_apf=true;
	}
}

void Slice::set_apf_level(int newval) {
	if (newval!=apf_level) {
		apf_level=newval;
		upd_apf_level=true;
	}
}

void Slice::set_diversity(int newval) {
	if (newval!=diversity) {
		diversity=newval;
		upd_diversity=true;
	}
}

void Slice::set_diversity_parent(int newval) {
	if (newval!=diversity_parent) {
		diversity_parent=newval;
		upd_diversity_parent=true;
	}
}

void Slice::set_diversity_child(int newval) {
	if (newval!=diversity_child) {
		diversity_child=newval;
		upd_diversity_child=true;
	}
}

void Slice::set_diversity_index(int newval) {
	if (newval!=diversity_index) {
		diversity_index=newval;
		upd_diversity_index=true;
	}
}

void Slice::set_filter_shift(int newval) {
	if (newval!=filter_shift) {
		filter_shift=newval;
		upd_filter_shift=true;
	}
}

void Slice::set_filter_width(int newval) {
	if (newval!=filter_width) {
		filter_width=newval;
		upd_filter_width=true;
	}
}

void Slice::set_rxant(String newval) {
	if (!newval.equals(rxant)) {
		rxant=newval;
		upd_rxant=true;
	}
}

void Slice::set_mode(String newval) {
	if (!newval.equals(mode)) {
		previousMode=mode;
		mode=newval;
		upd_mode=true;
	}
}

void Slice::set_step_list(String newval) {
    if (!newval.equals(step_list)) {
		step_list=newval;
		upd_step_list=true;
	}
}

void Slice::set_agc_mode(String newval) {
	if (!newval.equals(agc_mode)) {
		agc_mode=newval;
		upd_agc_mode=true;
	}
}

void Slice::set_txant(String newval) {
	if (!newval.equals(txant)) {
		txant=newval;
		upd_txant=true;
	}
}

void Slice::set_play(String newval) {
	if (!newval.equals(play)) {
		play=newval;
		upd_play=true;
	}
}

void Slice::set_ant_list(String newval) {
	if (!newval.equals(ant_list)) {
		ant_list=newval;
		upd_ant_list=true;
	}
}

void Slice::fireEvents() {

	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;
		
		- la proprietà updated deve diventare privata
	*/

	if ((upd_in_use) && (do_in_use_event!=NULL)) {
		do_in_use_event(sliceId); 
		upd_in_use=false; 
	}
	
	if ((upd_RF_frequency) && (do_RF_frequency_event!=NULL)) {
			do_RF_frequency_event(sliceId); 
			upd_RF_frequency=false; 
	}
	
	if ((upd_rit_on) && (do_rit_on_event!=NULL)) {
			do_rit_on_event(sliceId); 
			upd_rit_on=false; 
	}
	
	if ((upd_rit_freq) && (do_rit_freq_event!=NULL)) {
			do_rit_freq_event(sliceId); 
			upd_rit_freq=false; 
	}
	
	if ((upd_xit_on) && (do_xit_on_event!=NULL)) {
			do_xit_on_event(sliceId); 
			upd_xit_on=false; 
	}
	
	if ((upd_xit_freq) && (do_xit_freq_event!=NULL)) {
			do_xit_freq_event(sliceId); 
			upd_xit_freq=false; 
	}
	
	if ((upd_wide) && (do_wide_event!=NULL)) {
			do_wide_event(sliceId); 
			upd_wide=false; 
	}
	
	if ((upd_filter_lo) && (do_filter_lo_event!=NULL)) {
			do_filter_lo_event(sliceId); 
			upd_filter_lo=false; 
	}
	
	if ((upd_filter_hi) && (do_filter_hi_event!=NULL)) {
			do_filter_hi_event(sliceId); 
			upd_filter_hi=false; 
	}
	
	if ((upd_step) && (do_step_event!=NULL)) {
			do_step_event(sliceId); 
			upd_step=false; 
	}
	
	if ((upd_agc_threshold) && (do_agc_threshold_event!=NULL)) {
			do_agc_threshold_event(sliceId); 
			upd_agc_threshold=false; 
	}
	
	if ((upd_agc_off_level) && (do_agc_off_level_event!=NULL)) {
			do_agc_off_level_event(sliceId); 
			upd_agc_off_level=false; 
	}
	
	if ((upd_pan) && (do_pan_event!=NULL)) {
			do_pan_event(sliceId); 
			upd_pan=false; 
	}
	
	if ((upd_loopa) && (do_loopa_event!=NULL)) {
			do_loopa_event(sliceId); 
			upd_loopa=false; 
	}
	
	if ((upd_loopb) && (do_loopb_event!=NULL)) {
			do_loopb_event(sliceId); 
			upd_loopb=false; 
	}
	
	if ((upd_qsk) && (do_qsk_event!=NULL)) {
			do_qsk_event(sliceId); 
			upd_qsk=false; 
	}
	
	if ((upd_dax) && (do_dax_event!=NULL)) {
			do_dax_event(sliceId); 
			upd_dax=false; 
	}
	
	if ((upd_dax_clients) && (do_dax_clients_event!=NULL)) {
			do_dax_clients_event(sliceId); 
			upd_dax_clients=false; 
	}
	
	if ((upd_lock) && (do_lock_event!=NULL)) {
			do_lock_event(sliceId); 
			upd_lock=false; 
	}
	
	if ((upd_tx) && (do_tx_event!=NULL)) {
			do_tx_event(sliceId); 
			upd_tx=false; 
	}
	
	if ((upd_dax_tx) && (do_dax_tx_event!=NULL)) {
			do_dax_tx_event(sliceId); 
			upd_dax_tx=false; 
	}
	
	if ((upd_active) && (do_active_event!=NULL)) {
			do_active_event(sliceId); 
			upd_active=false; 
	}
	
	if ((upd_audio_gain) && (do_audio_gain_event!=NULL)) {
			do_audio_gain_event(sliceId); 
			upd_audio_gain=false; 
	}
	
	if ((upd_audio_pan) && (do_audio_pan_event!=NULL)) {
			do_audio_pan_event(sliceId); 
			upd_audio_pan=false; 
	}
	
	if ((upd_audio_mute) && (do_audio_mute_event!=NULL)) {
			do_audio_mute_event(sliceId); 
			upd_audio_mute=false; 
	}
	
	if ((upd_record) && (do_record_event!=NULL)) {
			do_record_event(sliceId); 
			upd_record=false; 
	}
	
	if ((upd_record_time) && (do_record_time_event!=NULL)) {
			do_record_time_event(sliceId); 
			upd_record_time=false; 
	}
	
	if ((upd_anf) && (do_anf_event!=NULL)) {
			do_anf_event(sliceId); 
			upd_anf=false; 
	}
	
	if ((upd_anf_level) && (do_anf_level_event!=NULL)) {
			do_anf_level_event(sliceId); 
			upd_anf_level=false; 
	}
	
	if ((upd_nr) && (do_nr_event!=NULL)) {
			do_nr_event(sliceId); 
			upd_nr=false; 
	}
	
	if ((upd_nr_level) && (do_nr_level_event!=NULL)) {
			do_nr_level_event(sliceId); 
			upd_nr_level=false; 
	}
	
	if ((upd_nb) && (do_nb_event!=NULL)) {
			do_nb_event(sliceId); 
			upd_nb=false; 
	}
	
	if ((upd_nb_level) && (do_nb_level_event!=NULL)) {
			do_nb_level_event(sliceId); 
			upd_nb_level=false; 
	}

	if ((upd_wnb) && (do_wnb_event!=NULL)) {
			do_wnb_event(sliceId); 
			upd_wnb=false; 
	}
	
	if ((upd_wnb_level) && (do_wnb_level_event!=NULL)) {
			do_wnb_level_event(sliceId); 
			upd_wnb_level=false; 
	}
	
	if ((upd_apf) && (do_apf_event!=NULL)) {
			do_apf_event(sliceId); 
			upd_apf=false; 
	}
	
	if ((upd_apf_level) && (do_apf_level_event!=NULL)) {
			do_apf_level_event(sliceId); 
			upd_apf_level=false; 
	}
	
	if ((upd_diversity) && (do_diversity_event!=NULL)) {
			do_diversity_event(sliceId); 
			upd_diversity=false; 
	}
	
	if ((upd_diversity_parent) && (do_diversity_parent_event!=NULL)) {
			do_diversity_parent_event(sliceId); 
			upd_diversity_parent=false; 
	}
	
	if ((upd_diversity_child) && (do_diversity_child_event!=NULL)) {
				do_diversity_child_event(sliceId); 
				upd_diversity_child=false; 
	}
	
	if ((upd_diversity_index) && (do_diversity_index_event!=NULL)) {
			do_diversity_index_event(sliceId); 
			upd_diversity_index=false; 
	}
	
	if ((upd_filter_shift) && (do_filter_shift_event!=NULL)) {
			do_filter_shift_event(sliceId); 
			upd_filter_shift=false; 
	}
	
	if ((upd_filter_width) && (do_filter_width_event!=NULL)) {
			do_filter_width_event(sliceId); 
			upd_filter_width=false; 
	}
	
	if ((upd_rxant) && (do_rxant_event!=NULL)) {
			do_rxant_event(sliceId); 
			upd_rxant=false; 
	}
	
	if ((upd_mode) && (do_mode_event!=NULL)) {
			do_mode_event(sliceId); 
			upd_mode=false; 
	}
	
	if ((upd_step_list) && (do_step_list_event!=NULL)) {
			do_step_list_event(sliceId); 
			upd_step_list=false; 
	}
	
	if ((upd_agc_mode) && (do_agc_mode_event!=NULL)) {
			do_agc_mode_event(sliceId); 
			upd_agc_mode=false; 
	}
	
	if ((upd_txant) && (do_txant_event!=NULL)) {
			do_txant_event(sliceId); 
			upd_txant=false; 
	}
	
	if ((upd_play) && (do_play_event!=NULL)) {
			do_play_event(sliceId); 
			upd_play=false; 
	}
	
	if ((upd_ant_list) && (do_ant_list_event!=NULL)) {
			do_ant_list_event(sliceId); 
			upd_ant_list=false; 
	}		
	
}

void Slice::attach_in_use_event(eventHandlerArrFunction _eventHandler) {
	do_in_use_event=_eventHandler;
}

void Slice::attach_RF_frequency_event(eventHandlerArrFunction _eventHandler) {
	do_RF_frequency_event=_eventHandler;
}

void Slice::attach_rit_on_event(eventHandlerArrFunction _eventHandler) {
	do_rit_on_event=_eventHandler;
}

void Slice::attach_rit_freq_event(eventHandlerArrFunction _eventHandler) {
	do_rit_freq_event=_eventHandler;
}

void Slice::attach_xit_on_event(eventHandlerArrFunction _eventHandler) {
	do_xit_on_event=_eventHandler;
}

void Slice::attach_xit_freq_event(eventHandlerArrFunction _eventHandler) {
	do_xit_freq_event=_eventHandler;
}

void Slice::attach_wide_event(eventHandlerArrFunction _eventHandler) {
	do_wide_event=_eventHandler;
}

void Slice::attach_filter_lo_event(eventHandlerArrFunction _eventHandler) {
	do_filter_lo_event=_eventHandler;
}

void Slice::attach_filter_hi_event(eventHandlerArrFunction _eventHandler) {
	do_filter_hi_event=_eventHandler;
}

void Slice::attach_step_event(eventHandlerArrFunction _eventHandler) {
	do_step_event=_eventHandler;
}

void Slice::attach_agc_threshold_event(eventHandlerArrFunction _eventHandler) {
	do_agc_threshold_event=_eventHandler;
}

void Slice::attach_agc_off_level_event(eventHandlerArrFunction _eventHandler) {
	do_agc_off_level_event=_eventHandler;
}

void Slice::attach_pan_event(eventHandlerArrFunction _eventHandler) {
	do_pan_event=_eventHandler;
}

void Slice::attach_loopa_event(eventHandlerArrFunction _eventHandler) {
	do_loopa_event=_eventHandler;
}

void Slice::attach_loopb_event(eventHandlerArrFunction _eventHandler) {
	do_loopb_event=_eventHandler;
}

void Slice::attach_qsk_event(eventHandlerArrFunction _eventHandler) {
	do_qsk_event=_eventHandler;
}

void Slice::attach_dax_event(eventHandlerArrFunction _eventHandler) {
	do_dax_event=_eventHandler;
}

void Slice::attach_dax_clients_event(eventHandlerArrFunction _eventHandler) {
	do_dax_clients_event=_eventHandler;
}

void Slice::attach_lock_event(eventHandlerArrFunction _eventHandler) {
	do_lock_event=_eventHandler;
}

void Slice::attach_tx_event(eventHandlerArrFunction _eventHandler) {
	do_tx_event=_eventHandler;
}

void Slice::attach_dax_tx_event(eventHandlerArrFunction _eventHandler) {
	do_dax_tx_event=_eventHandler;
}

void Slice::attach_active_event(eventHandlerArrFunction _eventHandler) {
	do_active_event=_eventHandler;
}

void Slice::attach_audio_gain_event(eventHandlerArrFunction _eventHandler) {
	do_audio_gain_event=_eventHandler;
}

void Slice::attach_audio_pan_event(eventHandlerArrFunction _eventHandler) {
	do_audio_pan_event=_eventHandler;
}

void Slice::attach_audio_mute_event(eventHandlerArrFunction _eventHandler) {
	do_audio_mute_event=_eventHandler;
}

void Slice::attach_record_event(eventHandlerArrFunction _eventHandler) {
	do_record_event=_eventHandler;
}

void Slice::attach_record_time_event(eventHandlerArrFunction _eventHandler) {
	do_record_time_event=_eventHandler;
}

void Slice::attach_anf_event(eventHandlerArrFunction _eventHandler) {
	do_anf_event=_eventHandler;
}

void Slice::attach_anf_level_event(eventHandlerArrFunction _eventHandler) {
	do_anf_level_event=_eventHandler;
}

void Slice::attach_nr_event(eventHandlerArrFunction _eventHandler) {
	do_nr_event=_eventHandler;
}

void Slice::attach_nr_level_event(eventHandlerArrFunction _eventHandler) {
	do_nr_level_event=_eventHandler;
}

void Slice::attach_nb_event(eventHandlerArrFunction _eventHandler) {
	do_nb_event=_eventHandler;
}

void Slice::attach_nb_level_event(eventHandlerArrFunction _eventHandler) {
	do_nb_level_event=_eventHandler;
}

void Slice::attach_wnb_event(eventHandlerArrFunction _eventHandler) {
	do_wnb_event=_eventHandler;
}

void Slice::attach_wnb_level_event(eventHandlerArrFunction _eventHandler) {
	do_wnb_level_event=_eventHandler;
}

void Slice::attach_apf_event(eventHandlerArrFunction _eventHandler) {
	do_apf_event=_eventHandler;
}

void Slice::attach_apf_level_event(eventHandlerArrFunction _eventHandler) {
	do_apf_level_event=_eventHandler;
}

void Slice::attach_diversity_event(eventHandlerArrFunction _eventHandler) {
	do_diversity_event=_eventHandler;
}

void Slice::attach_diversity_parent_event(eventHandlerArrFunction _eventHandler) {
	do_diversity_parent_event=_eventHandler;
}

void Slice::attach_diversity_child_event(eventHandlerArrFunction _eventHandler) {
	do_diversity_child_event=_eventHandler;
}

void Slice::attach_diversity_index_event(eventHandlerArrFunction _eventHandler) {
	do_diversity_index_event=_eventHandler;
}

void Slice::attach_filter_shift_event(eventHandlerArrFunction _eventHandler) {
	do_filter_shift_event=_eventHandler;
}

void Slice::attach_filter_width_event(eventHandlerArrFunction _eventHandler) {
	do_filter_width_event=_eventHandler;
}

void Slice::attach_rxant_event(eventHandlerArrFunction _eventHandler) {
	do_rxant_event=_eventHandler;
}

void Slice::attach_mode_event(eventHandlerArrFunction _eventHandler) {
	do_mode_event=_eventHandler;
}

void Slice::attach_step_list_event(eventHandlerArrFunction _eventHandler) {
	do_step_list_event=_eventHandler;
}

void Slice::attach_agc_mode_event(eventHandlerArrFunction _eventHandler) {
	do_agc_mode_event=_eventHandler;
}

void Slice::attach_txant_event(eventHandlerArrFunction _eventHandler) {
	do_txant_event=_eventHandler;
}

void Slice::attach_play_event(eventHandlerArrFunction _eventHandler) {
	do_play_event=_eventHandler;
}

void Slice::attach_ant_list_event(eventHandlerArrFunction _eventHandler) {
	do_ant_list_event=_eventHandler;
}


void Slice::updateObject(int objectId,int value){
    Serial.print("***********************************    objectId: "); Serial.println(objectId);	
    switch(objectId) {
	 	case SLICE_AUDIO_GAIN:
		     audio_gain=value;
	 		 break;
	 	case SLICE_AUDIO_PAN:
		     audio_pan=value;
	 		 break;
	 	case SLICE_AGC_THRESHOLD:
		     agc_threshold=value;
	 		 break;
		case SLICE_AGC_OFF_LEVEL:	 
		     agc_off_level=value;
	 		 break;
		case SLICE_WNB_LEVEL:
		     wnb_level=value;
	 		 break;
		case SLICE_NB_LEVEL:
		     nb_level=value;
	 		 break;
		case SLICE_NR_LEVEL:
		     nr_level=value;
	 		 break;
		case SLICE_APF_LEVEL:
		     apf_level=value;
	 		 break;
		case SLICE_ANF_LEVEL:
		     anf_level=value;
	 		 break;
		case SLICE_RIT_FREQ:
		     rit_freq=value;
	 		 break;
		case SLICE_XIT_FREQ:
		     xit_freq=value;
	 		 break;
		default:
			 Serial.print(F("Slice::updateObject - Unhandled id:")); Serial.println(objectId);
	}
	updated=true;
}

String Slice::getAgcTMode(){
    String s=agc_mode;
	if (s.length()==3) s=s+" ";
	for (int i = 0; i < s.length(); i++)
		s[i]=toupper(s[i]);
	
	return s;
}

/*
void Slice::setFilterLow(int value) {
	if (filter_lo+value<filter_hi) {
    	set_filter_lo(filter_lo+value);
		calcShiftWidthValue();	
	}
}*/
 
/*
void Slice::setFilterHigh(int value) {
		if (filter_hi+value>filter_lo) {
			set_filter_hi(filter_hi+value);
			calcShiftWidthValue();
		}
}*/

/*
void Slice::setFilterShift(int value) {
	set_filter_shift(filter_shift+value);
	calcHighLowValues();
}*/

/*
void Slice::setFilterWidth(int value) {
	set_filter_width(filter_width+value);
	calcHighLowValues();
}*/


void Slice::calcHighLowValues(){
     set_filter_lo(filter_shift-filter_width/2);
	 set_filter_hi(filter_shift+filter_width/2);    	
}


void Slice::calcShiftWidthValue(){
	set_filter_width(filter_hi-filter_lo);
	set_filter_shift(filter_lo+filter_width/2);	 
}
	
/*	
void Slice::setIntMode(String m) {
	//Serial.print(F("Mode:"));Serial.println(mode);
	if (m.equals(F("LSB"))) intMode=LSB;
	else if (m.equals(F("USB"))) intMode=USB;
	else if (m.equals(F("AM"))) intMode=AM;
	else if (m.equals(F("CW"))) intMode=CW;
	else if (m.equals(F("DIGL"))) intMode=DIGL;
	else if (m.equals(F("DIGU"))) intMode=DIGU;
	else if (m.equals(F("SAM"))) intMode=SAM_;
	else if (m.equals(F("FM"))) intMode=FM;
	else if (m.equals(F("NFM"))) intMode=NFM;
	else if (m.equals(F("DFM"))) intMode=DFM;
}
*/

/*
int Slice::getBand() {

	int b=(int)RF_frequency/1000000;
	switch (b) {
		case 1:
				  b=160;
				  break;
		case 3:
				  b=80;
				  break;
		case 5:
				  b=60;
				  break;
		case 7:
				  b=40;
				  break;
		case 10:
				  b=30;
				  break;
		case 14:
				  b=20;
				  break;
		case 18:
				  b=17;
				  break;
		case 21:
				  b=15;
				  break;
		case 24:
				  b=12;
				  break;
		case 28:
				  b=10;
				  break;
		case 29:
				  b=10;
				  break;
		case 50:
				  b=6;
				  break;
		case 51:
				  b=6;
				  break;
		default:
				  b=-1;
	}
	return b;
}
*/

int Slice::getParentPan() {
	return pan%40000000;
}

String Slice::getFilterWidthStr() {
	char res[5]; 
	if (filter_width<1000) sprintf(res,"%4d ",filter_width); 
	if (filter_width>=1000 && filter_width<10000) sprintf(res,"%.1fK ",(float)filter_width/1000); 
	if (filter_width>=10000) sprintf(res,"%.1fK",(float)filter_width/1000); 
	
	return String(res);
}