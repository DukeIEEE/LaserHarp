
import processing.serial.*;
import g4p_controls.*;
//import java.lang.*;

Serial myPort;
int kPin0 = 2;
int kNumOfPins = 12;
int[] vals = new int[kNumOfPins];
boolean get = false;
boolean set = false;
int baudRate = 9600;

GLabel[] labels = new GLabel[kNumOfPins];
GTextField[][] textFields = new GTextField[kNumOfPins][2];
GButton getButton;
GButton setButton;

String s = "";
boolean contact = false;

void setup() {
  size(500, 560, JAVA2D);
  startGUI();
  myPort = new Serial(this, Serial.list()[0], baudRate);
  myPort.bufferUntil('\n');
}

void draw() {
//  background(230);
  s = myPort.readStringUntil('\n');
  if (!contact && s==null) {
    println("no contact");
  }
  else if (!contact && s!=null) {
    myPort.clear();
    println("contact");
    contact = true;
  }
  else if (contact && s!=null) {
    s = trim(s);
    if (s.length()>1) {
      vals = int(split(s, ','));
      for (int i=0; i<kNumOfPins; i++) {
        textFields[i][0].setText(""+vals[i]);
        println("Pin "+(i+2)+": "+vals[i]);
      }
    }
  }
  
  if (get) {
    myPort.write(1);
    println(1);
    get = false;
  }
  if (set) {
    myPort.write(2);
    println(2);
    for (int i=0; i<kNumOfPins; i++) {
      if (textFields[i][1].getText()==null) {
        myPort.write(i+2);
        println(i+2);
      }
      else {
        myPort.write(textFields[i][1].getText());
        println(textFields[i][1].getText());
      }
    }
    set = false;
  }
  
//  try {
//    Thread.currentThread().sleep(1000);
//  }
//  catch(Exception e) {
//  }
}

public void startGUI(){
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setCursor(ARROW);
  if(frame != null) {
    frame.setTitle("Laser Harp");
  }
  for (int i=0; i<kNumOfPins; i++) {
    labels[i] = new GLabel(this, 20, 20+40*i, 80, 20);
    labels[i].setText(String.valueOf(kPin0+i));
    //labels[i].setOpaque(true);
  }
  for(int i=0; i<kNumOfPins; i++) {
    textFields[i][0] = new GTextField(this, 120, 20+40*i, 160, 30, G4P.SCROLLBARS_NONE);
    textFields[i][0].setOpaque(true);
    //textFields[i][0].addEventHandler(this, "textFieldsChange");
    textFields[i][1] = new GTextField(this, 300, 20+40*i, 160, 30, G4P.SCROLLBARS_NONE);
    textFields[i][1].setOpaque(true);
  }
  getButton = new GButton(this, 160, 500, 80, 30);
  getButton.setText("Get");
  getButton.addEventHandler(this, "getButtonClick");
  setButton = new GButton(this, 340, 500, 80, 30);
  setButton.setText("Set");
  setButton.addEventHandler(this, "setButtonClick");
}

public void getButtonClick(GButton source, GEvent event) {
  get = true;
}

public void setButtonClick(GButton source, GEvent event) {
  set = true;
}

//public void textFieldsChange(GTextField source, GEvent event) {
//  println("textfield20 - GTextField event occured " + System.currentTimeMillis()%10000000 );
//  get = true;
//}

//void serialEvent(Serial myPort) {
//  s = myPort.readStringUntil('\n');
//  if (!contact && s==null) {
//    println("no contact");
//  }
//  else if (!contact && s!=null) {
//    myPort.clear();
//    println("contact");
//    contact = true;
//  }
//  else if (contact && s!=null) {
//    for (int i=0; i<kNumOfPins; i++) {
//      textFields[i][0].setText(myPort.readStringUntil('\n'));
//    }
//    if (get) {
//      println("get");
//      myPort.write(1);
//      get = false;
//    }
//    if (set) {
//      println("set");
//      myPort.write(2);
//      for (int i=0; i<kNumOfPins; i++) {
//        if (textFields[i][1].getText() == null) {
//          myPort.write(i+2);
//        }
//        else {
//          myPort.write(textFields[i][1].getText());
//        }
//      }
//      set = false;
//    }
//  }
//}

