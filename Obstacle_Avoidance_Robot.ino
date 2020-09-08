


//                                                                              OBSTACLE AVOIDANCE ROBOT


//**********************************************************************************************************************************************************************************
// Created By: Palwinder S. Gill
// Created On: 27 July, 2020
// Synopsis: This code will let a robot know if an obstacle is in the way and tell it to stop and change direction
//**********************************************************************************************************************************************************************************


//variables for the ultrasonic sensor
const int trigPin = 11;                         //variable for the trigger on ultrasonic sensor
const int echoPin = 10;                         //variable for the echo reciever on ultrasonic sensor
int pingTravelTime;                             //amount of time it takes for the ping to travel back to sensor
int distance;

//variables for motor 1 (left leg)
const int m1Dir1Pin = 4;                        //this is the pin for direction pin 1 of motor 1
const int m1Dir2Pin = 5;                        //this is the pin for direction pin 2 of motor 2
const int m1SpeedPin = 6;                       //pin for speed of motor 1

//variables for motor 2 (right leg)
const int m2Dir1Pin = 7;                        //pin for direction pin 1 of motor 1
const int m2Dir2Pin = 8;                        //pin for direction pin 2 of motor 2
const int m2SpeedPin = 9;                       //pin for speed of motor 2

void setup() {
  //setup code here, to run once:
  //setting all of the motor control pins to output

  //motor 1
  pinMode(m1Dir1Pin, OUTPUT);
  pinMode(m1Dir2Pin, OUTPUT);
  pinMode(m1SpeedPin, OUTPUT);

  //motor 2
  pinMode(m2Dir1Pin, OUTPUT);
  pinMode(m2Dir2Pin, OUTPUT);
  pinMode(m2SpeedPin, OUTPUT);

  //setting up the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //begin serial moniter
  Serial.begin(9600);
}

void loop() {
  //main code here, to run repeatedly:
  //code below measures how far something is
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTravelTime = (pulseIn(echoPin, HIGH))/10000000;
  distance = 34300/pingTravelTime;
  //the line below is commented out but can be put back in to see what the sensor is  doing
  // Serial.println(distance);
  delay(25);

  if(distance <= 7){
    avoid_obstacle();
  }
  else {
    go_forward();
  }
}

void avoid_obstacle() {
  // this is the code that runs when the robot detects an obstacle in the way
  // the robot stops all of its motors before crashing into a wall etc.
  digitalWrite(m1Dir1Pin, LOW);
  digitalWrite(m1Dir2Pin, LOW);
  digitalWrite(m2Dir1Pin, LOW);
  digitalWrite(m2Dir2Pin, LOW);

  // the robot proceeds to reverse to the left/right
  digitalWrite(m1Dir1Pin, LOW);
  digitalWrite(m1Dir2Pin, HIGH);
  digitalWrite(m2Dir1Pin, LOW);
  digitalWrite(m2Dir2Pin, HIGH);
  analogWrite(m1SpeedPin, 255);
  analogWrite(m2SpeedPin, 255);
  
}

void go_forward() {
  //motor 1
  digitalWrite(m1Dir1Pin, LOW);
  digitalWrite(m1Dir2Pin, HIGH);
  analogWrite(m1SpeedPin, 255);

  // the directions on the motors alternate between high and low so that the wheels spin in the same direction when placed on the robot

  //motor 2
  digitalWrite(m2Dir1Pin, HIGH);
  digitalWrite(m2Dir2Pin, LOW);
  analogWrite(m2SpeedPin, 255);

  delay(1000);
}
