//https://github.com/esp8266/Arduino/blob/master/doc/reference.md
int blue = D2;
int green = D3;// the pin that the LED is attached to
int red = D1;
//d0 = onboard red
//d4= onboard blue

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  analogWriteRange(255);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
}
 
// the loop routine runs over and over again forever:
void loop() {
// 0 = bright, 255 = none
  analogWrite(blue, 50);
  analogWrite(green, 255);
  analogWrite(red, 20);

}
