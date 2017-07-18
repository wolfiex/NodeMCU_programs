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

If like me you have opted for the rather inexpensive T-28 unit, this has 4 available pins: A power, a ground , a digital and an analog. As I am interested in plotting the difference of soil humidity over time, I shall opt to connect the analog connector to the a0 pin on the nodemcu, the vcc pin to a 3v pin, and the ground to the corresponding ground. 

<img src="615DPhAC0wL._SL1100_.jpg" alt="Drawing" style="width: 200px;"/>

To test the ranges of our sensor we can run the following code and have the pins situated in and out of a glass of water. Since these units have a finite lifetime, and work by measuring the resistance of the soil, it is not in our interest to have them permanently on. It is for this reason we shall

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

Since these units have a finite lifetime, and work by measuring the resistance of the soil, it is not in our interest to have them permanently on. It is for this reason we shall add an on-off timer as well as the measurement delay above. 


