void GetDataFromMATLAB(void) {
  Serial.println("ready for data");
  for (target = 0; target <= 5; target++) {
    String dataString1 = Serial.readStringUntil('\n');
    String dataString2 = Serial.readStringUntil('\n');
    int stripeNumber = dataString1.toInt();
    float targetDistance = dataString2.toFloat();
    driveTo[target] = stripeNumber;
    xTargetVec[target] = targetDistance;
    Serial.print("For target ");
    Serial.print(target);
    Serial.print(", drive to stripe ");
    Serial.print(driveTo[target]);
    Serial.print(" and aim for ");
    Serial.print(xTargetVec[target], 3);
    Serial.println(" m.");
  }
  target = 0;
}