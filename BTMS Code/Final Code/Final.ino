// Code done by Charles Ford
// FSAE EV 2021
// 6/15/2021

#include <SPI.h>

float VoltageTable[] = {2.17, 2.14,	2.11,	2.08,	2.05,	2.02,	1.99,	1.955,	1.92,	1.89,	1.86,	1.83,	1.8,	1.77,	1.74,	1.71, 1.68,	1.655, 1.63, 1.61,1.59,	1.57,	1.55,	1.53,1.51,	1.495,	1.48,	1.465,	1.45,	1.44,	1.43};
int TempVRes[] = {158,140,127,110,100,91,83,72,67,60,55,49,45,40,37,33,31,28,26,23,22,19,18,17,16,15,13,12,11,10,9};

int len = 0;
bool TriggerLow = true;//Used to bias High or Low on the selection.

//These Coorespond to the output pins on the Schematic
const int SlaveS1 = 1;
const int SlaveS2 = 2;
const int SlaveS3 = 3;
const int SlaveS4 = 4;
const int SlaveS5 = 5;

 //You may need to change this depending on the voltage supplied by the internal batteries to the arduino. I used 3.3V since I think this is the right voltage.
float ReferenceVoltage = 3.3;
void setup() {
  analogReference(AR_EXTERNAL);
  Serial.begin(9600);
  pinMode(SlaveS1, OUTPUT);
  pinMode(SlaveS2, OUTPUT);
  pinMode(SlaveS3, OUTPUT);
  pinMode(SlaveS4, OUTPUT);
  pinMode(SlaveS5, OUTPUT);
  
  SPI.begin();
  len = sizeof(VoltageTable)/sizeof(VoltageTable[0]);
}

void digitalPotWrite(const int slaveSelectPin, int address, int value) {

  // take the SS pin low to select the chip:

  digitalWrite(slaveSelectPin, LOW);

  //delay(100);

  //  send in the address and value via SPI:

  SPI.transfer(address);

  SPI.transfer(value);

  //delay(100);

  // take the SS pin high to de-select the chip:

  digitalWrite(slaveSelectPin, HIGH);
}

void loop() {
  int test = 0;
  int sensorValue1 = analogRead(A1);
  float voltage1 = sensorValue1 * (ReferenceVoltage / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  for(int i = 0; i < len; i++)
  {
    if(i + 1 <= len && voltage1 < VoltageTable[i] && voltage1 > VoltageTable[i+1])
    {
      if(TriggerLow == 1)
      {
        test = TempVRes[i];
        digitalPotWrite(SlaveS1, 0, TempVRes[i]);
      }
      else
      {
        test = TempVRes[i+1];
        digitalPotWrite(SlaveS1, 0, TempVRes[i+1]);
      }
      
    }
  }
  
  int sensorValue2 = analogRead(A2);
  float voltage2 = sensorValue2 * (ReferenceVoltage / 1023.0);
  for(int i = 0; i < len; i++)
  {
    if(i + 1 <= len && voltage2 < VoltageTable[i] && voltage2 > VoltageTable[i+1])
    {
      if(TriggerLow == 1)
      {
        //test = TempVRes[i];
        digitalPotWrite(SlaveS2, 0, TempVRes[i]);
      }
      else
      {
        digitalPotWrite(SlaveS2, 0, TempVRes[i+1]);
      }
      
    }
  }

  int sensorValue3 = analogRead(A3);
  float voltage3 = sensorValue3 * (ReferenceVoltage / 1023.0);
  for(int i = 0; i < len; i++)
  {
    if(i + 1 <= len && voltage3 < VoltageTable[i] && voltage3 > VoltageTable[i+1])
    {
      if(TriggerLow == 1)
      {
        //test = TempVRes[i];
        digitalPotWrite(SlaveS3, 0, TempVRes[i]);
      }
      else
      {
        digitalPotWrite(SlaveS3, 0, TempVRes[i+1]);
      }
      
    }
  }

  int sensorValue4 = analogRead(A4);
  float voltage4 = sensorValue4 * (ReferenceVoltage / 1023.0);
  for(int i = 0; i < len; i++)
  {
    if(i + 1 <= len && voltage4 < VoltageTable[i] && voltage4 > VoltageTable[i+1])
    {
      if(TriggerLow == 1)
      {
        //test = TempVRes[i];
        digitalPotWrite(SlaveS4, 0, TempVRes[i]);
      }
      else
      {
        digitalPotWrite(SlaveS4, 0, TempVRes[i+1]);
      }
      
    }
  }


  int sensorValue5 = analogRead(A5);
  float voltage5 = sensorValue5 * (ReferenceVoltage / 1023.0);
  for(int i = 0; i < len; i++)
  {
    if(i + 1 <= len && voltage5 < VoltageTable[i] && voltage5 > VoltageTable[i+1])
    {
      if(TriggerLow == 1)
      {
        //test = TempVRes[i];
        digitalPotWrite(SlaveS5, 0, TempVRes[i]);
      }
      else
      {
        digitalPotWrite(SlaveS5, 0, TempVRes[i+1]);
      }
      
    }
  }


  //Uncomment this section and the different slave selects to debug any issues.
  Serial.print("Address: ");
  Serial.print(test);
  Serial.print("\t");
  Serial.print("Voltage: ");
  Serial.println(voltage1);
  delay(100);
}
