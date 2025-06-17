#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

int RX=7;
int TX=8;
// int dir_motor_1 = 10;
// int dir_motor_2 = 11;
int updown_motor_1 = 12;
int updown_motor_2 = 13;
int value1 = 0;
int value2 = 0;
int speed = 0;
int angle = 90;

SoftwareSerial BTSerial(RX, TX);
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
  // if (BTSerial.available())
  // {
  //   Serial.println(BTSerial.read());
  // }
  
  
  

  while (BTSerial.available()) {
    char c = BTSerial.read();
    if (c == 'A') 
    {
      input[index] = '\0'; // 문자열 종료
      // printf("%s\n", index);

      // 문자열 분리
      char *token;
      token = strtok(input, ",");

      int number = 0;
      char dir1 = '\0';
      char dir2 = '\0';

      if (token != NULL) {
        number = atoi(token); // "15" → 15
        token = strtok(NULL, ",");
      }
      if (token != NULL) {
        dir1 = token[0]; // "R" → 'R'
        token = strtok(NULL, ",");
      }
      if (token != NULL) {
        dir2 = token[0]; // "U" → 'U'
      }

      if (dir1 == 'R' || dir1 == 'r')
      {
        angle = 60;
      } else if (dir1 == 'L' || dir1 == 'l') 
      {
        angle = 120;
      } else 
      {
        angle = 90;
      }


      if (dir2 == 'U' || dir2 == 'u')
      {
        digitalWrite(updown_motor_1, LOW);
        digitalWrite(updown_motor_2, HIGH);
      } else if (dir2 == 'D' || dir2 == 'd') {
        digitalWrite(updown_motor_1, HIGH);
        digitalWrite(updown_motor_2, LOW);
      } else if (dir2 == 'F' || dir2 == 'f') {
        digitalWrite(updown_motor_1, LOW);
        digitalWrite(updown_motor_2, LOW);
      }
      

      // 결과 출력
      Serial.print("Number: ");
      Serial.println(number);
      Serial.print("Dir1: ");
      Serial.println(dir1);
      Serial.print("Dir2: ");
      Serial.println(dir2);

      // 버퍼 초기화
      index = 0;
      memset(input, 0, sizeof(input));
      ESC.write(number);
      servo.write(angle);
    } 
    else 
    {
      // 버퍼에 문자 저장
      if (index < sizeof(input) - 1) {
        input[index++] = c;
      }
      printf("%c", c);
    }
  }



  // byte data;
  // if (BTSerial.available()) {
  //   data = BTSerial.read();
  //   Serial.println(data);

    
    // if (data == 'n') 
    // {
      

    //   delay(1000);
      // if (val.equals("0")) {
      //   Serial.println("stop");
      //   speed = 0;
      //   value1 = 0;
      //   return;
      // }
      // splitString(val, value1, value2);
      // val = "";
    // } 
    // else 
    // {
    //   // val.concat(data);
    //   digitalWrite(motor_1, LOW);
    //   digitalWrite(motor_2, LOW);
    // }
  // }
  // Serial.print("Speed : ");
  // Serial.println(speed);
  // if(value1==1){
  //   speed = value2; 
  // }
  // ESC.write();
}

void splitString(String input, int &val1, int &val2) {
  int spaceIndex = input.indexOf(' ');  // 공백 위치 찾기
  if (spaceIndex != -1) {
    // 첫 번째 값: 공백 앞 부분
    val1 = input.substring(0, spaceIndex).toInt();
    
    // 두 번째 값: 공백 뒤 부분
    val2 = input.substring(spaceIndex + 1).toInt();
  }
}