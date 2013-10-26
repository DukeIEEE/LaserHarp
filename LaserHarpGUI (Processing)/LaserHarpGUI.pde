

import processing.serial.*;
import g4p_controls.*;

Serial myPort;
int kPin0 = 2;
int kNumOfPins = 12;
int[] vals = new int[kNumOfPins];
boolean calibrate = false;

GLabel[] myLabels = new GLabel[kNumOfPins];
GTextField[][] textfield = new GTextField[kNumOfPins][2];
GButton button;

String s;
boolean firstContact = false;

void setup() {
  size(500, 600, JAVA2D);
  //createGUI();
  customGUI();
}

void draw() {
  background(230);
}

public void customGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setCursor(ARROW);
  if(frame != null) {
    frame.setTitle("Sketch Window");
  }
  for (int i=0; i<kNumOfPins; i++) {
    myLabels[i] = new GLabel(this, 20, 20+40*i, 80, 20);
    myLabels[i].setText(String.valueOf(kPin0+i));
    myLabels[i].setOpaque(false);
  }
  for(int i=0; i<kNumOfPins; i++) {
    textfield[i][0] = new GTextField(this, 120, 20+40*i, 160, 30, G4P.SCROLLBARS_NONE);
    textfield[i][0].setOpaque(true);
    textfield[i][0].addEventHandler(this, "textfieldChange");
    textfield[i][1] = new GTextField(this, 300, 20+40*i, 160, 30, G4P.SCROLLBARS_NONE);
    textfield[i][1].setOpaque(true);
    textfield[i][1].addEventHandler(this, "textfieldChange");
  }
  button = new GButton(this, 340, 540, 80, 30);
  button.setText("Calibrate");
  button.addEventHandler(this, "buttonClick");
}

public void textfieldChange(GTextField source, GEvent event) {
  // println("GTextField event occurred at " + System.currentTimeMillis()%10000000 );
}

public void buttonClick(GButton source, GEvent event) {
  calibrate = true;
}

void serialEvent(Serial myPort) {
  s = myPort.readStringUntil('\n');
  if (s!=null) {
    s = trim(s);
    // println(val);
    if (!firstContact) {
      if (s=="x") {
        firstContact = true;
        myPort.clear();
        myPort.write(1);
        println("contact");
      }
    }
    else {
      println(s);
      if (mousePressed == true)
      {
        myPort.write(1);
        println("1");
      }
      if (calibrate) {
        calibrate = false;
        myPort.write('c');
      }

      myPort.write("A");
    }
  }
}

