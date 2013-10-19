

#define NUM_NOTES 13

int sensorPin = 13;              // 220 or 1k resistor connected to this pin
long result = 0;

const int noteON = 144;//144 = 10010000 in binary, note on command
const int noteOFF = 128;//128 = 10000000 in binary, note off command
const int light_threshold = 10;
int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
int notes[NUM_NOTES] = {48,49,50,51,52,53,54,55,56,57,58,59,60};
boolean on[NUM_NOTES];
void setup()                    // run once, when the sketch starts
{
  //Initialize the note array
  for(int i=0;i<NUM_NOTES;i++)
  {
    on[i]=0;
  }
   Serial.begin(31250);
   //Serial.begin(4800);
  
}
void loop()                     // run over and over again
{
 for(int i=2;i<14;i++){
   int time = RCtime(i); // Figure out the time constant of the RC circuit
//Serial.println( time );
   int laser_present = time<light_threshold; //See if the laser is present
   //Serial.println(laser_present);
   if(laser_present!=on[i-2]) //If the laser state is different than its previous state, we need to do stuff
   {
     //Serial.println("sending stuff...");
     on[i-2] = laser_present; // Set the state to the current value
     if(laser_present) // If the laser is here, play a note
     {
       MIDImessage(noteON, notes[i-2], velocity); //Turn the note on
     }
     else{
       MIDImessage(noteOFF, notes[i-2], velocity); //Turn the note off
     }
    // Serial.println("*************************");
   }
   
 }
 //Serial.println("*****************************");
 //delay(2000);
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
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
      if(result>light_threshold) //If the result is greater than the light threshold, stop because we know the laser is not there
      {
        return result+100; // Return a big number. The laser isn't there
      }
   }

   return result;                   // report results   
}   

