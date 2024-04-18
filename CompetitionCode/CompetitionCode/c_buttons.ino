void TestButtons(void) {

  // Keep track of the previously pressed button
  int prevButtonPressed = buttonPressed;

  // Check what button is currently pressed
  ReadButtons();

  // If appropriate, print a new message
  tslPrint = millis() - printTime;
  if (tslPrint > printInterval || buttonPressed != prevButtonPressed) {
    printTime = millis();
    switch (buttonPressed) {
      case 3:
        Serial.println(F("UP button pressed"));
        break;
      case 1:
        Serial.println(F("DOWN button pressed"));
        break;
      case 4:
        Serial.println(F("LEFT button pressed"));
        break;
      case 2:
        Serial.println(F("RIGHT button pressed"));
        break;
      case 5:
        Serial.println(F("SELECT button pressed"));
        break;
      case 0:
        Serial.println(F("NO button pressed"));
        break;

      default:
        Serial.println(F("Something went wrong"));
        break;
    }
  }
}