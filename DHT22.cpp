#include "DHT22.h"

DHT22::DHT22(uint8_t pin, uint8_t count) {
  _pin = pin;
  _count = count;
  firstReading = true;
}

void DHT22::begin(void) {
  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
  lastReadTime = 0;
}

float DHT22::readHumidity(void) {
  float f;
  if (read()) {
    f = data[0];
    f *= 256;
    f += data[1];
    f /= 10;
    return f;
  }
  return NAN;
}

float DHT22::readTemperature(void) {
  float f;
  if (read()) {
    f = data[2] & 0x7F;
    f *= 256;
    f += data[3];
    f /= 10;
    if (data[2] & 0x80)
      f *= -1;
    return f;
  }
  return NAN;
}

boolean DHT22::read(void) {
  uint8_t lastState = HIGH;
  uint8_t counter = 0;
  uint8_t i, j = 0;
  unsigned long currentTime = millis();

  if (currentTime < lastReadTime) {
    lastReadTime = 0;
  }

  if (!firstReading && ((currentTime - lastReadTime) < 2000)) {
    return true;
  }
  firstReading = false;
  lastReadTime = millis();
  
  data[0] = data[1] = data[2] = data[3] = data[4] = 0;
  
  // sending start signal
  digitalWrite(_pin, HIGH);
  delay(250);
  
  // detecting MCU's signal
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delay(20);
  
  // waiting for sensor's response
  noInterrupts();
  digitalWrite(_pin, HIGH);
  delayMicroseconds(40);
  pinMode(_pin, INPUT);
  
  for (i = 0; i < MAXTIMINGS; i++) {
    counter = 0;
    while (digitalRead(_pin) == lastState) {
      counter++;
      delayMicroseconds(1);
      if (counter == 255) {
        break;
      }
    }
    lastState = digitalRead(_pin);
    if (counter == 255) break;
    if ((i >= 4) && (i % 2 == 0)) {
      data[j / 8] <<= 1;
      if (counter > _count)
        data[j / 8] |= 1;
      j++;
    }
  }
  interrupts();
  
  // read 40 bits and calculate checksum
  if ((j >= 40) && 
      (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) ) {
    return true;
  }
  return false;
}