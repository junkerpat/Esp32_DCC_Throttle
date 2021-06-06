
#ifndef DCCGetLoco
#define DCCGetLoco

//My File
#include "Arduino.h"
#include "AllVariable.h"
#include "DCCconfig.h"
#include "DCCsend.h"

//Library
#include <FS.h>
#include <WiFi.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <AiEsp32RotaryEncoder.h>

// Keypad start position, key sizes and spacing
#define KEY_X 40 // Centre of key
#define KEY_Y 96
#define KEY_W 62 // Width and height
#define KEY_H 30
#define KEY_SPACING_X 18 // X and Y gap
#define KEY_SPACING_Y 1
#define KEY_TEXTSIZE 1   // Font size multiplier

// Numeric display box size and location
#define DISP_X 3
#define DISP_Y 2
#define DISP_W 315
#define DISP_H 48
#define DISP_TSIZE 3
#define DISP_TCOLOR TFT_CYAN

// Number length, buffer for storing it and character index
#define NUM_LEN 16
char numberBuffer[NUM_LEN + 1] = "";
uint8_t numberIndex = 0;

// We have a status line for messages
#define STATUS_X 160 // Centred on this
#define STATUS_Y 54

// Create 15 keys for the keypad
char keyLabel[20][5] = {"Del", "Back", "Add","Main", "1", "2", "3","L/C", "4", "5", "6", "C","7", "8", "9","D", ".", "0", "#","E" };
uint16_t keyColor[20] = {TFT_RED, TFT_DARKGREY, TFT_DARKGREEN,TFT_DARKGREEN,
                         TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_DARKGREEN,
                         TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_DARKGREEN,
                         TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_DARKGREEN,
                         TFT_BLUE, TFT_BLUE, TFT_BLUE,TFT_DARKGREEN
                        };



// Invoke the TFT_eSPI button class and create all the button objects
TFT_eSPI_Button key[20];

//------------------------------------------------------------------------------------------

void drawKeypad6()
{
  // Draw the keys
  

  	for (uint8_t row = 0; row < 5; row++) 
  	{
    	for (uint8_t col = 0; col < 4; col++) 
    	{
      		uint8_t a = col + row * 4;

      		if (a < 20) tft.setFreeFont(LABEL1_FONT);
      		else tft.setFreeFont(LABEL2_FONT);


      		key[a].initButton(&tft, KEY_X + col * (KEY_W + KEY_SPACING_X),
        			            KEY_Y + row * (KEY_H + KEY_SPACING_Y), // x, y, w, h, outline, fill, text
            			        KEY_W, KEY_H, TFT_RED, keyColor[a], TFT_WHITE,
                		        keyLabel[a], KEY_TEXTSIZE);
      		key[a].drawButton();
    	}
  	}
}

//------------------------------------------------------------------------------------------

// Print something in the mini status bar
void status(const char *msg) 
{
  	tft.setTextPadding(320);
  	tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
  	tft.setTextFont(4);
  	tft.setTextDatum(TC_DATUM);
  	tft.setTextSize(1);
  	tft.drawString(msg, STATUS_X, STATUS_Y);
}

//-----------------------------**** SETUP ****---------------------------------------------


void DCCGetLoco_setup() 
{
  
  	tft.setRotation(3);

  	// Clear the screen
  	tft.fillScreen(TFT_BLACK);

  	// Draw keypad background
  	tft.fillRect(0, 0, 320, 240, TFT_DARKGREY);

  	// Draw number display area and frame
  	tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  	tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_WHITE);

  	// Draw keypad
  	drawKeypad6();
}

