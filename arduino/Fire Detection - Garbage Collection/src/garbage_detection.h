#ifndef garbage_detection_h
#define garbage_detection_h

#define CLOCK_WISE 0
#define STOP 90
#define ANTI_CLOCK_WISE 180

#include <Arduino.h>
#include <Servo.h>

class GarbageDetection {
  static const int MOISTURE_PIN = 5;
  static const int SERVO_PIN = 6;
  static const int IR_SENSOR_PIN = 7;

  Servo servo;

  public:
    void init() {
      pinMode(MOISTURE_PIN, INPUT);
      pinMode(IR_SENSOR_PIN, INPUT);

      servo.attach(SERVO_PIN);
    }
    
    void detect() {
      if(digitalRead(IR_SENSOR_PIN) == HIGH) return;
      
      int moisture = digitalRead(MOISTURE_PIN);
      Serial.println("Moisture: " + String(moisture));

      if(moisture == HIGH) {
        moveServo(CLOCK_WISE);
      } else {
        moveServo(ANTI_CLOCK_WISE);
      }

      delay(1000);
    }

    void moveServo(int direction) {
      if(direction == CLOCK_WISE) {
        servo.write(0);
        delay(100);
        servo.write(90);
        delay(100);
        servo.write(180);
        delay(100);
        servo.write(90);
      } else {
        servo.write(180);
        delay(100);
        servo.write(90);
        delay(100);
        servo.write(0);
        delay(100);
        servo.write(90);
      }
    }

    void stopServo() {
      servo.write(STOP);
    }
};

#endif