void TestReloader(void) {
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 5:
      if (prevButtonPressed != buttonPressed) {
        if (state > 0) {
          Serial.println("Reload in progress");
        } else {
          state = 1;
        }
      }
      break;
  }
  
  switch (state) {
    case 1:
      reloaderServo.write(dispenseAngle);
      Serial.println("Dispensing");
      state = 2;
      stateChangeTime = millis();
      break;
      
    case 2:
      tslStateChange = millis() - stateChangeTime;
      if (tslStateChange > dispenseDuration) {
        reloaderServo.write(holdAngle);
        Serial.println("Holding");
        state = 0;
      }
      break;
  }
}
