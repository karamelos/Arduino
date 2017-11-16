#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
#define DHTTYPE DHT22
#define DHTPIN 8 // DATA DHT sensor.

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //PIN LCD
//DEGRES "°"
byte degre[8] = {                                           
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() 
{
 Serial.begin(9600); 
 lcd.begin(16, 2);
 lcd.createChar(1, degre);                           
 dht.begin();// Initialize

 // Print temperature
 sensor_t sensor;
 dht.temperature().getSensor(&sensor);

 // Print humidity
 dht.humidity().getSensor(&sensor);
 
 // Set delay between sensor readings
 delayMS = 10000;
 
}

void loop() 
{
 lcd.setCursor(16, 0);
 // Delay
 delay(delayMS);
 // Get temperature
 sensors_event_t event; 
 dht.temperature().getEvent(&event);
 if (isnan(event.temperature)) 
 {
 Serial.println("Error reading temperature!");
 }
 else 
 {
 lcd.setCursor(0, 0);
 Serial.print("Temp: ");
 Serial.print(event.temperature);
 lcd.print("Temp: ");
 lcd.print(event.temperature);
   lcd.setCursor(12, 0);
 lcd.write(1);
 }
 // Get humidity
 dht.humidity().getEvent(&event);
 if (isnan(event.relative_humidity)) 
 {
 Serial.println("Error reading humidity!");
 }
 else 
 {
   lcd.setCursor(0, 1);
 Serial.print("Humi: ");
 Serial.print(event.relative_humidity);
 Serial.println("%");
 lcd.print("Humi: ");
  lcd.setCursor(6, 1);
 lcd.print(event.relative_humidity);
 lcd.print(" %");
 }
}
