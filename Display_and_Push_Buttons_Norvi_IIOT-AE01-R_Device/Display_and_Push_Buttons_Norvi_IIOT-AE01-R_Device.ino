// set pin numbers
const int buttonPin = 32;
const int O1 = 14;
const int O2 = 12;
const int O3 = 13;
const int O4 = 15;
const int O5 = 2;
const int O6 = 33;

#include <Wire.h> 
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

int buttonState = 0; // variable for storing the pushbutton status
int count = 0; //variable for storing the number of time the push button is pushed

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT); // initialize the inputs and outputs
  pinMode(O1, OUTPUT);
  pinMode(O2, OUTPUT);
  pinMode(O3, OUTPUT);
  pinMode(O4, OUTPUT);
  pinMode(O5, OUTPUT);
  pinMode(O6, OUTPUT);
  Wire.begin(16, 17); // beginning the I2C connections
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //starting the display
  display.display();
  delay(1000);
  display.clearDisplay();

}

void loop() {

  buttonState = analogRead(buttonPin);  // read the state of the pushbutton value
  Display_Update();// Updating the display as per the button count
  if ((buttonState >= 3290 ) && (buttonState <= 3310) && count == 0) {

    display.clearDisplay();
    digitalWrite(O1, HIGH); // turn the output 1 on
    digitalWrite(O2, LOW);
    digitalWrite(O3, LOW);
    digitalWrite(O4, LOW);
    digitalWrite(O5, LOW);
    digitalWrite(O6, LOW);

    Display_Update();// Updating the display as per the button count

    buttonState = analogRead(buttonPin);
    if (buttonState == 0) {

      Serial.println("BUTTON PRESSED ONCE");
      count = count + 1;
    }
  }
  if ((buttonState >= 3290 ) && (buttonState <= 3310) && count == 1) {
    // turn LED on
    display.clearDisplay();
    digitalWrite(O1, LOW);
    digitalWrite(O2, HIGH);
    digitalWrite(O3, LOW);
    digitalWrite(O4, LOW);
    digitalWrite(O5, LOW);
    digitalWrite(O6, LOW);

    Display_Update();// Updating the display as per the button count

    buttonState = digitalRead(buttonPin);
    if (buttonState == 0) {

      Serial.println("BUTTON PRESSED TWICE");
      count = count + 1;
    }
  }
  if ((buttonState >= 3290 ) && (buttonState <= 3310) && count == 2) {
    // turn LED on
    display.clearDisplay();
    digitalWrite(O1, LOW);
    digitalWrite(O2, LOW);
    digitalWrite(O3, HIGH);
    digitalWrite(O4, LOW);
    digitalWrite(O5, LOW);
    digitalWrite(O6, LOW);

    Display_Update();// Updating the display as per the button count

    buttonState = digitalRead(buttonPin);

    if (buttonState == 0) {

      Serial.println("BUTTON PRESSED THRICE");
      count = count + 1;
    }
  }
  if ((buttonState >= 3290 ) && (buttonState <= 3310) && count == 3) {
    // turn LED on
    display.clearDisplay();
    digitalWrite(O1, LOW);
    digitalWrite(O2, LOW);
    digitalWrite(O3, LOW);
    digitalWrite(O4, HIGH);
    digitalWrite(O5, LOW);
    digitalWrite(O6, LOW);

    Display_Update();// Updating the display as per the button count

    buttonState = digitalRead(buttonPin);

    if (buttonState == 0) {

      Serial.println("BUTTON PRESSED 4TH TIME");
      count = count + 1;
    }
  }
  if ((buttonState >= 3290 ) && (buttonState <= 3310) && count == 4) {
    // turn LED on
    display.clearDisplay();
    digitalWrite(O1, LOW);
    digitalWrite(O2, LOW);
    digitalWrite(O3, LOW);
    digitalWrite(O4, LOW);
    digitalWrite(O5, HIGH);
    digitalWrite(O6, LOW);

    Display_Update();

    buttonState = digitalRead(buttonPin);

    if (buttonState == 0) {

      Serial.println("BUTTON PRESSED 5TH TIME");
      count = count + 1;
    }
  }
  if ((buttonState >= 3290 ) && (buttonState <= 3310) && count == 5) {
    // turn LED on
    display.clearDisplay();
    digitalWrite(O1, LOW);
    digitalWrite(O2, LOW);
    digitalWrite(O3, LOW);
    digitalWrite(O4, LOW);
    digitalWrite(O5, LOW);
    digitalWrite(O6, HIGH);

    Display_Update();// Updating the display as per the button count

    buttonState = digitalRead(buttonPin);

    if (buttonState == 0) {

      Serial.println("BUTTON PRESSED 6TH TIME AND GONNA REPEAT AGAIN");
      count = count + 1;
    }
  }
  if ((buttonState >= 3290 ) && (buttonState <= 3310) && count == 6) {

    count = 0;
  }
}

void Display_Update()

{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(45, 0);
  display.println("Outputs");
  display.setCursor(25, 15);
  display.println(digitalRead(14));
  display.setCursor(40, 15);
  display.println(digitalRead(12));
  display.setCursor(55, 15);
  display.println(digitalRead(13));
  display.setCursor(70, 15);
  display.println(digitalRead(15));
  display.setCursor(85, 15);
  display.println(digitalRead(2));
  display.setCursor(100, 15);
  display.println(digitalRead(33));
  display.display();
  delay(80);

}
