//All going to TFT Sceen here !!!!


#ifndef DCCTFT
#define DCCTFT

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

//For Key0 and Key1 
#define KEY0_X 29 // Centre of key
#define KEY0_Y 111
#define KEY0_W 51 // Width and height
#define KEY0_H 35
#define KEY0_SPACING_X 1 // X and Y gap
#define KEY0_SPACING_Y 1
#define KEY0_TEXTSIZE 1   // Font size multiplier

//For Key2
#define KEY2_X 32// Centre of key
#define KEY2_Y 72
#define KEY2_W 55 // Width and height
#define KEY2_H 35
#define KEY2_SPACING_X 1 // X and Y gap
#define KEY2_SPACING_Y 1
#define KEY2_TEXTSIZE 1   // Font size multiplier






// Create 24 keys for the keypad NUM 0
char keyLabel0[24][4] = { "F0", "F1", "F2", "F3", "--", "LS", "F4", "F5", "F6", "F7", "--", "--", "F8", "F9", "F10", "F11","--", "--", "F12", "F13","F14" ,"-->","--","Sw" };
uint16_t keyColor0[24] = {TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_BLUE,TFT_DARKGREEN,TFT_DARKGREEN,
                          TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_BLUE,TFT_DARKGREEN,TFT_DARKGREEN,
                          TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_BLUE,TFT_DARKGREEN,TFT_DARKGREEN,
                          TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_BLUE,TFT_DARKGREEN,TFT_DARKGREEN
                        };

uint16_t keyTextColor0[24] = {TFT_WHITE, TFT_WHITE, TFT_WHITE,TFT_WHITE,TFT_WHITE,TFT_WHITE,
                              TFT_WHITE, TFT_WHITE, TFT_WHITE,TFT_WHITE,TFT_WHITE,TFT_WHITE,
                              TFT_WHITE, TFT_WHITE, TFT_WHITE,TFT_WHITE,TFT_WHITE,TFT_WHITE,
                              TFT_WHITE, TFT_WHITE, TFT_WHITE,TFT_WHITE,TFT_WHITE,TFT_WHITE
                            };
// Invoke the TFT_eSPI button class and create all the button objects
TFT_eSPI_Button key0[30];

// Create 24 keys for the keypad NUM1
char keyLabel1[24][4] = {"F15", "F16", "F17", "F18", "--", "--", "F19", "F20", "F21", "F22", "--", "--", "F23", "F24", "F25", "F26","--", "--", "F27", "F28","F29" ,"<--","Mnu","Cal" };
uint16_t keyColor1[24] = {TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_BLUE,TFT_DARKGREEN,TFT_DARKGREEN,
                          TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_BLUE,TFT_DARKGREEN,TFT_DARKGREEN,
                          TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_BLUE,TFT_DARKGREEN,TFT_DARKGREEN,
                          TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_BLUE,TFT_DARKGREEN,TFT_RED
                        };

// Invoke the TFT_eSPI button class and create all the button objects
TFT_eSPI_Button key1[30];


// Create 4 keys for the keypad NUM1int a=1; 

char keyLabel2[4][5] = {"Pwr","--","Stop","Idle"};
uint16_t keyColor2[4] = {TFT_GREEN, TFT_BLUE, TFT_BLUE,TFT_BLUE};
uint16_t keyTextColor2[4] = {TFT_RED, TFT_WHITE, TFT_WHITE,TFT_WHITE};

// Invoke the TFT_eSPI button class and create all the button objects
TFT_eSPI_Button key2[4];


//=================****** DEBUGTFT ******=================

#define DEBUGDCCTFT


//====================BOUTTONS=============================
//=============== KEY0 Fonction 0/15 ======================

void drawKeypad0()
{
  // Draw the keys

    for (uint8_t row = 0; row < 4; row++) 
    {
        for (uint8_t col = 0; col < 6; col++) 
        {
            uint8_t b = col + row * 6;

            if (b < 24) tft.setFreeFont(LABEL1_FONT);
            else tft.setFreeFont(LABEL2_FONT);

            key0[b].initButton(&tft, KEY0_X + col * (KEY0_W + KEY0_SPACING_X),
                                KEY0_Y + row * (KEY0_H + KEY0_SPACING_Y), // x, y, w, h, outline, fill, text
                                KEY0_W, KEY0_H, TFT_RED, keyColor0[b], keyTextColor0[b],
                                keyLabel0[b], KEY0_TEXTSIZE);
            key0[b].drawButton();
        }
    }
}

//=============== KEY0 Fonction 16/29 ======================

