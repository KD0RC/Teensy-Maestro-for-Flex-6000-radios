//#include <SPI.h>
//#include <Ethernet.h>
//#include <FlexRig.h>
//#include <UTFT.h>

#include "T4_PowerButton.h"

#include <SPI.h>

#include "HX8357_t3n.h"
#include "ili9341_t3n_font_Arial.h"       // for the HX8357, not ili9341
#include "ili9341_t3n_font_ArialBold.h"   // for the HX8357, not ili9341
#include <ILI9341_t3n_font_ComicSansMS.h> // for the HX8357, not ili9341

#include <SD.h>
#include "NativeEthernet.h"
#include <FlexRigTeensy.h>
#include "Encoder.h"

#include <EEPROM.h>

#include <Wire.h>
#include "Adafruit_STMPE610.h"  // I2C connected resistive touch screen controller
// Option #1 - uses I2C, connect to hardware I2C port only! (T4.x SDA = pin 18, SCL = pin 19)
// tie MODE to GND and POWER CYCLE (there is no reset pin)
Adafruit_STMPE610 touch = Adafruit_STMPE610();

extern "C" 
{
  typedef void (*genericHandlerFunction)(void);
}

#define BAUD_RATE 115200

// For the Adafruit HX8357 TFT display, these are the default.
const byte TFT_DC = 9;
const byte TFT_CS = 10;
const byte TFT_RST = 8;

// Use hardware SPI.  MOSI = pin 11, MISO = pin 12, SCK = pin 13
HX8357_t3n tft = HX8357_t3n(TFT_CS, TFT_DC, TFT_RST);

FlexRig fRig;

//int SCREEN_HEIGHT;
//int SCREEN_WIDTH;

//END DISPLAY SETUP

//Ethernet
byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0xC2, 0x43};
byte myAddress[16];

void setup() {
  Serial.begin(BAUD_RATE);
  
  Serial.println("=== Started DHCP request");
  
  tft.begin();
  tft.setRotation(3);
  tft.setFont(Arial_14);
  tft.fillScreen(HX8357_NAVY);
  tft.setTextColor(HX8357_YELLOW);
  tft.setCursor(0, 0);
  tft.print("Waiting for IP Address       ");
  getIpAddress();
  //getFixedIpAddress();
  tft.print("My IP is: ");
  String addr=String(Ethernet.localIP()[0]) + "." +
              String(Ethernet.localIP()[1]) + "." +
              String(Ethernet.localIP()[2]) + "." +
              String(Ethernet.localIP()[3]); 
   tft.println(addr);
    
  fRig=FlexRig::findAFlex(NULL);   
  fRig.connect(); 
  if (fRig.connected) 
  {
    tft.println();
    tft.print("Connected to: "); tft.print(fRig.nickName); tft.print("  Ser: "); tft.println(fRig.serial);
    tft.print("Model: "); tft.print(fRig.modelName); tft.print("  Ver. "); tft.println(fRig.softVersion);

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

void loop() 
{
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
