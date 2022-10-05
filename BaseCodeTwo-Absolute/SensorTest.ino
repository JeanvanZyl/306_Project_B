// Comma delimiter to separate consecutive data if using more than 1 sensor
const char kDelimiter = ',';
const char kSpace = ' ';  
// Interval between serial writes
const int kSerialInterval = 50;   
// Timestamp to track serial interval
unsigned long serialPreviousTime;

void SensorTest() {
  // Function runs the motor at 255, 205 and 155 for 5 secs each and takes 50ms readings of
  //Serial.println("Starting Test");
  //unsigned long startTime;
  //for (int ii = 0; ii <= 2; ii++) {
    //Serial.println();
    //Serial.println();
    //Serial.print("Motor Speed: ");
    //int motorSpeed = 255 - 50*ii;
    //Serial.println(motorSpeed);
    // Adjust motor speed from 255, 205 and 155
    //analogWrite(6, (255 - 50*ii));
    //while(500 > (millis() - startTime)) {
      processOutgoingSerial(analogRead(18), analogRead(17), analogRead(16), analogRead(15), analogRead(14));
      //delay(1);
    //}
    //startTime = millis();
  //}
  //analogWrite(6, 0);
  //delay(10000);
}

void processOutgoingSerial(int Bit0, int Bit1, int Bit2, int Bit3, int Bit4)
{
   // Enter into this only when serial interval has elapsed
  if((millis() - serialPreviousTime) > kSerialInterval) 
  {
    // Reset serial interval timestamp
    serialPreviousTime = millis(); 
    sendDataToSerial(Bit0, Bit1, Bit2, Bit3, Bit4); 
  }
}

void sendDataToSerial(int Bit0, int Bit1, int Bit2, int Bit3, int Bit4)
{
  Serial.print(Bit0);
  Serial.print(kDelimiter);
  Serial.print(Bit1);
  Serial.print(kDelimiter);
  Serial.print(Bit2);
  Serial.print(kDelimiter);
  Serial.print(Bit3);
  Serial.print(kDelimiter);
  Serial.println(Bit4);
  //Serial.println(' '); // Add final line ending character only once
}
