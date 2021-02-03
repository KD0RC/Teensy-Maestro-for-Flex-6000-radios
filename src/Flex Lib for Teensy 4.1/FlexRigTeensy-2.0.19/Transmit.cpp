/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "Transmit.h"
Transmit::Transmit() {
	upd_freq=true;
	upd_lo=true;
	upd_hi=true;
	upd_rfpower=true;
	upd_tunepower=true; 
	upd_am_carrier_level=true; 
	upd_vox_enable=true;
	upd_vox_level=true; 
	upd_vox_delay=true; 
	upd_mic_level=true;
	upd_mic_boost=true; 
	upd_mic_bias=true; 
	upd_mic_acc=true; 
	upd_compander=true; 
	upd_compander_level=true; 
	upd_dax=true; 
	upd_pitch=true; 
	upd_speed=true; 
	upd_iambic=true;
	upd_iambic_mode=true; 
	upd_cwl_enabled=true; 
	upd_swap_paddles=true; 
	upd_break_in=true;
	upd_break_in_delay=true;
	upd_sidetone=true; 
	upd_monitor=true; 
	upd_sb_monitor=true; 
	upd_mon_gain_cw=true; 
	upd_mon_gain_sb=true; 
	upd_mon_pan_cw=true;
	upd_mon_pan_sb=true; 
	upd_tune=true; 
	upd_met_in_rx=true;
	upd_hwalc_enabled=true; 
	upd_inhibit=true;
	upd_speech_processor_enable=true;
	upd_speech_processor_level=true; 
	upd_show_tx_in_waterfall=true;
	upd_mic_selection=true;
	
	updated=false;
}

void Transmit::updateStatus(String msg) {

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
	Serial.println(freq);			
	Serial.println(lo);			
	Serial.println(hi);			
	Serial.println(rfpower);			
	Serial.println(tunepower);		
	Serial.println(am_carrier_level);	
	Serial.println(vox_enable);		
	Serial.println(vox_level);		
	Serial.println(vox_delay);		
	Serial.println(mic_level);		
	Serial.println(mic_selection);	
	Serial.println(mic_boost);		
	Serial.println(mic_bias);		
	Serial.println(mic_acc);			
	Serial.println(compander);		
	Serial.println(compander_level);		
	Serial.println(dax);			
	Serial.println(pitch);			
	Serial.println(speed);			
	Serial.println(iambic);			
	Serial.println(iambic_mode);		
	Serial.println(cwl_enabled);		
	Serial.println(swap_paddles);		
	Serial.println(break_in);		
	Serial.println(break_in_delay);		
	Serial.println(sidetone);		
	Serial.println(monitor);			
	Serial.println(mon_gain_cw);		
	Serial.println(mon_gain_sb);		
	Serial.println(mon_pan_cw);		
	Serial.println(mon_pan_sb);		
	Serial.println(tune);			
	Serial.println(met_in_rx);		
	Serial.println(hwalc_enabled);		
	Serial.println(inhibit);			
	Serial.println(speech_processor_enable);	
	Serial.println(speech_processor_level);	
	Serial.println(show_tx_in_waterfall);	
	*/

}

