//Main Program

//My File
#include "Arduino.h"
#include "AllVariable.h"
#include "DCCTFT.h"
#include "MyMenu.h"
#include "DCCconfig.h"
#include "EncoderBtn.h"
#include "DCCWifi.h"
#include "myLocoSpeed.h"
#include "DCCGetLoco.h"
#include "Touch_Calib.h"
#include "DCCsend.h"
#include "DCCincoming.h"

//Library
#include <FS.h>
#include <WiFi.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <AiEsp32RotaryEncoder.h>


#define DEBUG


void setup()
{

    Serial.begin(115200) ; // Start Serial comunication
    tft.init() ;           // Init the TFT Screen 

    DCCWifi_setup() ;
    delay(1000);
    EncoderBtn_setup() ;
    DCCTFT_setup() ;
    touch_calibrate() ;
    TFTLocoAdresse() ;
    TFTdirection();   
}

void loop()
{ 

    DCCincoming_Loop() ;
    EncoderBtn_loop() ;
    DCCWifi_loop() ;
    myLocoSpeed_loop() ;   
    //SendAdress() ;
    LocoDirSend() ;
    SendSpeed() ;
    My_Menu() ;
    SendFonction() ;
    Estop() ;
    Idle() ;

    if (key2[0].justPressed()) 
    {
    	Power();
    }
}   
  
