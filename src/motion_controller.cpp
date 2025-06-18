#include "motion_controller.hpp"
#include <Servo.h>

Servo rudderServo;
Servo ESC;

int updown_motor_1;
int updown_motor_2;

void start(int esc_pin, int rudder_servo_pin, int motor_1, int motor_2) {
    ESC.attach(esc_pin,1000,2000);
    ESC.write(0); //0~180

    rudderServo.attach(rudder_servo_pin);
    rudderServo.write(90);

    updown_motor_1 = motor_1;
    updown_motor_2 = motor_2;
}

void move_straight(char move) {
    if (move == 'T') {
        ESC.write(20);
    } else {
        ESC.write(0);
    }
}

void turn(char dir) {
    int angle;
    if (dir == 'R' || dir == 'r') {
        angle = 60;
    } else if (dir == 'L' || dir == 'l') {
        angle = 120;
    } else {
        angle = 90;
    }

    rudderServo.write(angle);
}

void level_updown(char level) {
    if (level == 'U' || level == 'u') {
        digitalWrite(updown_motor_1, LOW);
        digitalWrite(updown_motor_2, HIGH);
    } else if (level == 'D' || level == 'd') {
        digitalWrite(updown_motor_1, HIGH);
        digitalWrite(updown_motor_2, LOW);
    } else if (level == 'F' || level == 'f') {
        digitalWrite(updown_motor_1, LOW);
        digitalWrite(updown_motor_2, LOW);
    }
}