void Transmit::setValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++");
		//Serial.print(var); Serial.print(F("="));Serial.println(msg.substring(i+1));
		//Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++");
		if (var.equals(F("freq"))) { 
			set_freq(msg.substring(i+1).toFloat()*1000000); 
			return; 
		}
		if (var.equals(F("lo"))) { 
			set_lo(msg.substring(i+1).toInt()); 
			return; 
		}
		if (var.equals(F("hi"))) { 
			set_hi(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("rfpower"))) { 
			set_rfpower(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("tunepower"))) { 
			set_tunepower(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("am_carrier_level"))) { 
			set_am_carrier_level(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("vox_enable"))) { 
			set_vox_enable(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("vox_level"))) { 
			set_vox_level(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("vox_delay"))) { 
			set_vox_delay(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("mic_level"))) { 
			set_mic_level(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("mic_boost"))) { 
			set_mic_boost(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("mic_bias"))) { 
			set_mic_bias(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("mic_acc"))) { 
			set_mic_acc(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("compander"))) { 
			set_compander(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("compander_level"))) { 
			set_compander_level(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("dax"))) { 
			set_dax(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("pitch"))) { 
			set_pitch(msg.substring(i+1).toInt()); 
			return; 
		} 
		if (var.equals(F("iambic"))) { 
			set_iambic(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("iambic_mode"))) { 
			set_iambic_mode(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("cwl_enabled"))) { 
			set_cwl_enabled(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("swap_paddles"))) { 
			set_swap_paddles(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("break_in"))) { 
			set_break_in(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("break_in_delay"))) { 
			set_break_in_delay(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("sidetone"))) { 
			set_sidetone(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("monitor"))) { 
			set_monitor(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("sb_monitor"))) { 
			set_sb_monitor(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("mon_gain_cw"))) { 
			set_mon_gain_cw(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("mon_gain_sb"))) { 
			set_mon_gain_sb(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("mon_pan_cw"))) { 
			set_mon_pan_cw(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("mon_pan_sb"))) { 
			set_mon_pan_sb(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("tune"))) { 
			set_tune(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("met_in_rx"))) { 
			set_met_in_rx(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("hwalc_enabled"))) { 
			set_hwalc_enabled(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("inhibit"))) { 
			set_inhibit(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("speech_processor_enable"))) { 
			set_speech_processor_enable(msg.substring(i+1).toInt()); 
			return; 
		} 	
		if (var.equals(F("speech_processor_level"))) { 
			set_speech_processor_level(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("show_tx_in_waterfall"))) { 
			set_show_tx_in_waterfall(msg.substring(i+1).toInt()); 
			return;  
		}	
		if (var.equals(F("mic_selection"))) { 
			set_mic_selection(msg.substring(i+1)); 
			return; 
		} 	

	}
}

