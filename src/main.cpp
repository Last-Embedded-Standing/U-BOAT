#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#include <motion_controller.hpp>
#include <utils.hpp>


// pin variables
int bluetooth_rx=7;
int bluetooth_tx=8;

int updown_motor_1 = 12;
int updown_motor_2 = 13;

int rudder_servo_pin = 3;

int esc_pin = 9;

// state variables
int speed = 20;
int angle = 90;

char prev_move = 'F';
char prev_dir = 'F';
char prev_level = 'F';

char move = 'F'; // 앞 뒤 움직임
char dir = 'F'; // 방향
char level = 'F'; // 높이 조절

SoftwareSerial BTSerial(bluetooth_rx, bluetooth_tx);
Servo ESC;
Servo servo;
String val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);// set the data rate for the BT port

  start(esc_pin, rudder_servo_pin, updown_motor_1, updown_motor_2);
  
  delay(2000); //ESC가 켜질때까지 약간 기다려주기!
}

char input[20]; // 입력 저장 버퍼
byte index = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (BTSerial.available()) {

    char cmd = BTSerial.read();
    if (cmd == 'A') {
      input[index] = NULL;
      char* token;
      int tokenCount = split(input, ',', token);

      move = token[0];
      dir = token[1];
      level = token[2];

      index = 0;
      memset(input, 0, sizeof(input));
    } else {
      input[index] = cmd;
      index ++;
    }
  }

  if (prev_move != move) {
    move_straight(move);
    prev_move = move;
  }

  if (prev_dir != dir) {
    turn(dir);
    prev_dir = dir;
  }

  level_updown(level);
}