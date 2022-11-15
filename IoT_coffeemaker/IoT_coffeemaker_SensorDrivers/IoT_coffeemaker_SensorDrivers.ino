#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "HX711.h"

Adafruit_MLX90614 mlx = Adafruit_MLX90614();                //Infrared Sensor

#define Clock 2
#define Data 3

HX711 scale;                              //Making an obbject of HX711 (Load cell)

float calibration_factor = -973000;
float weight;

const char* ssid = "SOURCE";
const char* password = "Pelle!23";

int temperature;

void setup()
{
                                                                  
  Serial.begin(9600);
  Wire.setClock(100000);
  
  scale.begin(Data, Clock);
  scale.set_scale();
  scale.tare();

  long zero_factor = scale.read_average();
  
  Serial.print("Current Zero factor value: ");
  Serial.println(zero_factor);

  
  pinMode(A5, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);

  mlx.begin();  //Starting the infrared sensor
                                                                                 
  scale.set_scale(calibration_factor);        // Calibration factor for load cell
}                                                                                 //  END OF setup


                                                                                 
void read_values()
{  
 temperature = mlx.readObjectTempC() + 7; //Declaring heatsensor to temperature variable
 weight = scale.get_units();          //Getting load cell data
 if (weight <= 0.05) {                   // Frontend won't read negative numbers
  weight = 0;
  temperature = 0;
  }
 scale.set_scale(calibration_factor); // Adding the calibration factor to scale
  char kg[5];
 dtostrf(weight, 4, 3, kg);   //Formatting load cell output to 3 decimal weight in kg
  char resp[80];
    int n = sprintf(resp, "[{\"temperature\":\"%d\", \"weight\":\"%s\"}]", temperature, kg);
    Serial.println(resp);
   
}


 
void loop()
{

  // Enter 't' in serial monitor to tare
char temp = Serial.read();
  if(temp == 't')
    scale.tare();

      
  read_values(); //To call void read_values()
  delay(500);
}
