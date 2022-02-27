//this code is owned by #Aaqil-25
//this code is written  to work with L298N-motor-driver  and arduino
//the components used for the project
//Arduino Uno
//L298N_Motor_controller
//Ultra_sonic_sensor
//servo_motor-sg-90s

//the library used here. 
#include <Servo.h>      //Servo motor standard library
#include <NewPing.h>    //Ultrasonic sensor function library
//Install them before use

//configure L298N_motor_controller_pin
const int RightMotorForward = 3;
const int RightMotorBackward = 2;
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;

//Ultrasonic_sensor_pin
#define trig_pin A1 //Analog_trigger_pin 
#define echo_pin A2 //Analog_echo_pin

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //Ultra_sonic_sensor function
Servo servo_motor; // servo_name


void setup() {
  // put your setup code here, to run once:
  //define the motor pin for GPIO Output 
  pinMode(RightMotorForward, OUTPUT); 
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  servo_motor.attach(10); //connect the servo to digital pin 10
  
  servo_motor.write(115);//initial servo motor turn
  delay(2000);
  distance = readPing(); //distance read from ultra_sonic_sensor
  delay(100);
  distance = readPing(); //distance read from ultra_sonic_sensor
  delay(100);
  distance = readPing(); //distance read from ultra_sonic_sensor
  delay(100);
  distance = readPing(); //distance read from ultra_sonic_sensor
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){ // Distance between the obstacle and sensor less then 20cm, stop the robot.
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){// left side distance is less than  ditance is other side .
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
      
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW); 

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    
  }
}

void moveBackward(){

  goesForward=false;

  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  
}

void turnRight(){

  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  
  
  delay(500);
  
  
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  
 
  
  
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(500);
  
  
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  
}
