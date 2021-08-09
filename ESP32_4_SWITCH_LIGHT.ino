//#define BLYNK_PRINT Serial            
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>
//#include <BluetoothSerial.h>
//BluetoothSerial SerialBT;


// define the Light GPIO connected with Relays and switches
#define RelayPin1 22
#define RelayPin2 19
#define RelayPin3 18
#define RelayPin4 17 

//light switches
#define SwitchPin1 25 //SD2
#define SwitchPin2 26 //SD3
#define SwitchPin3 27 //SD1
#define SwitchPin4 13 //SD0


//Virtual Pins
#define VPIN_BUTTON_1 V1 //v1
#define VPIN_BUTTON_2 V2 //v2
#define VPIN_BUTTON_3 V3 //v3
#define VPIN_BUTTON_4 V4 //v4

int toggleState_1 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_3 = 1; //Define integer to remember the toggle state for relay 1
int toggleState_4 = 1; //Define integer to remember the toggle state for relay 1

int wifiFlag = 0;
int incoming;

char auth[] = "k1dYKP7xwopF1YhyGgtY4LbRfH8mXd3M";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jio Fiber";
char pass[] = "nakoda123";

BlynkTimer timer;

void relayOnOff(int relay) {
  switch (relay) {
    case 1:
      if (digitalRead(SwitchPin1) == LOW && toggleState_1 == 1) {
        digitalWrite(RelayPin1, LOW); // turn on relay 1
        toggleState_1 = 0;
        Serial.println("Device1 ON");
        Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); // Update Button Widget  
      } else if (digitalRead(SwitchPin1) == HIGH && toggleState_1 == 0) {
        digitalWrite(RelayPin1, HIGH); // turn off relay 1
        toggleState_1 = 1;
        Serial.println("Device1 OFF");
        Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); // Update Button Widget  
      }
      delay(100);
      break;
    case 2:
      if (digitalRead(SwitchPin2) == LOW && toggleState_2 == 1) {
        digitalWrite(RelayPin2, LOW); // turn on relay 2
        toggleState_2 = 0;
        Serial.println("Device2 ON");
        Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); // Update Button Widget  
      } else if (digitalRead(SwitchPin2) == HIGH && toggleState_2 == 0) {
        digitalWrite(RelayPin2, HIGH); // turn off relay 1
        toggleState_2 = 1;
        Serial.println("Device2 OFF");
        Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); // Update Button Widget  
      }
      delay(100);
      break;
    case 3:
      Serial.println("here");
      Serial.println(toggleState_3);
      if (digitalRead(SwitchPin3) == LOW && toggleState_3 == 1) {
        digitalWrite(RelayPin3, LOW); // turn on relay 1
        toggleState_3 = 0;
        Serial.println("Device3 ON");
        Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); // Update Button Widget  
      } else if (digitalRead(SwitchPin3) == HIGH && toggleState_3 == 0) {
        digitalWrite(RelayPin3, HIGH); // turn off relay 1
        toggleState_3 = 1;
        Serial.println("Device3 OFF");
        Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); // Update Button Widget  
      }
      delay(100);
      break;
    case 4:
      if (digitalRead(SwitchPin4) == LOW && toggleState_4 == 1) {
        digitalWrite(RelayPin4, LOW); // turn on relay 1
        toggleState_4 = 0;
        Serial.println("Device4 ON");
        Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); // Update Button Widget  
      } else if (digitalRead(SwitchPin4) == HIGH && toggleState_4 == 0) {
        digitalWrite(RelayPin4, HIGH); // turn off relay 1
        toggleState_4 = 1;
        Serial.println("Device4 OFF");
        Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); // Update Button Widget  
      }
      delay(100);
      break;
  
    default:
      break;
  }
}

void switch_button() {
  //Manual Switch Control
  delay(200);
  relayOnOff(1);
  delay(200);
  relayOnOff(2);
  delay(200);
  relayOnOff(3);
  delay(200);
  relayOnOff(4);
}

//BLYNK_CONNECTED() {
//  // Request the latest state from the server
//  Blynk.syncVirtual(VPIN_BUTTON_1);
//  Blynk.syncVirtual(VPIN_BUTTON_2);
//  Blynk.syncVirtual(VPIN_BUTTON_3);
//  Blynk.syncVirtual(VPIN_BUTTON_4);
//}

// When App button is pushed - switch the state

BLYNK_WRITE(VPIN_BUTTON_1) {
  Serial.println("VPIN_BUTTON_1");
  digitalWrite(RelayPin1, param.asInt());
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  Serial.println("VPIN_BUTTON_2");
  digitalWrite(RelayPin2, param.asInt());
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  Serial.println("VPIN_BUTTON_3");
  digitalWrite(RelayPin3, param.asInt());
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  Serial.println("VPIN_BUTTON_4");
  digitalWrite(RelayPin4, param.asInt());
}

void checkBlynkStatus() { // called every 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    wifiFlag = 1;
    //  digitalWrite(wifiLed, HIGH); //Turn off WiFi LED
  }
   if (isconnected == true) {
    wifiFlag = 0;
    //  digitalWrite(wifiLed, LOW); //Turn on WiFi LED
  }
}
void setup() {
  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  // pinMode(wifiLed, OUTPUT);

  Serial.begin(9600);

  digitalWrite(RelayPin1, toggleState_1);
  digitalWrite(RelayPin2, toggleState_2);
  digitalWrite(RelayPin3, toggleState_3);
  digitalWrite(RelayPin4, toggleState_4);

  Serial.println("The device started");
    
  WiFi.begin(ssid, pass);
  timer.setInterval(3000L, checkBlynkStatus); // check if connected to Blynk server every 3 seconds
  Blynk.config(auth);//, ssid, pass);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi Not Connected");
  } else {
    Serial.println("WiFi Connected");
    Blynk.run();
  }
  Serial.println("***********Light************");
  Serial.println(digitalRead(SwitchPin1));
  Serial.println(digitalRead(SwitchPin2));
  Serial.println(digitalRead(SwitchPin3));
  Serial.println(digitalRead(SwitchPin4));
  
//  if (Serial.available()) {
//    Serial.print("Test : ");
//    Serial.println(Serial.read());
//  }

  /*  if(SerialBT.available()){
           incoming = SerialBT.read();
           Serial.print("Receoved : "); Serial.println(incoming);
           switch(incoming){
              case 65 : digitalWrite(RelayPin1, LOW); break;// turn on relay 1
              case 97 : digitalWrite(RelayPin1, HIGH); break;// turn off relay 1
              case 68 : digitalWrite(RelayPin2, LOW); break;// turn on relay 2
              case 69 : digitalWrite(RelayPin2, HIGH); break;// turn off relay 2
              default : break;
           }
    }*/

  timer.run(); // Initiates SimpleTimer
  switch_button();
}
