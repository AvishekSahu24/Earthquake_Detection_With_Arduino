#include <SoftwareSerial.h>

#include <Printers.h>
#include <XBee.h>

#include <math.h>

// soil sensor
const int AirValue = 674;   // need to replace this value with Value_1
const int WaterValue = 374;  // need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3; 
int soilMoistureValue;

// flex sensor

const int FLEX_PIN = A0; // Pin connected to voltage divider output
int Flexvalue; //save analog value




//adxl sensor
const int x_out = A2; /* connect x_out of module to A2 of Atmega board */
const int y_out = A3; /* connect y_out of module to A3 of Atmega board */
const int z_out = A4; /* connect z_out of module to A4 of Atmega board */

//Buzzer as alarm
//const int buzzerPin = 7; //Define buzzer pin




void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  pinMode(FLEX_PIN, INPUT);
}

void loop() {
 

  //soil sensor
  
soilMoistureValue = analogRead(A1);  //put Sensor insert into soil
Serial.print("Soil Moisture Sensor 1 Reading:");
Serial.println(soilMoistureValue);
if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))

{
 
  Serial.println("Soil Moisture1: Very Wet");
}
else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
{
  Serial.println("Soil Moisture1: Wet");
}
else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
{
  Serial.println("Soil Moisture1: Dry");
  
    
}
//delay(5000);

// flex sensor
   Flexvalue = analogRead(FLEX_PIN);         //Read and save analog value from potentiometer
   Serial.print("Flex Sensor 1 Value:");
   Serial.println(Flexvalue);               //Print value
   Flexvalue = map(Flexvalue, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
   //delay(5000); 




  //adxl sensor

 int x_adc_value, y_adc_value, z_adc_value; 
  double x_g_value, y_g_value, z_g_value;
  double roll, pitch, yaw;
  x_adc_value = analogRead(x_out); /* Digital value of voltage on x_out pin */ 
  y_adc_value = analogRead(y_out); /* Digital value of voltage on y_out pin */ 
  z_adc_value = analogRead(z_out); /* Digital value of voltage on z_out pin */ 
  Serial.println("Accelerometer1:");
  Serial.print("x = ");
  Serial.print(x_adc_value);
  Serial.print("\t\t");
  Serial.print("y = ");
  Serial.print(y_adc_value);
  Serial.print("\t\t");
  Serial.print("z = ");
  Serial.print(z_adc_value);
  Serial.print("\t\t");
  //delay(700);
  
  x_g_value = ( ( ( (double)(x_adc_value * 5)/1024) - 1.65 ) / 0.330 ); /* Acceleration in x-direction in g units */ 
  y_g_value = ( ( ( (double)(y_adc_value * 5)/1024) - 1.65 ) / 0.330 ); /* Acceleration in y-direction in g units */ 
  z_g_value = ( ( ( (double)(z_adc_value * 5)/1024) - 1.80 ) / 0.330 ); /* Acceleration in z-direction in g units */ 

  roll = ( ( (atan2(y_g_value,z_g_value) * 180) / 3.14 ) + 180 ); /* Formula for roll */
  pitch = ( ( (atan2(z_g_value,x_g_value) * 180) / 3.14 ) + 180 ); /* Formula for pitch */
  
  Serial.print("Roll = ");
  Serial.print(roll);
  Serial.print("\t");
  Serial.print("Pitch = ");
  Serial.print(pitch);
  Serial.print("\n\n");


  
  

delay(30000);
}
