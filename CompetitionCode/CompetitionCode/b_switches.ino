void TestSwitches(void) {
  int tempLeftSwitchState = 0;
  int tempRightSwitchState = 0;
  // Keep track of previous switch states for comparison
  int prevLeftSwitchState = leftSwitchState;
  int prevRightSwitchState = rightSwitchState;

  // Update the switch state variables
  tempLeftSwitchState = digitalRead(leftPinSwitch);
  tempRightSwitchState = digitalRead(rightPinSwitch);

  // Left switch Debounce code
  if (tempLeftSwitchState != prevLeftSwitchState) {
    tslLeftSwitchChange = millis() - leftSwitchChangeTime;
    if (tslLeftSwitchChange > switchDebounceInterval) {
      leftSwitchState = tempLeftSwitchState;
      leftSwitchChangeTime = millis();
    }
  }
  // Right switch Debounce code
  if (tempRightSwitchState != prevRightSwitchState) {
    tslRightSwitchChange = millis() - rightSwitchChangeTime;
    if (tslRightSwitchChange > switchDebounceInterval) {
      rightSwitchState = tempRightSwitchState;
      rightSwitchChangeTime = millis();
    }
  }

  // If appropriate, print a new message
  tslPrint = millis() - printTime;
  if ((leftSwitchState != prevLeftSwitchState) || (rightSwitchState != prevRightSwitchState) || (tslPrint > printInterval)) {
    printTime = millis();
    Serial.print(F("The right switch state is "));
    Serial.print(tempRightSwitchState);
    Serial.print(F(" The left switch state is "));
    Serial.println(tempLeftSwitchState);
  }
}