#include "Arduino.h"
#include "Gimbal.h"
#include "Servo.h"
#include "KDTree.h"

Gimbal::Gimbal() {
  // TODO: optimize insert order
  for (int i = 0; i < number_of_keys; i++) {
    lookup_keys.insert(lookup_key_values[i], lookup_values[i]);
  }

}

void Gimbal::attach() {
  q1_servo.attach(D4);
  q2_servo.attach(D5);
}

void Gimbal::write(float x_angle, float y_angle) {
  float target[] = {x_angle, y_angle};
  KDTreeNode *nearestNode = lookup_keys.nearestNeighbor(target);

  // Serial.print("(");
  // Serial.print(nearestNode->point[0]);
  // Serial.print("\t");
  // Serial.print(nearestNode->point[1]);
  // Serial.print(")");
  // Serial.print("\t");
  // Serial.print("(");
  // Serial.print(nearestNode->value[0]);
  // Serial.print("\t");
  // Serial.print(nearestNode->value[1]);
  // Serial.print(")");
  // Serial.print("\t");

  q1_servo.writeMicroseconds(servo_center_q1 + nearestNode->value[0]);
  q2_servo.writeMicroseconds(servo_center_q2 + nearestNode->value[1]);
}


// DEBUG TOOLS
void Gimbal::printWrite() {
  // ...
}
