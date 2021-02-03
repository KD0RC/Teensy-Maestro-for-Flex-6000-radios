#include <SPI.h>
#include <Ethernet.h>
#include <FlexRig.h>
#include <UTFT.h>

extern "C" {
  typedef void (*genericHandlerFunction)(void);
}

#define BAUD_RATE 115200

FlexRig fRig;

//DISPLAY SETUP
UTFT myGLCD(ITDB50,25,26,27,28);  // 5" display

//int SCREEN_HEIGHT;
//int SCREEN_WIDTH;

//END DISPLAY SETUP

//Ethernet
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0xC2, 0x43};
byte myAddress[16];

void setup() {
  Serial.begin(BAUD_RATE);
  
  Serial.println("=== Started DHCP request");
  
  //setColor(VGA_WHITE,VGA_BLACK);
  myGLCD.print(F("Waiting for IP Address       "), 100, 200);
  getIpAddress();
  //getFixedIpAddress();
  //myGLCD.print(F("My IP is: "), 100, 250);
  String addr=String(Ethernet.localIP()[0]) + "." +
              String(Ethernet.localIP()[1]) + "." +
              String(Ethernet.localIP()[2]) + "." +
              String(Ethernet.localIP()[3]);
  //myGLCD.print(addr, 270, 250);  
    
  fRig=FlexRig::findAFlex(NULL); 
  //fRig=FlexRig::findAFlex("2114-420A-6300-3136");  
  fRig.connect(); 
  if (fRig.connected) {
    myGLCD.print("Connected to Flex Rig      ", 100, 250);
    //myGLCD.print("Initializing GUI ...       ", 100, 300);

    Serial.println("Connected");
    

    int d=millis();
    while ((millis()-d)<2000) {  //simulating main loop
      fRig.process();            //and processing intial rig data
      delay(100);  
    }

    
    //Configuring Events
    configureRadioEvents();
    configureEqEvents();  
    configureInterlockEvents();
    configureTransmitEvents();
    configurePanadapterEvents();
    configureWaterfallEvents();
    configureSliceEvents();
  }
     
}

void loop() {
  fRig.fireEvents();
  fRig.process();
}

//Ethernet service routine
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
  Serial.println(Ethernet.localIP());
}

//Ethernet service routine
void getFixedIpAddress() {
  
  IPAddress ip(192,168,0, 11);
  IPAddress gateway(192,168,0, 1);
  IPAddress subnet(255, 255, 255, 0);
  
  // start the Ethernet connection:
  Serial.println("=== Setting fixed IP address");
  Ethernet.begin(mac, ip, gateway, subnet);
  Serial.print("IP address is: ");
  Serial.println(Ethernet.localIP());
}
