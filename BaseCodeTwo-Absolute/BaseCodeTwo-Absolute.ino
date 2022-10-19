float deg = 45;  // Rotation degree
float s = 0;     //Encoder counts
int sm1 = 0;     //Built-in chanel 1
int sm2 = 0;     //Built-in chanel 2
int r = 0;       //indicator for reading builtin encoder to avoid the reading redundancy
float er;        //Proportional error for PI controller
float eri;       //Integral error for PI controller

// ***********************Task Variables************************* 
bool setHome = true;

uint8_t homeVal;
uint8_t currentVal;

int anVal4; // centre
int anVal3;
int anVal2;
int anVal1;
int anVal0;


bool isCW;

float localDeg;
// **************************************************************

int t = 0;   //time in ms
int t0 = 0;  //memory for time in ms

int finish = 0;  //finish indicator
int rep = 1;     //Repetition indicator

void setup() { 

  Serial.begin(250000);  //Baud rate of communication
  //SensorTest();
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

  // Set up anaolog pins as inputs
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);

  //PhotoTest(false, 8);
  Serial.println("*******************************");
  //float ass = Serial.readString().toFloat();
  //PhotoTest(false, 60);
}


float kp = .6 * 90 / deg;  //proportional gain of PI
float ki = .02;            //integral gain of PI

void loop() {
  // put your main code here, to run repeatedly: ********************
  
  // Read the starting value for any loop and setHome goes to false
  if (setHome) {
    currentVal = GenerateBits(5);
    homeVal = GrayToBin(currentVal);
    setHome = false;
    //Serial.print("Initial Segment: ");
    //Serial.println(currentVal);
  }
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
    // Read the current position
    currentVal = GenerateBits(5);
    currentVal = GrayToBin(currentVal);
    //Serial.print("Final Segment: ");
   // Serial.println(currentVal);
    setHome = true;
    
    SensorTest();
    delay(500);       //half second delay
    rep = rep + 1;    // increasing the repetition indicator
    // ***************************************************************
    localDeg = moveToDeg(currentVal, homeVal);
    // ***************************************************************
    
    Serial.print("shaft possition from optical absolute sensor from home position: ");
    float absoluteDeg = 11.25 * currentVal;
    Serial.println(abs(absoluteDeg));

    Serial.print("magnitude of shaft displacement from optical absolute sensor: ");
    Serial.println(abs(localDeg));

    Serial.print("Shaft displacement from motor's builtin encoder: ");
    Serial.println(s * 360 / 228);  //every full Revolution of the shaft is associated with 228 counts of builtin
                                    //encoder so to turn it to degre we can use this formula (s * 360 / 228), "s" is the number of  built-in encoder counts

    float Error = abs(localDeg) - s * 360 / 228;
    Serial.print("Error :");
    Serial.println(Error);  //displaying error
    Serial.print("Shaft displacement direction from optical absolute encoder: ");
    if (localDeg < 0) {
      Serial.println("CCW");
    } else {
      Serial.println("CW");
    }
    Serial.println();
    s = 0;
    finish = 0;
  }
  analogWrite(6, 0);  //turning off the motor
}

// Takes in the 10 bit integer value of an analogue read and returns the appropriate true of default false if over a threshold
// NOTE: The low range of 0 - 0.8V is includes the unsure range of 0.8 V - 1.8 V
bool HiOrLo(int val, int threshold) {
  if (val > threshold) {
    return true;
  } else {
    return false;
  }
}

// Function to use the current and home positions to a degrees moved float
float moveToDeg(uint8_t currentVal, uint8_t homeVal) {
  float delta = (float)(currentVal - homeVal)*11.25;

  if (delta > 90) {
    delta -= 360;
  } else if (delta < -90) {
    delta += 360;
  }
  return delta;
}

// Function to convert a number of segments moved into a degree estimate
float SegToDeg(int segments, bool isCW) {
  // 32 segments results in 11.25 degree steps
  return (isCW ? segments*11.25 : -segments*11.25);
}
