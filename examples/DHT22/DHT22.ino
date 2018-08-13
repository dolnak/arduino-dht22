// Sketch uses 5,584 bytes (17%) of program storage space. Maximum is 32,256 bytes.
// Global variables use 276 bytes (13%) of dynamic memory, leaving 1,772 bytes for local variables. Maximum is 2,048 bytes.

// Adafruit library uses:
// Sketch uses 6,338 bytes (19%) of program storage space. Maximum is 32,256 bytes.
// Global variables use 310 bytes (15%) of dynamic memory, leaving 1,738 bytes for local variables. Maximum is 2,048 bytes.


#include "DHT22.h"

#define DHT22_DATA_PIN 2

DHT22 dht(DHT22_DATA_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }
  Serial.print("Humidity: "); 
  Serial.print(h, 1);
  Serial.print(" %\t");

  Serial.print("Temperature: "); 
  Serial.print(t, 1);
  Serial.println(" *C");
}