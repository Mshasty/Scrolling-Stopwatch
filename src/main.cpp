#include <Arduino.h>
#include <Wire.h>

//#define DEBUG_SERIAL

//#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
//#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
// Text parameters
#define CHAR_SPACING  1 // pixels between characters

// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  8
char message[BUF_SIZE] = " CTAPT ";

#include "LED_output.h"
#include "timing.h"
#include "my_button.h"

void setup()
{
  mx.begin();
  mx.setFont(fontBG);
  mx.setShiftDataInCallback(scrollDataSource);
  //mx.setShiftDataOutCallback(scrollDataSink);
  strcpy(newMessage, "Секундомер ");    
  utf8rus(newMessage).toCharArray(curMessage, 512);

  newMessage[0] = '\0';

  button1.begin();
  button2.begin();

  Serial.begin(57600);
  Serial.print(F("\nStart timer\nMaximum time: 9:59.9\n\n"));
  oldtime = millis();
  //printText(0, MAX_DEVICES-1, message);
  //for (uint8_t i = 0; i < 8 * MAX_DEVICES; i++) {
  for (uint8_t i = 0; i < 70; i++) {
    mx.transform(MD_MAX72XX::TSL);
    delay(SCROLL_DELAY);
  }
  for (uint8_t i = 0; i < 8; i++) {
    mx.transform(MD_MAX72XX::TSU);
    delay(SCROLL_DELAY);
  }
  mx.setFont(ExtASCII);
  printText(0, MAX_DEVICES-1, message);
  delay(2000);
}

void loop()
{
  if (started) {
    newtime = millis();
    if (newtime >= oldtime + 100) {
      oldtime = millis();
      NextTime();
      printText(0, MAX_DEVICES-1, message);
    }
  }
  if (pressed) {
    if (millis() > keytime)
      pressed = false;
  } else {
    switch( button1.Loop() ){
      case SB_CLICK:
        if (stopped) {
          oldtime = millis();
          stopped = false;
          started = true;
          paused = false;
          myTime = 0;
          Serial.println(F("Start counting"));
        } else if (paused && started) {
          //stopped = true;
          started = false;
          ;paused = false;
          Serial.println(F("Stop counting"));
          keytime = millis() + 2000; // игнор кнопок 2 секунды
          pressed = true;
        } else
          Serial.println(F("Pressed button 1"));
        break;
      case SB_LONG_CLICK:
        if (paused || stopped || !started) {
          //message[BUF_SIZE] = " CTAPT ";
          printText(0, MAX_DEVICES-1, " CTAPT \0");
          started = false;
          paused = false;
          stopped = true;
          keytime = millis() + 2500; // игнор кнопок 2.5 секунды
          pressed = true;
          Serial.println(F("Reset all counter"));
        } else 
          Serial.println(F("Holded button 1"));
        break;
    }
    switch( button2.Loop() ){
      case SB_CLICK:
        if (started) {
          if (paused) {
            paused = false;
            Serial.println(F("Account continued"));
          } else {
            paused = true;
            Serial.println(F("Account suspended"));
          }
          keytime = millis() + 1000; // игнор кнопок 1 секунду
          pressed = true;
        } else
          Serial.println(F("Press button 2"));
        break;
      case SB_LONG_CLICK:
        if (started) {
          started = false;
          Serial.println(F("Account stopped"));
        } else
          Serial.println(F("Holded button 2"));
        break;
    }
  }
}