void drawKeypad1()
{
    // Draw the keys

    for (uint8_t row = 0; row < 4; row++) 
    {
        for (uint8_t col = 0; col < 6; col++) 
        {
            uint8_t c = col + row * 6;

            if (c < 24) tft.setFreeFont(LABEL1_FONT);
            else tft.setFreeFont(LABEL2_FONT);

            key1[c].initButton(&tft, KEY0_X + col * (KEY0_W + KEY0_SPACING_X),
                                KEY0_Y + row * (KEY0_H + KEY0_SPACING_Y), // x, y, w, h, outline, fill, text
                                KEY0_W, KEY0_H, TFT_RED, keyColor1[c], TFT_WHITE,
                                keyLabel1[c], KEY0_TEXTSIZE);
            key1[c].drawButton();
        }
    }
}

//=============== KEY0 Fonction 16/29 ======================

void drawKeypad2()
{
    // Draw the keys

    for (uint8_t row = 0; row < 1; row++) 
    {
        for (uint8_t col = 0; col < 4; col++) 
        {
            uint8_t d = col + row * 4;

            tft.setFreeFont(LABEL1_FONT);
            //if (d < 4) tft.setFreeFont(LABEL1_FONT);
            //else tft.setFreeFont(LABEL2_FONT);

            key2[d].initButton(&tft, KEY2_X + col * (KEY2_W + KEY2_SPACING_X),
                                KEY2_Y + row * (KEY2_H + KEY2_SPACING_Y), // x, y, w, h, outline, fill, text
                                KEY2_W, KEY2_H, TFT_RED, keyColor2[d], keyTextColor2[d],
                                keyLabel2[d], KEY2_TEXTSIZE);
            key2[d].drawButton();
        }
    }
}

//=================***** LocoAdress Section *****===========

void TFTLocoAdresse()
{
    tft.fillRect(197, 0, 122, 50,TFT_YELLOW);
    tft.setTextSize(1);
    tft.setTextDatum(C_BASELINE);
    tft.setFreeFont (LABEL5_FONT);
    tft.setTextColor(TFT_BLACK , TFT_YELLOW);
    tft.setTextPadding(1) ;
    tft.drawNumber(LocoAddress, 258, 37);
    delay(50);
    Serial.print("TFTLocoAdress = ");
    Serial.println(TFTLocoAddress);
}
//End of LocoAdress Section

//===================****** SETUP ******===================

void DCCTFT_setup()
{
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.fillRect(0, 0, 320, 240, TFT_WHITE);
    tft.fillRect(0, 0, 40, 50,TFT_DARKGREY);
    tft.setTextSize(1);
    tft.setTextColor(TFT_GREEN, TFT_DARKGREY); 
    tft.setTextFont(7);
    tft.setTextDatum(MR_DATUM);
    tft.drawNumber(Tnotch,36, 25, 7) ;
    delay(50);
    TFTTnotch = Tnotch ;
    TFTSpeed = 1 ;
    tft.setFreeFont(&FreeSansBold12pt7b);
    drawKeypad0();
    drawKeypad2();
    FcnPage = FcnPagecur ;
}   
//End of Setup Section

//==================******* LOOP ******=====================

