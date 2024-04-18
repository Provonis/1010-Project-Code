void MoveLauncher(void) {
  //DebugPrint("Calling MoveLauncher function = ", startMotion);
  if (motorOn == 1) {
    Moving();
  } else {
    if (startMotion == 1) {
      PreparingToMove();
    } else {
      NotMoving();
    }
  }
}
void PreparingToMove(void) {
  //set desired postition
  if (userInput == 'k' || userInput == 'v') {

    switch (headed) {
      case 0:
        leftSwitchState = digitalRead(leftPinSwitch);
        if (leftSwitchState == 1) {
          Serial.print("Already Home!");
          counts = 5;
          desiredPosition = 5;
          startMotion = 0;
          headed = 1;
        } else {
          Serial.println("Headed Home");
          desiredPosition = -50;
        }
        break;
      case 1:
        desiredPosition = driveTo[target];
        Serial.print("Desired position is now ");
        Serial.println(desiredPosition);
        break;
      case 2:
        desiredPosition = 100;
        break;
    }
  }
  //set motor right
  if (desiredPosition > counts) {
    motorRight = 1;  //need to move right
  } else {
    motorRight = 0;  // need to move left
  }
  //turn motor on
  if (counts != desiredPosition) {
    TurnMotorOn();
    startMotion = 0;
  }
}
void Moving(void) {
  //count stripes
  CountStripes();
  //stop at target
  if (counts == desiredPosition) {
    TurnMotorOff(30);
    CountStripes();
    Serial.print("Launcher at stripe ");
    Serial.println(counts);
  }
  //read switches
  leftSwitchState = digitalRead(leftPinSwitch);
  rightSwitchState = digitalRead(rightPinSwitch);
  //stop at home
  if (motorRight == 0 && leftSwitchState == 1) {
    TurnMotorOff(15); // if robot remains on wall can decrease time in mS
    CountStripes();
    counts = 5;
    Serial.println("Launcher at home - counts set to 5");
  }
  //stop at reloader
  if (motorRight == 1 && rightSwitchState == 1) {
    TurnMotorOff(15);
    CountStripes();
    counts = 43;
    Serial.println("Launcher at reloader - counts set to 43");
  }
}
