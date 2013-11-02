
const int kPin0 = 0; //set first pin #
const int kNumOfPins = 2;
int pins[kNumOfPins];
int vals[kNumOfPins]; //threshold values
int baudRate = 9600;

void setup() 
{
  for (int i=0; i<kNumOfPins; i++) {
    pins[i] = kPin0+i;
    pinMode(pins[i], OUTPUT);
  }
  Serial.begin(baudRate);
  establishContact();
}

void loop()
{
  if (Serial.available()>0) {
    if (Serial.read()==1) {
      for (int i=0; i<kNumOfPins-1; i++) {
        //Serial.println(digitalRead(pins[i]));
        Serial.print(digitalRead(pins[i]));
        Serial.print(",");
      }
      Serial.print(digitalRead(pins[kNumOfPins-1]));
      Serial.println();
    }
    else if (Serial.read()==2)
    {
      for (int i=0; i<kNumOfPins; i++) {
        vals[i] = Serial.read();
      }
    }
  }
  delay(1000);
}

void establishContact() {
  while (Serial.available()<=0) {
    Serial.println(0);
    delay(1000);
  }
}

