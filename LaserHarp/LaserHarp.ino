

const int kPin0 = 2; //set first pin #
const int kNumOfPins = 12;
int pins[kNumOfPins];
int vals[kNumOfPins]; //threshold values

void setup() 
{
  for (int i=0; i<kNumOfPins; i++) {
    pins[i] = kPin0+i;
    pinMode(pins[i], OUTPUT);
  }
  Serial.begin(9600);
  establishContact();
}

void loop()
{
  if (Serial.available()>0) {
    if (Serial.read()==1) {
      for (int i=0; i<kNumOfPins; i++) {
        Serial.println(digitalRead(pins[i]));
      }
    }
    else if (Serial.read()=='c')
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
    Serial.println(kPin0);
    Serial.println(kNumOfPins);
    delay(1000);
  }
}