void Transmit::fireEvents() {

	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;
		
		- la proprietà updated deve diventare privata
	*/

	if ((upd_freq) && (do_freq_event!=NULL)) {
		do_freq_event(); 
		upd_freq=false; 
	}
	
		if ((upd_lo) && (do_lo_event!=NULL)) {
		do_lo_event(); 
		upd_lo=false; 
	}
	
	if ((upd_hi) && (do_hi_event!=NULL)) {
			do_hi_event(); 
			upd_hi=false; 
	}
	
	if ((upd_rfpower) && (do_rfpower_event!=NULL)) {
			do_rfpower_event(); 
			upd_rfpower=false; 
	}
	
	if ((upd_tunepower) && (do_tunepower_event!=NULL)) {
			do_tunepower_event(); 
			upd_tunepower=false; 
	}
	
	if ((upd_am_carrier_level) && (do_am_carrier_level_event!=NULL)) {
			do_am_carrier_level_event(); 
			upd_am_carrier_level=false; 
	}
	
	if ((upd_vox_enable) && (do_vox_enable_event!=NULL)) {
			do_vox_enable_event(); 
			upd_vox_enable=false; 
	}
	
	if ((upd_vox_level) && (do_vox_level_event!=NULL)) {
			do_vox_level_event(); 
			upd_vox_level=false; 
	}
	
	if ((upd_vox_delay) && (do_vox_delay_event!=NULL)) {
			do_vox_delay_event(); 
			upd_vox_delay=false; 
	}
	
	if ((upd_mic_level) && (do_mic_level_event!=NULL)) {
			do_mic_level_event(); 
			upd_mic_level=false; 
	}
	
	if ((upd_mic_boost) && (do_mic_boost_event!=NULL)) {
			do_mic_boost_event(); 
			upd_mic_boost=false; 
	}
	
	if ((upd_mic_bias) && (do_mic_bias_event!=NULL)) {
			do_mic_bias_event(); 
			upd_mic_bias=false; 
	}
	
	if ((upd_mic_acc) && (do_mic_acc_event!=NULL)) {
			do_mic_acc_event(); 
			upd_mic_acc=false; 
	}
	
	if ((upd_compander) && (do_compander_event!=NULL)) {
			do_compander_event(); 
			upd_compander=false; 
	}
	
	if ((upd_compander_level) && (do_compander_level_event!=NULL)) {
			do_compander_level_event(); 
			upd_compander_level=false; 
	}
	
	if ((upd_dax) && (do_dax_event!=NULL)) {
			do_dax_event(); 
			upd_dax=false; 
	}
	
	if ((upd_pitch) && (do_pitch_event!=NULL)) {
			do_pitch_event(); 
			upd_pitch=false; 
	}
	
	if ((upd_speed) && (do_speed_event!=NULL)) {
			do_speed_event(); 
			upd_speed=false; 
	}
	
	if ((upd_iambic) && (do_iambic_event!=NULL)) {
			do_iambic_event(); 
			upd_iambic=false; 
	}
	
	if ((upd_iambic_mode) && (do_iambic_mode_event!=NULL)) {
			do_iambic_mode_event(); 
			upd_iambic_mode=false; 
	}
	
	if ((upd_cwl_enabled) && (do_cwl_enabled_event!=NULL)) {
			do_cwl_enabled_event(); 
			upd_cwl_enabled=false; 
	}
	
	if ((upd_swap_paddles) && (do_swap_paddles_event!=NULL)) {
			do_swap_paddles_event(); 
			upd_swap_paddles=false; 
	}
	
	if ((upd_break_in) && (do_break_in_event!=NULL)) {
			do_break_in_event(); 
			upd_break_in=false; 
	}
	
	if ((upd_break_in_delay) && (do_break_in_delay_event!=NULL)) {
			do_break_in_delay_event(); 
			upd_break_in_delay=false; 
	}
	
	if ((upd_sidetone) && (do_sidetone_event!=NULL)) {
			do_sidetone_event(); 
			upd_sidetone=false; 
	}
	
	if ((upd_monitor) && (do_monitor_event!=NULL)) {
			do_monitor_event(); 
			upd_monitor=false; 
	}
	
	if ((upd_sb_monitor) && (do_sb_monitor_event!=NULL)) {
			do_sb_monitor_event(); 
			upd_sb_monitor=false; 
	}
	
	if ((upd_mon_gain_cw) && (do_mon_gain_cw_event!=NULL)) {
			do_mon_gain_cw_event(); 
			upd_mon_gain_cw=false; 
	}
	
	if ((upd_mon_gain_sb) && (do_mon_gain_sb_event!=NULL)) {
			do_mon_gain_sb_event(); 
			upd_mon_gain_sb=false; 
	}
	
	if ((upd_mon_pan_cw) && (do_mon_pan_cw_event!=NULL)) {
			do_mon_pan_cw_event(); 
			upd_mon_pan_cw=false; 
	}
	
	if ((upd_mon_pan_sb) && (do_mon_pan_sb_event!=NULL)) {
			do_mon_pan_sb_event(); 
			upd_mon_pan_sb=false; 
	}
	
	if ((upd_tune) && (do_tune_event!=NULL)) {
			do_tune_event(); 
			upd_tune=false; 
	}
	
	if ((upd_met_in_rx) && (do_met_in_rx_event!=NULL)) {
			do_met_in_rx_event(); 
			upd_met_in_rx=false; 
	}
	
	if ((upd_hwalc_enabled) && (do_hwalc_enabled_event!=NULL)) {
			do_hwalc_enabled_event(); 
			upd_hwalc_enabled=false; 
	}
	
	if ((upd_inhibit) && (do_inhibit_event!=NULL)) {
			do_inhibit_event(); 
			upd_inhibit=false; 
	}
	
	if ((upd_speech_processor_enable) && (do_speech_processor_enable_event!=NULL)) {
			do_speech_processor_enable_event(); 
			upd_speech_processor_enable=false; 
	}
	
	if ((upd_speech_processor_level) && (do_speech_processor_level_event!=NULL)) {
			do_speech_processor_level_event(); 
			upd_speech_processor_level=false; 
	}
	
	if ((upd_show_tx_in_waterfall) && (do_show_tx_in_waterfall_event!=NULL)) {
			do_show_tx_in_waterfall_event(); 
			upd_show_tx_in_waterfall=false; 
	}
	
	if ((upd_mic_selection) && (do_mic_selection_event!=NULL)) {
			do_mic_selection_event(); 
			upd_mic_selection=false; 
	}
	
	
}


void Transmit::set_freq(int newval) {
	if (newval!=freq) {
		freq=newval;
		upd_freq=true;
	}
}

void Transmit::set_lo(int newval) {
	if (newval!=lo) {
		lo=newval;
		upd_lo=true;
	}
}

void Transmit::set_hi(int newval) {
	if (newval!=hi) {
		hi=newval;
		upd_hi=true;
	}
}

void Transmit::set_rfpower(int newval) {
	if (newval!=rfpower) {
		rfpower=newval;
		upd_rfpower=true;
	}
}

