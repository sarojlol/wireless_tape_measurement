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
  //สั่งเริ่มทำงานจอ LCD
  lcd.init();
  lcd.backlight();

  //สั่งหน้าจอ Splash Screen
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Wireless");
  lcd.setCursor(2, 1);
  lcd.print("Tape Measure");
  delay(2000);

  //สั่งพิมตัวอักศรคงที่ลงจอ LCD
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("0-400 CM");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
}

void loop()
{
  //อ่านค่าทุกๆ 200mS
  static unsigned long distance_fillter;
  if ((millis() - distance_fillter) > 150)
  {
    distance = sonar.ping_cm();
    distance_fillter = millis();
  }

  //ถ้าระยะทางที่อ่านไม่เท่าเดิมถึงจะupdateค่าลงจอLCD
  if (distance != last_distance){
    if (distance < 380)
    {
      lcd.setCursor(10, 1);
      //ถ้าค่าตำกว่า 99 ให้ใส่ช่องว่างต่อท้ายช่องเดียว
      if (distance > 99)
      {
        lcd.print(String(distance) + " ");
      }
      //ถ้าค่าน้อยกว่าหรือเท่ากับให้ใส่ช่องว่างต่อท้าง 2 ช่อง
      else if (distance <= 99)
      {
        lcd.print(String(distance) + "  ");
      }
      //แสดงคำว่า CM ต่อท้าย
      lcd.setCursor(14, 1);
      lcd.print("CM");
    }
    //ถ้าค่าเกิน380ให้แสดงคำว่า OL (Over Range)
    else if (distance >=380){
      lcd.setCursor(10, 1);
      lcd.print("OL     ");
    }
    last_distance = distance; //กำหนดให้ค่าที่แล้วเท่ากับค่าปัจจุบัญ
  }
}