#include <Adafruit_MAX31855.h>
#include <SoftwareSerial.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


#define LED 9

#define MAXDO   3
#define MAXCS   4
#define MAXCLK  5


// ATMEL ATMEGA8 & 168 / ARDUINO
//
//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5)   (arduino pin 19)  SCL
// RXD  (D 0) PD0  2|    |27  PC4 (AI 4)   (arduino pin 18)  SDA
// TXD  (D 1) PD1  3|    |26  PC3 (AI 3)
//      (D 2) PD2  4|    |25  PC2 (AI 2)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
//      (D 4) PD4  6|    |23  PC0 (AI 0)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13)
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
//      (D 7) PD7 13|    |16  PB2 (D 10) PWM  --> solid state relay
//      (D 8) PB0 14|    |15  PB1 (D 9) PWM
//                  +----+

Adafruit_MAX31855 thermocouple(MAXCLK, MAXCS, MAXDO);


void setup()
{
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.write('&');
  display.display();
  
  pinMode(LED, OUTPUT);
  for (int i = 0; i < 5; i++) { 
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200); 
  }
  delay(2000);
}

void loop()
{
  delay(1000);

   double t = thermocouple.readFarenheit();
   if (isnan(t)) {
     Serial.println("Something wrong with thermocouple!");
   } else {
     Serial.print("F = ");
     Serial.println(t);
   }

  digitalWrite(LED, HIGH);
  delay(100); 
  digitalWrite(LED, LOW);
}