void Transmit::set_tunepower(int newval) {
	if (newval!=tunepower) {
		tunepower=newval;
		upd_tunepower=true;
	}
}

void Transmit::set_am_carrier_level(int newval) {
	if (newval!=am_carrier_level) {
		am_carrier_level=newval;
		upd_am_carrier_level=true;
	}
}

void Transmit::set_vox_enable(int newval) {
	if (newval!=vox_enable) {
		vox_enable=newval;
		upd_vox_enable=true;
	}
}

void Transmit::set_vox_level(int newval) {
	if (newval!=vox_level) {
		vox_level=newval;
		upd_vox_level=true;
	}
}

void Transmit::set_vox_delay(int newval) {
	if (newval!=vox_delay) {
		vox_delay=newval;
		upd_vox_delay=true;
	}
}

void Transmit::set_mic_level(int newval) {
	if (newval!=mic_level) {
		mic_level=newval;
		upd_mic_level=true;
	}
}

void Transmit::set_mic_boost(int newval) {
	if (newval!=mic_boost) {
		mic_boost=newval;
		upd_mic_boost=true;
	}
}

void Transmit::set_mic_bias(int newval) {
	if (newval!=mic_bias) {
		mic_bias=newval;
		upd_mic_bias=true;
	}
}

void Transmit::set_mic_acc(int newval) {
	if (newval!=mic_acc) {
		mic_acc=newval;
		upd_mic_acc=true;
	}
}

void Transmit::set_compander(int newval) {
	if (newval!=compander) {
		compander=newval;
		upd_compander=true;
	}
}

void Transmit::set_compander_level(int newval) {
	if (newval!=compander_level) {
		compander_level=newval;
		upd_compander_level=true;
	}
}

void Transmit::set_dax(int newval) {
	if (newval!=dax) {
		dax=newval;
		upd_dax=true;
	}
}

void Transmit::set_pitch(int newval) {
	if (newval!=pitch) {
		pitch=newval;
		upd_pitch=true;
	}
}

void Transmit::set_speed(int newval) {
	//Serial.print("newval "); Serial.println(newval);
	//Serial.print("speed "); Serial.println(speed);
	if (newval!=speed) {
		speed=newval;
		upd_speed=true;
	}
}

void Transmit::set_iambic(int newval) {
	if (newval!=iambic) {
		iambic=newval;
		upd_iambic=true;
	}
}

void Transmit::set_iambic_mode(int newval) {
	if (newval!=iambic_mode) {
		iambic_mode=newval;
		upd_iambic_mode=true;
	}
}

void Transmit::set_cwl_enabled(int newval) {
	if (newval!=cwl_enabled) {
		cwl_enabled=newval;
		upd_cwl_enabled=true;
	}
}

void Transmit::set_swap_paddles(int newval) {
	if (newval!=swap_paddles) {
		swap_paddles=newval;
		upd_swap_paddles=true;
	}
}

void Transmit::set_break_in(int newval) {
	if (newval!=break_in) {
		break_in=newval;
		upd_break_in=true;
	}
}

void Transmit::set_break_in_delay(int newval) {
	if (newval!=break_in_delay) {
		break_in_delay=newval;
		upd_break_in_delay=true;
	}
}

void Transmit::set_sidetone(int newval) {
	if (newval!=sidetone) {
		sidetone=newval;
		upd_sidetone=true;
	}
}

void Transmit::set_monitor(int newval) {
	if (newval!=monitor) {
		monitor=newval;
		upd_monitor=true;
	}
}

void Transmit::set_sb_monitor(int newval) {
	if (newval!=sb_monitor) {
		sb_monitor=newval;
		upd_sb_monitor=true;
	}
}

void Transmit::set_mon_gain_cw(int newval) {
	if (newval!=mon_gain_cw) {
		mon_gain_cw=newval;
		upd_mon_gain_cw=true;
	}
}

void Transmit::set_mon_gain_sb(int newval) {
	if (newval!=mon_gain_sb) {
		mon_gain_sb=newval;
		upd_mon_gain_sb=true;
	}
}

void Transmit::set_mon_pan_cw(int newval) {
	if (newval!=mon_pan_cw) {
		mon_pan_cw=newval;
		upd_mon_pan_cw=true;
	}
}

