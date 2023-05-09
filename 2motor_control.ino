#include <AFMotor.h>
#include <ArduPID.h>

// Controller Globabl Initializations
ArduPID motor_control1;
ArduPID motor_control2;

//defining control parameters
double input1;
double output1;
double setpoint = 10;
double output1_adj;

double input2;
double output2;
double output2_adj;

int dirct1;
int dirct2;
//initializing controller PID values
double p = 6.61;
double i = 1.123;
double d = 0.534;

//initialize motors
AF_DCMotor motor1(2, MOTOR12_1KHZ);
AF_DCMotor motor2(3, MOTOR12_1KHZ);


//initialize sensor values
const int trigger1 = A0;
const int echo1 = A1;

const int trigger2 = A2;
const int echo2 = A3;

long duration1;
long duration2;
int distance1;
int distance2;

//initialize timing counter
int counter;

// Define setpoint incrementing function
double setpoint_increment(double setpoint){
  double set_new;
  set_new = setpoint+10;
  return set_new;
}

void setup() {
  //baud rate
  Serial.begin(9600);

  //controller 1 setup
  motor_control1.begin(&input1,&output1,&setpoint,p,i,d);
  motor_control1.reverse();
  motor_control1.setOutputLimits(0,255);
  motor_control1.setBias(255.0/2.0);
  motor_control1.setWindUpLimits(-10,10);

  //controller 2 setup (controllers are identical)
  motor_control2.begin(&input2,&output2,&setpoint,p,i,d);
  motor_control2.reverse();
  motor_control2.setOutputLimits(0,255);
  motor_control2.setBias(255.0/2.0);
  motor_control2.setWindUpLimits(-10,10);

  //begin calculations
  motor_control1.start();
  motor_control2.start();

  //sensor setup
  pinMode(trigger1,OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);

  //timing setup
  counter = 0;
}

void loop() {
  //check feedback
  digitalWrite(trigger1,LOW);
  digitalWrite(trigger2,LOW);
  delayMicroseconds(2);

  digitalWrite(trigger1,HIGH);
  digitalWrite(trigger2,HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger1,LOW);
  digitalWrite(trigger2,LOW);

  duration1 = pulseIn(echo1,HIGH);
  duration2 = pulseIn(echo2,HIGH);

  distance1 = duration1*0.034/2;
  distance2 = duration2*0.034/2;

  input1 = distance1;
  input2 = distance2;

  motor_control1.compute();
  motor_control2.compute();

  
  if (input1 > setpoint){
    motor1.run(FORWARDS);  
    output1_adj = output1;
    dirct1 = 1;
    motor1.setSpeed(output1_adj);
  }
  else if (input1 < setpoint){
    motor1.run(BACKWARDS);
    output1_adj = output1+127.5;
    dirct1 = -1;
    motor1.setSpeed(output1_adj);
  }
  else if (input1 = setpoint){
    output1_adj = output1-127.5;
    dirct1 = 0;
    motor1.setSpeed(output1_adj);
  }

  
  if (input2 > setpoint){
    motor2.run(FORWARDS);  
    output2_adj = output2;
    dirct2 = 1;
    motor2.setSpeed(output2_adj);
  }
  else if (input2 < setpoint){
    motor2.run(BACKWARDS);
    output2_adj = output2+127.5;
    dirct2 = -1;
    motor2.setSpeed(output2_adj);
  }
  else if (input2 = setpoint){
    output2_adj = output2-127.5;
    dirct2 = 0;
    motor2.setSpeed(output2_adj);
  }



  
  Serial.print(input2);
  Serial.println();
  Serial.print(output2);
  Serial.println();
  Serial.println(output2_adj);
  
}
