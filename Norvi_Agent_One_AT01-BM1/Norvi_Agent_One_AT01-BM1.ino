#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1015.h>
#include <Adafruit_NeoPixel.h>


#define PIN      25
#define NUMPIXELS 1


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_ADS1115 ads(0x48);
float Voltage = 0.0;

void setup(void) 
{
Wire.begin(21,22);
pixels.begin();
Serial.begin(115200); 
ads.begin();
}

void loop(void) 
{
int16_t adc0;

adc0 = ads.readADC_SingleEnded(1);
Voltage = (adc0 * 0.1875)/1000;

Serial.print("AIN0: "); 
Serial.print(adc0);
Serial.print("\tVoltage: ");
Serial.println(Voltage, 3); 
Serial.println();
if (Voltage<=0.8 && Voltage>=0.6)
{
pixels.setBrightness(30);
pixels.setPixelColor(0, pixels.Color(255, 0, 0));
pixels.show();
}
else if (Voltage<=1.0 && Voltage>=0.8)
{
pixels.setBrightness(30);
pixels.setPixelColor(0, pixels.Color(0, 255, 0));
pixels.show();
}
else if (Voltage<=1.2 && Voltage>=1.0)
{
pixels.setBrightness(30);
pixels.setPixelColor(0, pixels.Color(0, 0, 255));
pixels.show();
}
else
{
pixels.clear();
pixels.show();
}
delay(1000);
}
