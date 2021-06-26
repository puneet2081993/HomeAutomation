#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 

BlynkTimer timer;

// Pins of Fan Regulator Knob
#define relay1 13 //d7
#define relay2 12 //d6
#define relay3 14 //d5
#define relay4 15 //d8


// By default the mode is with_internet
int MODE = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "GWGzxc5TLn1i20jmkAk85yg1eSPkuOj3"; //blynk auth key

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "FD-26"; //wifi username
char pass[] = "asdjkl@12345"; //wifi password


BLYNK_WRITE(V0)
{
  Serial.println("r1");
  digitalWrite(relay1, param.asInt());
}

BLYNK_WRITE(V1)
{
  Serial.println("r2");
  digitalWrite(relay2, param.asInt());
}

BLYNK_WRITE(V2)
{
  Serial.println("r3");
  digitalWrite(relay3, param.asInt());
}

BLYNK_WRITE(V3)
{
  Serial.println("r4");
  digitalWrite(relay4, param.asInst());
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds
  Blynk.config(auth);//, ssid, pass);
}

void loop()
{

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Not Connected");
  }
  else
  {
    Serial.println(" Connected");
    Blynk.run();
  }


  timer.run(); // Initiates SimpleTimer

//  if (MODE == 0)
//    with_internet();
//  else
//    without_internet();
   //put your main code here, to run repeatedly:
}
