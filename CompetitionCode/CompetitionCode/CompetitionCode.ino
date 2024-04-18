/****************************************************************
Author Names: [James Utton and Daniel Sardoni]
Lab section: 004
Team number: 4.03
Date:  3/20/2024
Sketch Description: Prints menu to serial monitor with various character inputs 


Button Usage: Up/Down    -  
              Left/Right -  
              Select     -  

Pin Usage:    Pin type/number                             Hardware 
              ----------------                            ----------------                   
digital pin: 4, 5, 6, 9, 10, 11, 12, 13 analog pin : A5, A7         Mounted Romeo, irSensor, DCmotor, built-in buttons, switches, reloader             
*******************************************************************/

/****************************
 ** #defines and #includes **
 ****************************/
#include <Servo.h>
/***********************
 ** Global Variables ***
 ***********************/
// *** Declare & Initialize Pins ***
const int ledPin = 13;
const int leftPinSwitch = 11;
const int rightPinSwitch = 12;
const int buttonPin = A7;
const int directionMotorPin = 4;  //Initialize pin 4
const int powerMotorPin = 5;      //Initialize pin 5
const int irSensorPin = A5;
const int launcherServoPin = 9;
const int solenoidPowerPin = 6;
const int reloaderServoPin = 10;
const int debugLedPin = 13;  // onboard LED
// *** Create Servo Objects ***
Servo launcherServo;
Servo reloaderServo;

// *** Declare & Initialize Program Variables ***
//User Input
char userInput = 'z';
bool newUserInput = 1;
//Debug
unsigned long debugPrintTime = 0;
unsigned long tslDebugPrint = 0;  // time since last debug print
int debugPrintInterval = 200;     // you can choose this time
unsigned long debugBlinkTime = 0;
unsigned long tslDebugBlink = 0;  // time since last debug blink
int debugLedHiLo = 0;

//General
unsigned long incrementTime = 0;
unsigned long tslIncrement = 0;
int state = 0;
unsigned long stateChangeTime = 0;
unsigned long tslStateChange = 0;

//IR LED
int ledOnDuration = 1000;
int ledOffDuration = 2000;
unsigned long blinkTime = 0;
unsigned long tslBlink = 0;
bool ledOn = 0;

//Contact Switches
int leftSwitchState = 0;
int rightSwitchState = 0;
unsigned long printTime = 0;
unsigned long tslPrint = 0;
int printInterval = 250;
unsigned long leftSwitchChangeTime = 0;
unsigned long rightSwitchChangeTime = 0;
unsigned long tslLeftSwitchChange = 0;
unsigned long tslRightSwitchChange = 0;
int switchDebounceInterval = 20;

//Buttons
int buttonNumber = 0;
unsigned long cibn = 0;
int buttonPressed = 0;

//DC Motor
const int motorPower = 255;
bool motorOn = 0;
bool motorRight = 0;

//IR Reflectance Sensor + GetEncoderBoolean + CountStripes
bool black = 1;
unsigned long stripeChangeTime = 0;
unsigned long tslStripeChange = 0;
int counts = 24;
bool startMotion = 0;
int irSensorValue = 0;
int desiredPosition = 24;

//Solenoid
int solenoidActivationTime = 31;

//Launcher Servo
int desiredServoAngle = 90;
int servoAngleIncrement = 5;

//Reloader Servo
int holdAngle = 63;
int dispenseAngle = 20;
int dispenseDuration = 151; // changed

//demo_1
int target = 0;
int headed = 0;
int driveTo[] = { 19, 35, 33, 31, 32, 34 };
float xTargetVec[6] = { 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

//At Target
int writeToServo[] = { 140, 110, 130, 90, 120, 80 };
// float d[2] = { 0.0876, 0.1190 };
float kappa = 3.04;
float lambda = -0.0025;
//float xTarget = 1.20;  // Initializes the target distance
float H[] = { 0.0866, 0.0750, 0.1060, 0.0250 };
float alpha = 33.44;
float beta = 0.0132;
float thetaL0 = 26.76;









// 1 means just entered a letter
// 0 means user did not enter a letter this time through loop function
/********************
 ** Setup Function **
 ********************/
void setup(void) {
  // PUT YOUR SETUP CODE HERE, TO RUN ONCE:

  // *** Initialize Serial Communication ***
  Serial.begin(9600);

  // *** Configure Digital Pins & Attach Servos ***
  pinMode(ledPin, OUTPUT);
  pinMode(leftPinSwitch, INPUT_PULLUP);
  pinMode(rightPinSwitch, INPUT_PULLUP);
  pinMode(directionMotorPin, OUTPUT);  // sets the pin as an output
  pinMode(powerMotorPin, OUTPUT);      // sets the pin as an output
  launcherServo.attach(launcherServoPin);
  pinMode(solenoidPowerPin, OUTPUT);
  reloaderServo.attach(reloaderServoPin);
  // *** Take Initial Readings ***
  black = GetEncoderBoolean();
  // *** Move Hardware to Desired Initial Positions ***
  reloaderServo.write(holdAngle);

}  // end setup() function
