#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>

int RX=7;
int TX=8;
int value1 = 0;
int value2 = 0;
int speed = 0;

SoftwareSerial BTSerial(RX, TX);
Servo ESC;
String val;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESC.attach(9,1000,2000);
  // pinMode(13, OUTPUT);
  BTSerial.begin(9600);// set the data rate for the BT port
  //9번핀에 ESC가 연결되어있다!
  ESC.write(0); //0~180
  delay(2000); //ESC가 켜질때까지 약간 기다려주기!
}

void loop() {
  // put your main code here, to run repeatedly:
  char data;
  if (BTSerial.available()) {
    data = BTSerial.read();
    
    if (data == 'n') {
      Serial.println('~');
      if (val.equals("0")) {
        Serial.println("stop");
        speed = 0;
        value1 = 0;
        return;
      }
      splitString(val, value1, value2);
      val = "";
    } else {
      val.concat(data);
    }
  }
  // Serial.print("Speed : ");
  // Serial.println(speed);
  if(value1==1){
    speed = value2; 
  }
  ESC.write(speed);
  
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