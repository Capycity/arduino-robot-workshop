#include <Arduino.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
Servo myservo1;

static uint8_t deg = 90;  //| 0x80;

static constexpr uint8_t MIN_ANGLE_SERVO_0 = 5;
static constexpr uint8_t MAX_ANGLE_SERVO_0 = 120;

static constexpr uint8_t MIN_ANGLE_SERVO_1 = 0;
static constexpr uint8_t MAX_ANGLE_SERVO_1 = 180;

static float current_angle_servo_0 = MIN_ANGLE_SERVO_0;
static uint8_t target_angle_servo_0 = MIN_ANGLE_SERVO_0;

static float current_angle_servo_1 = MIN_ANGLE_SERVO_1;
static uint8_t target_angle_servo_1 = MIN_ANGLE_SERVO_1;

static uint32_t time_ms_before = 0;
static uint32_t time_ms_after = 0;

static float tolerance = 0.05f;

extern volatile unsigned long timer0_overflow_count;

float lerp(float a, float b, float t) {
  Serial.println("Current t: " + String(t));
  if (abs(a - b) < tolerance) {
    return b;
  }
  return a + (b - a) * t;
}

uint8_t limit(uint8_t val, uint8_t min, uint8_t max);

void setup() {
  Serial.begin(9600);
  delay(1000);
  myservo.attach(A1);  // modify each pin to adjust
  myservo1.attach(A0);
  myservo.write(current_angle_servo_0);   // angle value
  myservo1.write(current_angle_servo_1);  // angle value
}

void loop() {
  Serial.println("X: " + String(analogRead(A2)) + " ");
  Serial.println("Y: " + String(analogRead(A5)) + " ");

  // if(current_angle_servo_0 == target_angle_servo_0) {
  //   int8_t delta_servo_0 = map(analogRead(A5), 0, 1023, -10, 10);
  //   Serial.println("Delta Servo: " + String(delta_servo_0));
  //   if(delta_servo_0 != 0) {
  //     target_angle_servo_0 = current_angle_servo_0 + delta_servo_0;
  //   }

  //   if(target_angle_servo_0 < MIN_ANGLE_SERVO_0) {
  //     target_angle_servo_0 = MIN_ANGLE_SERVO_0;
  //   } else if(target_angle_servo_0 > MAX_ANGLE_SERVO_0) {
  //     target_angle_servo_0 = current_angle_servo_0 = MAX_ANGLE_SERVO_0;
  //   }
  //   Serial.println("New Target Servo Pos: " + String(target_angle_servo_0));
  //   delay(2500);
  // } else {
  //   Serial.println("Old Servo Pos: " + String(current_angle_servo_0));
  //   Serial.println("delta ticks: " + String(((time_ms_after = millis()) -
  //   time_ms_before))); current_angle_servo_0 = lerp(current_angle_servo_0,
  //   target_angle_servo_0, 4 *((time_ms_after = millis()) - time_ms_before) /
  //   1000.f); Serial.println("New Servo Pos: " +
  //   String(current_angle_servo_0));
  // }
  int8_t delta_servo_0 = map(analogRead(A5), 0, 1023, -2, 2);
  int8_t delta_servo_1 = map(analogRead(A2), 0, 1023, -2, 2);
  current_angle_servo_0 = limit(current_angle_servo_0 + delta_servo_0,
                                MIN_ANGLE_SERVO_0, MAX_ANGLE_SERVO_0);
  current_angle_servo_1 = limit(current_angle_servo_1 + delta_servo_1,
                                MIN_ANGLE_SERVO_1, MAX_ANGLE_SERVO_1);
  // Serial.println("Current current_angle_servo_0: " +
  //                String(current_angle_servo_0));
  // Serial.println("Current current_angle_servo_1: " +
  //                String(current_angle_servo_1));

  myservo.write(current_angle_servo_0);   // angle value
  myservo1.write(current_angle_servo_1);  // angle value
  delay(20);
  // time_ms_before = millis();

  // Serial.print("1: ");
  // Serial.print(deg & ~(0x80));
  // if((deg & ~(0x80)) == 127) {
  //   deg &= ~(0x80);
  // }

  // if((deg & ~(0x80)) == 90) {
  //   deg |= 0x80;
  // }

  // deg += (deg >> 8) ? -1 : 1;
  // Serial.print("2: ");
  // Serial.println(deg & ~(0x80));
  // myservo.write(deg & ~(0x80));  // angle value
  // delay(100);
}

uint8_t limit(uint8_t val, uint8_t min, uint8_t max) {
  // Serial.println("val: " + String(val));
  // Serial.println("min: " + String(min));
  // Serial.println("max: " + String(max));
  if (val <= max && val >= min) {
    // Serial.println("everything is fine: " + String(val));
    return val;
  }

  // Serial.println("everything is not fine: " + String((val < min) ? min :
  // max));
  return (val < min) ? min : max;
}