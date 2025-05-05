#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000, 11, -1);  // (speed, RX, TX)
int outputPin = 8;  // Pin 8 for 5V output (power for transmitter)

void setup() {
  Serial.begin(9600);   // Start serial communication
  driver.init();        // Initialize RadioHead
  pinMode(outputPin, OUTPUT);  // Set pin 8 as output
  digitalWrite(outputPin , HIGH);
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  // Check if a message has been received
  if (driver.recv(buf, &buflen)) {
    Serial.print("Received: ");
    for (int i = 0; i < buflen; i++) {
      Serial.print((char)buf[i]);  // Print received characters
    }
    Serial.println();  // Print newline after the message

    // Activate 5V output on pin 8 for powering the transmitter
    digitalWrite(outputPin, HIGH);  // Set pin 8 to 5V
    delay(500);                    // Keep 5V for 500ms (adjustable)
    digitalWrite(outputPin, LOW);   // Turn off 5V
  }
}
