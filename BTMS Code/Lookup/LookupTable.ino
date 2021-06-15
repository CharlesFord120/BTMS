float VoltageTable[] = {2.17, 2.14,	2.11,	2.08,	2.05,	2.02,	1.99,	1.955,	1.92,	1.89,	1.86,	1.83,	1.8,	1.77,	1.74,	1.71, 1.68,	1.655, 1.63,
	1.61,1.59,	1.57,	1.55,	1.53,1.51,	1.495,	1.48,	1.465,	1.45,	1.44,	1.43,	1.415,	1.4,	1.39,	1.38,	1.375,	1.37,	1.36,	1.35,	1.345,	1.34};
float TemperatureTable[] = {31770,	28355,	24940,	22310,	19680,	17650,	15620,	14045,	12470,	11235,	10000,	9032,	8064,	7301,	6538,	5932.5,	5327,	4845,	4363,	3977.5,	3592,	3282,
	2972,	2722,	2472,	2269,	2066,	1900.5,	1735,	1600,	1465,	1354,	1243,	1151,	1059,	983.65,	908.3,	844.95,	781.6,	728,	674.4};
int len = 0;

void setup() {
  Serial.begin(9600);
  len = sizeof(VoltageTable)/sizeof(VoltageTable[0]);
}

void loop() {
  float resistance = 0;
  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (3.3 / 1023.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  for(int i = 0; i < len; i++)
  {
    if(i + 1 <= len && voltage < VoltageTable[i] && voltage > VoltageTable[i+1])
    {
      float r1 = TemperatureTable[i];
      float r2 = TemperatureTable[i+1];
      float resAdd = r1 + r2;
      float resAvg = resAdd/2;
      resistance = resAvg;
    }
    if(voltage < VoltageTable[len-1])
    {
      resistance = TemperatureTable[len-1];
    }
    if(voltage > VoltageTable[0])
    {
      resistance = TemperatureTable[0];
    }
  }
  Serial.print("Resistance: ");
  Serial.print(resistance);
  Serial.print("\t");
  Serial.print("Voltage: ");
  Serial.println(voltage);
  delay(10);
}
