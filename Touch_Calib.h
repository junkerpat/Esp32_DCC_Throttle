#ifndef Touch_Calib
#define Touch_Calib

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



#define DEBUGTOUCH
#define CALIBRATION_FILE "/TouchCalData2"
//#define REPEAT_CAL false
//int REPEAT_CAL = false;



//TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

//void touch_calibrate(int & Mymenu)
void touch_calibrate()
{
	uint16_t calData[5] ;
  	uint8_t calDataOK = 0 ;

  	// check file system exists
  	if (!SPIFFS.begin()) 
  	{
    	Serial.println("Formating file system") ;
    	SPIFFS.format() ;
    	SPIFFS.begin() ;
  	}

  	// check if calibration file exists and size is correct
  	if (SPIFFS.exists(CALIBRATION_FILE)) 
  	{
    	if (REPEAT_CAL)
    	{
      		// Delete if we want to re-calibrate
      		SPIFFS.remove(CALIBRATION_FILE) ;
    	}
    	else
    	{
      		File f = SPIFFS.open(CALIBRATION_FILE, "r") ;
      		if (f) 
      		{
        		if (f.readBytes((char *)calData, 14) == 14)
          		calDataOK = 1 ;
        		f.close() ;
      		}
    	}
  	}

  	if (calDataOK && !REPEAT_CAL) 
  	{
    	// calibration data valid
    	tft.setTouch(calData);
  	}	 
  	else 
  	{
    	// data not valid so recalibrate
    	tft.fillScreen(TFT_BLACK) ;
    	tft.setCursor(20, 0) ;
    	tft.setTextFont(2) ;
    	tft.setTextSize(1) ;
    	tft.setTextColor(TFT_WHITE, TFT_BLACK) ;
    	tft.println("Touch corners as indicated") ;
    	tft.setTextFont(1) ;
    	tft.println() ;

    	if (REPEAT_CAL) 
    	{
    	  	tft.setTextColor(TFT_RED, TFT_BLACK) ;
    		tft.println("Set REPEAT_CAL to false to stop this running again!") ;
    	}

    	tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15) ;
    	tft.setTextColor(TFT_GREEN, TFT_BLACK) ;
    	tft.println("Calibration complete!") ;

    	// store data
    	File f = SPIFFS.open(CALIBRATION_FILE, "w") ;
    	if (f) 
    	{
      		f.write((const unsigned char *)calData, 14) ;
      		f.close() ;
      		delay(400) ;
      		Mymenu = 0 ;
    	}	      
  	}	  
}

#endif