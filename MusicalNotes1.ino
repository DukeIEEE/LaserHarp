void setup() {
  Serial.begin(31250);
}
 int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 //higher velocity usually makes MIDI instruments louder
 
 int noteON = 144;//144 = 10010000 in binary, note on command
 int noteOFF = 128;//128 = 10000000 in binary, note off command

int on = 0;

void loop() {
  int val = analogRead(A4);
  //Serial.println(val);
    if(val < 100) {
    if(on != 1) {
        MIDImessage(noteON, 50, velocity); 
    }
    on = 1;
  } else {
   if(on == 1)
    MIDImessage(noteOFF, 50, velocity);
    on = 0;
  }
}


//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}