void Transmit::set_mon_pan_sb(int newval) {
	if (newval!=mon_pan_sb) {
		mon_pan_sb=newval;
		upd_mon_pan_sb=true;
	}
}

void Transmit::set_tune(int newval) {
	if (newval!=tune) {
		tune=newval;
		upd_tune=true;
	}
}

void Transmit::set_met_in_rx(int newval) {
	if (newval!=met_in_rx) {
		met_in_rx=newval;
		upd_met_in_rx=true;
	}
}

void Transmit::set_hwalc_enabled(int newval) {
	if (newval!=hwalc_enabled) {
		hwalc_enabled=newval;
		upd_hwalc_enabled=true;
	}
}

void Transmit::set_inhibit(int newval) {
	if (newval!=inhibit) {
		inhibit=newval;
		upd_inhibit=true;
	}
}

void Transmit::set_speech_processor_enable(int newval) {
	if (newval!=speech_processor_enable) {
		speech_processor_enable=newval;
		upd_speech_processor_enable=true;
	}
}

void Transmit::set_speech_processor_level(int newval) {
	if (newval!=speech_processor_level) {
		speech_processor_level=newval;
		upd_speech_processor_level=true;
	}
}

void Transmit::set_show_tx_in_waterfall(int newval) {
	if (newval!=show_tx_in_waterfall) {
		show_tx_in_waterfall=newval;
		upd_show_tx_in_waterfall=true;
	}
}

void Transmit::set_mic_selection(String newval) {
	if (!newval.equals(mic_selection)) {
			mic_selection=newval;
			upd_mic_selection=true;
	}
}

void Transmit::attach_freq_event(eventHandlerFunction _eventHandler) {
	do_freq_event=_eventHandler;
}

void Transmit::attach_lo_event(eventHandlerFunction _eventHandler) {
	do_lo_event=_eventHandler;
}

void Transmit::attach_hi_event(eventHandlerFunction _eventHandler) {
	do_hi_event=_eventHandler;
}

void Transmit::attach_rfpower_event(eventHandlerFunction _eventHandler) {
	do_rfpower_event=_eventHandler;
}

void Transmit::attach_tunepower_event(eventHandlerFunction _eventHandler) {
	do_tunepower_event=_eventHandler;
}

void Transmit::attach_am_carrier_level_event(eventHandlerFunction _eventHandler) {
	do_am_carrier_level_event=_eventHandler;
}

void Transmit::attach_vox_enable_event(eventHandlerFunction _eventHandler) {
	do_vox_enable_event=_eventHandler;
}

void Transmit::attach_vox_level_event(eventHandlerFunction _eventHandler) {
	do_vox_level_event=_eventHandler;
}

void Transmit::attach_vox_delay_event(eventHandlerFunction _eventHandler) {
	do_vox_delay_event=_eventHandler;
}

void Transmit::attach_mic_level_event(eventHandlerFunction _eventHandler) {
	do_mic_level_event=_eventHandler;
}

void Transmit::attach_mic_boost_event(eventHandlerFunction _eventHandler) {
	do_mic_boost_event=_eventHandler;
}

void Transmit::attach_mic_bias_event(eventHandlerFunction _eventHandler) {
	do_mic_bias_event=_eventHandler;
}

void Transmit::attach_mic_acc_event(eventHandlerFunction _eventHandler) {
	do_mic_acc_event=_eventHandler;
}

void Transmit::attach_compander_event(eventHandlerFunction _eventHandler) {
	do_compander_event=_eventHandler;
}

void Transmit::attach_compander_level_event(eventHandlerFunction _eventHandler) {
	do_compander_level_event=_eventHandler;
}

void Transmit::attach_dax_event(eventHandlerFunction _eventHandler) {
	do_dax_event=_eventHandler;
}

void Transmit::attach_pitch_event(eventHandlerFunction _eventHandler) {
	do_pitch_event=_eventHandler;
}

void Transmit::attach_speed_event(eventHandlerFunction _eventHandler) {
	do_speed_event=_eventHandler;
}

void Transmit::attach_iambic_event(eventHandlerFunction _eventHandler) {
	do_iambic_event=_eventHandler;
}

void Transmit::attach_iambic_mode_event(eventHandlerFunction _eventHandler) {
	do_iambic_mode_event=_eventHandler;
}

