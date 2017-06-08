#include <ESP8266WiFi.h>

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "thereisnospoon";


String getValue(String data, char separator, int index)
{
 int found = 0;
  int strIndex[] = {
0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

WiFiServer server(80);

int blue = D2;
int green = D3;// the pin that the LED is attached to
int red = D1;
//d0 = onboard red
//d4= onboard blue

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  setupWiFi();
  server.begin();

  analogWriteRange(255);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
}


void loop() 
{

  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val = -1; // We'll use 'val' to keep track of both the
                // request type (read/set) and value if set.
  if (req.indexOf("/led/0") != -1)
    val = 0; // Will write LED low
  else if (req.indexOf("/led/1") != -1)
    val = 1; // Will write LED high
  else if (req.indexOf("/read") != -1)
    val = -2; // Will print pin reads


  client.flush();

  if (req.indexOf("/rgb/") != -1){
    String changes = getValue(req, '/', 2);
    Serial.println(getValue(changes,',',0));
   Serial.println(getValue(changes,',',1));
   Serial.println(getValue(changes,',',2));
   int   f = atoi(getValue(changes,',',0).c_str());
   analogWrite(red,255-f);   
   f = atoi(getValue(changes,',',1).c_str());
   analogWrite(green,255-f);
   f = atoi(getValue(changes,',',2).c_str());
   analogWrite(blue,255-f);
   
   ///analogWrite(green,255-toInt(getValue(changes,',',1))));
   //analogWrite(blue,255-toInt(getValue(changes,',',2)))); 
    //analogWrite(blue,changes.getValue(changes,',',2)));
    
  }

  

  client.flush();

  

  // Prepare the response. Start with the common header:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  // If we're setting the LED, print out a message saying we did
  if (val <= 0)
  {
    s += "Invalid Request.<br> Try /rgb/r,g,b where r,g,b are 0-255.";
  }
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "LED_Strip [NodeMCU] " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar);// passwordless, WiFiAPPSK);
}

