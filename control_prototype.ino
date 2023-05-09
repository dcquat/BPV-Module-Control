#include <AFMotor.h>
#include <ArduPID.h>

// Controller Globabl Initializations
ArduPID motor_control;
//defining control parameters
double input;
double output;
double setpoint = 5;
double output_adj;
int dirct;
//initializing controller PID values
double p = 6.61;
double i = 1.123;
double d = 0.534;

// initialize motor
AF_DCMotor motor(3, MOTOR12_1KHZ);

// Sensor Global Initializations
const int trigger = A0;
const int echo = A1;
long duration;
int distance;

// initialize timing counter
int counter;
void setup() {
  // setup baud rate
  Serial.begin(9600);
  
  // controller setup
  
  motor_control.begin(&input,&output,&setpoint,p,i,d); // define controller parameters
  motor_control.reverse();
  motor_control.setOutputLimits(0,255);                // set output limits to match arduino pwm
  motor_control.setBias(255.0 / 2.0);                  // 
  motor_control.setWindUpLimits(-10,10);               // prevent integral wind up
  
  motor_control.start();                               // begin control calc

  // sensor setup
  pinMode(trigger,OUTPUT);
  pinMode(echo, INPUT);

  // timing setup
  counter = 0;
}

// Define setpoint incrementing function
double setpoint_increment(double setpoint){
  double set_new;
  set_new = setpoint+10;
  return set_new;
}

void loop() {
  // check feedback
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);

  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);

  duration = pulseIn(echo,HIGH);
  distance = duration*0.034/2;

  input = distance;
  
  
  motor_control.compute();

  if (input > setpoint){
    motor.run(FORWARDS);  
    output_adj = 255.0*(output/127.5);
    dirct = 1;
    motor.setSpeed(output_adj);
  }
  else if (input < setpoint){
    motor.run(BACKWARDS);
    output_adj = 255.0*((output-127.5)/127.5);
    dirct = -1;
    motor.setSpeed(output_adj);
  }
  else if (input = setpoint){
    output_adj = output-127.5;
    dirct = 0;
    motor.setSpeed(output_adj);
  }

  //increment counter and check to see if desired time elapsed
  counter = counter + 1;
  if (counter == 10000000){
    setpoint = setpoint_increment(setpoint);
    counter = 0;
  }

  // prevent setpoint from exceeding physical boundaries
  if (setpoint >= 40){
    exit(0);
  }

  
  Serial.print(input);
  Serial.println();
  Serial.print(output_adj);
  Serial.println();
  Serial.print(dirct);
  Serial.println();
  
}
