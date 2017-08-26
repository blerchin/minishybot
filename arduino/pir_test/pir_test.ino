/***********************************************************************
 * Exp5_Bumpers -- RedBot Experiment 5
 * 
 * Now let's experiment with the whisker bumpers. These super-simple switches
 * let you detect a collision before it really happens- the whisker will
 * bump something before your robot crashes into it.
 * 
 * This sketch was written by SparkFun Electronics, with lots of help from 
 * the Arduino community.
 * This code is completely free for any use.
 * Visit https://learn.sparkfun.com/tutorials/redbot-inventors-kit-guide 
 * for SIK information.
 * 
 * 8 Oct 2013 M. Hord
 * Revised 30 Oct 2014 B. Huang
 ***********************************************************************/

#include <RedBot.h>

const int ledPin = 13;
const int pirLeftPin = A0;
const int pirRightPin = A1;

void setup()
{
  pinMode(pirLeftPin, INPUT_PULLUP);
  pinMode(pirRightPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  delay(2000);
}

void loop()
{
    if(digitalRead(pirRightPin) == LOW) {
      digitalWrite(ledPin, HIGH);
    } else if (digitalRead(pirLeftPin) == LOW) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    delay(125);   // Wait for 125ms. 
}

