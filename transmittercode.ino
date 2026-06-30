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
