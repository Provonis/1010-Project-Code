void NotMoving(void) {
  leftSwitchState = digitalRead(leftPinSwitch);
  rightSwitchState = digitalRead(rightPinSwitch);
  if (leftSwitchState == 1) {
    AtHome();
  }
  //at reloader
  else if (rightSwitchState == 1) {
    AtReloader();
  }
  //at target
  else if (desiredPosition == counts) {
    AtTarget();
  }
}
void AtReloader(void) {
  switch (state) {
    case 1:
      reloaderServo.write(dispenseAngle);
      Serial.println("Dispensing");
      state = 2;
      stateChangeTime = millis();
      break;
    case 2:
      // desiredServoAngle = writeToServo[target];
      Serial.print("target == ");
      Serial.println(target);
      Serial.print("The desired servo angle is ");
      Serial.println(desiredServoAngle);
      // launcherServo.write(desiredServoAngle);
      Serial.println(F("Changing servo angle at reloader"));
      tslStateChange = millis() - stateChangeTime;
      //target = target + 1;
      if (tslStateChange > dispenseDuration) {
        reloaderServo.write(holdAngle);
        Serial.println("Holding");
        state = 3;
        stateChangeTime = millis();
      }
      break;
    case 3:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1) {  //changed (1000)
        headed = 1;
        // target = 0;
        startMotion = 1;
        // target = target + 1;
        // desiredServoAngle = writeToServo[target];
        // launcherServo.write(desiredServoAngle);
        Serial.println("Ball reloaded - setting motion variables");
        state = 1;
      }
      break;
  }
}
void AtHome(void) {
  switch (state) {
    case 1:
      digitalWrite(ledPin, HIGH);
      Serial.println("Starting timer - led on");
      state = 2;
      stateChangeTime = millis();
      break;
    case 2:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {  //do not change
        digitalWrite(ledPin, LOW);
        Serial.println("Triggering timer - led off");
        state = 3;
      }
      break;

    case 3:
      Serial.println("Setting motion variable");
      if (target < 5) {
        if (target == 0 && userInput == 'v') {
          Serial.println("Calling ComputeStuff()");
          ComputeStuff();
          launcherServo.write(writeToServo[target]);
        }
        startMotion = 1;
        headed = 1;
        state = 1;
        Serial.println("I did this i set the motion");
      } else {
        target = 0;
        state = 0;
        Serial.println("All done");
        if (userInput == 'v') {
          Serial.println("done");
        }
        userInput = 'x';
      }
      break;
  }
}
void AtTarget(void) {
  switch (state) {
    case 1:
      desiredServoAngle = writeToServo[target];
      launcherServo.write(desiredServoAngle);
      Serial.print("Commanding launcher servo to ");
      Serial.print(desiredServoAngle);
      Serial.print(" for target ");
      Serial.println(target);
      state = 2;
      stateChangeTime = millis();
      break;
    case 2:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1) {  // changed (1000)
        digitalWrite(solenoidPowerPin, HIGH);
        Serial.println("Firing!");
        state = 3;
        stateChangeTime = millis();
      }
      break;
    case 3:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > solenoidActivationTime) {
        digitalWrite(solenoidPowerPin, LOW);
        Serial.println("Done firing");
        state = 4;
        stateChangeTime = millis();
        Serial.print(target);
      }
      break;
    case 4:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1) {  //changed (2000)
        //launcherServo.write(75); changed
        // desiredServoAngle = writeToServo[target];
        // launcherServo.write(desiredServoAngle);
        Serial.println("Commanding launcher servo to reload angle");
        state = 5;
      }
      break;
    case 5:
      startMotion = 1;
      if (target < 5) {
        headed = 2;
      } else {
        headed = 0;
      }
      target = target + 1;
      desiredServoAngle = writeToServo[target];
      launcherServo.write(desiredServoAngle);
      Serial.println("Target actions complete - setting motion variable");
      state = 1;
      break;
  }
}
