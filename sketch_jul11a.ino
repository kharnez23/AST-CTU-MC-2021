   /*
  ULN2003-4Phase-Stepper-Motor-Driver
  modified on 06 Dec 2020
  by Amir Mohammad Shojaee @ Electropeak
  https://electropeak.com/learn/
  
  based on Arduino library 
*/

#include <Stepper.h>
#include <Servo.h>
Servo Myservo; 
int capacitivesensor = 4;
int wetmaterial = 5;
const int trigPin = 2;
const int echoPin = 3;
const int stepsPerRevolution = 2048;
const int rpm = 12;
Stepper stepper1 = Stepper(stepsPerRevolution, 8, 10, 9, 11);
String currentbin;
float duration, distance;

void setup() {

  pinMode(capacitivesensor, INPUT);
  pinMode(wetmaterial, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   Myservo.attach(6);
   Myservo.write(180);
  stepper1.setSpeed(rpm);
  Serial.begin(9600);
  currentbin="Paper";
  Serial.println("Input trash: ");
  Serial.println("1.Paper");
  Serial.println("2.Wet");
  Serial.println("3.Plastic");
  Serial.println(currentbin);
}

void loop() {
 if((digitalRead(capacitivesensor) == LOW)&&(digitalRead(wetmaterial) == HIGH)){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  delay(4000);
 if(distance < 16){
  Paper();
 }
 
 }

 
 if(digitalRead(wetmaterial) == LOW){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  delay(4000);
 if(distance < 16) {
  wet();}
  

 }
 if((digitalRead(capacitivesensor) == HIGH)&&(digitalRead(wetmaterial) == HIGH)){
   
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
 delay(4000);
if(distance < 16) {
 plastic();}
  

 }
}                                                                                                                                                                                                          

void Paper(){
  if(currentbin=="Plastic"){
  stepper1.step(stepsPerRevolution/3);
  delay(1000);
  Myservo.write(70);
      delay(1500);
     Myservo.write(180);
      currentbin = "Paper";
  Serial.println(currentbin);
  delay(100);
  }
  else if(currentbin=="Wet"){
    stepper1.step(-stepsPerRevolution/3);
  delay(1000);
    Myservo.write(70);
      delay(1500);
     Myservo.write(180);
       currentbin = "Paper";
    Serial.println(currentbin);
  delay(100);
    }
    else if(currentbin=="Paper"){
      //servo drop open directly
      delay(1000);
      Myservo.write(70);
      delay(1500);
     Myservo.write(180);
      currentbin = "Paper";
      Serial.println(currentbin);
    }
}
void wet(){
   if(currentbin=="Paper"){
  stepper1.step(stepsPerRevolution/3);
   delay(1000);
    Myservo.write(70);
      delay(1500);
     Myservo.write(180);
  currentbin = "Wet";
  Serial.println(currentbin);
  delay(100);
  }
  else if(currentbin=="Plastic"){
    stepper1.step(-stepsPerRevolution/3);
     delay(1000);
    Myservo.write(70);
      delay(1500);
     Myservo.write(180);
    currentbin = "Wet";
    Serial.println(currentbin);
  delay(100);
    }
      else if(currentbin=="Wet"){
      //servo drop open directly
       delay(1000);
    Myservo.write(70);
      delay(1500);
     Myservo.write(180);
      currentbin = "Wet";
      Serial.println(currentbin);
    }
}
void plastic(){
  if(currentbin=="Wet"){
  stepper1.step(stepsPerRevolution/3);
   delay(1000);
    Myservo.write(70);
      delay(1500);
     Myservo.write(180);
  currentbin = "Plastic";
  Serial.println(currentbin);
  delay(100);
  }
  else if(currentbin=="Paper"){
    stepper1.step(-stepsPerRevolution/3);
     delay(1000);
    Myservo.write(70);
      delay(1500);
     Myservo.write(180);
    currentbin = "Plastic";
    Serial.println(currentbin);
  delay(100);
    }
      else if(currentbin=="Plastic"){
      //servo drop open directly
       delay(1000);
    Myservo.write(70);
      delay(1500);
     Myservo.write(180);
      currentbin = "Plastic";
      Serial.println(currentbin);
    }
}
//IF ELSE USES FOR DETECTION
// in detection flow, first the material detection, second Presence of material detection (to lessen the error when placing the material in <16 range), lastly rotation and drop of material
//start of detection during the <16 ultrasonic range
//use "-" for stepper reverse direction.
