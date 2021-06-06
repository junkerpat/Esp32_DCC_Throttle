#ifndef DCCsend
#define DCCsend

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


//=============================POWER===========================

void Power() 
{
  
  	if (PowerState == 0   && (PowerState != Powercur)) 
  	{
    	client.println("PPA0");
    	Powercur = PowerState ;
  	}
  	else if (PowerState == 1   && (PowerState != Powercur)) 
  	{
    	client.println("PPA1");
    	Powercur = PowerState ;
  	} 
}
//======================== LocoDir ===========================
void LocoDirSend() 
{

  	if (LocoDirectioncur != LocoDirection && (LocoDirection == 1 )) 
  	{
    	XmitD += "M";
    	XmitD += (ActiveAddress + 1);
    	XmitD += "A*";
    	XmitD += "<;>";
    	XmitD += "R";
    	XmitD += LocoDirection ;
    	Serial.println(XmitD);
    	client.println (XmitD);
    	XmitD = "";
    	delay(40);
    	LocoDirectioncur = LocoDirection ;
  	}

  	if (LocoDirectioncur != LocoDirection && (LocoDirection == 0 )) 
  	{
    	XmitD += "M";
    	XmitD +=  (ActiveAddress + 1);
    	XmitD += "A*";
    	XmitD += "<;>";
    	XmitD += "R";
    	XmitD += LocoDirection;
    	Serial.println(XmitD);
    	client.println (XmitD);
    	XmitD = "";
    	delay(40);
    	LocoDirectioncur = LocoDirection ;
  	}
}

//======================= Send LocoSpeed =======================

void SendSpeed() 
{

  	if (SendSpeedcur != LocoSpeed) 
  	{
    	XmitV += "M";
    	XmitV += ( ActiveAddress +1 );
    	XmitV += "A*";
    	XmitV += "<;>";
    	XmitV += "V";
    	XmitV += (LocoSpeed );
    	Serial.println(XmitV);
    	client.println (XmitV);
    	XmitV = "";
    	delay(50);
    	SendSpeedcur = LocoSpeed ;
  	}
}


//======================= Send Adresse =========================
void SendAdress()
{
  
  	losh = "s"; // Unlikely default
  	if (LocoAddress < 128) losh = "S";
  	else if (LocoAddress > 127) losh = "L";
     
    XmitA += "M" ;
    XmitA += (ActiveAddress + 1) ;
    XmitA += AddRemLoco ;
    XmitA += losh ;
    XmitA += LocoAddress ;
    XmitA += "<;>";
    XmitA += losh;
    XmitA += LocoAddress ;
    Serial.print("XmitA = ");
    Serial.println(XmitA);
    client.println (XmitA);
    XmitA = "";
    delay(50);
}

//======================= Send Fonctions =========================

void SendFonction()
{


 	if(FcnPage == 0)
 	{
    	for (uint8_t i = 0 ; i < 24 ; i ++) 
    	{
      		if (key0[i].justPressed())
      		{
        		Fonction = Fonction0_14[i] ;
        		if(Fonction < 31  &&(Fonction != -1 ))
        		{
          			XmitF += "M" ;
          			XmitF += (1) ;
          			XmitF += "A" ;
          			XmitF += "*";
          			XmitF += "<;>";
          			XmitF += "F" ;
          			XmitF += "1";
          			XmitF += Fonction ;
          			client.println (XmitF);
          			Serial.println(XmitF) ;
          			XmitF = "";
        		}   
      		}

        
      		if (key0[i].justReleased())
      		{
        		if(Fonction < 31 &&(Fonction != -1))
        		{
          			XmitF += "M" ;
          			XmitF += (1) ;
          			XmitF += "A" ;
          			XmitF += "*";
          			XmitF += "<;>";
          			XmitF += "F" ;
          			XmitF += "0";
          			XmitF += Fonction ;
          			delay(50);
          			client.println (XmitF);
          			Serial.println (XmitF);
          			XmitF = "";
          			Serial.println(XmitF);
          			Fonction = -1 ;
        		}
      		}
    	}     
  	}
  
 	if(FcnPage == 1)
  	{
    	for (uint8_t xyz = 0 ; xyz < 24 ; xyz ++)  
    	{
      		if (key1[xyz].justPressed())
      		{
        		Fonction = Fonction15_29[xyz] ;
        		if(Fonction < 31  &&(Fonction != -1))
        		{
          			XmitF += "M" ;
          			XmitF += (1) ;
          			XmitF += "A" ;
          			XmitF += "*";
          			XmitF += "<;>";
          			XmitF += "F" ;
          			XmitF += "1";
          			XmitF += Fonction ;
          			client.println (XmitF);
          			Serial.println(XmitF) ;
          			XmitF = "";
        		}
      		}
        
      		if (key1[xyz].justReleased())
      		{
        		if(Fonction < 31  &&(Fonction != -1))
        		{
          			XmitF += "M" ;
          			XmitF += (1) ;
          			XmitF += "A" ;
          			XmitF += "*";
          			XmitF += "<;>";
          			XmitF += "F" ;
          			XmitF += "0";
          			XmitF += Fonction ;
          			client.println (XmitF);
          			Serial.println (XmitF);
          			XmitF = "";
          			Serial.println(XmitF);
          			Fonction = -1 ;
        		}
      		}
    	}      
  	}
}
void Idle()
{
  	if (key2[3].justPressed())
  	{
    	XmitI += "M" ;
    	XmitI += (1) ;
    	XmitI += "A" ;
    	XmitI += losh;
    	XmitI += LocoAddress;
    	XmitI += "<;>";
    	XmitI += "I" ;
    	Tnotch = 0 ;
    	LocoSpeed = 0 ;
    	client.println (XmitI);
    	Serial.println (XmitI);
    	XmitI = "";
    	Serial.println(XmitI);
  	}
}

void Estop()
{
  	if (key2[2].justPressed())
  	{
    	XmitS += "M" ;
    	XmitS += (1) ;
    	XmitS += "A" ;
    	XmitS += losh;
    	XmitS += LocoAddress;
    	XmitS += "<;>";
    	XmitS += "X" ;
    	//XmitS += "0";
    	//XmitS += Fonction ;
    	Tnotch = 0 ;
    	LocoSpeed = 0 ;
    	client.println (XmitS);
    	Serial.println (XmitS);
    	XmitS = "";
    	Serial.println(XmitS);
  	}
}




#endif