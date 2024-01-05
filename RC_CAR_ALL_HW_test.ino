#include <SoftwareSerial.h>

// 핀을 정의합니다.
const int motorIn1 = 9;
const int motorIn2 = 8;
const int motorENA = 10;
const int motorIn3 = 13;
const int motorIn4 = 12;
const int motorENB = 11;
const int trigPin1 = 7;
const int echoPin1 = 6;
const int trigPin2 = 5;
const int echoPin2 = 4;
const int bluetoothTXD = 2;
const int bluetoothRXD = 3;

#define speed 100
#define speen 400
#define d_time 200

// 변수를 설정합니다.
long duration1, distance1;
long duration2, distance2;

SoftwareSerial bt(bluetoothRXD, bluetoothTXD);

void setup() {
  // 핀 모드를 설정합니다.
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorENA, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  pinMode(motorENB, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(bluetoothTXD, OUTPUT);
  pinMode(bluetoothRXD, INPUT);
  Serial.begin(9600); // 시리얼 포트를 시작합니다.
  bt.begin(9600);
}

void loop() {
  // 초음파 센서1의 거리 측정
  duration1 = getDistance(trigPin1, echoPin1);

  // 초음파 센서2의 거리 측정
  duration2 = getDistance(trigPin2, echoPin2);

  
  // 시리얼 모니터 출력
  // Serial.print("Sensor1: ");
  // Serial.print(duration1);
  // Serial.print("cm, Sensor2: ");
  // Serial.print(duration2);
  // Serial.println("cm");
  

  // 장애물이 감지되면 움직임
  if (duration1 <= 25 && duration1 > 0) {
    // 장애물이 감지되면 후진
    forward();
    delay(1000); // 후진 시간 (2초)
  } else if (duration2 <= 25 && duration2 > 0) {
    // 다른 장애물이 감지되면 전진
    backward();
    delay(1000); // 전진 시간 (2초)
  } else {
    // 장애물이 없으면 정지
    stopMotors();
  }

  if (bt.available()) {
    char command = bt.read();
    Serial.println(command);
    if (command == 'F') {
      forward();
      delay(100);
      stopMotors();
    } 
    else if(command == 'B') {
      backward();
      delay(100);
      stopMotors();
    } 
    else if(command == 'R') {
      right();
      delay(speen);
      stopMotors();
      delay(d_time);
    }
    else if(command == 'L') {
      left();
      delay(speen);
      stopMotors();
      delay(d_time);
    }
    
    else if(command == 'H') {
      int l_count = 0;
      int r_count = 0;
      int goal = 5;
      int i = 0;
      int duration;
      for (int i = 0; i < goal; i++) {
        Serial.println(i);
        forward();
        delay(500);
        stopMotors();
        delay(d_time);
        duration = getDistance(trigPin2, echoPin2);
        Serial.println(duration);
        if (duration <= 25) { //장애물1 우회전
          right();
          delay(speen);
          stopMotors();
          delay(d_time);
          duration = getDistance(trigPin2, echoPin2);
          if (duration <= 25) { //장애물2 180도 회전
            left();
            delay(speen * 2);
            stopMotors();
            delay(d_time);
            duration = getDistance(trigPin2, echoPin2);
            if (duration <= 25) { //장애물3 막다른 길
              right();
              delay(speen);
              stopMotors();
              delay(d_time);
              backward();
              delay(500);
              stopMotors();
              delay(d_time);
              i--;
              right();
              delay(speen);
              stopMotors();
              delay(d_time);
              forward();
              delay(700);
              stopMotors();
              delay(d_time);
              left();
              delay(speen);
              stopMotors();
              delay(d_time);
              r_count++;
            }
            else {
              forward();
              delay(700);
              stopMotors();
              delay(d_time);
              right();
              delay(speen);
              stopMotors();
              delay(d_time);
              l_count++;
            }
          }
          else {
            forward();
            delay(700);
            stopMotors();
            delay(d_time);
            left();
            delay(speen);
            stopMotors();
            delay(d_time);
            r_count++;
          }
        }
      }

      if (l_count > r_count) {
        l_count = l_count - r_count;
        right();
        delay(350);
        stopMotors();
        delay(d_time);
        for(i = 0; i < l_count; i++) {
          forward();
          delay(700);
          stopMotors();
          delay(d_time);
        }
        left();
        delay(speen);
      }
      else if (r_count > l_count) {
        r_count = r_count - l_count;
        left();
        delay(350);
        stopMotors();
        delay(d_time);
        for(i = 0; i < r_count; i++) {
          forward();
          delay(700);
          stopMotors();
          delay(d_time);
        }
        right();
        delay(speen);
        stopMotors();
        delay(d_time);
      }
      stopMotors();
    }
    else if(command == 'U') {
      int l_count = 0;
      int r_count = 0;
      int goal = 5;
      int i = 0;
      int duration;
      for (int i = 0; i < goal; i++) {
        Serial.println(i);
        forward();
        delay(500);
        duration = getDistance(trigPin2, echoPin2);
        Serial.println(duration);
        if (duration <= 25) { //장애물1 우회전
          right();
          delay(500);
          duration = getDistance(trigPin2, echoPin2);
          if (duration <= 25) { //장애물2 180도 회전
            left();
            delay(1000);
            duration = getDistance(trigPin2, echoPin2);
            if (duration <= 25) { //장애물3 막다른 길
              right();
              delay(500);
              backward();
              delay(500);
              i--;
              right();
              delay(500);
              forward();
              delay(500);
              left();
              delay(500);
              r_count++;
            }
            else {
              forward();
              delay(500);
              right();
              delay(500);
              l_count++;
            }
          }
          else {
            forward();
            delay(500);
            left();
            delay(500);
            r_count++;
          }
        }
      }

      if (l_count > r_count) {
        l_count = l_count - r_count;
        right();
        delay(speen);
        for(i = 0; i < l_count; i++) {
          forward();
          delay(500);
        }
        left();
        delay(speen);
      }
      else if (r_count > l_count) {
        r_count = r_count - l_count;
        left();
        delay(speen);
        for(i = 0; i < r_count; i++) {
          forward();
          delay(500);
        }
        right();
        delay(500);
      }

      left();
      delay(speen);
      forward();
      delay(150);
      stopMotors();
    }
    else if (command == 'T') {
      int i = 0;
      int duration;
      
      while (i < 5) {
        duration = getDistance(trigPin2, echoPin2);
        if (duration > 25 && duration < 70) {
          backward();
          delay(300);
          stopMotors();
          delay(d_time);
          i++;
        }
        else {
          stopMotors();
        }
      }
    }
  }

  if (Serial.available()) {
    bt.write(Serial.read());
  }
}

// 거리 측정 함수
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

// 전진 함수
void backward() {
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorENA, speed); // 속도 조절을 위한 PWM 값
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorENB, speed);
}

// 후진 함수
void forward() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  analogWrite(motorENA, speed);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);
  analogWrite(motorENB, speed);
}

void left() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  analogWrite(motorENA, speed);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorENB, speed);
}

void right() {
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorENA, speed);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);
  analogWrite(motorENB, speed);
}

// 정지 함수
void stopMotors() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorENA, 0);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorENB, 0);
}
