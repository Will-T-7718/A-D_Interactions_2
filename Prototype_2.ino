#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];
const int R1 = 4;
const int R2 = 5;
const int R3 = 6;
const int R4 = 7;

void setup()
{  
 
  qtr.setTypeRC(); 
  qtr.setSensorPins((const uint8_t[]){4, 5, 6, 7}, SensorCount);

  Serial.begin(9600);
  Serial.println("go go ga ga");
}

void loop()
{
  uint16_t sensors[4];
  int16_t position = qtr.readLineBlack(sensors);

  qtr.read(sensorValues);

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);  
    Serial.print('\t');
    delay(100);
  }
  Serial.print("<Line Sensor Values");
  Serial.println();
}
