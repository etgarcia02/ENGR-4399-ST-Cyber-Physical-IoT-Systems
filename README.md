# ENGR 4399 ST: Cyber-Physical & IoT Systems

## Simulation Assignment 2 — Ultrasonic Distance Gauge

**Student:** Garcia, Ethan
**Course:** ENGR 4399 ST: Cyber-Physical & IoT Systems
**Instructor:** Dr. Okan Caglayan
**Semester:** Fall 2026

---

## Project Description

This project uses an HC-SR04 ultrasonic sensor to measure distance and drives a servo motor as an analog gauge needle. As an object moves closer to or farther from the sensor, the servo sweeps between 0 and 180 degrees to visually represent the measured distance, similar to a speedometer or fuel gauge. The distance reading is also printed to the Serial Monitor for verification.

---

## Hardware

- ESP32 Dev Module
- HC-SR04 ultrasonic distance sensor
- SG90 servo motor

---

## Pin Mapping

| Component | ESP32 Pin | Function |
|---|---|---|
| HC-SR04 TRIG | GPIO5 | Digital output, triggers the ultrasonic pulse |
| HC-SR04 ECHO | GPIO18 | Digital input, measures pulse return time |
| Servo PWM | GPIO13 | PWM output, drives the gauge needle |

---

## How It Works

1. The ESP32 sends a short trigger pulse to the HC-SR04.
2. The sensor returns an echo pulse whose duration corresponds to the round-trip time of the ultrasonic pulse.
3. That duration is converted to a distance in centimeters.
4. The distance is clamped to a defined range (2 to 30 cm) and mapped to a servo angle (0 to 180 degrees).
5. The servo moves to that angle, acting as the gauge needle, and the distance/angle pair is printed to Serial.

---

## Simulation

**Wokwi project link:** https://wokwi.com/projects/475911533633851393

---

## Files

- `distance_gauge.ino` — main source code
- `diagram.json` — Wokwi wiring diagram

---

## Author

**Ethan Garcia**
GitHub: [github.com/etgarcia02](https://github.com/etgarcia02)
