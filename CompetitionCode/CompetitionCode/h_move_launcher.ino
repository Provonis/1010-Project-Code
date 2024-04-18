void TestMoveLauncher(void) {
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:
    case 1:
      tslIncrement = millis() - incrementTime;
      if (prevButtonPressed != buttonPressed || tslIncrement > 250) {
        incrementTime = millis();
        if (buttonPressed == 3) {
          counts = counts + 1;
        } else if (buttonPressed == 1) {
          counts = counts - 1;
        }
        Serial.print("New value of counts is ");
        Serial.println(counts);
      }
      break;
    case 4:
    case 2:
      tslIncrement = millis() - incrementTime;
      if (prevButtonPressed != buttonPressed || tslIncrement > 250) {
        incrementTime = millis();
        if (buttonPressed == 2) {
          desiredPosition = desiredPosition + 1;
        } else if (buttonPressed == 4) {
          desiredPosition = desiredPosition - 1;
        }
        Serial.print("New value of desiredPosition is ");
        Serial.println(desiredPosition);
      }
      break;
    case 5:
      startMotion = 1;
      break;
    case 0:
      MoveLauncher();
      break;
    default:
      //nothing
      break;
  }
}