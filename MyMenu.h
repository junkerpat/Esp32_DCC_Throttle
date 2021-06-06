#ifndef MyMenu
#define MyMenu

//My File
#include "Arduino.h"
#include "AllVariable.h"
#include "DCCconfig.h"
#include "DCCGetLoco.h"
#include "Touch_Calib.h"
#include "DCCTFT.h"

//Library
#include <FS.h>
#include <WiFi.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <AiEsp32RotaryEncoder.h>

void My_Menu()
{

    if (Mymenu == 0 )
    {
        if (Mymenucur != Mymenu)
        {  
            DCCTFT_setup() ;
            TFTLocoAdresse();
            TFTdirection();
            Mymenucur = Mymenu ;
        }
        DCCTFT_loop() ;
        //TFTLocoAdresse(); 
    }  
    
    if (Mymenu == 1 )
    {
        if (Mymenucur != Mymenu)
        {
            DCCGetLoco_setup() ;
            Mymenucur = Mymenu ;
        }
        DCCGetLoco_loop() ;
    }

    if (Mymenu == 10) 
    {
        REPEAT_CAL = true ;
        touch_calibrate() ;
        Mymenucur = Mymenu ;  
    }
}

#endif