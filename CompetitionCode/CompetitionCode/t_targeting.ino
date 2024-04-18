void ComputeStuff(void) {
  Serial.println("Performing targeting calculations");
  float d[2] = { 0.0876, 0.1190 };
  float H[] = { 0.0866, 0.0750, 0.1060, 0.0250 };
  TargetServoAngles(d, kappa, lambda, H, alpha, beta, thetaL0, xTargetVec);
  for (int target = 0; target <= 5; target++) {
    Serial.print("To hit a target at ");
    Serial.print(xTargetVec[target]);
    Serial.print(" stripe = ");
    Serial.print(driveTo[target]);
    Serial.print(", command the servo to ");
    Serial.print(writeToServo[target]);
    Serial.println(" deg");
  }
}



float Deg2Rad(float degAngle) {  //Converts degrees to radians
  float radAngle = degAngle * (M_PI / 180.0);
  return radAngle;
}

float Quadratic(float a, float b, float c, int plusOrMinus) {  //calculates the positive or negative root of a quadratic equation
  float root = (-b + plusOrMinus * sqrt(pow(b, 2) - (4.0 * a * c))) / (2.0 * a);
  return root;
}

float LandingDistance(float d[], float kappa, float lambda, float thetaL) {  //calculates the landing distance of a projectile
  float v0 = kappa + (lambda * thetaL);
  float d1 = d[0];
  float d2 = d[1];
  float g = 9.81;                                         //Acceleration due to gravity in m/s^2
  float x_0 = InitialCoordsX0(d1, d2, thetaL);            //Calculates the inital x position by utilizing the InitialCoordsX0 function
  float y_0 = InitialCoordsY0(d1, d2, thetaL);            //Calculates the inital y position by utilizing the InitialCoordsy0 function
  float v_0x = InitialVelocityComponentsV0x(v0, thetaL);  //Calculates the inital velocity in the x direction by utilizing the InitialVelocityComponentsV0x function
  float v_0y = InitialVelocityComponentsV0y(v0, thetaL);  //Calculates the inital velocity in the y direction by utilizing the InitialVelocityComponentsV0y function
  float a = -(1.0 / 2.0) * g;
  float b = v_0y;
  float c = y_0;
  int plusOrMinus = -1;                           //distinguishes that we'll be calculating the negative root
  float tLand = Quadratic(a, b, c, plusOrMinus);  //Calculates the total time the projectile is in the air by utilizing teh Quadratic funtion
  float xLand = x_0 + (v_0x * tLand);             //Calculates the final landing distance
  return xLand;
}

float InitialCoordsX0(float d1, float d2, float thetaL) {  //Calculates the initial position of x
  float x0 = d2 * cos(Deg2Rad(thetaL));                    //Uses the function Deg2Rad to convert the launch angle from degrees to radians
  return x0;
}

float InitialCoordsY0(float d1, float d2, float thetaL) {  //Calculates the initial position of y
  float y0 = d1 + (d2 * sin(Deg2Rad(thetaL)));             //Uses the function Deg2Rad to convert the launch angle from degrees to radians
  return y0;
}

float InitialVelocityComponentsV0x(float v0, float thetaL) {  //Calculates the initial velocity of the projectile in the x direction
  float v0x = v0 * cos(Deg2Rad(thetaL));                      //Uses the function Deg2Rad to convert the launch angle from degrees to radians
  return v0x;
}

float InitialVelocityComponentsV0y(float v0, float thetaL) {  //Calculates the initial velocity of the projectile in the y direction
  float v0y = v0 * sin(Deg2Rad(thetaL));                      //Uses the function Deg2Rad to convert the launch angle from degrees to radians
  return v0y;
}

float RangeAngle(float d[], float kappa, float lambda) {  // Calculates at what angle the maximum range is achievable
  float d1 = d[0];
  float d2 = d[1];
  float thetaL = 30;      // Initializes values
  float range = 0;       // Initializes values
  float rangeAngle = 0;  // Initializes values
  thetaL = 30;
  float xLand = LandingDistance(d, kappa, lambda, thetaL);  // Calls the LandingDistance function to calculate the landing distance
  if (xLand > range) {
      range = xLand;
      rangeAngle = thetaL;
    }
  //   thetaL = thetaL + 0.5;  // Increments thetaL by 0.05 degrees
  // while (thetaL == 30) {
  //   float xLand = LandingDistance(d, kappa, lambda, thetaL);  // Calls the LandingDistance function to calculate the landing distance
  //   if (xLand > range) {
  //     range = xLand;
  //     rangeAngle = thetaL;
  //   }
  //   thetaL = thetaL + 0.5;  // Increments thetaL by 0.05 degrees
  // }
  return rangeAngle;
}

float LaunchAngle(float d[], float kappa, float lambda, float xTarget) {  // Calulates the required steep angle to hit a target
  float d1 = d[0];
  float d2 = d[1];
  float rangeAngle = RangeAngle(d, kappa, lambda);          // Initialize values
  float thetaL = rangeAngle;                                // Initialize values
  float xLand = LandingDistance(d, kappa, lambda, thetaL);  // Initialize values
  while ((xLand >= xTarget) & (thetaL >= rangeAngle)) {
    thetaL = thetaL + 1.57;  // Increments the launch angle by 0.05 degrees
    xLand = LandingDistance(d, kappa, lambda, thetaL);
  }
  return thetaL;
}

// Function to convert radians to degrees
float Rad2Deg(float radAngle) {
  float degAngle = radAngle * (180.0 / M_PI);
  return degAngle;
}

void TargetServoAngles(float d[], float kappa, float lambda, float H[], float alpha, float beta, float thetaL0, float xTargetVec[]) {
  float launchAngleVec[6];
  float servoAngleVec[6];

  for (int k = 0; k < 6; ++k) {  // Corrected loop condition
    Serial.print("Computing target ");
    Serial.println(k);

    // Call LaunchAngle function to compute launch angle for the current target distance
    launchAngleVec[k] = LaunchAngle(d, kappa, lambda, xTargetVec[k]);

    // Call ThetaServo function to compute servo angle for the current launch angle
    servoAngleVec[k] = ThetaServo(H, launchAngleVec[k], alpha, beta, thetaL0);

    // Round the servo angle and cast it to an integer
    writeToServo[k] = int(round(servoAngleVec[k]));
  }
}
// Function to calculate thetaS (servo angle) given H, thetaL, alpha, beta, and thetaL0
float ThetaServo(float H[], float thetaL, float alpha, float beta, float thetaL0) {
  float plusOrMinus = -1;
  float thetaLRad = Deg2Rad(thetaL);
  float alphaRad = Deg2Rad(alpha);
  float thetaL0Rad = Deg2Rad(thetaL0);
  float K1 = H[0] / H[1];
  float K2 = H[0] / H[3];
  float K3 = (pow(H[0], 2) + pow(H[1], 2) - pow(H[2], 2) + pow(H[3], 2)) / (2 * H[1] * H[3]);
  float theta2Rad = thetaLRad + thetaL0Rad;
  float a = cos(theta2Rad) - K1 - K2 * cos(theta2Rad) + K3;
  float b = -2 * sin(theta2Rad);
  float c = K1 - (K2 + 1) * cos(theta2Rad) + K3;
  float root = Quadratic(a, b, c, plusOrMinus);
  float theta4Rad = 2 * atan(root);
  float thetaSRad = (theta4Rad + alphaRad) / (1 - beta);
  float thetaSDeg = Rad2Deg(thetaSRad);

  return thetaSDeg;
}