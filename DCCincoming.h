#ifndef DCCincoming
#define DCCincoming

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


void DCCincoming_Loop()
{
    while (client.available()) 
    {
        String JmriRead = client.readStringUntil('\n');
        Serial.print(" Jmri Read = ");
        Serial.println(JmriRead);

        if (JmriRead.substring(0) == "PPA0") 
        {
            TFTpowerCur = 1 ;
            PowerState = 0 ;
            Serial.println("It's an PPA0 file");
        }

        if (JmriRead.substring(0) == "PPA1") 
        {
            TFTpowerCur = 0  ;
            PowerState = 1 ;
            Serial.println("It's an PPA1 file");
        }

        if (JmriRead.indexOf("*10") != -1) 
        {
            Serial.println("Ready receive *10 done");
        }

        if (JmriRead.indexOf("R0")!= -1) 
        {
            LocoDirection = 0 ;
            Serial.print("LocoDirection = ");
            Serial.println(LocoDirection);
            Serial.println("LocoDirection = REV");
        }
  
        if (JmriRead.indexOf("R1") != -1) 
        {
            LocoDirection = 1 ;
            Serial.print("LocoDirection = ");
            Serial.println(LocoDirection);
            Serial.println("LocoDirection = FWR");
        }
    }   
}

#endif