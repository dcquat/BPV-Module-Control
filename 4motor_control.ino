double output1;
double output2;
double angle_dist;
double set1;
double set2;

const int trigger1 = A0;
const int echo1 = A1;

const int trigger2 = A2;
const int echo2 = A3;

long duration1;
long duration2;
int distance1;
int distance2;

const int RPWM1 = 5;
const int LPWM1 = 6;

const int RPWM2 = 9;
const int LPWM2 = 10;

int counter;

void setup() {
  Serial.begin(9600);

  angle_dist = 10.0;

  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);

  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);

  counter = 0;
}


double set_change(double angle_dist){
  double new_set;
  new_set = angle_dist+5.0;
  return(new_set);
}


void loop() {

  // Sensor Feedback
  digitalWrite(trigger1,LOW);
  delayMicroseconds(2);

  digitalWrite(trigger1,HIGH);
  delayMicroseconds(10);

  duration1 = pulseIn(echo1,HIGH);
  distance1 = duration1*0.034/2;

  digitalWrite(trigger2,LOW);
  delayMicroseconds(2);

  digitalWrite(trigger2,HIGH);
  delayMicroseconds(10);

  duration2 = pulseIn(echo2,HIGH);
  distance2 = duration2*0.034/2;

  
  set1 = abs(angle_dist-distance1);
  output1 = (set1/36.0)*255.0;
  output1 = output1 + 200.0;
  if (output1 > 255.0){
    output1 = 255.0;
  }

  set2 = abs(angle_dist-distance2);
  output2 = (set2/36.0)*255.0;
  output2 = output2+200.0;
  if (output2 > 255.0){
    output2 = 255.0;
  }
  
  if (distance1 > angle_dist){
    analogWrite(RPWM1, output1);
    analogWrite(LPWM1, 0);
  }

  else if (distance1 < angle_dist){
    analogWrite(RPWM1, 0);
    analogWrite(LPWM1, output1);
  }

  else if (distance1 = angle_dist){
    analogWrite(RPWM1, 0);
    analogWrite(LPWM1, 0);
  }


  if (distance2 > angle_dist){
    analogWrite(RPWM2, output2);
    analogWrite(LPWM2, 0);
  }

  else if (distance2 < angle_dist){
    analogWrite(RPWM2, 0);
    analogWrite(LPWM2, output2);
  }

  else if (distance2 = angle_dist){
    analogWrite(RPWM2, 0);
    analogWrite(LPWM2, 0);
  }

  counter = counter + 1;
  
  if (counter == 1000){
    angle_dist = set_change(angle_dist);
    counter = 0;
  }

  if (angle_dist > 25){
    angle_dist = 10;
    counter = 0;
  }

 
  Serial.print(angle_dist);
  Serial.println();
  Serial.print(output1);
  Serial.println();
  
}
