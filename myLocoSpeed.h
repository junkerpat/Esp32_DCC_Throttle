// Speed of loco here 

#ifndef myLocoSpeed
#define myLocoSpeed

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




//============= ****** DEBUGLSP ******=====================

//#define DEBUGLSP


//===================****** SETUP ******===================

void myLocoSpeed_setup() 
{

}

//==================******* LOOP ******====================

void myLocoSpeed_loop() 
{

    for(int i = 0; i < 11; i++)
    {
        if (Switching == 1)
        {
            ThrottleLimit[i] = ThrottleLimit1[i] / 2 ;
        }
        else 
        {
            ThrottleLimit[i] = ThrottleLimit1[i]  ;
        }
    }


    //_________N_0__________

    if (Tnotch < Tnotchcur && (Tnotch == 0)|| (Tnotch == 0 &&( LocoSpeed > ThrottleLimit[0]))) 
    {

        if (millis() - Decel < Brake) 
        {
		    return ;
	    }
	        Decel = millis() ;

        if(Brake < 100)
        {
            LocoSpeed = (LocoSpeed - 3 ) ;
        }
        else
        {
            LocoSpeed -- ;
        }

        if (LocoSpeed < 0)
        {
            LocoSpeed = 0 ;
        }
        Tnotchcur = Tnotch ;
        //if (LocoSpeed == ThrottleLimit[0] ) 
        //{
        //  Tnotchcur = Tnotch ;
        //}
    }
    
    //_________N_1__________
    
    if (Tnotch > Tnotchcur && (Tnotch == 1) || (Tnotch == 1 &&( LocoSpeed < ThrottleLimit[1]))) 
    {
   
        if (millis() - Accel < Acceltime) 
        {
	  	    return ;
	    }
	    Accel = millis();
        LocoSpeed ++ ;
        Tnotchcur = Tnotch ;
        //if (LocoSpeed == ThrottleLimit[1] ) Tnotchcur = Tnotch ;    
    }

    if (Tnotch< Tnotchcur && (Tnotch == 1) || (Tnotch == 1 &&( LocoSpeed > ThrottleLimit[1]))) 
    {

        if (millis() - Decel < Brake) 
        {
		    return ;
	    }
	    Decel = millis() ;
        LocoSpeed -- ;
        Tnotchcur = Tnotch ;
        //if (LocoSpeed== ThrottleLimit[1] ) Tnotchcur = Tnotch ;
    }

    //_________N_2__________
    
    if (Tnotch > Tnotchcur && (Tnotch == 2)|| (Tnotch == 2 &&( LocoSpeed< ThrottleLimit[2]))) 
    {

        if (millis() - Accel < Acceltime) 
        {
		    return ;
	    }
	    Accel = millis() ;
        LocoSpeed ++ ;
        Tnotchcur = Tnotch ;
        //if (LocoSpeed == ThrottleLimit[2] ) Tnotchcur = Tnotch ;
    }

    if (Tnotch < Tnotchcur && (Tnotch == 2)|| (Tnotch == 2 &&( LocoSpeed > ThrottleLimit[2]))) 
    {

        if (millis() - Decel < Brake) 
        {
	        return ;
	    }
	    Decel = millis() ;
        LocoSpeed -- ;
        Tnotchcur = Tnotch ;
        //if (LocoSpeed == ThrottleLimit[2] ) Tnotchcur = Tnotch ;
        
    }

    //_________N_3__________

    if (Tnotch > Tnotchcur && (Tnotch == 3)|| (Tnotch == 3 &&( LocoSpeed < ThrottleLimit[3]))) 
    {

        if (millis() - Accel < Acceltime) 
        {
		    return ;
	    }
	    Accel = millis() ;
        LocoSpeed ++ ;
        Tnotchcur = Tnotch ;
        //if (LocoSpeed == ThrottleLimit[3] ) Tnotchcur = Tnotch ;
    }
    
    if (Tnotch < Tnotchcur && (Tnotch == 3)|| (Tnotch == 3 &&( LocoSpeed > ThrottleLimit[3]))) 
    {

        if (millis() - Decel < Brake) 
        {
		    return ;
	    }
	    Decel = millis() ;
        LocoSpeed -- ;
        Tnotchcur = Tnotch ;
        //if (LocoSpeed == ThrottleLimit[3] ) Tnotchcur = Tnotch ;
    }

    //_________N_4__________

    if (Tnotch > Tnotchcur && (Tnotch == 4)|| (Tnotch == 4 &&( LocoSpeed < ThrottleLimit[4]))) 
    {

        if (millis() - Accel < Acceltime) 
        {
		    return ;
	    }
	    Accel = millis() ;
        LocoSpeed ++ ;
        Tnotchcur = Tnotch ;
        //if (LocoSpeed == ThrottleLimit[4]) Tnotchcur = Tnotch ;
    }
    
    if (Tnotch < Tnotchcur && (Tnotch == 4)|| (Tnotch == 4 &&( LocoSpeed > ThrottleLimit[4]))) 
    {

        if (millis() - Decel < Brake) 
        {
	        return ;
	    }
	    Decel = millis() ;
        LocoSpeed -- ;
        Tnotchcur = Tnotch ;
        //if (LocoSpeed == ThrottleLimit[4] ) Tnotchcur = Tnotch ;
    }

    //_________N_5__________

    if (Tnotch > Tnotchcur && (Tnotch == 5)|| (Tnotch == 5 &&( LocoSpeed < ThrottleLimit[5]))) 
    {

        if (millis() - Accel < Acceltime) 
        {
		    return ;
	    }
	    Accel = millis() ;
        LocoSpeed ++ ;
        if (LocoSpeed == ThrottleLimit[5] ) Tnotchcur = Tnotch ;
    }
    
    if (Tnotch < Tnotchcur && (Tnotch == 5)|| (Tnotch == 5 &&( LocoSpeed > ThrottleLimit[5]))) 
    {

        if (millis() - Decel < Brake)
        {
		    return ;
	    }
	    Decel = millis() ;
        LocoSpeed -- ;
        if (LocoSpeed == ThrottleLimit[5] ) Tnotchcur = Tnotch ;      
    }

    //_________N_6__________

    if (Tnotch > Tnotchcur && (Tnotch == 6)|| (Tnotch == 6 &&( LocoSpeed < ThrottleLimit[6]))) 
    {

        if (millis() - Accel < Acceltime) 
        {
		    return ;
	    }
	    Accel = millis() ;
        LocoSpeed ++ ;
        if (LocoSpeed == ThrottleLimit[6] ) Tnotchcur = Tnotch ;      
    }
  
    if (Tnotch < Tnotchcur && (Tnotch == 6)|| (Tnotch == 6 &&( LocoSpeed > ThrottleLimit[6]))) 
    {

        if (millis() - Decel < Brake) 
        {
		    return ;
	    }
	    Decel = millis() ;
        LocoSpeed -- ;
        if (LocoSpeed == ThrottleLimit[6] ) Tnotchcur = Tnotch;      
    }

    //_________N_7__________

    if (Tnotch > Tnotchcur && (Tnotch == 7)|| (Tnotch == 7 &&( LocoSpeed < ThrottleLimit[7]))) 
    {

        if (millis() - Accel < Acceltime) 
        {
	        return ;
	    }
	    Accel = millis() ;
        LocoSpeed++ ;
        if (LocoSpeed == ThrottleLimit[7] ) Tnotchcur = Tnotch ;    
    }
    
    if (Tnotch < Tnotchcur && (Tnotch == 7)|| (Tnotch == 7 &&( LocoSpeed > ThrottleLimit[7]))) 
    {

        if (millis() - Decel < Brake) 
        {
		    return ;
	    }
	    Decel = millis() ;
        LocoSpeed -- ;
        if (LocoSpeed == ThrottleLimit[7] ) Tnotchcur = Tnotch ;      
    }

    //_________N_8__________

    if (Tnotch > Tnotchcur && (Tnotch == 8)|| (Tnotch == 8 &&( LocoSpeed < ThrottleLimit[8]))) 
    {

        if (millis() - Accel < Acceltime) 
        {
		    return ;
	    }
	    Accel = millis() ;
        LocoSpeed ++ ;
        if (LocoSpeed == ThrottleLimit[8] ) Tnotchcur = Tnotch ;
    }
    
    if (Tnotch < Tnotchcur && (Tnotch == 8)|| (Tnotch == 8 &&( LocoSpeed > ThrottleLimit[8]))) 
    {

        if (millis() - Decel < Brake) 
        {
		    return ;
	    }
	    Decel = millis() ;
        LocoSpeed -- ;
        if (LocoSpeed == ThrottleLimit[8] ) Tnotchcur = Tnotch;      
    }
    
    #ifdef DEBUGLSP

	    Serial.print("LocoSpeed: ") ;
        Serial.println(LocoSpeed) ;

    #endif

    if (LocoSpeed > LocoSpeedcur && (Brake < BrakealertDaTa)) 
    {
        BrakeAlert = 1 ;
        LocoSpeedcur = LocoSpeed ;
    }
    else 
    {
        BrakeAlert = 0 ;
        LocoSpeedcur = LocoSpeed ;
    }
  

}
#endif