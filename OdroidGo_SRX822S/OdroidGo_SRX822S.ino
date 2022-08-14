/*
  F4GMU
  SRX822S simple receiver on Odroid-GO
  Wiring :
  (SRX) VCC and CS - 6 (Odroid-Go)
  (SRX)       DATA - 4 (Odroid-Go)
  (SRX)        GND - 1 (Odroid-Go)

  Board :
  ESP32 Wrover kit (all versions)
  -speed 921600
  -CPU 240MHz (Wifi/BT)
  -Flash Freq : 80MHz
  -Flash mode : QIO
  -Flash size : 4MB (32Mb)
  
  Library (included in github repo):  
  https://github.com/djecom1/ODROID-GO/
*/

#include <odroid_go.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int posLigne = 10;

void setup() {
  Serial.begin(38400);

  GO.begin();
  GO.lcd.println("SRX882S     F4GMU v0.1");
  GO.lcd.setCursor(10, 70);
  GO.lcd.println("PRESS B TO CLEAR DISPLAY");
  GO.Speaker.setVolume(1);
  delay(1000);
  
  mySwitch.enableReceive(digitalPinToInterrupt(15));//connect the module pin to GPIO4
  
}

void loop() {
    GO.update();
    trameReceived();
    checkButton();    
}

void trameReceived() {
    if (mySwitch.available()) {

    /*
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );
    */

    GO.lcd.setCursor(0, posLigne);
    GO.lcd.setTextSize(1);
    GO.lcd.setTextFont(4);
    GO.lcd.setTextColor(GREEN);
    GO.lcd.print("Received: ");
    GO.lcd.print( mySwitch.getReceivedValue() );
    GO.lcd.print(" / ");
    GO.lcd.print( mySwitch.getReceivedBitlength() );
    GO.lcd.println(" bit");
    //GO.lcd.print("Protocol : ");
    //GO.lcd.println( mySwitch.getReceivedProtocol() );
    posLigne = (posLigne + 30);

    mySwitch.resetAvailable();
    }
    return;
}

void checkButton() {
  if (GO.BtnB.wasPressed()) {
        GO.lcd.clearDisplay();
        //GO.Speaker.tone(3000, 200);
        GO.Speaker.beep();
        posLigne = 10;
        return;
    }
}
