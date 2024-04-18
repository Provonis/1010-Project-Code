/****************************
 ** User-Defined Functions **
 ****************************/
void ReadButtons(void) {
  // Keep track of the previous button number

  int prevButtonNumber = buttonNumber;

  // Read the button value

  int buttonValue = 0;
  buttonValue = analogRead(buttonPin);

  // Determine the button number that corresponds to the button value

  if (buttonValue < 5) {
    buttonNumber = 1;
  } else if ((buttonValue > 115) && (buttonValue < 175)) {
    buttonNumber = 2;
  } else if ((buttonValue > 305) && (buttonValue < 365)) {
    buttonNumber = 3;
  } else if ((buttonValue > 480) && (buttonValue < 540)) {
    buttonNumber = 4;
  } else if ((buttonValue > 715) && (buttonValue < 775)) {
    buttonNumber = 5;
  } else if (buttonValue > 1015) {
    buttonNumber = 0;
  } else {
    buttonNumber = -1;
  }


  // Determine if the button number is an actual button press or a bounce

  if (buttonNumber == prevButtonNumber) {
    cibn = cibn + 1;
    if (cibn > 100) {
      buttonPressed = buttonNumber;
    }
  } else {
    cibn = 0;
  }
}
void TurnMotorOn(void) {
  if (motorOn == 0) {
    digitalWrite(directionMotorPin, motorRight);
    analogWrite(powerMotorPin, motorPower);
    motorOn = 1;
  }
}
void TurnMotorOff(int reverseTime) {
  if (motorOn == 1) {
    analogWrite(powerMotorPin, LOW);
    delay(10);
    digitalWrite(directionMotorPin, !motorRight);
    analogWrite(powerMotorPin, motorPower);
    delay(reverseTime);
    analogWrite(powerMotorPin, LOW);
    motorOn = 0;
  }
}
bool GetEncoderBoolean(void) {
  irSensorValue = analogRead(irSensorPin);
  if (black == 1 & irSensorValue < 150) {
    return 0;
  } else if (black == 0 & irSensorValue > 500) {
    return 1;
  } else {
    return black;
  }
}
void CountStripes(void) {
  bool prevBlack = black;
  black = GetEncoderBoolean();
  tslStripeChange = millis() - stripeChangeTime;
  if (black != prevBlack) {
    stripeChangeTime = millis();
    if (motorRight == 1) {
      counts = counts + 1;
    } else {
      counts = counts - 1;
    }
    Serial.println(counts);
    // Serial.println(tslStripeChange);
  }
}