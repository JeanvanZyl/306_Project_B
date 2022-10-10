uint8_t GenerateBits(uint8_t n) {
  int finalReading = 0;
  int LSB, bit1, bit2, bit3, MSB;

  anVal4 = analogRead(A4);
  anVal3 = analogRead(A3);
  anVal2 = analogRead(A2);
  anVal1 = analogRead(A1);
  anVal0 = analogRead(A0);
  PrintValues(anVal0, anVal1, anVal2, anVal3, anVal4, ',');

  MSB = HiOrLo(anVal4);
  bit3 = HiOrLo(anVal3);
  bit3 = HiOrLo(anVal3);
  bit3 = HiOrLo(anVal3);
  LSB = HiOrLo(anVal3);
  PrintValues(LSB, bit1, bit2, bit3, MSB, ',');
  
  finalReading = MSB*(2^4) + bit3*(2^3) + bit2*(2^2) + bit1*(2^1) + LSB*(2^0);
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