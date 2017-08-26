/***********************************************************************
 * MiniShyBot -- Shy Drive
 * 
 * This sketch was based on code written by SparkFun Electronics, with lots of help from 
 * the Arduino community.
 * This code is completely free for any use.
 * 
 * 8 Oct 2013 M. Hord
 * Revised 30 Oct 2014 B. Huang
 * PIR functionality added 26 August 2017 B. Lerchin
 ***********************************************************************/

#include <RedBot.h>
RedBotMotors motors;

RedBotBumper lBumper = RedBotBumper(3);  // initialzes bumper object on pin 3
RedBotBumper rBumper = RedBotBumper(11); // initialzes bumper object on pin 11

const int LED_PIN = 13;
const int PIR_PIN_LEFT = A0;
const int PIR_PIN_RIGHT = A1;
const int PIR_WAIT = 10000; // length of time to wait for PIR to calibrate
const int MOVE_DURATION = 5000; // length of time to move after detecting motion

int lBumperState;  // state variable to store the bumper value
int rBumperState;  // state variable to store the bumper value
int lPirState; // state variable to store the pir value
int rPirState; // state variable to store the pir value
unsigned long lastMotion; // time when last motion occurred

void setup()
{
  // The PIRs (like most sensors) require a "pull up" resistor to hold
  // the voltage high until an event pulls the signal low.
  // Fortunately, we can turn this on in software with Arduino.
  pinMode(PIR_PIN_LEFT, INPUT_PULLUP);
  pinMode(PIR_PIN_RIGHT, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  lastMotion = millis();
  delay(30000); // allow the PIR sensor to warm up for 30s
  Serial.begin(9600);
}

void loop()
{
  getSensorState();

  unsigned long timer = millis() - lastMotion; // time since we last detected motion
  if (timer < MOVE_DURATION) {
    // if we detected motion recently, drive for MOVE_DURATION ms
    drive();
  } else if (timer > (MOVE_DURATION + PIR_WAIT)) {
    // if the bot has been stopped for PIR_WAIT ms, we can start scanning for movement
    scan();
  } else {
    // if the bot has been in motion for MOVE_DURATION ms, we should stop
    motors.brake();
  }
}

void getSensorState() {
  lBumperState = lBumper.read();  // default INPUT state is HIGH, it is LOW when bumped
  rBumperState = rBumper.read();  // default INPUT state is HIGH, it is LOW when bumped
  lPirState = digitalRead(PIR_PIN_LEFT); // default INPUT state is HIGH, it is LOW when motion detected
  rPirState = digitalRead(PIR_PIN_RIGHT); // default INPUT state is HIGH, it is LOW when motion detected 
}

void scan() {
  if (lPirState == LOW) {
    // We detected motion on the left!
    Serial.println("MOTION LEFT");
    lastMotion = millis();
    reverse();
    turnRight();
  } else if (rPirState == LOW) {
    // We detected motion on the right!
    Serial.println("MOTION RIGHT");
    lastMotion = millis();
    reverse();
    turnLeft();
  }
}

void drive() {
  motors.drive(255);
  if (lBumperState == LOW) { // left side hazard 
    reverse();    // backs up
    turnRight();  // turns
  }

  if (rBumperState == LOW) { // right side hazard
    reverse();   // backs up
    turnLeft();  // turns
  }
}

// reverse() function -- backs up at full power
void reverse()
{
  motors.drive(-255);
  delay(500);
  motors.brake();
  delay(100);  // short delay to let robot fully stop
}

// turnRight() function -- turns RedBot to the Right
void turnRight()
{
  motors.leftMotor(-150);  // spin CCW
  motors.rightMotor(-150); // spin CCW
  delay(500);
  motors.brake();
  delay(100);  // short delay to let robot fully stop
}

// turnRight() function -- turns RedBot to the Left
void turnLeft()
{
  motors.leftMotor(+150);  // spin CW
  motors.rightMotor(+150); // spin CW
  delay(500);
  motors.brake();
  delay(100);  // short delay to let robot fully stop
}


