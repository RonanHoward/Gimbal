#ifndef Gimbal_h
#define Gimbal_h

#include "Arduino.h"
#include "Servo.h"
#include "KDTree.h"

class Gimbal {

    public:
        Gimbal();
        void attach();
        void write(float x_angle, float y_angle);
        void printWrite();
        Servo q1_servo;
        Servo q2_servo;
        KDTree lookup_keys;
        int lookup_values[49][2];

        int servo_center;
        
};

#endif