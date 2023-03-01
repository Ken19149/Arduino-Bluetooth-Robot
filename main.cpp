#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/**

PIN

2 - LED LIGHT

**/

BluetoothSerial SerialBT;

int pin1 = 14;
int pin2 = 13;
int pin3 = 26;
int pin4 = 27;

int pinAttache1 = 0;
int pinAttache2 = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("hello");
  Serial.println("world");
  SerialBT.begin("SCP-028");

  pinMode(12, OUTPUT);    //Motor driver
  digitalWrite(12, HIGH);  //TURN ON MOTOR DRIVER

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

//----------PWM GENERATOR------------

  ledcSetup(0 ,10000,8);
  ledcSetup(1 ,10000,8);


/**
//----------CONNECT PIN TO PWM GENERATOR-----------

  ledcAttachPin(pin1,pinAttache1);
  ledcAttachPin(pin2,pinAttache2);
  ledcAttachPin(pin3,pinAttache1);
  ledcAttachPin(pin4,pinAttache2);

**/

  pinMode(2,OUTPUT);  //LED LIGHT
}

//-----------control motor-----------------
/**
void rightForward(int speed){
  //digitalWrite(pin1, LOW);
  //digitalWrite(pin2, HIGH);

  digitalWrite(pin1, LOW);
  ledcWrite(pinAttache2, speed);

}

void rightBackward(int speed){
  //digitalWrite(pin1, HIGH);
  //digitalWrite(pin2, LOW);

  ledcWrite(pinAttache1, speed);

  //digitalWrite(pin2, LOW);
  ledcWrite(pinAttache2, 0);
}

void leftForward(int speed){
  //digitalWrite(pin3, LOW);
  //digitalWrite(pin4, HIGH);

  //digitalWrite(pin3, LOW);
  ledcWrite(pinAttache1, 0);
  ledcWrite(pinAttache2, speed);
}

void leftBackward(int speed){
  //digitalWrite(pin3, HIGH);
  //digitalWrite(pin4, LOW);

  ledcWrite(pinAttache1, speed);

  //digitalWrite(pin4, LOW);
  ledcWrite(pinAttache2, 0);
}

**/

//----------------movement----------------

void up(int speed = 255){
  ledcAttachPin(pin1,pinAttache1);
  ledcAttachPin(pin2,pinAttache2);
  ledcAttachPin(pin3,pinAttache1);
  ledcAttachPin(pin4,pinAttache2);

  ledcWrite(pinAttache2, speed);
  ledcWrite(pinAttache1, 0);
}

void down(int speed = 255){
  ledcAttachPin(pin1,pinAttache1);
  ledcAttachPin(pin2,pinAttache2);
  ledcAttachPin(pin3,pinAttache1);
  ledcAttachPin(pin4,pinAttache2);

  ledcWrite(pinAttache1, speed);
  ledcWrite(pinAttache2, 0);
}

void left(int speed = 100){
  //leftForward(speed);
  //3 low, 4 high

  //rightBackward(speed);
  //1 high, 2 low

  ledcAttachPin(pin1,pinAttache1);
  ledcAttachPin(pin4,pinAttache1);
  ledcAttachPin(pin2,pinAttache2);
  ledcAttachPin(pin3,pinAttache2);

  ledcWrite(pinAttache1, speed);
  ledcWrite(pinAttache2, 0);
}

void right(int speed = 100){
  //leftBackward(speed);
  //3 high, 4 low

  //rightForward(speed);
  //1 low, 2 high

  ledcAttachPin(pin1,pinAttache1);
  ledcAttachPin(pin4,pinAttache1);
  ledcAttachPin(pin2,pinAttache2);
  ledcAttachPin(pin3,pinAttache2);

  ledcWrite(pinAttache2, speed);
  ledcWrite(pinAttache1, 0);
}

void loop() {
  if(SerialBT.available()){
    char Data = SerialBT.read();

    if(Data == 'W'){
      Serial.println("forward");
      digitalWrite(2,HIGH);
      up(255);
    } else if(Data == 'A'){
      Serial.println("left");
      digitalWrite(2,HIGH);
      left(200);
    } else if(Data == 'S'){
      Serial.println("backward");
      digitalWrite(2,HIGH);
      down(255);
    } else if(Data == 'D'){
      Serial.println("right");
      digitalWrite(2,HIGH);
      right(200);
    } else if(Data == 'P'){
      digitalWrite(2,LOW);
      /**
      digitalWrite(pin1,LOW);
      digitalWrite(pin2,LOW);
      digitalWrite(pin3,LOW);
      digitalWrite(pin4,LOW);
      **/
      ledcWrite(pinAttache1, 0);
      ledcWrite(pinAttache2, 0);
    } else{
      /**
      digitalWrite(2,LOW);
      digitalWrite(pin1,LOW);
      digitalWrite(pin2,LOW);
      digitalWrite(pin3,LOW);
      digitalWrite(pin4,LOW);
      **/
    }
  }
}
