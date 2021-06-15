#include <SPI.h>

float VoltageTable[] = {2.17, 2.14,	2.11,	2.08,	2.05,	2.02,	1.99,	1.955,	1.92,	1.89,	1.86,	1.83,	1.8,	1.77,	1.74,	1.71, 1.68,	1.655, 1.63, 1.61,1.59,	1.57,	1.55,	1.53,1.51,	1.495,	1.48,	1.465,	1.45,	1.44,	1.43};
int TempVRes[] = {158,140,127,110,100,91,83,72,67,60,55,49,45,40,37,33,31,28,26,23,22,19,18,17,16,15,13,12,11,10,9};

int len = 0;
bool TriggerLow = true;
int slaveSelectPin;

void setup() {
  Serial.begin(9600);
  pinMode(slaveSelectPin, OUTPUT);
  SPI.begin();
  len = sizeof(VoltageTable)/sizeof(VoltageTable[0]);
}

void loop() {
  int sensorValue1 = analogRead(A1);
  float voltage = sensorValue1 * (3.3 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  slaveSelectPin = 1;
  for(int i = 0; i < len; i++)
  {
    if(i + 1 <= len && voltage < VoltageTable[i] && voltage > VoltageTable[i+1])
    {
      if(TriggerLow == 1)
      {
        digitalPotWrite(0,TempVRes[i]);
      }
      else
      {
        digitalPotWrite(0,TempVRes[i+1]);
      }
      
    }
    /*if(voltage < VoltageTable[len-1])
    {
      Addr1 = TempVRes[len-1];
    }
    if(voltage > VoltageTable[0])
    {
      Addr1 = TempVRes[0];
    }*/
  }
  int sensorValue2 = analogRead(A1);
  slaveSelectPin = 2;
  for(int i = 0; i < len; i++)
  {
    if(i + 1 <= len && voltage < VoltageTable[i] && voltage > VoltageTable[i+1])
    {
      if(TriggerLow == 1)
      {
        digitalPotWrite(0,TempVRes[i]);
      }
      else
      {
        digitalPotWrite(0,TempVRes[i+1]);
      }
      
    }
    /*if(voltage < VoltageTable[len-1])
    {
      Addr1 = TempVRes[len-1];
    }
    if(voltage > VoltageTable[0])
    {
      Addr1 = TempVRes[0];
    }*/
  
  Serial.print("Voltage: ");
  Serial.println(voltage);
  }
}
void digitalPotWrite(int address, int value) {

  // take the SS pin low to select the chip:

  digitalWrite(slaveSelectPin, LOW);

  delay(100);

  //  send in the address and value via SPI:

  SPI.transfer(address);

  SPI.transfer(value);

  delay(100);

  // take the SS pin high to de-select the chip:

  digitalWrite(slaveSelectPin, HIGH);
}