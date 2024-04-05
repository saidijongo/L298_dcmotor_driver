#define IN1 2 //+
#define IN2 6 //-
#define IN3 7 //+
#define IN4 12 //-


#define POT_PIN A2

void setup() {
  Serial.begin(115200);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

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
  analogWrite(IN1, map(analogRead(POT_PIN), 0, 1023, 0, 255));
  digitalWrite(IN2, LOW);
}

void motor1CCW() {
  analogWrite(IN1, map(analogRead(POT_PIN), 0, 1023, 0, 255));
  digitalWrite(IN2, HIGH);
}

void motor1Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motor2CW() {
  analogWrite(IN3, map(analogRead(POT_PIN), 0, 1023, 0, 255));
  digitalWrite(IN4, LOW);
}

void motor2CCW() {
  analogWrite(IN3, map(analogRead(POT_PIN), 0, 1023, 0, 255));
  digitalWrite(IN4, HIGH);
}

void motor2Stop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

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
