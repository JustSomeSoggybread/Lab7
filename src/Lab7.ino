SYSTEM_THREAD(ENABLED);

#include <blynk.h>

#define BLYNK_PRINT Serial

//#include "oled-wing-adafruit.h"

BlynkTimer timer;

boolean buttonEnabled = true;

//OledWingAdafruit display;

void setup() {
  Blynk.begin("ko3xEgY1CtzZLGjHWlJ4DPUOsoZLNmmr", IPAddress(167, 172, 234, 162), 9090);
  
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(D3, INPUT);

  timer.setInterval(1000, tempDisplay);
  
}

void loop() {
  Blynk.run();
  timer.run();

/*
  if (display.pressedA() && buttonEnabled){
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    Blynk.notify("Hey, got a push notification!");
    display.println("Push sent");
    display.display();
    buttonEnabled = false;
    timer.setTimeout(5000, enableTimerCall);
  }
*/
  if (digitalRead(D3) == HIGH && buttonEnabled){
    Blynk.notify("Got a push notification");
    Serial.println("Push sent");
    buttonEnabled = false;
    timer.setTimeout(5000, enableTimerCall);
  }
}

void tempDisplay(){
  if (buttonEnabled){
    uint64_t reading = analogRead(A4);

    double voltage = (reading * 3.3) / 4095.0;

    double temperature = (voltage - 0.5) * 100;
/*
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(temperature);
    display.println(" C");
    display.print(temperature);
    display.println(" F");
    display.display();
*/
    

    Serial.print(temperature);
    Serial.println(" C");
  }
}

void enableTimerCall(){
  buttonEnabled = true;
}