//----------------------------**** LOOP ****-------------------------------------------
void DCCGetLoco_loop() 
{

  	if(LocoAddress == 0)
  	{
    	status("No Loco Select") ;
  	}
  	else 
  	{
    	char status_char[24] ;
      	sprintf(status_char , "Active Loco = %d" , LocoAddress) ;
      	status(status_char) ;
  	}

    uint16_t t_x = 0, t_y = 0; // To store the touch coordinates
    int number = LocoAddress;
    char numberstring[(((sizeof number) * CHAR_BIT) + 2)/3 + 2];
    sprintf(numberstring, "%d", number);
    //status(numberstring);

    // Pressed will be set true is there is a valid touch on the screen
    boolean pressed = tft.getTouch(&t_x, &t_y);

    // Check if any key coordinate boxes contain the touch coordinates
  	for (uint8_t a = 0; a < 20; a++) 
  	{
    	if (pressed && key[a].contains(t_x, t_y)) 
    	{
      		key[a].press(true);  // tell the button it is pressed
    	} 
    	else 
    	{
      		key[a].press(false);  // tell the button it is NOT pressed
    	}
  	}

  	// Check if any key has changed state
  	for (uint8_t a = 0; a < 20; a++) 
  	{
    	tft.setFreeFont(LABEL1_FONT);
    	//if (a < 3) tft.setFreeFont(LABEL1_FONT);
    	//else tft.setFreeFont(LABEL1_FONT);

    	if (key[a].justReleased()) key[a].drawButton();     // draw normal

    	if (key[a].justPressed()) 
    	{
      		key[a].drawButton(true);  // draw invert

      		// if a numberpad button, append the relevant # to the numberBuffer
      		if (a >= 4) 
      		{
        		if (numberIndex < NUM_LEN) 
        		{
          			numberBuffer[numberIndex] = keyLabel[a][0];
          			numberIndex++;
          			numberBuffer[numberIndex] = 0; // zero terminate
        		}
        		status(""); // Clear the old status
      		}

      		if (a == 0) 
      		{
        		if (atoi(numberBuffer)!= LocoAddress) 
        		{
          			status("Loco Not Match !");
          			delay(2000);
          			numberIndex = 0; // Reset index to 0
          			numberBuffer[numberIndex] = 0; // Place null in buffer
        		}
        		else 
        		{
         			//status("Remove Loco to throttle");
         			AddRemLoco = "-";
         			Serial.print(AddRemLoco);
         			Serial.println(numberBuffer);
         			LocoAddress = atoi(numberBuffer) ;
         			char status_char[24] ;
         			sprintf(status_char , "Loco  %d  Release " , LocoAddress) ;
         			status(status_char) ;
         			delay(2000);
         			SendAdress() ;
         			LocoAddress = (LocoAddress - LocoAddress) ;
         			numberIndex = 0; // Reset index to 0
         			numberBuffer[numberIndex] = 0; // Place null in buffer
        		}
      		}

      		// Del button, so delete last char
      		if (a == 1) 
      		{
        		numberBuffer[numberIndex] = 0;
        		if (numberIndex > 0) 
        		{
          			numberIndex--;
          			numberBuffer[numberIndex] = 0;//' ';
        		}
        		status(""); // Clear the old status
      		}

      		if (a == 2) 
      		{
        		if (LocoAddress > 0)
        		{
          			char status_char[30] ;
          			sprintf(status_char , "Remove Loco  %d  First" , LocoAddress) ;
          			status(status_char) ;
          			delay(2000) ;
          			numberIndex = 0; // Reset index to 0
          			numberBuffer[numberIndex] = 0; // Place null in buffer
        		}
        		else 
        		{
        
          			AddRemLoco = "+";
          			Serial.print(AddRemLoco);
          			Serial.println(numberBuffer);
          			LocoAddress = atoi(numberBuffer) ;
          			char status_char[24] ;
          			sprintf(status_char , "Dispatch Loco  %d" , LocoAddress) ;
          			status(status_char) ;
          			delay(2000) ;
          			SendAdress() ;
          			numberIndex = 0; // Reset index to 0
          			numberBuffer[numberIndex] = 0; // Place null in buffer
        		}
        
      		}

      		if (a == 3) 
      		{
        		status("Main Screen");
        		numberIndex = 0; // Reset index to 0
        		numberBuffer[numberIndex] = 0; // Place null in buffer
        		Mymenu = 0 ;
        		//TFTLocoAdresse();
        		status(""); // Clear the old status
      		}

      		if (a == 7) 
      		{
        		GetLocoMode++ ;
        		if (GetLocoMode >= 2)GetLocoMode = 0 ;
        		if (GetLocoMode == 0)
        		{ 
          			status("Mode Single Loco");
          			delay(2000);
          			numberIndex = 0; // Reset index to 0
          			numberBuffer[numberIndex] = 0; // Place null in buffer
          			status(""); // Clear the old status
        		}
        		else 
        		{
          			status("Mode Consiste");
          			delay(2000);
          			numberIndex = 0; // Reset index to 0
          			numberBuffer[numberIndex] = 0; // Place null in buffer
          			status(""); // Clear the old status}
        		}
      		}		

        	if (a == 19) 
        	{
          		// status("Main Screen");
          		// numberIndex = 0; // Reset index to 0
          		// numberBuffer[numberIndex] = 0; // Place null in buffer
          		// Mymenu = 0 ;
          		// //TFTLocoAdresse();
          		// status(""); // Clear the old status
        	}

    		// Update the number display field
      		tft.setTextDatum(TL_DATUM);        // Use top left corner as text coord datum
      		tft.setFreeFont(&FreeSans18pt7b);  // Choose a nicefont that fits box
      		tft.setTextColor(DISP_TCOLOR);     // Set the font colour

      		// Draw the string, the value returned is the width in pixels
      		int xwidth = tft.drawString(numberBuffer, DISP_X + 4, DISP_Y + 12);

      		// Now cover up the rest of the line up by drawing a black rectangle.  No flicker this way
      		// but it will not work with italic or oblique fonts due to character overlap.
      		tft.fillRect(DISP_X + 4 + xwidth, DISP_Y + 1, DISP_W - xwidth - 5, DISP_H - 2, TFT_BLACK);

      		delay(10); // UI debouncing
		}
	}
}

//------------------------------------------------------------------------------------------
#endif