void Transmit::attach_cwl_enabled_event(eventHandlerFunction _eventHandler) {
	do_cwl_enabled_event=_eventHandler;
}

void Transmit::attach_swap_paddles_event(eventHandlerFunction _eventHandler) {
	do_swap_paddles_event=_eventHandler;
}

void Transmit::attach_break_in_event(eventHandlerFunction _eventHandler) {
	do_break_in_event=_eventHandler;
}

void Transmit::attach_break_in_delay_event(eventHandlerFunction _eventHandler) {
	do_break_in_delay_event=_eventHandler;
}

void Transmit::attach_sidetone_event(eventHandlerFunction _eventHandler) {
	do_sidetone_event=_eventHandler;
}

void Transmit::attach_monitor_event(eventHandlerFunction _eventHandler) {
	do_monitor_event=_eventHandler;
}

void Transmit::attach_sb_monitor_event(eventHandlerFunction _eventHandler) {
	do_sb_monitor_event=_eventHandler;
}

void Transmit::attach_mon_gain_cw_event(eventHandlerFunction _eventHandler) {
	do_mon_gain_cw_event=_eventHandler;
}

void Transmit::attach_mon_gain_sb_event(eventHandlerFunction _eventHandler) {
	do_mon_gain_sb_event=_eventHandler;
}

void Transmit::attach_mon_pan_cw_event(eventHandlerFunction _eventHandler) {
	do_mon_pan_cw_event=_eventHandler;
}

void Transmit::attach_mon_pan_sb_event(eventHandlerFunction _eventHandler) {
	do_mon_pan_sb_event=_eventHandler;
}

void Transmit::attach_tune_event(eventHandlerFunction _eventHandler) {
	do_tune_event=_eventHandler;
}

void Transmit::attach_met_in_rx_event(eventHandlerFunction _eventHandler) {
	do_met_in_rx_event=_eventHandler;
}

void Transmit::attach_hwalc_enabled_event(eventHandlerFunction _eventHandler) {
	do_hwalc_enabled_event=_eventHandler;
}

void Transmit::attach_inhibit_event(eventHandlerFunction _eventHandler) {
	do_inhibit_event=_eventHandler;
}

void Transmit::attach_speech_processor_enable_event(eventHandlerFunction _eventHandler) {
	do_speech_processor_enable_event=_eventHandler;
}

void Transmit::attach_speech_processor_level_event(eventHandlerFunction _eventHandler) {
	do_speech_processor_level_event=_eventHandler;
}


void Transmit::attach_show_tx_in_waterfall_event(eventHandlerFunction _eventHandler) {
	do_show_tx_in_waterfall_event=_eventHandler;
}

void Transmit::attach_mic_selection_event(eventHandlerFunction _eventHandler) {
	do_mic_selection_event=_eventHandler;
}




void Transmit::updateObject(int objectId,int value){
	switch(objectId) {
		case TRANSMIT_RF_POWER:
			 rfpower=value;
			 break;
		case TRANSMIT_ATU_POWER:
			 tunepower=value;
			 break;
		case TRANSMIT_BREAK_IN_DELAY:
			 break_in_delay=value;
			 break;
		case TRANSMIT_MONITOR_GAIN_CW:
			 mon_gain_cw=value;
			 break;
		case TRANSMIT_MONITOR_PAN_CW:
			 mon_pan_cw=value;
			 break;
		case TRANSMIT_SPEED:
			 speed=value;
			 break;
		case TRANSMIT_PITCH:
			 pitch=value;
			 break;
		case TRANSMIT_MIC_LEVEL:
			 mic_level=value;
			 break;
		case TRANSMIT_MONITOR_GAIN_SB:
			 mon_gain_sb=value;
			 break;
		case TRANSMIT_COMPANDER_LEVEL:
			 compander_level=value;
			 break;	 
		case TRANSMIT_VOX_LEVEL:
			 vox_level=value;
			 break;	 
		case TRANSMIT_VOX_DELAY:
			 vox_delay=value;
			 break;	 
		case TRANSMIT_AM_CARRIER:
			 am_carrier_level=value;
			 break;
		case TRANSMIT_LO:
			 lo=value;
			 break;
		case TRANSMIT_HI:
			 hi=value;
			 break;	 
		default:
			 Serial.print(F("Transmit::updateObject - Unhandled id:")); Serial.println(objectId);
	}
	
}