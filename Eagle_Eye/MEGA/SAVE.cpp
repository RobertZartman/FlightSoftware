/**
 * Save.cpp fills out the 'time capsule' with all the current data and saves it to the SD cards.
 *    This happens every time the program cycles. This replaces the old way of saving every individual
 *    event/altitude/etc.. Now is it saved in one decently long string that is seperated by commas -> ','
 */


#include "SAVE.h"
#include "DATA.h"
#include "Globals.h"
#include <Arduino.h>
#include <SD.h>


/**
 * Constructor used to reference all other variables & functions.
 */
SAVE::SAVE()
{
  
}


/**
 * Manages the saving process. For a more detailed explanation, bug James. 
 *
 *    Capsule -> "Altitude, TempExt, Pressure, Roll, Pitch, Yaw, LoRa Event, Mega Event"
 *                    1        2         3       4     5     6       7           8
 */
void SAVE::saveData()
{
	
	//All flight data is consolidated into one char array. All values are casted (turned into) to chars
  //   to be saved.
  char temp[] = {char(Data.Local.GPSTime),
                 ',',
                 char(Data.Local.Altitude),
                 ',',
                 char(Data.Local.Latitude),
                 ',',
                 char(Data.Local.Longitude),
                 ',',
                 char(Data.Local.GPSSpeed),
                 ',',
                 char(Data.Local.GPSTargetDistance),
                 ',',
                 char(Data.Local.LE),
                 ',',
                 char(Data.Local.ME)
                };

  //File object used to access the SD card.
  File Storage;
  
  //Opens up SD card and saves the data capsule.
  Storage = SD.open("MEGA_FltData", FILE_WRITE);
  Storage.println(temp);
  Storage.close();
  
  //Resets Local.LE & Local.ME to prevent repeated recording of the same event over multiple cycles.
  Data.Local.LE = 0;
  Data.Local.ME = 0;
}


/**
 * Assigns correct pin to connect to the SD card. Tests connection.
 */
void SAVE::initialize()
{
	//Sets GPIO pin 53 to communicate to the SD card.
	pinMode(SD_PIN, OUTPUT);
	
	//Checks for physical and data connection through the pin assigned above.
	//   If invalid connection, the program will stall and print an error message.
	if(!SD.begin(SD_PIN)){
		//Serial.println("PROBLEM WITH SD CARD.");
		//while(1);
	}
	//Valid connection, program proceeds as planned.
	else{
		//Serial.println("SD Card Online.");
	}
}