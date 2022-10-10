// Function to generate a 5-bit number for the encoder light sensor readings
/*uint8_t GenerateBits(uint8_t n) {
  uint8_t finalReading = 0b00000;
  uint8_t analogInput;
  analogInput = analogRead(A0);
  Serial.print("TEST: ");
  Serial.println(analogInput);
  // For bits until n read analog readings and store them in an overarching total
  for (uint8_t ii = 0; ii < n; ii++) {
    analogInput = analogRead((18-n));
    Serial.print("Sensor Reading: ");
    Serial.println(analogInput);
    finalReading |= ((analogInput > 325) * (2^n));
  }
  Serial.print("Reading processing: ");
  Serial.println(finalReading);
  return finalReading;
}*/

// **** From loop ****

// Five digit binary number 32 possible states from 0b00000 to 0b11111
  // 360/32 = 11.25 deg
  // Read the state of each of the analogue pins
  /*anVal0 = analogRead(A0);
  anVal1 = analogRead(A1);
  anVal2 = analogRead(A2);
  anVal3 = analogRead(A3);
  anVal4 = analogRead(A4);
  Serial.println(anVal0);
  Serial.println(anVal1);
  Serial.println(anVal2);
  Serial.println(anVal3);
  Serial.println(anVal4);*/
  
  //Serial.println("Generated Bits: ");
  //Serial.println(currentVal);

// Calculate the delta value
  /*deltaVal = (int)currentVal - (int)homeVal;
  
  // If the delta value is larger than 0 it currentVal is larger than home and it is turning clockwise
  if (deltaVal != 0 && setDirection) {
    if(deltaVal > 0) {
      movingClockwise = true;
    } else {
      movingClockwise = false;
    }
    // Handle the edge case where the disk has gone from 32 to 1
    if (homeVal == 0b11111) {
      movingClockwise = true;
    }
    // Direction is now set
    setDirection = false;
  }*/
  

  // Convert the values to booleans
  //LSB = HiOrLo(anVal0);
  //bit1 = HiOrLo(anVal1);
  //bit2 = HiOrLo(anVal2);
  //bit3 = HiOrLo(anVal3);
  //MSB = HiOrLo(anVal4);
  //Serial.print(LSB);
  //Serial.print(bit1);
  //Serial.print(bit2);
  //Serial.print(bit3);
  //Serial.println(MSB);

// Calculate the shaft displacement from the local home position
    /*if (movingClockwise) {
      // If the current value is now less than the local home value it has overshot
      if (homeVal > currentVal) {
        // TODO Check whether this should be 31 or 32
        int toZero = (int)(32 - homeVal);
        localDeg = SegToDeg((toZero + currentVal), movingClockwise);
      } else {
        localDeg = SegToDeg((currentVal - homeVal), movingClockwise);
      }
    } else {
      // If the current value is now more than the local home value it has overshot
      if (homeVal < currentVal) {
        // TODO Check whether this should be 31 or 32
        int toZero = (int)(32 - currentVal);
        localDeg = SegToDeg((toZero + homeVal), movingClockwise);
      } else {
        localDeg = SegToDeg((currentVal - currentVal), movingClockwise);
      }
    }


    
    // Calculate the displacement from the 0b00000 position
    if (movingClockwise) {
      // If CW this is just the current value
      totalDeg = SegToDeg(currentVal, movingClockwise);
    } else {
      // If CCW this is 32 minus the currentvalue
       totalDeg = SegToDeg((32 - currentVal), movingClockwise);
    }*/