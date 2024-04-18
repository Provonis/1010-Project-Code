void Demo1(void) {
  int prevButtonPressed = buttonPressed;
  ReadButtons();
  switch (buttonPressed) {
    case 3:

    case 1:
      tslIncrement = millis() - incrementTime;
      if (buttonPressed != prevButtonPressed || tslIncrement > 250) {
        incrementTime = millis();
        if (buttonPressed == 3) {
          target = target + 1;
        }
        else if (buttonPressed == 1) {
            target = target - 1;
          }
        target = constrain(target, 0, 5);
        Serial.print("New value of target is ");
        Serial.println(target);
      }
      break;
    case 4:
    case 2:
      tslIncrement = millis() - incrementTime;
      if (buttonPressed != prevButtonPressed || tslIncrement > 250) {
        incrementTime = millis();
        if (buttonPressed == 4) {
          headed = headed - 1;
        }
        else if (buttonPressed ==2) {
          headed = headed + 1;
        }
        
        headed = constrain(headed,0 ,2); 
        Serial.print("New value of headed is ");
        Serial.println(headed);
      }
      break;
    case 5:
      startMotion = 1;
      state = 1;
      break;
    case 0: 
    MoveLauncher();
    break;
  }
}