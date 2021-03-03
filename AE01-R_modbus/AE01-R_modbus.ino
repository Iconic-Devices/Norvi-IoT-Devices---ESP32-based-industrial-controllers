#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ModbusRTU.h>


#define SLAVE_ID 1
#define INPUT1 18
#define INPUT2 39
#define INPUT3 34
#define INPUT4 35
#define INPUT5 19
#define INPUT6 21
#define INPUT7 22
#define INPUT8 23


#define OUTPUT1 14
#define OUTPUT2 12
#define OUTPUT3 13
#define OUTPUT4 15  
#define OUTPUT5 2
#define OUTPUT6 33

ModbusRTU mb;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

void setup()
{
  Serial.begin(9600, SERIAL_8N1);
#if defined(ESP32) || defined(ESP8266)
  mb.begin(&Serial,4);
#else
  mb.begin(&Serial,4);
  //mb.begin(&Serial, RXTX_PIN);  //or use RX/TX direction control pin (if required)
  mb.setBaudrate(9600);
#endif
  Wire.begin(16, 17);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //starting the display
  display.display();
  delay(2000);
  display.clearDisplay();
  pinMode(INPUT1,INPUT);
  pinMode(INPUT2,INPUT);
  pinMode(INPUT3,INPUT);
  pinMode(INPUT4,INPUT);
  pinMode(INPUT5,INPUT);
  pinMode(INPUT6,INPUT);
  pinMode(INPUT7,INPUT);
  pinMode(INPUT8,INPUT);
  
  pinMode(OUTPUT1,OUTPUT);
  pinMode(OUTPUT2,OUTPUT);
  pinMode(OUTPUT3,OUTPUT);
  pinMode(OUTPUT4,OUTPUT);
  pinMode(OUTPUT5,OUTPUT);
  pinMode(OUTPUT6,OUTPUT);
}

void loop()
{
  
 
  Serial.print("INPUTS\n");
  Serial.print(" ");
  Serial.println(digitalRead(INPUT1));
  Serial.print(" ");
  Serial.println(digitalRead(INPUT2));
  Serial.print(" ");
  Serial.println(digitalRead(INPUT3));
  Serial.print(" ");
  Serial.println(digitalRead(INPUT4));
  Serial.print(" ");
  Serial.println(digitalRead(INPUT5));
  Serial.print(" ");
  Serial.println(digitalRead(INPUT6));
  Serial.print(" ");
  Serial.println(digitalRead(INPUT7));



  Serial.print("OUTPUTS\n");
  Serial.print(" ");
  Serial.println(digitalRead(OUTPUT1));
  Serial.print(" ");
  Serial.println(digitalRead(OUTPUT2));
  Serial.print(" ");
  Serial.println(digitalRead(OUTPUT3));
  Serial.print(" ");
  Serial.println(digitalRead(OUTPUT4));
  Serial.print(" ");
  Serial.println(digitalRead(OUTPUT5));
  Serial.print(" ");
  Serial.println(digitalRead(OUTPUT6));
 
  
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Outputs");
  display.setCursor(90, 0);
  display.println("Inputs");
  display.setCursor(5, 8);
  display.println(digitalRead(OUTPUT1));
  display.setCursor(5, 16);
  display.println(digitalRead(OUTPUT2));
  display.setCursor(5, 24);
  display.println(digitalRead(OUTPUT3));
  display.setCursor(5, 32);
  display.println(digitalRead(OUTPUT4));
  display.setCursor(5, 40);
  display.println(digitalRead(OUTPUT5));
  display.setCursor(5, 48);
  display.println(digitalRead(OUTPUT6));

  
  display.setCursor(100, 8);
  display.println(digitalRead(INPUT1));
  display.setCursor(100, 16);
  display.println(digitalRead(INPUT2));
  display.setCursor(100, 24);
  display.println(digitalRead(INPUT3));
  display.setCursor(100, 32);
  display.println(digitalRead(INPUT4));
  display.setCursor(100, 40);
  display.println(digitalRead(INPUT5));
  display.setCursor(100, 48);
  display.println(digitalRead(INPUT6));
  display.setCursor(100, 54);
  display.println(digitalRead(INPUT7));
  display.display();
  delay(1000);
  
  display.clearDisplay();
  mb.slave(SLAVE_ID);
  mb.addCoil(1);
  mb.Coil(1);
  mb.addCoil(2);
  mb.Coil(2);
  mb.addCoil(3);
  mb.Coil(3);
  mb.addCoil(4);
  mb.Coil(4);
  mb.addCoil(5);
  mb.Coil(5);
  mb.addCoil(6);
  mb.Coil(6);

 if(mb.Coil(1)==1)
 {
 digitalWrite(14,HIGH);
 }
 else
 {digitalWrite(14,LOW);
 }


 if(mb.Coil(2)==1)
 {
 digitalWrite(12,HIGH);
 }
 else
 {digitalWrite(12,LOW);
 }


 if(mb.Coil(3)==1)
 {
 digitalWrite(13,HIGH);
 }
 else
 {digitalWrite(13,LOW);
 }

  if(mb.Coil(4)==1)
 {
 digitalWrite(15,HIGH);
 }
 else
 {digitalWrite(15,LOW);
 }

  if(mb.Coil(5)==1)
 {
 digitalWrite(2,HIGH);
 }
 else
 {digitalWrite(2,LOW);
 }
 
   if(mb.Coil(6)==1)
 {
 digitalWrite(33,HIGH);
 }
 else
 {digitalWrite(33,LOW);
 }
 
  mb.addIsts(1);
  mb.Ists(1,digitalRead(INPUT1));
  mb.addIsts(2);
  mb.Ists(2,digitalRead(INPUT2));
  mb.addIsts(3);
  mb.Ists(3,digitalRead(INPUT3));
  mb.addIsts(4);
  mb.Ists(4,digitalRead(INPUT4));
  mb.addIsts(5);
  mb.Ists(5,digitalRead(INPUT5));
  mb.addIsts(6);
  mb.Ists(6,digitalRead(INPUT6));
  mb.addIsts(7);
  mb.Ists(7,digitalRead(INPUT7));
  mb.task();
  yield();

  
}
