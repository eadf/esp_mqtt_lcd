
/**
 * A really simple processing app
 * Requires controlP5 and https://github.com/256dpi/processing-mqtt
 */
 
import mqtt.*;
import controlP5.*;

ControlP5 cp5;
String mqttServer = "192.168.0.43";

MQTTClient client;

void setup() {
  size(335,370);
  
  PFont font = createFont("arial",20); 
  cp5 = new ControlP5(this);
  
  int yPos = 25;
  int yDelta = 40;
  for (int i=0; i<6; i++) {
    cp5.addTextfield("line" + i)
       .setPosition(20,yPos)
       .setSize(200,35)
       .setLabel("")
       .setFont(createFont("arial",20))
       .setAutoClear(false)
       ;
       
    cp5.addBang("publishLine" + i)
       .setPosition(240,yPos)
       .setSize(80,35)
       .setLabel("send")
       .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
       ;    
    yPos += yDelta;
  }
  
  yPos += 15;
  cp5.addTextfield("contrastField")
       .setPosition(20,yPos)
       .setSize(200,35)
       .setFont(createFont("arial",20))
       .setAutoClear(false)
       ;
       
    cp5.addBang("publishContrast")
       .setPosition(240,yPos)
       .setSize(80,35)
       .setLabel("Set Contrast")
       .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
       ;    
  textFont(font);
  
  client = new MQTTClient(this);
  client.connect("mqtt://" + mqttServer, "processing");
}

void draw() {}

public void publishLine0() {
  client.publish("/lcd0", cp5.get(Textfield.class,"line0").getText());
}

public void publishLine1() {
  client.publish("/lcd1", cp5.get(Textfield.class,"line1").getText());
}

public void publishLine2() {
  client.publish("/lcd2", cp5.get(Textfield.class,"line2").getText());
}

public void publishLine3() {
  client.publish("/lcd3", cp5.get(Textfield.class,"line3").getText());
}

public void publishLine4() {
  client.publish("/lcd4", cp5.get(Textfield.class,"line4").getText());
}

public void publishLine5() {
  client.publish("/lcd5", cp5.get(Textfield.class,"line5").getText());
}

public void publishContrast() {
  int contrast = int(cp5.get(Textfield.class,"contrastField").getText());
  if (contrast < 55) {
    contrast = 55;
  } else if (contrast > 60) {
    contrast = 60;
  }
  cp5.get(Textfield.class,"contrastField").setText(""+contrast);
  client.publish("/lcd/contrast", ""+contrast);
}