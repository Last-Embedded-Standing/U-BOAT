#include "Arduino.h"

void start(int esc_pin, int rudder_servo_pin, int motor_1, int motor_2);
void move_straight(char move);
void turn(char dir);
void level_updown(char level);