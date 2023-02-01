#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
#define RelayPin1 5 //D1
#define RelayPin2 4 //D2
#define RelayPin3 14 //D5
#define RelayPin4 12 //D6
#define SwitchPin1 10 //SD3
#define SwitchPin2 0 //D3
#define SwitchPin3 13 //D7
#define SwitchPin4 3 //RX
#define wifiLed 16 //D0
char auth[] = "t59NF2-956IxglFTa4GqsRIYLeiBk9Zw";
int toggleState_1 = 0;
int toggleState_2 = 0;
int toggleState_3 = 0;
int toggleState_4 = 0;
boolean connectWifi();
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);
// WiFi Credentials
const char* ssid = "ssid";
const char* password = "pass";
// device names
String Device_1_Name = "Study Lamp";
String Device_2_Name = "CFL";
String Device_3_Name = "Yellow light";
String Device_4_Name = "Red light";
17 | P a g e
boolean wifiConnected = false;
Espalexa espalexa;
//our callback functions
void firstLightChanged(uint8_t brightness)
{
//Control the device
if (brightness == 255)
{
digitalWrite(RelayPin1, LOW);
Serial.println("Device1 ON");
toggleState_1 = 1;
}
else
{
digitalWrite(RelayPin1, HIGH);
Serial.println("Device1 OFF");
toggleState_1 = 0;
}
}
void secondLightChanged(uint8_t brightness)
{
//Control the device
if (brightness == 255)
{
digitalWrite(RelayPin2, LOW);
Serial.println("Device2 ON");
toggleState_2 = 1;
}
else
{
digitalWrite(RelayPin2, HIGH);
Serial.println("Device2 OFF");
toggleState_2 = 0;
}
}
void thirdLightChanged(uint8_t brightness)
{
//Control the device
if (brightness == 255)
{
digitalWrite(RelayPin3, LOW);
Serial.println("Device3 ON");
18 | P a g e
toggleState_3 = 1;
}
else
{
digitalWrite(RelayPin3, HIGH);
Serial.println("Device3 OFF");
toggleState_3 = 0;
}
}
void fourthLightChanged(uint8_t brightness)
{
//Control the device
if (brightness == 255)
{
digitalWrite(RelayPin4, LOW);
Serial.println("Device4 ON");
toggleState_4 = 1;
}
else
{
digitalWrite(RelayPin4, HIGH);
Serial.println("Device4 OFF");
toggleState_4 = 0;
}
}
void relayOnOff(int relay){
switch(relay){
case 1:
if(toggleState_1 == 0){
digitalWrite(RelayPin1, LOW); // turn on relay 1
toggleState_1 = 1;
Serial.println("Device1 ON");
}
else{
digitalWrite(RelayPin1, HIGH); // turn off relay 1
toggleState_1 = 0;
Serial.println("Device1 OFF");
}
delay(100);
break;
case 2:
if(toggleState_2 == 0){
digitalWrite(RelayPin2, LOW); // turn on relay 2
toggleState_2 = 1;
19 | P a g e
Serial.println("Device2 ON");
}
else{
digitalWrite(RelayPin2, HIGH); // turn off relay 2
toggleState_2 = 0;
Serial.println("Device2 OFF");
}
delay(100);
break;
case 3:
if(toggleState_3 == 0){
digitalWrite(RelayPin3, LOW); // turn on relay 3
toggleState_3 = 1;
Serial.println("Device3 ON");
}else{
digitalWrite(RelayPin3, HIGH); // turn off relay 3
toggleState_3 = 0;
Serial.println("Device3 OFF");
}
delay(100);
break;
case 4:
if(toggleState_4 == 0){
digitalWrite(RelayPin4, LOW); // turn on relay 4
toggleState_4 = 1;
Serial.println("Device4 ON");
}
else{
digitalWrite(RelayPin4, HIGH); // turn off relay 4
toggleState_4 = 0;
Serial.println("Device4 OFF");
}
delay(100);
break;
default : break;
}
}
// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
boolean state = true;
int i = 0;
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);
Serial.println("");
Serial.println("Connecting to WiFi");
20 | P a g e
// Wait for connection
Serial.print("Connecting...");
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
if (i > 20) {
state = false; break;
}
i++;
}
Serial.println("");
if (state) {
Serial.print("Connected to ");
Serial.println(ssid);
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
}
else {
Serial.println("Connection failed.");
}
return state;
}
void addDevices(){
espalexa.addDevice(Device_1_Name, firstLightChanged);
espalexa.addDevice(Device_2_Name, secondLightChanged);
espalexa.addDevice(Device_3_Name, thirdLightChanged);
espalexa.addDevice(Device_4_Name, fourthLightChanged);
espalexa.begin();
}
void setup()
{
Serial.begin(115200);
Blynk.begin(auth, ssid, password);
pinMode(RelayPin1, OUTPUT);
pinMode(RelayPin2, OUTPUT);
pinMode(RelayPin3, OUTPUT);
pinMode(RelayPin4, OUTPUT);
pinMode(wifiLed, OUTPUT);
pinMode(SwitchPin1, INPUT_PULLUP);
pinMode(SwitchPin2, INPUT_PULLUP);
pinMode(SwitchPin3, INPUT_PULLUP);
pinMode(SwitchPin4, INPUT_PULLUP);
21 | P a g e
//During Starting all Relays should TURN OFF
digitalWrite(RelayPin1, HIGH);
digitalWrite(RelayPin2, HIGH);
digitalWrite(RelayPin3, HIGH);
digitalWrite(RelayPin4, HIGH);
// Initialise wifi connection
wifiConnected = connectWifi();
if (wifiConnected)
{
addDevices();
}
else
{
Serial.println("Cannot connect to WiFi. So in Manual Mode");
delay(1000);
}
}
void loop()
{
Blynk.run();
if (WiFi.status() != WL_CONNECTED)
{
//Serial.print("WiFi Not Connected ");
//Serial.println(wifiConnected);
digitalWrite(wifiLed, HIGH); //Turn off WiFi LED
//Manual Switch Control
if (digitalRead(SwitchPin1) == LOW){
delay(200);
relayOnOff(1);
}
else if (digitalRead(SwitchPin2) == LOW){
delay(200);
relayOnOff(2);
}
else if (digitalRead(SwitchPin3) == LOW){
delay(200);
relayOnOff(3);
}
else if (digitalRead(SwitchPin4) == LOW){
delay(200);
relayOnOff(4);
}
}
22 | P a g e
else
{
//Serial.print("WiFi Connected ");
//Serial.println(wifiConnected);
digitalWrite(wifiLed, LOW);
//Manual Switch Control
if (digitalRead(SwitchPin1) == LOW){
delay(200);
relayOnOff(1);
}
else if (digitalRead(SwitchPin2) == LOW){
delay(200);
relayOnOff(2);
}
else if (digitalRead(SwitchPin3) == LOW){
delay(200);
relayOnOff(3);
}
else if (digitalRead(SwitchPin4) == LOW){
delay(200);
relayOnOff(4);
}
//WiFi Control
if (wifiConnected){
espalexa.loop();
delay(1);
}
else {
wifiConnected = connectWifi(); // Initialise wifi connection
if(wifiConnected){
addDevices();
}
}
}
}