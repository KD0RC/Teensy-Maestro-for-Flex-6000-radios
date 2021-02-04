void configurePanadapterEvents() {
  for (int i=0; i<fRig.nMaxPanadapter; i++) {
    // fRig.panadapter[i].attach_pan_event(onPanadapter_pan); 
// fRig.panadapter[i].attach_y_pixels_event(onPanadapter_y_pixels); 
    // fRig.panadapter[i].attach_min_dbm_event(onPanadapter_min_dbm);  
    // fRig.panadapter[i].attach_max_dbm_event(onPanadapter_max_dbm);  
    // fRig.panadapter[i].attach_fps_event(onPanadapter_fps); 
    // fRig.panadapter[i].attach_average_event(onPanadapter_average);  
    // fRig.panadapter[i].attach_weighted_average_event(onPanadapter_weighted_average); 
    // fRig.panadapter[i].attach_rfgain_event(onPanadapter_rfgain); 
    // fRig.panadapter[i].attach_wide_event(onPanadapter_wide);  
    // fRig.panadapter[i].attach_loopa_event(onPanadapter_loopa);  
    // fRig.panadapter[i].attach_loopb_event(onPanadapter_loopb);  
    fRig.panadapter[i].attach_band_event(onPanadapter_band);  
    // fRig.panadapter[i].attach_daxiq_event(onPanadapter_daxiq);  
    // fRig.panadapter[i].attach_daxiq_rate_event(onPanadapter_daxiq_rate);  
    // fRig.panadapter[i].attach_capacity_event(onPanadapter_capacity); 
    // fRig.panadapter[i].attach_available_event(onPanadapter_available);  
    // fRig.panadapter[i].attach_waterfall_event(onPanadapter_waterfall); 
    // fRig.panadapter[i].attach_xvtr_event(onPanadapter_xvtr); 
    // fRig.panadapter[i].attach_pre_event(onPanadapter_pre);  
    // fRig.panadapter[i].attach_min_bw_event(onPanadapter_min_bw); 
    // fRig.panadapter[i].attach_max_bw_event(onPanadapter_max_bw);  
    // fRig.panadapter[i].attach_bandwidth_event(onPanadapter_bandwidth);  
    // fRig.panadapter[i].attach_center_event(onPanadapter_center);  
    // fRig.panadapter[i].attach_ant_list_event(onPanadapter_ant_list); 
    // fRig.panadapter[i].attach_rxant_event(onPanadapter_rxant); 
  }
}

// void onPanadapter_pan(const int senderId) {
  // Serial.print("onPanadapter_pan(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_x_pixels(const int senderId) {
  // Serial.print("onPanadapter_x_pixels(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_y_pixels(const int senderId) {
  // Serial.print("onPanadapter_y_pixels(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_min_dbm(const int senderId) {
  //Serial.print("onPanadapter_min_dbm(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_max_dbm(const int senderId) {
  //Serial.print("onPanadapter_max_dbm(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_fps(const int senderId) {
  // Serial.print("onPanadapter_fps(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_average(const int senderId) {
  //Serial.print("onPanadapter_average(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_weighted_average(const int senderId) {
  // Serial.print("onPanadapter_weighted_average(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_rfgain(const int senderId) {
  // Serial.print("onPanadapter_rfgain(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_wide(const int senderId) {
  // Serial.print("onPanadapter_wide(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_loopa(const int senderId) {
  // Serial.print("onPanadapter_loopa(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_loopb(const int senderId) {
  // Serial.print("onPanadapter_loopb(");   Serial.print(senderId);  Serial.println(") event!");
// }

void onPanadapter_band(const int senderId) {
  Serial.print("onPanadapter_band(");   Serial.print(senderId);  Serial.println(") event!");
  Serial.print("Band:"); Serial.println(fRig.panadapter[senderId].band);
  //Do your business here
}

// void onPanadapter_daxiq(const int senderId) {
  // Serial.print("onPanadapter_daxiq(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_daxiq_rate(const int senderId) {
  // Serial.print("onPanadapter_daxiq_rate(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_capacity(const int senderId) {
  // Serial.print("onPanadapter_capacity(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_available(const int senderId) {
  // Serial.print("onPanadapter_available(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_waterfall(const int senderId) {
  // Serial.print("onPanadapter_waterfall(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_xvtr(const int senderId) {
  // Serial.print("onPanadapter_xvtr(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_pre(const int senderId) {
  // Serial.print("onPanadapter_pre(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_min_bw(const int senderId) {
  // Serial.print("onPanadapter_min_bw(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_max_bw(const int senderId) {
  // Serial.print("onPanadapter_max_bw(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_bandwidth(const int senderId) {
  //Serial.print("onPanadapter_bandwidth(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_center(const int senderId) {
  // Serial.print("onPanadapter_center(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_ant_list(const int senderId) {
  // Serial.print("onPanadapter_ant_list(");   Serial.print(senderId);  Serial.println(") event!");
// }

// void onPanadapter_rxant(const int senderId) {
  // Serial.print("onPanadapter_rxant(");   Serial.print(senderId);  Serial.println(") event!");
// }
