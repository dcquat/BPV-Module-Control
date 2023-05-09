int photo0, photo1, photo2, photo3, photo4, photo5;
float volt0, volt1, volt2, volt3, volt4, volt5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //read photodiode inputs
  photo0 = analogRead(A0);
  photo1 = analogRead(A1);
  photo2 = analogRead(A2);
  photo3 = analogRead(A3);
  photo4 = analogRead(A4);

  //convert to voltage
  volt0 = photo0*(5.0/1023.0);
  volt1 = photo1*(5.0/1023.0);
  volt2 = photo2*(5.0/1023.0);
  volt3 = photo3*(5.0/1023.0);
  volt4 = photo4*(5.0/1023.0);

  //plot voltages
  Serial.print(volt0);
  Serial.print(" , ");
  Serial.print(volt1);
  Serial.print(" , ");
  Serial.print(volt2);
  Serial.print(" , ");
  Serial.print(volt3);
  Serial.print(" , ");
  Serial.println(volt4);


  delay(20);
}
