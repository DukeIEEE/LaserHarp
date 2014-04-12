#include <Arduino.h>
#include "HarpSettings.h"
#include <SoftwareSerial.h>

HarpSettings settings;

SoftwareSerial mySerial(2, 3); // RX, TX

byte note = 0; //The MIDI note value to be played
byte resetMIDI = 4; //Tied to VS1053 Reset line
byte ledPin = 13; //MIDI traffic inidicator

void setup() {
  initializeSettings(settings);
  initializeHarp();
}

void loop() {
}
