/*******************
 ** Loop Function **
 *******************/
void loop(void) {
  //PUT YOUR MAIN CODE HERE, TO RUN REPEATEDLY
  //Serial.print(Serial.available());
  //Serial.println("bytes available to read");

  if (Serial.available() >= 2) {
    userInput = Serial.read();
    Serial.read();
    Serial.print("User entered");
    Serial.println(userInput);
    newUserInput = 1;
  }

  // switch (userInput)  {
  //   case 'a':
  //   // do something once
  //   if (newUserInput == 1)  {
  //     //CODE HERE (once code)
  //     newUserInput = 0; // do NOT delete!!
  //   }
  //   //do something over and over
  //   // CODE HERE
  //   break;

  switch (userInput) {
    case 'a':
      if (newUserInput == 1) {
        Serial.println(F("Test a: Check that IR LED is blinking"));
        //CODE HERE (once code)
        newUserInput = 0;  // do NOT delete!!
      }
      TestIRLED();
      break;

    case 'b':
      if (newUserInput == 1) {
        Serial.println(F("Test b: Press the switches to test"));
        newUserInput = 0;  // do NOT delete!!
      }
      TestSwitches();
      break;

    case 'c':
      if (newUserInput == 1) {
        Serial.println(F("Test c: Press the buttons to test"));
        newUserInput = 0;  // do NOT delete!!
      }
      TestButtons();
      break;

    case 'd':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to test the motor."));
        newUserInput = 0;  // do NOT delete!!
      }
      //do something over and over
      TestMotor();
      break;

    case 'e':
      // do something once
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to test the motor and sensor."));
        newUserInput = 0;  // do NOT delete!!
      }
      TestMotor();
      break;

    case 'f':
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to test the motor and encoder."));
        newUserInput = 0;  // do NOT delete!!
      }
      TestMotor();
      break;
    case 'g':
      if (newUserInput == 1) {
        Serial.println(F("Press the left and right buttons to count stripes"));
        Serial.println(F("Press the up and down buttons to increment counts"));
        Serial.println(F("Press the select button to set counts to 24"));

        newUserInput = 0;  // do NOT delete!!
      }
      TestMotor();
      break;
    case 'h':
      if (newUserInput == 1) {
        startMotion = 0;
        Serial.println(F("Press the left and right buttons to increment desiredPosition"));
        Serial.println(F("Press the up and down buttons to increment counts"));
        Serial.println(F("Press the select button to send the launcher to the desired position"));

        newUserInput = 0;  // do NOT delete!!
      }
      TestMoveLauncher();
      break;
    case 'i':
      if (newUserInput == 1) {
        Serial.println(F("Press the up/down/left/right buttons to increment desiredServoAngle"));
        Serial.println(F("Press the select button to command the servo and fire the solenoid"));

        newUserInput = 0;  // do NOT delete!!
      }
      TestAimFire();
      break;
    case 'j':
      if (newUserInput == 1) {
        Serial.println(F("Press the select button to reload a ball"));
        newUserInput = 0;  // do NOT delete!!
      }
      TestReloader();
      break;
    case 'k':
      if (newUserInput == 1) {
        startMotion = 0;
        Serial.println(F("Press the left and right buttons to increment headed"));
        Serial.println(F("Press the up and down buttons to increment target"));
        Serial.println(F("Press the select button to start Demo1"));

        newUserInput = 0;  // do NOT delete!!
      }
      Demo1();
      break;
    case 'z':
      // do something oncection
      if (newUserInput == 1) {
        PrintMenu();
        newUserInput = 0;  // do NOT delete!!
      }
      break;

    case 's':  // get data from MATLAB
      Serial.println("Getting data from MATLAB");
      GetDataFromMATLAB();
      userInput = 'x';
      Serial.println("done");
      break;

    case 't':
      GetDataFromMATLAB();
      ComputeStuff();
      userInput = 'x';
      Serial.println("done");
      break;

    case 'v':

      if (newUserInput == 1) {
        Serial.println(F("Running competition code"));
        newUserInput = 0;
        GetDataFromMATLAB();
        startMotion = 1;
        state = 1;
      }
      Demo1();
      break;


    default:
      // do something oncection
      if (newUserInput == 1) {
        Serial.println(F("Waiting for a valid user input"));
        Serial.println(F("Enter z to print menu"));
        newUserInput = 0;  // do NOT delete!!
        TurnMotorOff(30);
        Serial.println(F("Aborting!"));
        startMotion = 0;
        headed = 0;
        target = 0;
        state = 0;
        digitalWrite(solenoidPowerPin, LOW);
      }
      break;
  }
}