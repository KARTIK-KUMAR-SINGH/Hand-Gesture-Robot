#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000, -1, 12);  // (speed, RX, TX)

void setup() {
  driver.init();  // Initialize RadioHead
}

void loop() {
  const char *msg = "Hello";  // Message to send
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();  // Wait until the message is sent
  delay(1000);  // Send every second
}
