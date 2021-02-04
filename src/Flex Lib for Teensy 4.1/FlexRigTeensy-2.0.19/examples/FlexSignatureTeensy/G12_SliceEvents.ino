void configureSliceEvents() {
  for (int i=0; i<fRig.nMaxSlice; i++) {
    // fRig.slice[i].attach_in_use_event(onSlice_in_use);
    fRig.slice[i].attach_RF_frequency_event(onSlice_RF_frequency); 
    // fRig.slice[i].attach_rit_on_event(onSlice_rit_on); 
    // fRig.slice[i].attach_rit_freq_event(onSlice_rit_freq); 
    // fRig.slice[i].attach_xit_on_event(onSlice_xit_on); 
    // fRig.slice[i].attach_xit_freq_event(onSlice_xit_freq);
    // fRig.slice[i].attach_wide_event(onSlice_wide);  
    // fRig.slice[i].attach_filter_lo_event(onSlice_filter_lo);
    // fRig.slice[i].attach_filter_hi_event(onSlice_filter_hi);
    // fRig.slice[i].attach_step_event(onSlice_step); 
    // fRig.slice[i].attach_agc_threshold_event(onSlice_agc_threshold); 
    // fRig.slice[i].attach_agc_off_level_event(onSlice_agc_off_level); 
    // fRig.slice[i].attach_pan_event(onSlice_pan);
    // fRig.slice[i].attach_loopa_event(onSlice_loopa); 
    // fRig.slice[i].attach_loopb_event(onSlice_loopb); 
    // fRig.slice[i].attach_qsk_event(onSlice_qsk); 
    // fRig.slice[i].attach_dax_event(onSlice_dax); 
    // fRig.slice[i].attach_dax_clients_event(onSlice_dax_clients); 
    // fRig.slice[i].attach_lock_event(onSlice_lock); 
    // fRig.slice[i].attach_tx_event(onSlice_tx); 
    // fRig.slice[i].attach_dax_tx_event(onSlice_dax_tx);
    // fRig.slice[i].attach_active_event(onSlice_active);
    // fRig.slice[i].attach_audio_gain_event(onSlice_audio_gain); 
    // fRig.slice[i].attach_audio_pan_event(onSlice_audio_pan);
    // fRig.slice[i].attach_audio_mute_event(onSlice_audio_mute); 
    // fRig.slice[i].attach_record_event(onSlice_record);  
    // fRig.slice[i].attach_record_time_event(onSlice_record_time); 
    // fRig.slice[i].attach_anf_event(onSlice_anf);  
    // fRig.slice[i].attach_anf_level_event(onSlice_anf_level); 
    // fRig.slice[i].attach_nr_event(onSlice_nr); 
    // fRig.slice[i].attach_nr_level_event(onSlice_nr_level);
    // fRig.slice[i].attach_wnb_event(onSlice_wnb); 
    // fRig.slice[i].attach_wnb_level_event(onSlice_wnb_level); 
    // fRig.slice[i].attach_nb_event(onSlice_nb); 
    // fRig.slice[i].attach_nb_level_event(onSlice_nb_level); 
    // fRig.slice[i].attach_apf_event(onSlice_apf); 
    // fRig.slice[i].attach_apf_level_event(onSlice_apf_level); 
    // fRig.slice[i].attach_diversity_event(onSlice_diversity); 
    // fRig.slice[i].attach_diversity_parent_event(onSlice_diversity_parent); 
    // fRig.slice[i].attach_diversity_child_event(onSlice_diversity_child); 
    // fRig.slice[i].attach_diversity_index_event(onSlice_diversity_index); 
    // fRig.slice[i].attach_filter_shift_event(onSlice_filter_shift);
    // fRig.slice[i].attach_filter_width_event(onSlice_filter_width); 
    // fRig.slice[i].attach_rxant_event(onSlice_rxant); 
    // fRig.slice[i].attach_mode_event(onSlice_mode); 
    // fRig.slice[i].attach_step_list_event(onSlice_step_list); 
    // fRig.slice[i].attach_agc_mode_event(onSlice_agc_mode); 
    // fRig.slice[i].attach_txant_event(onSlice_txant); 
    // fRig.slice[i].attach_play_event(onSlice_play); 
    // fRig.slice[i].attach_ant_list_event(onSlice_ant_list);
  }
}

// void onSlice_in_use(const int senderId) {
  // Serial.print("onSlice_in_use(");   Serial.print(senderId);  Serial.println(") event!");
// }
	
void onSlice_RF_frequency(const int senderId) {
  Serial.print("onSlice_RF_frequency(");   Serial.print(senderId);  Serial.println(") event!");
  Serial.print("Slice: "); Serial.print(senderId); Serial.print(" - Frequency:"); Serial.println(fRig.slice[senderId].RF_frequency);
} 
	
