#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ModbusRTU.h>


#define SLAVE_ID 1
#define INPUT1 39
#define INPUT2 34
#define INPUT3 35
#define INPUT4 13
#define INPUT5 21
#define INPUT6 22
#define INPUT7 15


ModbusRTU mb;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

Adafruit_ADS1115 ads1(0x48);
Adafruit_ADS1115 ads2(0x49);
float Voltage1 = 0.0;
float Voltage2 = 0.0;
float Voltage3 = 0.0;
float Voltage4 = 0.0;
float Voltage5 = 0.0;
float Voltage6 = 0.0;

void setup()
{ Serial.begin(9600, SERIAL_8N1);
  Serial2.begin(9600, SERIAL_8N1);
#if defined(ESP32) || defined(ESP8266)
  mb.begin(&Serial2,4);
#else
  mb.begin(&Serial2,4);
  //mb.begin(&Serial, RXTX_PIN);  //or use RX/TX direction control pin (if required)
  mb.setBaudrate(9600);
#endif
  Wire.begin(16, 17);
  ads1.begin();
  ads2.begin();
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
}

void loop()
{
  float adc0 = ads1.readADC_SingleEnded(0);
  float adc1 = ads1.readADC_SingleEnded(1);
  float adc2 = ads1.readADC_SingleEnded(2);
  float adc3 = ads1.readADC_SingleEnded(3);
  float adc4 = ads2.readADC_SingleEnded(0);
  float adc5 = ads2.readADC_SingleEnded(1);
  
  Voltage1 = (adc0 * 0.1875) / 1000;
  Voltage2 = (adc1 * 0.1875) / 1000;
  Voltage3 = (adc2 * 0.1875) / 1000;
  Voltage4 = (adc3 * 0.1875) / 1000;
  Voltage5 = (adc4 * 0.1875) / 1000;
  Voltage6 = (adc5 * 0.1875) / 1000;

 
  Serial.print("Voltages\n");
  Serial.print(" ");
  Serial.println(Voltage1 * 2.5, 3);
  Serial.print(" ");
  Serial.println(Voltage2 * 2.5, 3);
  Serial.print(" ");
  Serial.println(Voltage3 * 2.5, 3);
  Serial.print(" ");
  Serial.println(Voltage4 * 2.5, 3);
  Serial.print(" ");
  Serial.println(Voltage5 * 2.5, 3);
  Serial.print(" ");
  Serial.println(Voltage6 * 2.5, 3);

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
 
  
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Voltage");
  display.setCursor(90, 0);
  display.println("Inputs");
  display.setCursor(5, 8);
  display.println(Voltage1 * 2.5);
  display.setCursor(5, 16);
  display.println(Voltage2 * 2.5);
  display.setCursor(5, 24);
  display.println(Voltage3 * 2.5);
  display.setCursor(5, 32);
  display.println(Voltage4 * 2.5);
  display.setCursor(5, 40);
  display.println(Voltage5 * 2.5);
  display.setCursor(5, 48);
  display.println(Voltage6 * 2.5);
  display.display();
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
  mb.addHreg(1);
  mb.Hreg(1,100);
  mb.addHreg(2);
  mb.Hreg(2,Voltage1*2.5);
  mb.addHreg(3);
  mb.Hreg(3,Voltage2*2.5);
  mb.addHreg(4);
  mb.Hreg(4,Voltage3*2.5);
  mb.addHreg(5);
  mb.Hreg(5,Voltage4*2.5);
  mb.addHreg(6);
  mb.Hreg(6,Voltage5*2.5);
  mb.addHreg(7);
  mb.Hreg(7,Voltage6*2.5);

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
