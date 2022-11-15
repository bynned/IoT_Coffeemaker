#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>

            //            network credentials


const char* ssid = "WIFI";
const char* password = "PASSWORD";



                                                                        // Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String from_mega="";                                                    // lidar distance value in String format
int is;
char buf[40];                                                           //  Serial bus buffer   

int temperature;
int weight;

void setup()
{
                                                                          // Serial port for transfer data with Mega
  Serial.begin(9600);
  Wire.setClock(100000);
  Serial.println("");

  Serial.println("----------------");

  Serial.println("----------------");



  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

                                                                          // Start file subsystem


                                                                            // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

                                                                            // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  

                                                                            // Route for root / web page


                                                                                //  Method GET - query from MEGA to to web page tag is / from_MEGA
  server.on("/from_mega", HTTP_GET, [](AsyncWebServerRequest *request)
    {
      request->send_P(200, "text/plain", string_to_JS().c_str());               // return value to web page JS
      Serial.println("HTTP GET /from_mega");
    }); 


                                                                                  // Start server
  server.begin();


}                                                                                 //  END OF setup


                                                                                  // reservation 




String string_to_JS()                                                             // funtion to be called with GET from_MEGA tag
  {
    return from_mega;
  }


 
void loop()
{
  if (Serial.available() > 0) 
    {
      serial_read();                                            // read string from Mega
      from_mega=buf;
    }
}

void serial_read()                                    // read serial in string, save received characters to buff[]
{
  boolean done=0; 

  while (done==0)                                     // wait end of message LF
    {
        while(Serial.available() > 0)
        {
          char char_in = Serial.read();
        
          if(char_in>13)                              // is input char above CR
                {   
                 buf[is]=char_in;
                 is++;
                }
  
          if(char_in==10){                            // check if end of message  LF   
                    buf[is]=0;                        // end of string
                    is=0;
                    done=1;
                  }
    
        }                                            // end of while serial available  

        if(done==1) { done=0; break; }

    }                                                 // while END , End of message  LF
   
}
