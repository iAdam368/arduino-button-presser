// Define the pins connected to the ULN2003 driver
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12

// Declare global variables
int step_number = 0; 
int steps_per_activation = 435;
int activation_action_pause = 200; // time in ms
const unsigned long interval = 60000; // Interval time between each activation in ms


void setup() {
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);

  // Run once immediately on startup
  runMotorSequence();
}


void loop() {
  delay(interval);
  runMotorSequence();
}


void runMotorSequence() {
  for (int i = 0; i < steps_per_activation; i++) {
    stepMotor(true);
    delay(2);
  }

  delay(activation_action_pause); 

  for (int i = 0; i < steps_per_activation; i++) {
    stepMotor(false);
    delay(2);
  }

  // Power down pins to prevent overheating
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
}


void stepMotor(bool clockwise) {
  if (clockwise) {
    step_number++;
    if (step_number > 3) step_number = 0;
  } else {
    step_number--;
    if (step_number < 0) step_number = 3;
  }

  switch (step_number) {
    case 0: digitalWrite(STEPPER_PIN_1, HIGH); digitalWrite(STEPPER_PIN_2, LOW);  digitalWrite(STEPPER_PIN_3, LOW);  digitalWrite(STEPPER_PIN_4, LOW);  break;
    case 1: digitalWrite(STEPPER_PIN_1, LOW);  digitalWrite(STEPPER_PIN_2, HIGH); digitalWrite(STEPPER_PIN_3, LOW);  digitalWrite(STEPPER_PIN_4, LOW);  break;
    case 2: digitalWrite(STEPPER_PIN_1, LOW);  digitalWrite(STEPPER_PIN_2, LOW);  digitalWrite(STEPPER_PIN_3, HIGH); digitalWrite(STEPPER_PIN_4, LOW);  break;
    case 3: digitalWrite(STEPPER_PIN_1, LOW);  digitalWrite(STEPPER_PIN_2, LOW);  digitalWrite(STEPPER_PIN_3, LOW);  digitalWrite(STEPPER_PIN_4, HIGH); break;
  }
}
