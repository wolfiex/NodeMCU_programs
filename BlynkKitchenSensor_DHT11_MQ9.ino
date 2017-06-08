
//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
char auth[] = "";
char ssid[] = "";
char pass[] = "";
WidgetLED led1(V15);



#include "DHT.h"
#define DHTPIN D4     // what digital pin the DHT11 is conected to
#define DHTTYPE DHT11   // there are multiple kinds of DHT sensors
DHT dht(DHTPIN, DHTTYPE);


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

// initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); //led off
    led1.off();
}

void loop()
{
  Blynk.run();

    float sensorValue = analogRead(A0);
    float sensor_volt = sensorValue / 1024 * 5.0;

    float R0 = 0.46;
    float RS_gas = (5.0 - sensor_volt) / sensor_volt;
    Blynk.virtualWrite(1, RS_gas / 9.9);//ROair
float ratio = RS_gas / R0; // ratio = RS/R0;

    if (ratio < 5) { // we have a breach?
      Serial.print("SS");
        digitalWrite(LED_BUILTIN, LOW);
        led1.on();
    };

    float limit=5.;
    
    Blynk.virtualWrite(5, limit);
    Serial.println(ratio);
    Blynk.virtualWrite(0, ratio);
    Blynk.virtualWrite(10, ratio);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Blynk.virtualWrite(6, t);
  Blynk.virtualWrite(7, h);
  Blynk.virtualWrite(8, hic);
  
    delay(1000);
}
