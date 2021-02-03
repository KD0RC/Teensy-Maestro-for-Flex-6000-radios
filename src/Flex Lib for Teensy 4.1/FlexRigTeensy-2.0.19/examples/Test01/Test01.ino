#include <Ethernet.h>
#include <SPI.h>
#include <FlexRig.h>


//Ethernet Shield Mac Address
//You can get it from adesive label on the shield
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0xC2, 0x43};

//Rig instance
FlexRig fRig;

void setup() {
  Serial.begin(115200);
  Serial.println("=== Started DHCP request");
  getIpAddress();
  
  fRig=FlexRig::findAFlex(NULL);  
  //fRig=FlexRig::findAFlex("2114-AAAA-6300-BBB1"); 
  
  
  fRig.connect(); 
  if (fRig.connected) {
     Serial.println("Connected to Flex Rig");
  } 
}

void loop() {
  //fRig.readEthernetData();    //Never remove this from loop() routine
  fRig.process();
  for (int i=0;i<fRig.nMaxSlice;i++) {
    if (fRig.slice[i].in_use) {
        Serial.println("=========================");
        Serial.print("Slice #     : "); Serial.print (i);
          if (fRig.slice[i].active) Serial.print(" - active"); 
        Serial.println();
        Serial.print("RX Frequency: "); Serial.println(fRig.slice[i].RF_frequency);
        fRig.slice[i].updated=false;
    }
  }
  
  delay(1000);
  
}



//Ethernet DHCP service routine
void getIpAddress() {
  // start the Ethernet connection:
  Serial.println("=== Waiting for IP address");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    //do nothing forevermore
    for (;;)
      ;
  }
  Serial.print("IP address is: ");
  for (byte thisByte = 0; thisByte < 3; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.print(Ethernet.localIP()[3], DEC); 
  Serial.println();
}

