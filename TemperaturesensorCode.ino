#include "Adafruit_SHT31.h" //https://github.com/adafruit/Adafruit_SHT31/archive/master.zip
Adafruit_SHT31 sht31 = Adafruit_SHT31();

#include <Wire.h>
#include <Adafruit_GFX.h> //https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
      Serial.begin(9600);
      delay(10);
      Serial.println("SHT31 test");
      if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
      Serial.println("Couldn't find SHT31");
      while (1) delay(1);
      }

        if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

}

void loop() {
  
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    
    if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.println(t);
    }
    else {    
    t=0.0;
    Serial.println("Failed to read temperature");
    }
    
    if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
    }
    else { 
    h=0.0;
    Serial.println("Failed to read humidity");    
    }
    Serial.println();
    delay(500);

display.clearDisplay();
    
    // display temperature
    display.setTextSize(1);
    display.setCursor(0,7);
    display.print("Temperature: ");
    display.setTextSize(2);
    display.setCursor(0,18);
    display.print(t);
    display.print(" ");
    display.setTextSize(1);
    display.cp437(true);
    display.write(167);
    display.setTextSize(2);
    display.print("F");
    
    // display humidity
    display.setTextSize(2);
    display.setCursor(0, 45);
    display.print(h);
    display.print("%");
    display.setTextSize(1);
    display.setCursor(74, 50);
    display.print(" ");
    display.print("Rel H");  
    display.display(); 
}