// void onSlice_rit_on(const int senderId) {
  // Serial.print("onSlice_rit_on(");   Serial.print(senderId);  Serial.println(") event!");
// } 
	
// void onSlice_rit_freq(const int senderId) {
  // Serial.print("onSlice_rit_freq(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_xit_on(const int senderId) {
  // Serial.print("onSlice_xit_on(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_xit_freq(const int senderId) {
  // Serial.print("onSlice_xit_freq(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_wide(const int senderId) {
  // Serial.print("onSlice_wide(");   Serial.print(senderId);  Serial.println(") event!");
// }  

// void onSlice_filter_lo(const int senderId) {
  //Serial.print("onSlice_filter_lo(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_filter_hi(const int senderId) {
  //Serial.print("onSlice_filter_hi(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_step(const int senderId) {
  // Serial.print("onSlice_step(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_agc_threshold(const int senderId) {
  // Serial.print("onSlice_agc_threshold(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_agc_off_level(const int senderId) {
  // Serial.print("onSlice_agc_off_level(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_pan(const int senderId) {
  // Serial.print("onSlice_pan(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_loopa(const int senderId) {
  // Serial.print("onSlice_loopa(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_loopb(const int senderId) {
  // Serial.print("onSlice_loopb(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_qsk(const int senderId) {
  // Serial.print("onSlice_qsk(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_dax(const int senderId) {
  // Serial.print("onSlice_dax(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_dax_clients(const int senderId) {
  // Serial.print("onSlice_dax_clients(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_lock(const int senderId) {
  // Serial.print("onSlice_lock(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_tx(const int senderId) {
  // Serial.print("onSlice_tx(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_dax_tx(const int senderId) {
  // Serial.print("onSlice_dax_tx(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_active(const int senderId) {
  //Serial.print("onSlice_active(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_audio_gain(const int senderId) {
  //Serial.print("onSlice[");   Serial.print(senderId);  Serial.println("] audio_gain event!");
// } 

// void onSlice_audio_pan(const int senderId) {
  // Serial.print("onSlice_audio_gain(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_audio_mute(const int senderId) {
  // Serial.print("onSlice_audio_mute(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_record(const int senderId) {
  // Serial.print("onSlice_record(");   Serial.print(senderId);  Serial.println(") event!");
// }  

// void onSlice_record_time(const int senderId) {
  // Serial.print("onSlice_record_time(");   Serial.print(senderId);  Serial.println(") event!");
// } 


// void onSlice_anf(const int senderId) {
  // Serial.print("onSlice_anf(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_anf_level(const int senderId) {
  //Serial.print("onSlice_anf_level(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_nr(const int senderId) {
  //Serial.print("onSlice_nr(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_nr_level(const int senderId) {
  //Serial.print("onSlice_nr_level(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_wnb(const int senderId) {
  //Serial.print("onSlice_wnb(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_nb(const int senderId) {
  //Serial.print("onSlice_nb(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_wnb_level(const int senderId) {
  //Serial.print("onSlice_wnb_level(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_nb_level(const int senderId) {
  //Serial.print("onSlice_nb_level(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_apf(const int senderId) {
  // Serial.print("onSlice_apf(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_apf_level(const int senderId) {
  //Serial.print("onSlice_apf_level(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_diversity(const int senderId) {
  // Serial.print("onSlice_diversity(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_diversity_parent(const int senderId) {
  // Serial.print("onSlice_diversity_parent(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_diversity_child(const int senderId) {
  // Serial.print("onSlice_diversity_child(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_diversity_index(const int senderId) {
  // Serial.print("onSlice_diversity_index(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_filter_shift(const int senderId) {
  //Serial.print("onSlice_filter_shift(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onSlice_filter_width(const int senderId) {
  //Serial.print("onSlice_filter_width(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_rxant(const int senderId) {
  //Serial.print("onSlice_rxant(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_mode(const int senderId) {
  // Serial.print("onSlice_mode(");   Serial.print(senderId);  Serial.println(") event!"); 
// } 

// void onSlice_step_list(const int senderId) {
  // Serial.print("onSlice_step_list(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_agc_mode(const int senderId) {
  //Serial.print("onSlice_agc_mode(");   Serial.print(senderId);  Serial.println(") event!");  
// } 

// void onSlice_txant(const int senderId) {
  // Serial.print("onSlice_txant(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_play(const int senderId) {
  // Serial.print("onSlice_play(");   Serial.print(senderId);  Serial.println(") event!");
// } 

// void onSlice_ant_list(const int senderId) {
  // Serial.print("onSlice_ant_list(");   Serial.print(senderId);  Serial.println(") event!");
// }
