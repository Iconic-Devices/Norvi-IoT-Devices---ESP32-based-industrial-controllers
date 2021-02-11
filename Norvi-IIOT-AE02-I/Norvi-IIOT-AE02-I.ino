#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

Adafruit_ADS1115 ads1(0x48);
Adafruit_ADS1115 ads2(0x49);

float Voltage = 0.0;
void setup()
{
  Wire.begin(16, 17);
  Serial.begin(115200);
  ads1.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //starting the display
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop()
{
  float adc1;

  adc1 = ads1.readADC_SingleEnded(1);
  Voltage = (adc1 * 0.1875) ;

  Serial.print("AIN0: ");
  Serial.print(adc1);
  Serial.print("\tVoltage: ");
  Serial.println(Voltage /20, 3);
  Serial.print("\tCurrent: ");
  Serial.println(Voltage /200, 3);
  delay(1000);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 0);
  display.println("Voltage Value");
  display.setCursor(45, 15);
  display.println(Voltage/20,3);
  display.setCursor(15, 30);
  display.println("Current Value");
  display.setCursor(45, 45);
  display.println(Voltage/200,3);
  display.display();
  delay(1000);
  display.clearDisplay();

}
