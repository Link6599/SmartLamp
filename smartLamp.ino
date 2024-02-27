/*************************************************************
  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL2pWSkrpCg"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "na7lkYqh19vGtjgJ11borcFpwtqbV3RW"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <CapacitiveSensor.h>
CapacitiveSensor sensor = CapacitiveSensor(4,6);
long val;
int pos;


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

BlynkTimer timer;

const int relayPin = D2;  // Cambiar al pin D2 para el relé

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Blynk.virtualWrite(V1, value);
}

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(relayPin, value ? HIGH : LOW);  // Controla el relé según el valor del botón en la aplicación Blynk
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V1, digitalRead(relayPin));  // Envía el estado actual del relé
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Asegura que el relé esté ENCENDIDO al iniciar
}

void loop()
{ 
  Blynk.run();
  timer.run();

  val = sensor.capacitiveSensor(30);
  Serial.println(val);

  if(val >=1000 && pos == 0){

    digitalWrite(relayPin,HIGH);
  }else{

  if(val >=1000 && pos == 1){

    digitalWrite(relayPin,LOW);
    
    
    }
  

  
}
}
