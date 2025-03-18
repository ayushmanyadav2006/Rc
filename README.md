# Rc
Rc car project codes (receiver and transmitter)
//receiver code
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define enA 2  // Motor A speed control (Left side)
#define in1 3  // Motor A direction 1
#define in2 4  // Motor A direction 2
#define enB 7  // Motor B speed control (Right side)
#define in3 5  // Motor B direction 1
#define in4 6  // Motor B direction 2

RF24 radio(8, 9); // CE, CSN
const byte address[6] = "00001";
int xAxis = 512, yAxis = 512; // Default centered joystick values

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {   
    int receivedData[2];  
    radio.read(&receivedData, sizeof(receivedData));
    xAxis = receivedData[0];
    yAxis = receivedData[1];
  }

  Serial.print("X: ");
  Serial.print(xAxis);
  Serial.print(" Y: ");
  Serial.println(yAxis);

  // Dead zone to prevent jitter
  int deadZone = 50; 

  // Forward motion
  if (yAxis > 550) { 
    int speed = map(yAxis, 550, 1023, 0, 255);
    moveForward(speed);
  } 
  // Backward motion
  else if (yAxis < 470) { 
    int speed = map(yAxis, 470, 0, 0, 255);
    moveBackward(speed);
  } 
  // Right turn
  else if (xAxis > 550) { 
    int speed = map(xAxis, 550, 1023, 0, 255);
    turnRight(speed);
  } 
  // Left turn
  else if (xAxis < 470) { 
    int speed = map(xAxis, 470, 0, 0, 255);  // FIXED ERROR HERE
    turnLeft(speed);
  } 
  else {
    stopMotors();
  }
}

// Functions for movement control
void moveForward(int speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void moveBackward(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void turnRight(int speed) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void turnLeft(int speed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
//transmitter
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define VRX A1  // Joystick X-axis
#define VRY A0  // Joystick Y-axis

RF24 radio(8, 9); // CE, CSN
const byte address[6] = "00001";

struct Data {
  int xAxis;
  int yAxis;
};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();  // Transmitter mode
}

void loop() {
  Data joystickData;
  joystickData.xAxis = analogRead(VRX);
  joystickData.yAxis = analogRead(VRY);

  Serial.print("X: "); Serial.print(joystickData.xAxis);
  Serial.print(" | Y: "); Serial.println(joystickData.yAxis);

  radio.write(&joystickData, sizeof(joystickData));
  delay(100);  // Reduce lag
}
