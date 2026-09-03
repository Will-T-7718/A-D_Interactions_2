
//ultrsonic Sensor Pins
const int trig = 3;
const int echo = 2;

//Colour sensor pins
#define S0 A0
#define S1 A1
#define S2 A3
#define S3 A2
#define sensorOut A4

int frequency = 0;

//Motor
int IN1 = 9;
int IN2 = 8;

long duration;
int distance;

int redMin = 25; // Red minimum value
int redMax = 197; // Red maximum value
int greenMin = 26; // Green minimum value
int greenMax = 205; // Green maximum value
int blueMin = 26; // Blue minimum value
int blueMax = 196; // Blue maximum value
 
// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
 
// Variables for final Color values
int redValue;
int greenValue;
int blueValue;

void setup() 
{
  //Colour sensor pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //motor pinmodes
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  ColourSensor();
  UltrasonicSensor();

  if (blueValue < 100 && distance < 30)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
}


void ColourSensor()
{
  // Read Red value
  redPW = getRedPW();
  // Map to value from 0-255
  redValue = map(redPW, redMin,redMax,255,0);
  // Delay to stabilize sensor
  delay(150);
  
  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  // Delay to stabilize sensor
  delay(150);
  
  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  // Delay to stabilize sensor
  delay(150);
  
  // Print output to Serial Monitor
  Serial.print("Red = ");
  Serial.print(redValue);
  Serial.print(" - Green = ");
  Serial.print(greenValue);
  Serial.print(" - Blue = ");
  Serial.println(blueValue);
}

int getRedPW() 
{
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
 
// Function to read Green Pulse Widths
int getGreenPW() 
{
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
 
// Function to read Blue Pulse Widths
int getBluePW() 
{
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
  
void UltrasonicSensor()
{
  // Clear trigger pin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  // Set trigger high for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  // Read echo time
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm
  
  /*if (distance < 20) {
    // Run motor if object is closer than 20cm
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    // Stop motor otherwise
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }*/
  delay(10);
}
