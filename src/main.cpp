#include <Arduino.h>
#include <pin_define.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

LiquidCrystal_I2C lcd(0x27,20,4);

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int distance;
int last_distance;


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Wireless");
  lcd.setCursor(2, 1);
  lcd.print("Tape Measure");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("0-400 CM");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
}

void loop()
{
  static unsigned long distance_fillter;
  if ((millis() - distance_fillter) > 200)
  {
    distance = sonar.ping_cm();
    distance_fillter = millis();
  }
  if (distance != last_distance){
    if (distance < 380)
    {
      lcd.setCursor(10, 1);
      if (distance > 99)
      {
        lcd.print(String(distance) + " ");
      }
      else if (distance <= 99)
      {
        lcd.print(String(distance) + "  ");
      }
      lcd.setCursor(14, 1);
      lcd.print("CM");
    }
    else if (distance >=380){
      lcd.setCursor(10, 1);
      lcd.print("OL     ");
    }
    last_distance = distance;
  }
}