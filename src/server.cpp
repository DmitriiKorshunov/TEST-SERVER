#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Lib for Blynk

//////////////////////////

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//////////////////////////

// Setting for Blynk
//////////////////////////

char auth[] = "rg_Do05VEkRRT5SCAQKvW3v9LM_DgSy3"; // KEY
char ssid[] = "iPhone"; // Username of wifi
char pass[] = "redisochka"; // Password
int buttonState1;
int pinout;
// Widget Blynk LCD

WidgetLCD lcd1(V5); // V5 is number of virtual pin for Blynk

//////////////////////////


//////////////////////////
// Setting LCD display
LiquidCrystal_I2C lcd(0x27,16,2); 
//////////////////////////

void setup()
{
  // Debug console

   // Init wifi
  Wire.begin(22, 21);            // Init I2C bus
  lcd.init();                    // Init display
  lcd.backlight();               // Swith on LED
  delay(1000);                   
  lcd.setCursor(0,0);            
  lcd.print("Smart room"); 
  lcd.setCursor(0,1);
  lcd.print("Version 1.0");
  delay(3000);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Start");
  lcd.setCursor(1,1);
  lcd.print("Initialization");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print(ssid); 
  lcd.setCursor(0,1);
  lcd.print(pass);
  delay(3000);
  Blynk.begin(auth, ssid, pass);
  delay(3000);
  lcd1.print(0,0,"System is ready"); // There is text for Blynk
  lcd.clear();
}
BLYNK_CONNECTED() {
  //запросить информацию у сервера о состоянии пина V1
  Blynk.syncVirtual(pinout);
}

//этот метод будет вызыван после ответа сервера 
BLYNK_WRITE(pinout) {
  lcd.clear();
  lcd.setCursor(0,0);
  buttonState1 = param.asInt();
  lcd.print(buttonState1);
  if (buttonState1 == 1)
  {
  lcd1.clear();
  lcd1.print(0,0,"1st group ON");
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print("1st group ON"); 
  delay(3000);
  lcd.clear();
   lcd1.clear();
  }
  else
  {
  lcd1.clear();
  lcd1.print(0,0,"1st group OFF");
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print("1st group OFF"); 
  delay(3000);
  lcd.clear();
   lcd1.clear();
  }
  }
  
 
void loop()
{
  lcd.setCursor(0,0);
  lcd.print("System is ready");
  lcd1.print(0,0,"System is ready");
  Blynk.run(); 
  pinout = V1;
  Blynk.connected();
  if (buttonState1 == 1)
  {
  
  }
  
}


