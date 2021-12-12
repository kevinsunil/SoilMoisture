#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
int sensorpin=A0;
int sensorvalue=0;
int outputvalue=0;
int count = 10;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a6Y3hXRPLF84mSJhFh8vy2pBnf2arXI9";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "varshini11";
char pass[] = "varshini11";

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  sensorvalue=analogRead(sensorpin);
  outputvalue=map(sensorvalue,0,1023,0,100); //100,0 pottupaaru

  if(outputvalue>74)
  {
       Serial.println("Soil moisture is low, Motor started!!!");
       Serial.print(outputvalue);
       
       digitalWrite(5, LOW);

if(count==0){
       Blynk.notify("Soil moisture is low, Motor started!!!");
       count = 10;
       }
       else{
        count--;
        }
  }
  else
  {
       Serial.println("Moisture content is stable, Motor Stopped");
       Serial.print(outputvalue);
              digitalWrite(5, HIGH);

       if(count==0){
       Blynk.notify("Moisture content is stable, Motor Stopped");
       count = 10;
       }
       else{
        count--;
        }
  }
  delay(2000);
  Blynk.virtualWrite(V1,outputvalue);
  Blynk.run();
}