void DCCTFT_loop()
{
  //======***** Fonction page for fonction 0/15 and 15 to 29 ***** ======//

    if (FcnPage == 0 && (FcnPagecur!= FcnPage))
    { 
        drawKeypad0();
        FcnPagecur = FcnPage ;   
    }

    if (FcnPage == 1 && (FcnPagecur!= FcnPage))
    { 
        drawKeypad1();
        FcnPagecur = FcnPage ;  
    } 
    //End of fonction page section
  
 //===================****** Loco Speed *****===================//

    if (TFTSpeed != LocoSpeed) // this section print LocoSpeed on TFT
    { 
  
        tft.fillRect(41, 0, 114, 50,TFT_BLUE);
        tft.setTextSize(1);

        if ( BrakeAlert == 1 )
        { 
            tft.setTextColor(TFT_RED, TFT_BLUE); tft.setTextFont(7); // LocoSpeed in red if brak apply
        }
        else 
        {
            tft.setTextColor(TFT_WHITE, TFT_BLUE); tft.setTextFont(7); // LocoSpeed white if no brake apply
        }
    
        tft.setTextDatum(MR_DATUM);
        tft.setTextPadding(0);
        tft.drawNumber(LocoSpeed, 138, 25 ) ;
        delay(50);
        TFTSpeed = LocoSpeed ;
    } 
    //End of Loco Speed

    if (GetLocoMode == 0)
    {
        //tft.fillRect(231, 52, 90, 40,TFT_WHITE);
        tft.setTextSize(1);
        tft.setTextDatum(MC_DATUM);
        tft.setFreeFont (LABEL9_FONT);
        //tft.setTextPadding(0);
        tft.setTextColor(TFT_BLACK , TFT_YELLOW);
        tft.drawString("L", 203, 39);
    }
    else
    {
        //tft.fillRect(231, 52, 90, 40,TFT_WHITE);
        tft.setTextSize(1);
        tft.setTextDatum(MC_DATUM);
        tft.setFreeFont (LABEL9_FONT);
        //tft.setTextPadding(0);
        tft.setTextColor(TFT_BLACK , TFT_YELLOW);
        tft.drawString("C", 203, 39);
    }

  //===================****** Loco Notch *****===================//

    if (TFTTnotch != Tnotch || (TFTActiveAddress != ActiveAddress)) // this section print Throttle Notch on TFT
    {
  
        tft.fillRect(0, 0, 40, 50,TFT_DARKGREY);
        tft.setTextSize(1);
        tft.setTextColor(TFT_GREEN, TFT_DARKGREY); 
        tft.setTextFont(7);
        tft.setTextDatum(MR_DATUM);
        tft.drawNumber(Tnotch,36, 25, 7) ;
        delay(50);
        TFTTnotch = Tnotch ;
        TFTActiveAddress = ActiveAddress ;
    }
     //End of Notch
  
  //===================****** Brake LVL indicatior  *****===================//

    if ( Brake < 2400 ) 
    {
        tft.fillRect(156, 40, 40, 10, TFT_DARKGREEN ) ;
    }
    else 
    {
        tft.fillRect(156, 40, 40, 10, TFT_SKYBLUE ) ;
        tft.drawRect(155, 40, 40, 10,TFT_DARKGREEN);
    }

    if ( Brake < 1800 ) 
    {
        tft.fillRect(156, 30, 40, 9, TFT_YELLOW ) ;
    }
    else 
    {
        tft.fillRect(156, 30, 40, 9, TFT_SKYBLUE ) ;
        tft.drawRect(156, 30, 40, 9,TFT_YELLOW);
    }

    if ( Brake < 1200 ) 
    {
        tft.fillRect(156, 20, 40, 9, TFT_RED ) ;
    }
    else 
    {
        tft.fillRect(156, 20, 40, 9, TFT_SKYBLUE ) ;
        tft.drawRect(156, 20, 40, 9,TFT_RED);
    }

    if ( Brake < 800 ) 
    {
        tft.fillRect(156, 10, 40, 9, TFT_RED ) ;
    }
    else 
    {
        tft.fillRect(156, 10, 40, 9, TFT_SKYBLUE ) ;
        tft.drawRect(156, 10, 40, 9,TFT_RED);
    }

    if ( Brake < 50 ) 
    {
        tft.fillRect(156, 0, 40, 9, TFT_RED ) ;
    }
    else 
    {
        tft.fillRect(156, 0, 40, 9, TFT_SKYBLUE ) ;
        tft.drawRect(156, 0, 40, 9,TFT_RED);
    } 
    //End of Brake Level Section

    //========***** This Section is for loco  touch bouton *****============

    uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

    // Pressed will be set true is there is a valid touch on the screen
    boolean pressed = tft.getTouch(&t_x, &t_y);


    //======**** Fonction Page 1 (0 To 29 and 14 optinal right Btn) ****==============

    if (FcnPage == 0)
    {
  
        for (uint8_t b = 0; b < 24; b++) 
        {
            if (pressed && key0[b].contains(t_x, t_y)) 
            {
                key0[b].press(true);  // tell the button it is pressed
            } 
            else 
            {
                key0[b].press(false);  // tell the button it is NOT pressed
            }
        }
    }

  // Check if any key has changed state 
    if (FcnPage == 0)
    {
        for (uint8_t b = 0; b < 24; b++) 
        {
            tft.setFreeFont(LABEL1_FONT);
            if (key0[b].justReleased()&& ( b < 22)) key0[b].drawButton();     // draw normal
            if (key0[b].justPressed()) 
            {
                key0[b].drawButton(true);  // draw invert
      
      

                if (b == 5) 
                { 
                    Mymenu = 1 ;
        
                }

                if (b == 21) 
                {
                    if (millis() - DebounceTime < 500) 
                    {
		                return ;
	                }

	                DebounceTime = millis() ;
                    FcnPage++ ;
                    if (FcnPage >= 2) FcnPage = 0 ;
                        Fonction = -1 ;
                }

                if (b == 23) 
                {

                    if (millis() - DebounceTime < 500) 
                    {
		                return ;
	                }

	                DebounceTime = millis() ;
                    Switching ++ ;
                    if (Switching >= 2) Switching = 0 ;
                    Serial.print("Switching mode = ");
                    Serial.println(Switching);
                }

                if (Switching == 1)
                {
                    key0[23].drawButton(true);  // draw invert
                }
                else 
                {
                    key0[23].drawButton();  // draw 
                }
    
                Serial.print("Fonction");
                Serial.println(Fonction);
                Serial.print("FcnPage ");
                Serial.println(FcnPage);
            } 
        }
    }   
    // End of Fonction 0 to 14 Section

    //======**** Fonction Page 2 (15 To 29 and 8 optinal right Btn) ****==============

    if (FcnPage == 1)
    {
  
        for (uint8_t c = 0; c < 24; c++) 
        {
            if (pressed && key1[c].contains(t_x, t_y)) 
            {
                key1[c].press(true);  // tell the button it is pressed
            } 
            else 
            {
                key1[c].press(false);  // tell the button it is NOT pressed
            }
        }
    }

  
    if (FcnPage == 1)
    {
        for (uint8_t c = 0; c < 24; c++) 
        {   // Check if any key has changed state

            tft.setFreeFont(LABEL1_FONT);
    
            if (key1[c].justReleased()) key1[c].drawButton();     // draw normal

            if (key1[c].justPressed()) 
            {
                key1[c].drawButton(true);  // draw invert


                if (c == 21) 
                {
                    if (millis() - DebounceTime < 500) 
                    {
		                return ;
	                }
	                DebounceTime = millis() ;
                    FcnPage ++ ;
                    if (FcnPage >= 2) FcnPage = 0 ;
                    Fonction = -1 ;
                }

                if (c == 23) 
                {
                    Mymenu = 10 ;
                }    
            }
        }
    } 
    // End of Fonction 0 to 14 Section

 
    //======**** 4 Top Btn Section ****==============

    for (uint8_t d = 0; d < 4; d++) 
    {
        if (pressed && key2[d].contains(t_x, t_y)) 
        {
            key2[d].press(true);  // tell the button it is pressed
        } 
        else 
        {
            key2[d].press(false);  // tell the button it is NOT pressed
        }
    }
  
    for (uint8_t d = 0; d < 4; d++) 
    {    //Check if any key has changed state

        tft.setFreeFont(LABEL1_FONT);

        if (TFTpowerCur!= PowerState && (PowerState == 1 ))
        {
            key2[0].drawButton();  // draw invert
            TFTpowerCur = PowerState ;
        }

        if (TFTpowerCur!= PowerState && (PowerState == 0 ))
        {
            key2[0].drawButton(true);
            TFTpowerCur = PowerState ;
        }

        if (d >= 1)
        {
            if (key2[d].justReleased()) key2[d].drawButton();     // draw normal 
        }

        if (key2[d].justPressed()) 
        {
            //key2[d].drawButton(true);  // draw invert
    
            if (d == 0) 
            {
                PowerState ++;
                if  (PowerState >= 2)  PowerState = 0 ;
                Serial.print("PowerState = ") ;
                Serial.println(PowerState) ;      
            }

            if (d == 1) 
            {
                key2[d].drawButton(true);
                Serial.println("key 1 working") ;
            }

            if (d == 2) 
            {
                key2[d].drawButton(true);
                Serial.println("key 2 working") ;
            }

            if (d == 3) 
            {
                key2[d].drawButton(true);
                Serial.println("key 3 working") ;
            }
        }
    } 
    // End of 4 Top Btn Section 
} 
// END OF LOOP (Need to corect as fonction)


 //==========***** Loco Dirction Section *****=========

void TFTdirection() 
{

    if (Mymenu == 0 ) 
    {
        if (LocoDirection == 1) 
        {
            tft.fillRect(231, 52, 90, 40,TFT_WHITE);
            tft.setTextSize(1);tft.setTextDatum(MC_DATUM);
            tft.setFreeFont (LABEL3_FONT);
            //tft.setTextPadding(0);
            tft.setTextColor(TFT_BLACK , TFT_WHITE);
            tft.drawString("FWR", 272, 72) ;
            delay(50);
            //TFTdir = LocoDirection ;

        }
            
        if (LocoDirection == 0) 
        {
            tft.fillRect(231, 52, 90, 40,TFT_WHITE);
            tft.setTextSize(1);tft.setTextDatum(MC_DATUM);
            tft.setFreeFont (LABEL3_FONT);
            //tft.setTextPadding(0);
            tft.setTextColor(TFT_BLACK , TFT_WHITE);
            tft.drawString("REV", 272, 72);
            delay(50);
            //TFTdir= LocoDirection ;
        }
    }
} 
// End of Loco Direction section
#endif