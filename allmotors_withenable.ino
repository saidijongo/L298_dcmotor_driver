#define IN1 2 //+
#define IN2 6 //-
#define IN3 7 //+
#define IN4 12 //-
#define EN1 8 //M1
#define EN2 9 //M2

//control motor speed (0 - 255)
int speed = 80;

void setup() {
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming serial command
    String command = Serial.readStringUntil('\n');

    //motor control command
    if (command.startsWith("Motor1-CW")) {
      motor1CW();
    } else if (command.startsWith("Motor1-CCW")) {
      motor1CCW();
    } else if (command.startsWith("Motor1-stop")) {
      motor1Stop();
    } else if (command.startsWith("Motor2-CW")) {
      motor2CW();
    } else if (command.startsWith("Motor2-CCW")) {
      motor2CCW();
    } else if (command.startsWith("Motor2-stop")) {
      motor2Stop();
    } else if (command.startsWith("all-Motors-CW")) {
      allMotorsCW();
    } else if (command.startsWith("all-Motors-CCW")) {
      allMotorsCCW();
    } else if (command.startsWith("all-Motors-stop")) {
      allMotorsStop();
    }
  }
}

void motor1CW() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, speed); // Set speed
}

void motor1CCW() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(EN1, speed); // Set speed
}

void motor1Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(EN1, 0); // Stop motor
}

void motor2CW() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(EN2, speed); // Set speed
}

void motor2CCW() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(EN2, speed); // Set speed
}

void motor2Stop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(EN2, 0); // Stop motor
}

// Functions to control all motors
void allMotorsCW() {
  motor1CW();
  motor2CW();
}

void allMotorsCCW() {
  motor1CCW();
  motor2CCW();
}

void allMotorsStop() {
  motor1Stop();
  motor2Stop();
}
