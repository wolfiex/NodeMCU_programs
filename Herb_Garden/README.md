# A simple automated plant watering system using the node_MCU arduino board. 

#### Requirements
1. waterproof water pump capable of running from 3/5v (£5)
2. NodeMCU (£4)
3. A watering container (I used a 5L pvc container)
4. Some plants to water
5. Some plastic tubing for the pump
6. Soil humidity Sensors ($1 each)

and finally a WiFi connection (optional but useful)

#### Methodology
Provided we already know how to flash and run the NodeMCU controller (find the blink example online if you dont), we wish to test the range of our humidity sensors. 
We can do this by connecting the nodeMCU to a computer and viewing the results in our serial window. 


Run this with the sensor tips in water, and out on a completely dry surface. 

```arduino
void setup()
{  
  Serial.begin(9600);
}
void loop()
{
  Serial.print(analogRead(A0));
  delay(10000);
}

```
