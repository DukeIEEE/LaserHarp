#include <Arduino.h>
#include "HarpSettings.h"
#include <SoftwareSerial.h>

HarpSettings settings;
SoftwareSerial mySerial(2, 3); // RX, TX
boolean on[PINS]; //keeps track of whether the laser is on or not

const byte resetMIDI = 4; //Tied to VS1053 Reset line
const byte ledPin = 13; //MIDI traffic inidicator

void setup() {
  initializeSettings(settings);
  initializeMIDI();
  initializeHarp();
}

void loop() {
  for(int i = 0; i < PINS; ++i) {
    if(!settings.enabled[i]) continue;
    boolean laserOn = RCtime(i) < settings.threshold[i];
    if(laserOn != on[i]) {
      //state changed
      on[i] = laserOn;
      if(laserOn)
        noteOff(0, settings.note[i], settings.onVelocity);
      else
        noteOn(0, settings.note[i], settings.offVelocity);
    }
  }
}

void initializeHarp() {
  for(int i = 0; i < PINS; ++i)
    on[i] = false;
    
  setLightThresholds();
}

void setLightThresholds() {
  //set the threshold values for each photodiode
  for(int i = 0; i < PINS; ++i) {
    if(!settings.enabled[i]) continue;
    //loop through 10 times and choose maximum value
    int maxTime = 0;
    for(int j = 0; j < 10; ++j) {
      int time = RCtime(i);
      if(time > maxTime)
        maxTime = time;
    }
    //finally set the treshold
    settings.threshold[i] = (int)(maxTime * 1.1);
  }
}


long RCtime(int sensPin){
   long result = 0;
   pinMode(sensPin, OUTPUT);       // make pin OUTPUT
   digitalWrite(sensPin, HIGH);    // make pin HIGH to discharge capacitor - study the schematic
   delay(1);                       // wait a  ms to make sure cap is discharged

   pinMode(sensPin, INPUT);        // turn pin into an input and time till pin goes low
   digitalWrite(sensPin, LOW);     // turn pullups off - or it won't work
   while(digitalRead(sensPin)){    // wait for pin to go low
      result++;
      if(result > settings.threshold[sensPin]) //If the result is greater than the light threshold, stop because we know the laser is not there
      {
        return result + 100; // Return a big number. The laser isn't there
      }
   }

   return result;                   // report results   
}   

