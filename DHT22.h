#ifndef DHT22_H
#define DHT22_H

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define MAXTIMINGS 85

class DHT22 {
 private:
   uint8_t _pin, _count;
   uint8_t data[5];
   boolean firstReading;
   unsigned long lastReadTime;

 public:
   DHT22(uint8_t pin, uint8_t count=6);
   void begin(void);
   float readHumidity(void);
   float readTemperature(void);
   boolean read(void);
};
#endif