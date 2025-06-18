#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

int bluetooth_rx=7;
int bluetooth_tx=8;

int updown_motor_1 = 12;
int updown_motor_2 = 13;

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

  servo.attach(3);
  servo.write(90);

  ESC.attach(9,1000,2000);
  ESC.write(0); //0~180
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
      token = strtok(input, ",");

      if (token != NULL) {
        move = token[0];
        token = strtok(NULL, ",");
      }
      if (token != NULL) {
        dir = token[0];
        token = strtok(NULL, ",");
      }
      if (token != NULL) {
        level = token[0];
      }

      if (dir == 'R' || dir == 'r')
      {
        angle = 60;
      } else if (dir == 'L' || dir == 'l') 
      {
        angle = 120;
      } else 
      {
        angle = 90;
      }

      index = 0;
      memset(input, 0, sizeof(input));
    } else {
      index ++;
      input[index] = cmd;
    }
  }

  if (prev_move != move) {
    ESC.write(20);
  } else {
    ESC.write(0);
  }

  if (prev_dir != dir) {
    servo.write(angle);
  }

  if (level == 'U' || level == 'u')
  {
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