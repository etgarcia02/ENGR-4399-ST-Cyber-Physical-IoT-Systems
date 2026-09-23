// ESP32 ULTRASONIC DISTANCE GAUGE
// HC-SR04 ultrasonic sensor drives a servo needle like an analog gauge

#include <ESP32Servo.h>

const int TRIG_PIN = 5;
const int ECHO_PIN = 18;
const int SERVO_PIN = 13;

Servo gaugeServo;

// Distance range the gauge covers (cm)
const int MIN_DISTANCE_CM = 2;
const int MAX_DISTANCE_CM = 30;

// Servo angle range (0 = near end of gauge, 180 = far end)
const int MIN_ANGLE = 0;
const int MAX_ANGLE = 180;

const unsigned long ECHO_TIMEOUT_US = 30000; // ~5m max range before giving up

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  ESP32PWM::allocateTimer(0);
  gaugeServo.setPeriodHertz(50);
  gaugeServo.attach(SERVO_PIN, 500, 2400);
  gaugeServo.write(MIN_ANGLE); // start the needle at the near end

  Serial.println("Ultrasonic distance gauge ready.");
}

void loop() {
  long distance = readDistanceCM();

  if (distance < 0) {
    Serial.println("Out of range / no echo");
  } else {
    // Clamp so anything past the gauge's range still points at an endpoint
    long clamped = constrain(distance, MIN_DISTANCE_CM, MAX_DISTANCE_CM);
    int angle = map(clamped, MIN_DISTANCE_CM, MAX_DISTANCE_CM, MIN_ANGLE, MAX_ANGLE);

    gaugeServo.write(angle);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm  ->  Angle: ");
    Serial.print(angle);
    Serial.println(" deg");
  }

  delay(200);
}

// Sends a 10us trigger pulse and times the echo to get distance in cm
long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);

  if (duration == 0) {
    return -1; // no echo received within the timeout
  }

  // Speed of sound ~0.034 cm/us, divide by 2 for the round trip
  return duration * 0.034 / 2;
}
