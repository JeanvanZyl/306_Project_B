uint8_t GenerateBits(uint8_t n) {
  int finalReading = 0;
  int LSB, bit1, bit2, bit3, MSB;

  anVal4 = analogRead(A4); // centre
  anVal3 = analogRead(A3);
  anVal2 = analogRead(A2);
  anVal1 = analogRead(A1);
  anVal0 = analogRead(A0); // outermost
  //PrintValues(anVal0, anVal1, anVal2, anVal3, anVal4, ',');

  MSB = HiOrLo(anVal4, 450);
  bit3 = HiOrLo(anVal3,320);
  bit2 = HiOrLo(anVal2, 320);
  bit1 = HiOrLo(anVal1, 320);
  LSB = HiOrLo(anVal0, 320);
  //PrintValues(LSB, bit1, bit2, bit3, MSB, ',');
  
  finalReading = MSB*(16) + bit3*(8) + bit2*(4) + bit1*(2) + LSB*(1);
  return finalReading;
}

void PrintValues(int v0, int v1, int v2, int v3, int v4, char delim) {
    Serial.print(v4);
    Serial.print(delim);
    Serial.print(" ");
    Serial.print(v3);
    Serial.print(delim);
    Serial.print(" ");
    Serial.print(v2);
    Serial.print(delim);
    Serial.print(" ");
    Serial.print(v1);
    Serial.print(delim);
    Serial.print(" ");
    Serial.println(v0);
}