#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Initialize MPU6050 object
Adafruit_MPU6050 mpu;
// Flex sensor pins
const int flexPins[5] = {A0, A1, A2, A3, A6};
// Flex sensor detection function
void detectFlexSensors(int fvs[], sensors_event_t a) {
  // Gesture detection
  if (a.acceleration.x > 2.5) {
    Serial.println("Hello");
  }
  else if (fvs[0] == 1023 && fvs[1] > 0) {
    Serial.println("Superb or Nice");
  }
  else if (fvs[0] == 1023 && fvs[1] == 0 && fvs[2] == 1023 && fvs[3] == 0 && fvs[4] > 0 && fvs[4] < 60) {
    Serial.println("Wait");
  }
  else if (fvs[3] > 0 && fvs[4] > 65) {
    Serial.println("Peace");
  }
  else if (a.acceleration.y > 2.5) {s
    Serial.println("Well Done");
  }
  else if (fvs[0] == 1023 && fvs[1] == 1023 && fvs[2] == 1023) {
    Serial.println("Thank You");
  }
  else if (fvs[1] == 0 && fvs[2] == 1023 && a.acceleration.z > 2.0) {
    Serial.println("Bye");
  }
  else if (fvs[0] < 600 && fvs[1] > 900) {
    Serial.println("Sorry");
  }
  else if (fvs[0] == 1023 && fvs[1] < 100 && fvs[4] > 700) {
    Serial.println("Yes");
  }
  else if (fvs[0] < 100 && fvs[3] > 900) {
    Serial.println("No");
  }
  else if (fvs[1] > 900 && fvs[2] < 600 && a.acceleration.x < -2.0) {
    Serial.println("Had Food");
  }
  else if (fvs[0] > 900 && fvs[1] < 200 && fvs[3] < 200 && fvs[4] > 800) {
    Serial.println("Love");
  }
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  // Configure sensor range
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}
void loop() {
  // Read flex sensor values into an array
  int fvs[5];
  for (int i = 0; i < 5; i++) {
    fvs[i] = analogRead(flexPins[i]);
  }
  // Read MPU6050 values
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  // Detect flex sensor states
  detectFlexSensors(fvs, a);
  delay(500);  // Adjust delay as needed for continuous detection
}