//for the servo library constant setup//
#include <Servo.h>
Servo myServo1;
Servo myServo2;
unsigned long deltaTime;
int pos=0;
unsigned long currentTime;



//------依照不同伺服馬達型號做更改(like 0.17s per 60 degree)---------//
float  motor_constant_speed = 0.17/60; 
//------依照不同步進馬達型號做更改(此步進馬達步級角為1.8度)----------//
float  stepper_degree = 360/200;
//--------stepper 1~4 class----------------//
class stepper1{
  public:
    void init(int _driverPUL1, int _driverDIR1){
        driverPUL1     = _driverPUL1;
        driverDIR1     = _driverDIR1;
        pinMode(driverPUL1,OUTPUT); 
        pinMode(driverDIR1,OUTPUT);
        
      }
    void speedcontrol(float stepper_omega1){
        currentTime = micros();
        setdir1 = (stepper_omega1>0)? HIGH:LOW;//正反轉控制
        digitalWrite(driverDIR1, setdir1);
        delayTime1 = abs((stepper_degree*PI*1000000)/(180*stepper_omega1));
        if( (currentTime - deltaTime1) > delayTime1 ){
              //pulseCount2++;
              Serial.println(delayTime1);

              // Each HIGH or LOW is a "pulse"
              // But each step of the motor requires two "pulses"
              
          
              Pulse1 = Pulse1 == LOW ? HIGH : LOW;
              digitalWrite(driverPUL1, Pulse1);
              deltaTime1 = currentTime;
            }
    }
   private:
    //for the first stepper motor constant setup// 
      boolean setdir1 = LOW;
      boolean Pulse1;
      float   delayTime1;
      int     driverPUL1,driverDIR1;
      unsigned long deltaTime1;
        
      
};stepper1 stepper1;
class stepper2{
  public:
    void init(int _driverPUL2, int _driverDIR2){
        driverPUL2     = _driverPUL2;
        driverDIR2     = _driverDIR2;
        pinMode(driverPUL2,OUTPUT);
        pinMode(driverDIR2,OUTPUT);
        
      }
    void speedcontrol(float stepper_omega2){
        currentTime = micros();
        setdir2 = (stepper_omega2>0)? HIGH:LOW;//正反轉控制
        digitalWrite(driverDIR2, setdir2);
        delayTime2 = abs((2*PI*1000000)/(400*stepper_omega2));
        if( (currentTime - deltaTime2) > delayTime2 ){
              //pulseCount2++;
          
              // Each HIGH or LOW is a "pulse"
              // But each step of the motor requires two "pulses"
              
          
              Pulse2 = Pulse2 == LOW ? HIGH : LOW;
              digitalWrite(driverPUL2, Pulse2);
              deltaTime2 = currentTime;
            }
    }
   private:
    //for the first stepper motor constant setup// 
      boolean setdir2 = LOW;
      boolean Pulse2;
      float   delayTime2;
      int     driverPUL2,driverDIR2;
      unsigned long deltaTime2;
        
      
};stepper2 stepper2;
class stepper3{
  public:
    void init(int _driverPUL3, int _driverDIR3){
        driverPUL3     = _driverPUL3;
        driverDIR3     = _driverDIR3;
        pinMode(driverPUL3,OUTPUT); 
        pinMode(driverDIR3,OUTPUT);
        
      }
    void speedcontrol(float stepper_omega3){
        currentTime = micros();
        setdir3 = (stepper_omega3>0)? HIGH:LOW;//正反轉控制
        digitalWrite(driverDIR3, setdir3);
        delayTime3 = abs((2*PI*1000000)/(400*stepper_omega3));
        if( (currentTime - deltaTime3) > delayTime3 ){
              //pulseCount2++;
          
              // Each HIGH or LOW is a "pulse"
              // But each step of the motor requires two "pulses"
              
          
              Pulse3 = Pulse3 == LOW ? HIGH : LOW;
              digitalWrite(driverPUL3, Pulse3);
              deltaTime3 = currentTime;
            }
    }
   private:
    //for the first stepper motor constant setup// 
      boolean setdir3 = LOW;
      boolean Pulse3;
      float   delayTime3;
      int     driverPUL3,driverDIR3;
      unsigned long deltaTime3;
        
      
};stepper3 stepper3;
class stepper4{
  public:
    void init(int _driverPUL4, int _driverDIR4){
        driverPUL4     = _driverPUL4;
        driverDIR4     = _driverDIR4;
        pinMode(driverPUL4,OUTPUT); 
        pinMode(driverDIR4,OUTPUT);
        
      }
    void speedcontrol(float stepper_omega4){
        currentTime = micros();
        setdir4 = (stepper_omega4>0)? HIGH:LOW;//正反轉控制
        digitalWrite(driverDIR4, setdir4);
        delayTime4 = abs((2*PI*1000000)/(400*stepper_omega4));
        if( (currentTime - deltaTime4) > delayTime4 ){
              //pulseCount2++;
          
              // Each HIGH or LOW is a "pulse"
              // But each step of the motor requires two "pulses"
              
              //Serial.println(delayTime4);
              Pulse4 = Pulse4 == LOW ? HIGH : LOW;
              digitalWrite(driverPUL4, Pulse4);
              deltaTime4 = currentTime;
            }
    }
   private:
    //for the first stepper motor constant setup// 
      boolean setdir4 = LOW;
      boolean Pulse4;
      float   delayTime4;
      int     driverPUL4,driverDIR4;
      unsigned long deltaTime4;
      
      
};stepper4 stepper4;
//-----------------------------------------------//


void motor_set(float thita1,float omega1,float thita2,float omega2){
  
   //motor angular velocity is constant,
   //to seperate time between the former position and future position time to change angular velocity.
   float servo_delaytime = (thita1/(omega1)-(motor_constant_speed))/((thita2)-1);//formula
   
    //servo_delaytime is second(the time) change to microsecond for micros()
    //if currenTime/1000000 to second will work step by step obviously
    if( (currentTime - deltaTime) > servo_delaytime*1000000 ){ 
                  
      pos++;
      myServo1.write((thita1/thita2)*pos);
      myServo2.write(pos);

     deltaTime = currentTime; //in order to compare the former position and future position time
     pos = (pos >= thita2) ? thita2 : pos; // limit not to exceed thita2 which is reference thita(position)
    }
  }

void setup() {
  //Serial.begin(9600);
  myServo1.attach(9);
  myServo2.attach(10);
  Serial.begin(9600);
  myServo1.write(0);
  myServo2.write(0);
  delay(2000);
  stepper1.init(1,2);
  stepper2.init(3,4);
  stepper3.init(5,6);
  stepper4.init(7,8);
  Serial.begin(9600);
}

void loop() {
    stepper1.speedcontrol(-40/2);
    stepper2.speedcontrol(40/2);
    stepper3.speedcontrol(-25);
    stepper4.speedcontrol(40);

    motor_set(45,5,90,10);
    
}
