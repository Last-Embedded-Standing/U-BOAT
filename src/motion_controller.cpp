#include "motion_controller.hpp"
#include <Servo.h>

Servo rudderServo;
Servo ESC;

int motor_1;
int motor_2;

void start(int esc_pin, int rudder_servo_pin, int motor1, int motor2) {
    ESC.attach(esc_pin,1000,2000);
    ESC.write(0); //0~180

    rudderServo.attach(rudder_servo_pin);
    rudderServo.write(90);

    motor_1 = motor_1;
    motor_2 = motor_2;

    
}

void move_straight(char move, int speed) {
    if (move == 'T') {
        ESC.write(speed);
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
    
}