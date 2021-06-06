// Connection to Wifi and Host here ( DCC++EX or JMRI )

#ifndef DCCWifi
#define DCCWifi

//My File
#include "Arduino.h"
#include "AllVariable.h"
#include "DCCconfig.h"

//Library
#include <FS.h>
#include <WiFi.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <AiEsp32RotaryEncoder.h>

//=================****** DEBUGWIFI ******=================

#define DEBUGWIFI

//===================****** SETUP ******===================

void DCCWifi_setup() 
{
    WiFi.begin(SSID, PASS) ;
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100) ;
    }
    tft.setRotation(3) ;
    tft.fillScreen(TFT_BLACK) ;
    tft.setTextSize(1) ;
    tft.setTextColor(TFT_WHITE, TFT_BLACK) ; 
    tft.setFreeFont(&FreeSansOblique9pt7b) ;
    tft.println("") ;
    tft.println("My DCC Throttle") ;
    tft.println(Version) ;
    tft.println("WiFi connected") ;
    tft.print("IP address : ") ;
    tft.println(WiFi.localIP()) ;
    tft.print("connecting to : ") ;
    tft.println(HOST) ;
    delay(1000) ;
    
 #ifdef DEBUGWIFI

    Serial.println("") ;
    Serial.println("WiFi connected") ;
    Serial.print("IP address : ") ;
    Serial.println(WiFi.localIP()) ;
    Serial.print("connecting to : ") ;
    Serial.println(HOST) ;

  #endif

    if (!client.connect(HOST, PORT)) 
    {
     Serial.println("Connection Fail") ;
     tft.println("Connection Fail") ;
    }

    client.println("H" + Id ) ;
    tft.println("H ID : " + Id ) ;
    client.println("N" + Tname ) ;
    tft.println("Tname : " + Tname ) ;
    delay(1000) ;
}

//==================******* LOOP ******=====================

void DCCWifi_loop() 
{

}

#endif