void TestAimFire(void) {

  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:

    case 1:

    case 4:

    case 2:
      switch (buttonPressed) {
        case 3:
          servoAngleIncrement = 5;
          break;
        case 1:
          servoAngleIncrement = -5;
          break;
        case 4:
          servoAngleIncrement = -1;
          break;
        case 2:
          servoAngleIncrement = 1;
          break;
      }
      tslIncrement = millis() - incrementTime;
      if (prevButtonPressed != buttonPressed || tslIncrement > 250) {
        incrementTime = millis();
        desiredServoAngle = desiredServoAngle + servoAngleIncrement;
        desiredServoAngle = constrain(desiredServoAngle, 0, 180);
        Serial.print("new value of the servo angle is ");
        Serial.println(desiredServoAngle);
      }
      break;
    case 5:
      if (prevButtonPressed != buttonPressed) {
        if (state > 0) {
          Serial.println("The aim/fire sequence is in progress");

        } else {
          state = 1;
          stateChangeTime = millis();
        }
        break;
      }
  }
  switch (state) {
    case 1:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {
        launcherServo.write(desiredServoAngle);
        Serial.print("Launcher servo commanded to ");
        Serial.println(desiredServoAngle);
        state = 2;
        stateChangeTime = millis();
      }

      break;

    case 2:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > 1000) {
        digitalWrite(solenoidPowerPin, HIGH);
        Serial.println("Firing");
        state = 3;
        stateChangeTime = millis();
      }
      break;

    case 3:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > solenoidActivationTime) {
        digitalWrite(solenoidPowerPin, LOW);
        Serial.println("Done firing");
        state = 0;
      }
      break;


    case 0:
      break;

    default:
      break;
  }
}
