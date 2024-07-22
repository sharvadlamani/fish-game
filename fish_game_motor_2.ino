/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->  http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>
#include "pitches.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

// notes in the melody:
int melody[] = {
  NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_D5, NOTE_D5, NOTE_F4, NOTE_C5, NOTE_DS5, NOTE_D5, NOTE_AS4, NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_AS4, NOTE_C4, NOTE_A4, NOTE_C5, NOTE_AS4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8, 8, 8, 4, 4, 8, 4, 4, 4, 4, 8, 8, 8, 4, 4, 8, 4, 4, 4
};

void play_melody() {
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 19; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);
  }

  delay(2000);
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  while (!Serial);
  Serial.println("Stepper test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }

  myMotor->setSpeed(50);  // 10 rpm

  play_melody();
}

void loop() {
  // Serial.println("Single coil steps");
  // myMotor->step(100, FORWARD, SINGLE);
  // myMotor->step(100, BACKWARD, SINGLE);

  // Serial.println("Double coil steps");
  // myMotor->step(100, FORWARD, DOUBLE);
  // myMotor->step(100, BACKWARD, DOUBLE);

  // Serial.println("Interleave coil steps");
  // myMotor->step(100, FORWARD, INTERLEAVE);
  // myMotor->step(100, BACKWARD, INTERLEAVE);

  // Serial.println("Microstep steps");
  // myMotor->step(50, FORWARD, MICROSTEP);
  // myMotor->step(50, BACKWARD, MICROSTEP);
  char inputVariable = Serial.read();

  myMotor->step(150, BACKWARD, DOUBLE);

  while (inputVariable == 'c') {
    Serial.println("Stopping...");
    myMotor->setSpeed(0);
    inputVariable = Serial.read();
    Serial.println(inputVariable);
  }
}