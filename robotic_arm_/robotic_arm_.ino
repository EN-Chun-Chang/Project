// 改造伺服馬達的部分可參考影片
// https://youtu.be/4Pouf9iWLns

#include <Servo.h>

//////////////動作參數設定//////////////
int moveSmooth = 25; //兩個動作之間的平滑參數
int stepTime = 100;   //到定點之後停留的時間
//////////////////////////////////////
int D2;
int D4;

//////////////各零件腳位設定////////////
//伺服馬達腳位
int servopinA = 3;
int servopinB = 5;
int servopinC = 6;
int servopinD = 9;
int servopinE = 10;
int servopinF = 11;



//伺服馬達訊號回傳腳位
int sensorpinA = A0;
int sensorpinB = A1;
int sensorpinC = A2;
int sensorpinD = A3;
int sensorpinE = A4;
int sensorpinF = A5;



// LED燈腳位
int LedPin = 12;
int GLedPin = 15;
int BLedPin = 14;

// 按鈕腳位
int ButtonA = 2;
int ButtonB = 4;
//////////////////////////////////////

//馬達校正基準點

int posCount = 100;
int POS [100][6] ; //最多可紀錄100組手臂狀態

int ServoPosA ; //轉動角度
int ServoPosB ; //轉動角度
int ServoPosC; //轉動角度
int ServoPosD ; //轉動角度
int ServoPosE ;
int ServoPosF ;


int sensorMaxA , sensorMaxB, sensorMaxC, sensorMaxD ; //紀錄可變電阻最大值
int sensorMinA , sensorMinB, sensorMinC, sensorMinD ; //紀錄可變電阻最小值

Servo servoA;
Servo servoB;
Servo servoC;
Servo servoD;
Servo servoE;
Servo servoF;



int arrayCount = 0;
int clearPos = 0;

//所有馬達連接
void MotorON() {
  servoA.attach(servopinA);
  servoB.attach(servopinB);
  servoC.attach(servopinC);
  servoD.attach(servopinD);
  servoE.attach(servopinE);
  servoF.attach(servopinF);


}

//所有馬達斷開連接
void MotorOFF() {
  servoA.detach();
  servoB.detach();
  servoC.detach();
  servoD.detach();
  servoE.detach();
  servoF.detach();

}

void setup() { 
Serial.begin(9600);

  pinMode(LedPin, OUTPUT);

  digitalWrite(LedPin, LOW);

 


  pinMode(ButtonA, INPUT_PULLUP);
  pinMode(ButtonB, INPUT_PULLUP);
}


void loop() { // put your main code here, to run repeatedly:
//Serial.begin(digitalRead(D2));
//Serial.begin(digitalRead(D4));

//紀錄按鈕
  if (digitalRead(ButtonA) == LOW) {
    if (clearPos == 1) {
      arrayCount = 0;
      clearPos = 0;
    }
    digitalWrite(LedPin, HIGH);
    delay(200);
    digitalWrite(LedPin, LOW);
        delay(200);

    digitalWrite(LedPin, HIGH);
        delay(200);

    digitalWrite(LedPin, LOW);
    
    MotorOFF();
    delay(100);
    
    //將讀取到的數值，轉換成伺服馬達角度

    ServoPosA = map(analogRead(sensorpinA), 60, 203, 130, 180);
    ServoPosA = 310 - ServoPosA;
    //Serial.println(ServoPosA);
    
    ServoPosB = map(analogRead(sensorpinB), 221, 536, 50, 160);
    //Serial.println(ServoPosA+2);
    
    ServoPosC = map(analogRead(sensorpinC), 77, 602, 0, 180);
    //Serial.println(ServoPosC);
    //Serial.println(ServoPosC);

    ServoPosD = map(analogRead(sensorpinD), 324, 594, 90, 180);
    //Serial.println(ServoPosD);
  
    ServoPosE = map(analogRead(sensorpinE), 144, 519, 30, 155);
    ServoPosE = ServoPosE+1 ;
    //Serial.println(ServoPosE);

    ServoPosF = map(analogRead(sensorpinF), 58, 604, 0, 180);
    ServoPosF = ServoPosF + 1 ;
    Serial.println(ServoPosF);

    if (arrayCount < posCount) {
      POS[arrayCount][0] = ServoPosA;
      POS[arrayCount][1] = ServoPosB;
      POS[arrayCount][2] = ServoPosC;
      POS[arrayCount][3] = ServoPosD;
      POS[arrayCount][4] = ServoPosE;
      POS[arrayCount][5] = ServoPosF;
      
      arrayCount++;
    } else {
      for (int i = 0; i < 10; i++) {
        digitalWrite(LedPin, HIGH);
        delay(100);
        digitalWrite(LedPin, LOW);
        delay(100);
      }
      arrayCount = posCount - 1;
    }
    delay(200);
    
  }

//播放按鈕
  if (digitalRead(ButtonB) == LOW) {
    digitalWrite(LedPin, HIGH);
  
   
    MotorON();
    servoA.write(POS[0][0]);
    servoB.write(POS[0][1]);
    servoC.write(POS[0][2]);
    servoD.write(POS[0][3]);
    servoE.write(POS[0][4]);
    servoF.write(POS[0][5]);

    delay(1000);

    for (int i = 0; i < arrayCount - 1; i++) {
      int POSNowA = POS[i][0];
      int POSNowB = POS[i][1];
      int POSNowC = POS[i][2];
      int POSNowD = POS[i][3];
      int POSNowE = POS[i][4];
      int POSNowF = POS[i][5];

      int POSGoalA = POS[i + 1][0];
      int POSGoalB = POS[i + 1][1];
      int POSGoalC = POS[i + 1][2];
      int POSGoalD = POS[i + 1][3];
      int POSGoalE = POS[i + 1][4];
      int POSGoalF = POS[i + 1][5];
      

      for (int j = 0; j < moveSmooth; j++) {
        servoA.write(map(j, 0, moveSmooth, POSNowA, POSGoalA));
        servoB.write(map(j, 0, moveSmooth, POSNowB, POSGoalB));
        servoC.write(map(j, 0, moveSmooth, POSNowC, POSGoalC));
        servoD.write(map(j, 0, moveSmooth, POSNowD, POSGoalD));
        servoE.write(map(j, 0, moveSmooth, POSNowE, POSGoalE));
        servoF.write(map(j, 0, moveSmooth, POSNowF, POSGoalF));

        delay(10);
      }
      delay(stepTime);
    }
    delay(500);
    clearPos = 1;
    MotorOFF();
    digitalWrite(LedPin, LOW);
  }

}
