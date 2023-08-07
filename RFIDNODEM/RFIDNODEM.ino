
#include <SPI.h>

#include <MFRC522.h>
#define BLYNK_TEMPLATE_ID           "TMPLQi6atOae"
#define BLYNK_DEVICE_NAME           "RFID"
#define BLYNK_AUTH_TOKEN            "zr29KAKs8iXXsCGCwA7CIwZfhuvyrKgp"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#define SS_PIN 4

#define RST_PIN 5


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

char auth[] ="zr29KAKs8iXXsCGCwA7CIwZfhuvyrKgp";    //Blynk Authentication Token -- sent via Email from Blynk
 
char ssid[] = "TECHAID";   //Enter WiFi Name
char password[] = "RBREEZY2021";   //Enter Wifi Password
#include <Servo.h> 

Servo myServo; //define servo name
#define ledR  16
#define ledG  0 
#define BUZZER 15 //buzzer pin


SimpleTimer timer;

int fflag = 0; 

int eflag = 0; 

int jflag = 0; 

WidgetTerminal terminal(V2);


void setup() 

{

  Serial.begin(9600);   // Initiate a serial communication

      Blynk.begin(auth, ssid, password);

  SPI.begin();      // Initiate  SPI bus

    myServo.attach(2); //servo pin D4

  myServo.write(0); //servo start position

  pinMode(BUZZER, OUTPUT);
pinMode(ledG, OUTPUT);
pinMode(ledR, OUTPUT);
  noTone(BUZZER);

  

  mfrc522.PCD_Init();   // Initiate MFRC522

  Serial.println("Welcome!!");

  Serial.println();

  Serial.println("Circuit is Ready");

  timer.setInterval(1000L, iot_rfid);


}

void loop() 

{

    timer.run(); // Initiates SimpleTimer

  Blynk.run();

  

  

  

}



void iot_rfid(){


  // Look for new cards

 // Look for new cards

  if ( ! mfrc522.PICC_IsNewCardPresent()) 

  {

    return;

  }

  // Select one of the cards

  if ( ! mfrc522.PICC_ReadCardSerial()) 

  {

    return;

  }

  //Show UID on serial monitor

  Serial.print("UID tag :");

  String content= "";

  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) 

  {

     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");

     Serial.print(mfrc522.uid.uidByte[i], DEC);

     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));

     content.concat(String(mfrc522.uid.uidByte[i], DEC));

  }

  Serial.println();

  if( (content.substring(1) == "228 148 113 24")  && (fflag == 1))

  {

         Serial.println("Cognate");

         Blynk.virtualWrite(V2, "Cognate" );
           Blynk.logEvent("Cognate Entered the Facility");
digitalWrite(ledG, HIGH);
digitalWrite(BUZZER, HIGH);

    delay(250);
digitalWrite(ledG, LOW);
     digitalWrite(BUZZER, LOW);
  
          myServo.write(180);

          delay(3000);

          myServo.write(1);
  }
     


                else 

        Serial.println("Access Denied");
      
digitalWrite(ledR, HIGH);
         digitalWrite(BUZZER, HIGH);

    delay(1500);
digitalWrite(ledR, LOW);
      digitalWrite(BUZZER, LOW);


  }


// in Blynk app writes values to the Virtual Pin 3

BLYNK_WRITE(V3)

{

   fflag = param.asInt(); // assigning incoming value from pin V3 to a variable

  // Blynk.virtualWrite(V2, fflag );

 

}

 

