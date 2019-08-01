#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Lib for Blynk

//////////////////////////

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//////////////////////////


// Lib for Blynk

//////////////////////////

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//////////////////////////


// Lib for CAN

//////////////////////////

#include <ESP32CAN.h>
#include <CAN_config.h>
#include <ESP32CAN.h>

// Setting for Blynk
//////////////////////////

char auth[] = "rg_Do05VEkRRT5SCAQKvW3v9LM_DgSy3"; // KEY
char ssid[] = "SPEECH_405"; // sername of wifi
char pass[] = "multimodal"; // Password
int buttonState1;


//////////////////////////

// Setting for CAN
//////////////////////////
CAN_device_t CAN_cfg;

int l1; // Lamp group 1
int l2; // Lamp group 2
int l3; // Lamp group 3
int l4; // Lamp group 4
int s1; // Lamp group status 1
int s2; // Lamp group status 2
int s3; // Lamp group status 3
int s4; // Lamp group status 4
//////////////////////////


// Widget Blynk LCD

WidgetLCD lcd1(V5); // V5 is number of virtual pin for Blynk

//////////////////////////


//////////////////////////
// Setting LCD display
LiquidCrystal_I2C lcd(0x27,16,2); 
//////////////////////////

// SEND CAN 
//////////////////////////////////
void sendcan()
{
CAN_frame_t rx_frame;
rx_frame.FIR.B.FF = CAN_frame_std;
      rx_frame.MsgID = 1;
      rx_frame.FIR.B.DLC = 8;
      rx_frame.data.u8[0] = l1;
      rx_frame.data.u8[1] = l2;
      rx_frame.data.u8[2] = l3;
      rx_frame.data.u8[3] = l4;
      rx_frame.data.u8[4] = s1;
      rx_frame.data.u8[5] = s2;
      rx_frame.data.u8[6] = s3;
      rx_frame.data.u8[7] = s4;
      ESP32Can.CANWriteFrame(&rx_frame);
}
//////////////////////////////////


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
  
  // Init CAN
  CAN_cfg.speed=CAN_SPEED_1000KBPS;
  CAN_cfg.tx_pin_id = GPIO_NUM_3;
  CAN_cfg.rx_pin_id = GPIO_NUM_1;
    /* create a queue for CAN receiving */
  CAN_cfg.rx_queue = xQueueCreate(10,sizeof(CAN_frame_t));
    //initialize CAN Module
  ESP32Can.CANInit();
}

 





 
void loop()
{
  
  lcd.setCursor(0,0);
  lcd.print("System is ready");
  lcd1.print(0,0,"System is ready");
  Blynk.run(); 
  Blynk.connected();
  

  // Blynk.disconnect();
} 


//////////////////////////////////
// Sync data from server

BLYNK_CONNECTED() 
{
  Blynk.syncVirtual(V1); 
    Blynk.syncVirtual(V2); 
      Blynk.syncVirtual(V3); 
        Blynk.syncVirtual(V4); 
}


BLYNK_WRITE(V1) {
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
  l1=1;
  sendcan();
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
  l1=0;
  sendcan();
  }
  }

  BLYNK_WRITE(V2) {
  lcd.clear();
  lcd.setCursor(0,0);
  buttonState1 = param.asInt();
  lcd.print(buttonState1);
  if (buttonState1 == 1)
  {
  lcd1.clear();
  lcd1.print(0,0,"2nd group ON");
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print("2nd group ON"); 
  delay(3000);
  lcd.clear();
  lcd1.clear();
  l2=1;
  sendcan();
  }
  else
  {
  lcd1.clear();
  lcd1.print(0,0,"2nd group OFF");
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print("2nd group OFF"); 
  delay(3000);
  lcd.clear();
  lcd1.clear();
  l2=0;
  sendcan();
  }
  }

  BLYNK_WRITE(V3) {
  lcd.clear();
  lcd.setCursor(0,0);
  buttonState1 = param.asInt();
  lcd.print(buttonState1);
  if (buttonState1 == 1)
  {
  lcd1.clear();
  lcd1.print(0,0,"3rd group ON");
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print("3rd group ON"); 
  delay(3000);
  lcd.clear();
  lcd1.clear();
  l3=1;
  sendcan();
  }
  else
  {
  lcd1.clear();
  lcd1.print(0,0,"3rd group OFF");
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print("3rd group OFF"); 
  delay(3000); 
  l3=0;
  
  lcd.clear();
  lcd1.clear();
  sendcan();
  
  }
  }
  

  BLYNK_WRITE(V4) {
  lcd.clear();
  lcd.setCursor(0,0);
  buttonState1 = param.asInt();
  lcd.print(buttonState1);
  if (buttonState1 == 1)
  {
  lcd1.clear();
  lcd1.print(0,0,"4th group ON");
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print("4th group ON"); 
  delay(3000);
  l4=1;
  lcd.setCursor(0,1);            
  lcd.print(l4); 
     delay(3000);
    lcd1.clear();
  lcd.clear();
  sendcan();
 

  
  }
  else
  {
  lcd1.clear();
  lcd1.print(0,0,"4th group OFF");
  lcd.clear();
  lcd.setCursor(0,0);            
  lcd.print("4th group OFF"); 
  delay(3000);
  lcd.clear();
  lcd1.clear();
  l4=0;
  lcd.setCursor(0,1);            
  lcd.print(l4);
  delay(3000);
    lcd1.clear();
  lcd.clear(); 
  sendcan();
    
  }
  }