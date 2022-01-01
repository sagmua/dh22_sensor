/*
    Example on how to use the DHT-22 sensor in combination with the
    LiquidCrystal Library so the humidity and temperature are printed
    in a LCD display (without I2C)
*/

// include the library code:
#include <LiquidCrystal.h>
#include <String.h>
#include <DHT.h>

//Constants
// #define __debug__
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

float temp = 0.0, hum = 0.0;
const int ACCURANCY = 2;
const unsigned int sample_period = 20000;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
    // set up the LCD's number of columns and rows:
    #ifdef __debug__
    Serial.begin(9600);
    #endif
    lcd.begin(16, 2);
    dht.begin();
}

void loop() {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    // lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    String HUM_STRING = "Humedad: $1%";
    String TEMP_STRING = "Temp: $1 C";
    // Here we obtain the temp and hum:
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    // transform them into strings:
    String temp_s(temp, ACCURANCY);
    String hum_s(hum, ACCURANCY);
    #ifdef __debug__
    Serial.println("Humedad" + hum_s);
    Serial.println("Temperatura" + temp_s);
    #endif

    //We transform everything to string:
    TEMP_STRING.replace("$1", temp_s);
    HUM_STRING.replace("$1", hum_s);

    #ifdef __debug__
    Serial.println(HUM_STRING);
    Serial.println(TEMP_STRING);
    #endif

    // Print the info
    lcd.setCursor(0,0);
    lcd.print(HUM_STRING);
    lcd.setCursor(0,1);
    lcd.print(TEMP_STRING);

    delay(sample_period);
}