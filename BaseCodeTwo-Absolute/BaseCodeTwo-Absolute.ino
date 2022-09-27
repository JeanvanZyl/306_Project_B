float deg = 45;  // Rotation degree
float s = 0;     //Encoder counts
int sm1 = 0;     //Built-in chanel 1
int sm2 = 0;     //Built-in chanel 2
int r = 0;       //indicator for reading builtin encoder to avoid the reading redundancy
float er;        //Proportional error for PI controller
float eri;       //Integral error for PI controller

// ***********************Task Variables************************* 
int anVal0;
int anVal1;
int anVal2;
int anVal3;
int anVal4;

bool LSB;
bool bit1;
bool bit2;
bool bit3;
bool MSB;
bool setHome = true;
bool setDirection = true;
bool movingClockwise = true;

uint8_t homeVal;
uint8_t currentVal;
int deltaVal;
int movedDeg;

float localDeg;
float totalDeg;
// **************************************************************

int t = 0;   //time in ms
int t0 = 0;  //memory for time in ms



int finish = 0;  //finish indicator
int rep = 1;     //Repetition indicator




void setup() {

  Serial.begin(250000);  //Baud rate of communication

  Serial.println("Enter the desired rotation in degree.");

  while (Serial.available() == 0)  //Obtaining data from user
  {
    //Wait for user input
  }

  deg = Serial.readString().toFloat();  //Reading the Input string from Serial port.
  if (deg < 0) {
    analogWrite(3, 255);  //change the direction of rotation by applying voltage to pin 3 of arduino
  }
  deg = abs(deg);
}


float kp = .6 * 90 / deg;  //proportional gain of PI
float ki = .02;            //integral gain of PI






void loop() {
  // put your main code here, to run repeatedly: ********************
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
  currentVal = GenerateBits(5);
  Serial.println("Generated Bits: ");
  Serial.println(currentVal);

  if (setHome) {
    homeVal = currentVal;
  }

  // Calculate the delta value
  deltaVal = (int)currentVal - (int)homeVal;
  
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
  }
  

  // Convert the values to booleans
  LSB = HiOrLo(anVal0);
  bit1 = HiOrLo(anVal1);
  bit2 = HiOrLo(anVal2);
  bit3 = HiOrLo(anVal3);
  MSB = HiOrLo(anVal4);
  Serial.print(LSB);
  Serial.print(bit1);
  Serial.print(bit2);
  Serial.print(bit3);
  Serial.println(MSB);
  // ****************************************************************
  
  t = millis();                       //reading time
  t0 = t;                             //sving the current time in memory
  while (t < t0 + 4000 && rep <= 10)  //let the code to ran for 4 seconds each with repetitions of 10
  {

    if (t % 10 == 0)  //PI controller that runs every 10ms
    {
      if (s < deg * 114 * 2 / 360) {
        er = deg - s * 360 / 228;
        eri = eri + er;
        analogWrite(6, kp * er + ki * eri);
      }

      if (s >= deg * 228 / 360) {
        analogWrite(6, 0);
        eri = 0;
      }
      delay(1);
    }



    sm1 = digitalRead(7);  //reading chanel 1
    sm2 = digitalRead(8);  //reading chanel 2




    if (sm1 != sm2 && r == 0) {  //counting the number changes for both chanels
      s = s + 1;
      r = 1;  // this indicator wont let this condition, (sm1 != sm2), to be counted until the next condition, (sm1 == sm2), happens
    }
    if (sm1 == sm2 && r == 1) {
      s = s + 1;
      r = 0;  // this indicator wont let this condition, (sm1 == sm2), to be counted until the next condition, (sm1 != sm2), happens
    }




    t = millis();  //updating time
    finish = 1;    //cghanging finish indicator
  }

  if (finish == 1) {  //this part of the code is for displaying the result
    delay(500);       //half second delay
    rep = rep + 1;    // increasing the repetition indicator
    // ***************************************************************
    
    // Calculate the shaft displacement from the local home position
    if (movingClockwise) {
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
    }
    // ***************************************************************
    
    Serial.print("shaft possition from optical absolute sensor from home position: ");
    Serial.println(totalDeg);

    Serial.print("shaft displacement from optical absolute sensor: ");
    Serial.println(localDeg);

    Serial.print("Shaft displacement from motor's builtin encoder: ");
    Serial.println(s * 360 / 228);  //every full Revolution of the shaft is associated with 228 counts of builtin
                                    //encoder so to turn it to degre we can use this formula (s * 360 / 228), "s" is the number of  built-in encoder counts

    float Error = 0 - s * 360 / 228;
    Serial.print("Error :");
    Serial.println(Error);  //displaying error
    Serial.println();
    s = 0;
    finish = 0;
  }
  analogWrite(6, 0);  //turning off the motor
}

// Takes in the 10 bit integer value of an analogue read and returns the appropriate true of default false if over a threshold
// NOTE: The low range of 0 - 0.8V is includes the unsure range of 0.8 V - 1.8 V
bool HiOrLo(int val) {
  if (val > 368) {
    return true;
  } else {
    return false;
  }
}

// Function to generate a 5-bit number for the encoder light sensor readings
uint8_t GenerateBits(uint8_t n) {
  uint8_t finalReading = 0b00000;
  uint8_t analogInput;
  // For bits until n read analog readings and store them in an overarching total
  for (uint8_t ii = 0; ii < n; ii++) {
    analogInput = analogRead((n+14));
    finalReading |= ((analogInput > 368) * (2^n));
    Serial.print("Reading processing: ");
    Serial.println(finalReading);
  }
}

// Function to convert a number of segments moved into a degree estimate
float SegToDeg(int segments, bool isCW) {
  // 32 segments results in 11.25 degree steps
  return (isCW ? segments*11.25 : -segments*11.25);
}
