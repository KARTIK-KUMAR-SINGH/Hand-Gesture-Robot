#include <RH_ASK.h>
#include <SPI.h>  // Required by RH_ASK

RH_ASK rf_driver;  // Defaults: data pin D11

// L293D Motor Driver Pins
#define IN1 8   // Left Motor Input 1
#define IN2 9   // Left Motor Input 2
#define IN3 10  // Right Motor Input 1
#define IN4 12  // Right Motor Input 2

void setup() {
  Serial.begin(9600);

  if (!rf_driver.init()) {
    Serial.println("RF init failed");
    while (1);
  }
  Serial.println("Receiver Ready");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();
}

void loop() {
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  if (rf_driver.recv(buf, &buflen)) {
    char command = (char)buf[0];
    Serial.print("Received: ");
    Serial.println(command);

    switch (command) {
      case 'F': moveForward(); break;
      case 'B': moveBackward(); break;
      case 'L': turnLeft(); break;
      case 'R': turnRight(); break;
      default:  stopMotors(); break;
    }
  }

  delay(10);
}

// Movement Functions

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
