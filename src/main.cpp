#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

// 예시: motion_controller.hpp, utils.hpp에 함수들이 선언되어 있다고 가정
// 실제로는 아래 함수들을 구현해야 합니다.
void start(int esc_pin, int rudder_servo_pin, int updown_motor_1, int updown_motor_2);
void move_straight(char move, int speed);
void turn(char dir);
void level_updown(char level);
int split(char *data, char delimiter, char tokens[][10]);

// pin variables
int bluetooth_rx = 7;
int bluetooth_tx = 8;
int updown_motor_1 = 11;
int updown_motor_2 = 12;
int rudder_servo_pin = 6;
int esc_pin = 9;

// state variables
int speed = 15;
int angle = 90;

char prev_move = 'F';
char prev_dir = 'F';
char prev_level = 'F';

char move = 'F'; // 앞 뒤 움직임
char dir = 'F';  // 방향
char level = 'F'; // 높이 조절

SoftwareSerial BTSerial(bluetooth_rx, bluetooth_tx);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); // 블루투스 포트 설정

  pinMode(updown_motor_1, OUTPUT);
  pinMode(updown_motor_2, OUTPUT);

  start(esc_pin, rudder_servo_pin, updown_motor_1, updown_motor_2);
  delay(2000); // ESC 초기화 대기
}

char input[10];
byte index = 0;

void loop() {
  if (BTSerial.available()) {
    char cmd = BTSerial.read();
    if (cmd == 'A') { // 명령 종료 신호
      input[index] = '\0';
      Serial.println(input);

      char tokens[3][10];
      int tokenCount = split(input, ',', tokens);

      // 토큰이 3개 이상이면 각각 할당
      if (tokenCount >= 3) {
        move = tokens[0][0];
        dir = tokens[1][0];
        level = tokens[2][0];
      }

      index = 0;
      memset(input, 0, sizeof(input));
      memset(tokens, 0, sizeof(tokens));
    } else if(cmd == 'S') {
      input[index] = '\0';
      speed = atoi(input);
      EEPROM.update(0, speed);
    } else {
      if (index < sizeof(input) - 1) {
        input[index++] = cmd;
      }
    }
  }

  if (prev_move != move) {
    move_straight(move, EEPROM.read(0));
    prev_move = move;
  }
  if (prev_dir != dir) {
    turn(dir);
    prev_dir = dir;
  }

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
