#ifndef HARP_SETTINGS_H
#define HARP_SETTINGS_H
//This file defines settings for the laser harp

#define PINS 70 //number of digital and analog pins on microcntroller

struct HarpSettings {
  byte bank; //music bank
  byte instrument; //instrument
  
  byte note[PINS]; //maps pins to the MIDI note values (i.e. note[A1] maps pin A1 to MIDI value given in note[A1]
  bool enabled[PINS]; //true if pin is enabled and should play a note
  byte onVelocity; //velocity when note pressed
  byte offVelocity; //velocity when note released
};

#endif
