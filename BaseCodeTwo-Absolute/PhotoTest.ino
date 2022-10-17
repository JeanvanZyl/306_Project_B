void PhotoTest(bool moveMotor, int timeLimit) {
    // start the motor
    if (moveMotor) {
        analogWrite(6, 150);
    }
    int startTime = millis();
    uint8_t gray;
    uint8_t binary;
    while((millis() - startTime) < timeLimit * 1000) {
        gray = GenerateBits(5);
        binary = GrayToBin(gray);
        Serial.println(binary);
        delay(50);
    }
    analogWrite(6, 0);
}