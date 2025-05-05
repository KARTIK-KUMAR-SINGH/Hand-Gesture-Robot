#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <RH_ASK.h>
#include <SPI.h>  // Needed by RH_ASK

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
RH_ASK rf_driver;

void setup() {
  Serial.begin(9600);

  if (!accel.begin()) {
    Serial.println("No ADXL345 detected");
    while (1);
  }

  if (!rf_driver.init()) {
    Serial.println("RF driver init failed");
    while (1);
  }

  Serial.println("Transmitter Ready");
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  const char* msg = "S";  // Default to stop

  if (event.acceleration.x < -6) {
    msg = "F";  // Forward
    Serial.println("Forward");
  } else if (event.acceleration.x > 6) {
    msg = "B";  // Backward
    Serial.println("Backward");
  } else if (event.acceleration.y < -6) {
    msg = "L";  // Left
    Serial.println("Left");
  } else if (event.acceleration.y > 6) {
    msg = "R";  // Right
    Serial.println("Right");
  }

  rf_driver.send((uint8_t*)msg, strlen(msg));
  rf_driver.waitPacketSent();

  delay(200);
}
