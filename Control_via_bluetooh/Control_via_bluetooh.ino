// HCSR04 Pins:
const int echoPin = 11;
const int trigPin = 12;

// Motor Driver Pins:
const int OUT_1_rightBackward = 5;
const int OUT_2_rightForward = 6;
const int OUT_3_leftBackward = 7;
const int OUT_4_leftForward = 8;

const int EN_A = 9;
const int EN_B = 10;

// HC06 Bluetooth Module Pins:
const int RX = 0;
const int TX = 1;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

int distanceCalculator() {
  long time, distance;
  digitalWrite(trigPin, LOW); // reset the sensor before the next signal
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Sensor sends the ultrasonic signal
  delayMicroseconds(10);       // Duration of sensor sending a signal
  digitalWrite(trigPin, LOW);  // End of signal transfer. Sensor starts waiting for the returning signal

  sure = pulseIn(echoPin, HIGH);
}
