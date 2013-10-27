

import processing.serial.*;
import g4p_controls.*;

Serial myPort;
int kPin0;
int kNumOfPins;
// int[] vals = new int[kNumOfPins];
boolean calibrate = false;

GLabel[] labels = new GLabel[kNumOfPins];
GTextField[][] textFields = new GTextField[kNumOfPins][2];
GButton button;

String s;
boolean contact = false;

void setup() {
  size(500, 600, JAVA2D);
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background(230);
}

public void startGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setCursor(ARROW);
  if(frame != null) {
    frame.setTitle("Sketch Window");
  }
  for (int i=0; i<kNumOfPins; i++) {
    labels[i] = new GLabel(this, 20, 20+40*i, 80, 20);
    labels[i].setText(String.valueOf(kPin0+i));
    labels[i].setOpaque(false);
  }
  for(int i=0; i<kNumOfPins; i++) {
    textFields[i][0] = new GTextField(this, 120, 20+40*i, 160, 30, G4P.SCROLLBARS_NONE);
    textFields[i][0].setOpaque(true);
    textFields[i][0].addEventHandler(this, "textFieldsChange");
    textFields[i][1] = new GTextField(this, 300, 20+40*i, 160, 30, G4P.SCROLLBARS_NONE);
    textFields[i][1].setOpaque(true);
    textFields[i][1].addEventHandler(this, "textFieldsChange");
  }
  button = new GButton(this, 340, 540, 80, 30);
  button.setText("Calibrate");
  button.addEventHandler(this, "buttonClick");
}

public void textFieldsChange(GTextField source, GEvent event) {
  // println("GTextField event occurred at " + System.currentTimeMillis()%10000000 );
}

public void buttonClick(GButton source, GEvent event) {
  calibrate = true;
}

void serialEvent(Serial myPort) {
  s = myPort.readStringUntil('\n');
  if (!contact && s==null) {
    println("no contact");
  }
  else if (!contact && s!=null) {
    kPin0 = Integer.parseInt(trim(s));
    kNumOfPins = Integer.parseInt(myPort.readStringUntil('\n'));
    myPort.clear();
    startGUI();
    println("contact");
    contact = true;
  }
  else if (contact && s!=null) {
    for (int i=0; i<kNumOfPins; i++) {
      textFields[i][0].setText(myPort.readStringUntil('\n'));
    }
  }
  if (mousePressed)
  {
    myPort.write(1);
    // println(1);
  }
  if (calibrate) {
    myPort.write('c');
    for (int i=0; i<kNumOfPins; i++) {
      myPort.write(textFields[i][1].getText());
    }
    calibrate = false;
  }
}

