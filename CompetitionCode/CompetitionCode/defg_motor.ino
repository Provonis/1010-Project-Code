void TestMotor(void) {
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:  // UP button
    case 1:  // DOWN button
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
      break;  // doing nothing
    case 4:   // LEFT button
      motorRight = 0;
      TurnMotorOn();
      break;
    case 2:  // RIGHT button
      motorRight = 1;
      TurnMotorOn();
      break;
    case 5:  // SELECT button
      if (counts != 24) {
        counts = 24;
        Serial.print("New value of counts is ");
        Serial.println(counts);
      }
      break;  // doing nothing
    case 0:   // NONE button
      TurnMotorOff(30);
      if (userInput == 'g') {
        CountStripes();
      }
      break;
    default:
      break;
  }
  if (motorOn == 1) {
    switch (userInput) {
      case 'd':
        PrintLeftRight();
        break;
      case 'e':
        PrintSensorValue();
        break;
      case 'f':
        PrintBlackWhite();
        break;
      case 'g':
        CountStripes();
        break;
    }
  }
}
void PrintLeftRight(void) {
  tslPrint = millis() - printTime;
  if (tslPrint > printInterval) {
    printTime = millis();
    Serial.print("Launcher is moving ");
    if (motorRight == 1) {
      Serial.println("RIGHT");
    } else {
      Serial.println("LEFT");
    }
  }
}
void PrintSensorValue(void) {
  irSensorValue = analogRead(irSensorPin);
  tslPrint = millis() - printTime;
  if (tslPrint > 50) {
    printTime = millis();
    Serial.print("IrSensorValue is ");
    Serial.println(irSensorValue);
  }
}
void PrintBlackWhite(void) {
  bool prevBlack = black;
  black = GetEncoderBoolean();
  if (black != prevBlack) {
    if (black == 1) {
      Serial.println("Over black");
    } else {
      Serial.println("Over white");
    }
  }
}