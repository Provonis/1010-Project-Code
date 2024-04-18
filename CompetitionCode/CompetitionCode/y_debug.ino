void DebugPrint(String debugText, int debugVal) {
  // *** This function requires the following GLOBAL variables: ***
  //  unsigned long debugPrintTime = 0;
  //  unsigned long tslDebugPrint = 0;  // time since last debug print
  //  int debugPrintInterval = 200;     // you can choose this time

  // *** Sample calling syntax: ***
  //  DebugPrint("buttonPressed: ", buttonPressed);
  //  DebugPrint("The value of black is ", black);

  tslDebugPrint = millis() - debugPrintTime;

  if (tslDebugPrint > debugPrintInterval) {
    debugPrintTime = millis();
    Serial.print(debugText);
    Serial.println(debugVal);
  }  // end if

}  // end function


void DebugBlink(int debugBlinkDuration) {
  // *** This function requires the following GLOBAL variables: ***
  //  const int debugLedPin = 13;   // onboard LED
  //  unsigned long debugBlinkTime = 0;
  //  unsigned long tslDebugBlink = 0;  // time since last debug blink
  //  int debugLedHiLo = 0;

  // *** Sample calling syntax: ***
  //  DebugBlink(200);
  //  DebugBlink(500);

  pinMode(debugLedPin, OUTPUT);

  tslDebugBlink = millis() - debugBlinkTime;

  if (tslDebugBlink > debugBlinkDuration) {
    debugBlinkTime = millis();
    debugLedHiLo = 1 - debugLedHiLo;
    digitalWrite(debugLedPin, debugLedHiLo);
  }  // end if

}  // end function
