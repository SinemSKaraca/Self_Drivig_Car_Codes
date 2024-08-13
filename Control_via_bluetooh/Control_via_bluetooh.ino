// HCSR04 Pins:
const int echoPin = 11;
const int trigPin = 12;

// Motor Driver Pins:
const int OUT1_RF = 5;
const int OUT2_RB = 6;
const int OUT3_LB = 7;
const int OUT4_LF = 8;

const int EN_A = 9;
const int EN_B = 10;

// HC06 Bluetooth Module Pins:
const int RX = 0; // HC-06 TX
const int TX = 1; // HC-06 RX

int velocity = 200;

void setup() {
  // Motor Driver pin setup:
  pinMode(OUT1_RF, OUTPUT); 
  pinMode(OUT2_RB, OUTPUT);
  pinMode(OUT3_LB, OUTPUT);
  pinMode(OUT4_LF, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  // HCSR04 pin setup:
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  // Starting values:
  digitalWrite(EN_A, LOW);
  digitalWrite(EN_B, LOW);
  digitalWrite(OUT1_RF, LOW);
  digitalWrite(OUT2_RB, LOW);
  digitalWrite(OUT3_LB, LOW);
  digitalWrite(OUT4_LF, LOW);

  Serial.begin(9600);
}

void loop() {
  int distance = distance_calculator();
  
  if(distance > 40) {
    // Bluetooth control:
    if(Serial.available() > 0) {
    char command = Serial.read(); // Read the incoming command from Bluetooth

    // Process the command
    if(command == 'F') { // Forward
      motor_control(1, 0, 0, 1, velocity);
    }
    else if(command == 'B') { // Backward
      motor_control(0, 1, 1, 0, velocity);
    }
    else if(command == 'L') { // Left
      motor_control(1, 0, 1, 0, velocity);
    }
    else if(command == 'R') { // Right
      motor_control(0, 1, 0, 1, velocity);
    }
    else if(command == 'S') { // Stop
      motor_control(0, 0, 0, 0, 0);
    }
    else if(command == 'T') { // Speed Up
      velocity += 5;
    }
    else if(command == 'X') { // Slow Down
      if(velocity >= 100) {
        velocity -= 5;
      }
      else
        return;
    }
    }
  }
  else {
    motor_control(0, 1, 1, 0, velocity);
    delay(500);
    motor_control(0, 0, 0, 0, 0);
  }
  // If bluetooth doesn't control the car autonomous obstacle avoidance:
  /*else {
    if(distance > 40) {
    Serial.println("Moving Forward");
    Serial.println(distance);
    motor_control(1, 0, 0, 1, velocity);
    delay(500);
    motor_control(0, 0, 0, 0, 0);
    }
    else {
      Serial.println("Obstacle Detected, Reversing");
      Serial.println(distance);
      motor_control(0, 1, 1, 0, velocity);
      delay(500);
      motor_control(0, 0, 0, 0, 0);
    }
  }*/
}

int distance_calculator() {
  long time, distance;
  digitalWrite(trigPin, LOW); // reset the sensor before the next signal
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Sensor sends the ultrasonic signal
  delayMicroseconds(10);       // Duration of sensor sending a signal
  digitalWrite(trigPin, LOW);  // End of signal transfer. Sensor starts waiting for the returning signal

  time = pulseIn(echoPin, HIGH);
  distance = time / 29.1 / 2;
  delay(50);

  return distance;
}

int motor_control(int val1, int val2, int val3, int val4, int velocity) {
  digitalWrite(OUT1_RF, val1);
  digitalWrite(OUT2_RB, val2);
  digitalWrite(OUT3_LB, val3);
  digitalWrite(OUT4_LF, val4);

  analogWrite(EN_A, velocity);
  analogWrite(EN_B, velocity);
}
