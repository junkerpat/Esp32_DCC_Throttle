// All Bouton Switch input,output from the card are here , Direction are here ....


#ifndef EncoderBtn
#define EncoderBtn

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



#define ROTARY_ENCODER_A_PIN 34
#define ROTARY_ENCODER_B_PIN 35
#define ROTARY_ENCODER_BUTTON_PIN 39
const int BUTTON_PIN = 32 ;

#define ROTARY_ENCODER_VCC_PIN -1 /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

const int BrakePin = 36 ; //Pot PIN for Brake

//depending on your encoder - try 1,2 or 4 to get expected behaviour
//#define ROTARY_ENCODER_STEPS 1
//#define ROTARY_ENCODER_STEPS 2
#define ROTARY_ENCODER_STEPS 4

//instead of changing here, rather change numbers above
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

//============= ****** DEBUGENC ******==============

//#define DEBUGENC

//================= Loco Direction =================

void rotary_onButtonClick() 
{
	static unsigned long lastTimePressed = 0 ;
	//ignore multiple press in that time milliseconds
	if (millis() - lastTimePressed < 500) 
	{
		return ;
	}
	lastTimePressed = millis() ;

	#ifdef DEBUGENC

    Serial.print("LocoDir = ") ;
    Serial.print(LocoDir) ;
    Serial.print(" : ") ;
	Serial.print("button pressed at ") ;
	Serial.println(millis()) ;

	#endif
}


//==================Void Rotary Loop=====================
void rotary_loop() 
{
	//dont print anything unless value changed
  	if (!rotaryEncoder.encoderChanged())
	{
		return;
	}
    Tnotch = (rotaryEncoder.readEncoder()) ;

	#ifdef DEBUGENC

	Serial.print("Tnotch : ") ;
	Serial.println(Tnotch[ActiveAddress]) ;	

	#endif
}

//===================****** SETUP ******===================

void EncoderBtn_setup() 
{
	pinMode(BUTTON_PIN,INPUT_PULLUP) ;
	
	//we must initialize rotary encoder
	rotaryEncoder.begin() ;

	rotaryEncoder.setup(
		[] { rotaryEncoder.readEncoder_ISR(); },
		[] { rotary_onButtonClick(); }) ;

	
	bool circleValues = false ;
	rotaryEncoder.setBoundaries(0, 8, circleValues) ; //minValue, maxValue, circleValues true|false (when max go to min and vice versa)

	
	//rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
	rotaryEncoder.setAcceleration(0) ; //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
}

//=====================******* LOOP ******=========================

void EncoderBtn_loop() 
{
	DirState = digitalRead(BUTTON_PIN) ;
  
	if (DirState == LOW) 
	{
	  	if (millis() - DebounceTime < 500) 
		{
		    return ;
	    }
		DebounceTime = millis() ;
	  	LocoDirection ++ ;
      	if (LocoDirection >= 2) LocoDirection = 0 ; //Switch 1 or 0 for direction
	    TFTdirection() ;
      	delay(50) ;
	  	Serial.println(LocoDirection) ;
  	}

	//_________Brake_________

    Brake = analogRead(BrakePin) ; // la variable Brake = BrakePin pin 36
	Brake=(Brake * 3) ;           // le tier du potentiometre est utilise alors multiplie par 3
	 
	#ifdef DEBUGENC

	Serial.print("Brake : ") ;
	Serial.println(Brake) ;	

	#endif


	//in loop call your custom function which will process rotary encoder values
	rotary_loop() ;
	delay(50); //or do whatever you need to do...
}
	#endif