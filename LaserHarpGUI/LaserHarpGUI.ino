

int pin0 = 2; //set first pin #
int numOfPins = 49;
int pins[numOfPins];
int vals[numOfPins];

void setup() 
{
  for (int i=0; i<numOfPins; i++) {
    pin[i] = 2 + i;
    pinMode(pin[i], OUTPUT);
  }
  Serial.begin(9600);
  establishContact();
}

void loop()
{
  if (Serial.available()>0) {
    if (strcmp(Serial.read(),"read")==0) {
      for (int i=0; i<numOfPins; i++) {
        vals[i] = Serial.read();
      }
    }
    else if (strcmp(Serial.read(),"write")==0)
    {
      for (int i=0; i<numOfPins; i++) {
        digitalWrite(pin[i], Serial.read());
      }
    }
  }
  else {
    for(int i=0; i<numOfPins; i++) {
      Serial.println(vals[i]);
    }
  }
  delay(1000);
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("no contact");
    delay(1000);
  }
}

