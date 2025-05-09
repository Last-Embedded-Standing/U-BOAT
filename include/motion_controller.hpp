#include "Arduino.h"

enum class TurnDirection {
    LEFT,
    RIGHT
};

void move_straight(int8_t speed);
void turn(TurnDirection dir);