#ifndef AllVariable
#define AllVariable

//My File
#include "DCCconfig.h"

//Library
#include <FS.h>
#include <WiFi.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <AiEsp32RotaryEncoder.h>

#define LABEL1_FONT &FreeSansBoldOblique9pt7b // Key label font 1
#define LABEL2_FONT &FreeSansBoldOblique12pt7b  //#define LABEL2_FONT &FreeSansBold12pt7b 
#define LABEL3_FONT &FreeSansBoldOblique18pt7b
#define LABEL4_FONT &FreeSansBoldOblique24pt7b
#define LABEL5_FONT &FreeSansBold24pt7b
#define LABEL6_FONT &FreeMonoBoldOblique24pt7b
#define LABEL7_FONT &FreeMonoBold24pt7b
#define LABEL8_FONT &FreeMono9pt7b
#define LABEL9_FONT &FreeMonoBold9pt7b

#define TIMEOUT 5500 // mS

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

WiFiClient client ;


String Version = "Verison 1.1 WIFI" ;

//DCCGetLoco

String AddRemLoco ;
int GetLocoMode ;


//DCCsend

int SendSpeedcur = 0 ;
String XmitA ;
String XmitD ;
String XmitV ;
String XmitF ;
String XmitS ;
String XmitI ;
String losh = "s" ;

//DCCTFT

int TFTSpeed = 1 ;
int TFTTnotch = 0 ;
int TFTActiveAddress ;
int TFTLocoAddress ;
int TFTLocoAddressCur ;
int FcnPage = 0 ;
int FcnPagecur = 0 ;
int PowerState ;
int Powercur ;
int TFTpowerCur ;
int Fonction ;
int Fonction0_14[24]= {0, 1, 2, 3, -1, -1, 4, 5, 6, 7, -1, -1, 8, 9, 10, 11, -1, -1, 12, 13, 14, 37, -1, -1};
int Fonction15_29[24]= {15, 16, 17, 18, -1, -1, 19, 20, 21, 22, -1, -1, 23, 24, 25, 26, -1, -1, 27, 28, 29, -1, -1, -1};
int Switching = 0 ;
int SwitchingCur = 0 ;


//EncoderBtn

static unsigned long DebounceTime = 0 ;
int Brake ;
int DirState = 0 ;
int Tnotch = 0 ;
int Tnotchcur = 0 ;
int LocoDir  = 0 ;

//mylocoSpeed

int LocoSpeed = 0 ;
int LocoSpeedcur = 0 ;
int Decel ;
int Accel = 0 ;
int BrakeAlert = 0 ;

//MyMenu

int Mymenu = 0 ;
int Mymenucur ;

//Touch_Calib

int REPEAT_CAL = false ;

//DccGetLoco

int ActiveAddress = 0 ; 
int MaxLoco = 4 ;
int LocoAddress = 0 ;
int LocoDirection  ;
int LocoDirectioncur  ;
int ConsistLoco[4] = {1000,2000,3000,4000} ;

#endif