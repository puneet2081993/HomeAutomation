#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 

BlynkTimer timer;

// Pins of Fan Regulator Knob
#define s1 13 //d7
#define s2 12 //d6
#define s3 14 //d5
#define s4 15 //d8

// Pins of Relays
#define Speed1 16 //d0
#define Speed2 5 //d1
#define Speed4 4 //d2

// By default the mode is with_internet
int MODE = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "GWGzxc5TLn1i20jmkAk85yg1eSPkuOj3"; //blynk auth key

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "FD-26"; //wifi username
char pass[] = "asdjkl@12345"; //wifi password

bool speed1_flag = 1;
bool speed2_flag = 1;
bool speed3_flag = 1;
bool speed4_flag = 1;
bool speed0_flag = 1;


BLYNK_WRITE(V0)
{
  int fan_speed = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println(fan_speed);
  if (fan_speed == 0)
  {
    Serial.println("S0");
    speed0();
  }
  if (fan_speed == 1)
  {
    Serial.println("S1");
    speed1();
  }
  if (fan_speed == 2)
  {
    Serial.println("S2");
    speed2();
  }
  if (fan_speed == 3)
  {
    Serial.println("S3");
    speed3();
  }
  if (fan_speed == 4)
  {
    speed4();
  }
}


void setup()
{
  // put your setup code here, to run once:
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);

  pinMode(Speed1, OUTPUT);
  pinMode(Speed2, OUTPUT);
  pinMode(Speed4, OUTPUT);

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

  if (MODE == 0)
    with_internet();
  else
    without_internet();
   put your main code here, to run repeatedly:
}


void with_internet()
{
  if (digitalRead(s1) == LOW && speed1_flag == 1)
  {
    speed1();
    Blynk.virtualWrite(V0, 1);
    Serial.println("SPEED 1");
    speed1_flag = 0;
    speed2_flag = 1;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 1;


  }
  if (digitalRead(s2) == LOW && digitalRead(s3) == HIGH && speed2_flag == 1)
  {
    speed2();
    Blynk.virtualWrite(V0, 2);
    Serial.println("SPEED 2");
    speed1_flag = 1;
    speed2_flag = 0;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 1;

  }
  if (digitalRead(s2) == LOW && digitalRead(s3) == LOW && speed3_flag == 1)
  {
    speed3();
    Blynk.virtualWrite(V0, 3);
    Serial.println("SPEED 3");
    speed1_flag = 1;
    speed2_flag = 1;
    speed3_flag = 0;
    speed4_flag = 1;
    speed0_flag = 1;
  }
  if (digitalRead(s4) == LOW  && speed4_flag == 1)
  {
    speed4();
    Blynk.virtualWrite(V0, 4);
    Serial.println("SPEED 4");
    speed1_flag = 1;
    speed2_flag = 1;
    speed3_flag = 1;
    speed4_flag = 0;
    speed0_flag = 1;
  }
  if (digitalRead(s1) == HIGH && digitalRead(s2) == HIGH && digitalRead(s3) == HIGH && digitalRead(s4) == HIGH  && speed0_flag == 1)
  {
    speed0();
    Blynk.virtualWrite(V0, 0);
    Serial.println("SPEED 0");
    speed1_flag = 1;
    speed2_flag = 1;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 0;
  }
}


void without_internet()
{
  if (digitalRead(s1) == LOW && speed1_flag == 1)
  {
    speed1();

    Serial.println("SPEED 1");
    speed1_flag = 0;
    speed2_flag = 1;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 1;


  }
  if (digitalRead(s2) == LOW && digitalRead(s3) == HIGH && speed2_flag == 1)
  {
    speed2();

    Serial.println("SPEED 2");
    speed1_flag = 1;
    speed2_flag = 0;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 1;

  }
  if (digitalRead(s2) == LOW && digitalRead(s3) == LOW && speed3_flag == 1)
  {
    speed3();

    Serial.println("SPEED 3");
    speed1_flag = 1;
    speed2_flag = 1;
    speed3_flag = 0;
    speed4_flag = 1;
    speed0_flag = 1;
  }
  if (digitalRead(s4) == LOW  && speed4_flag == 1)
  {
    speed4();

    Serial.println("SPEED 4");
    speed1_flag = 1;
    speed2_flag = 1;
    speed3_flag = 1;
    speed4_flag = 0;
    speed0_flag = 1;
  }
  if (digitalRead(s1) == HIGH && digitalRead(s2) == HIGH && digitalRead(s3) == HIGH && digitalRead(s4) == HIGH  && speed0_flag == 1)
  {
    speed0();

    Serial.println("SPEED 0");
    speed1_flag = 1;
    speed2_flag = 1;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 0;
  }
}


void speed0()
{
  digitalWrite(Speed1, HIGH);
  digitalWrite(Speed2, HIGH);
  digitalWrite(Speed4, HIGH);
  Serial.println("SPEED 0");

}

void speed1()
{
  //Speed1 Relay On - Fan at speed 1
  digitalWrite(Speed2, HIGH);
  digitalWrite(Speed4, HIGH);
  delay(500);
  digitalWrite(Speed1, LOW);
  Serial.println("SPEED 1");
}

void speed2()
{
  //Speed2 Relay On - Fan at speed 2

  digitalWrite(Speed1, HIGH);
  digitalWrite(Speed4, HIGH);
  delay(500);
  digitalWrite(Speed2, LOW);
  Serial.println("SPEED 2");
}

void speed3()
{
  //Speed1 & Speed2 Relays On - Fan at speed 3
  digitalWrite(Speed4, HIGH);
  delay(500);
  digitalWrite(Speed1, LOW);
  digitalWrite(Speed2, LOW);
  Serial.println("SPEED 3");

}

void speed4()
{
  //Speed4 Relay On - Fan at speed 4

  digitalWrite(Speed1, HIGH);
  digitalWrite(Speed2, HIGH);
  delay(500);
  digitalWrite(Speed4, LOW);
  Serial.println("SPEED 4");
}

void checkBlynk()
{
  bool isconnected = Blynk.connected();
  if (isconnected == false)
  {
    MODE = 1;
  }
  if (isconnected == true)
  {
    MODE = 0;
  }
}
