#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Firebase.h>

#include <Ticker.h>  //Ticker Library

Ticker interrupt;
#define BUFFER  50
#define LEDBUILTIN D0


//#define FIREBASE_HOST "smartdis-f49ae.firebaseio.com"
//#define FIREBASE_AUTH "sxTbbdGxGuEiS30FjNpqpoVRIadB2WgExRk5woAR"

//#define FIREBASE_HOST "smartdisastercompanion-714c4.firebaseio.com"
//#define FIREBASE_AUTH "tSnFs5rUy862Gjr6DLluZcwCVHB5DSN6mLoVnCma"
//#define FIREBASE_AUTH   "dYvCq162RPegfqSf3For3GfgSz6SJX134lFaxQWQ"
//#define FIREBASE_AUTH   "bavHpwWBgrIHzPt71D0Cteu7J7EBI5weFQJj3I8T"


#define FIREBASE_HOST "smartdisastercompanion-714c4.firebaseio.com"
#define FIREBASE_AUTH "dYvCq162RPegfqSf3For3GfgSz6SJX134lFaxQWQ"

//#define FIREBASE_HOST "smartdisaster-a180c.firebaseio.com"
//#define FIREBASE_AUTH "lsajM4OtCdSmMwRKe30mmArzu2YmhsDBQ5EwPuiI"


//#define WIFI_SSID "SDC-Hotspot" // Change the name of your WIFI
//#define WIFI_PASSWORD "poiuytrewq" // Change the password of your WIFI
//#define WIFI_SSID "Haqi" // Change the name of your WIFI
//#define WIFI_PASSWORD "muhabdulhaq" // Change the password of your WIFI
//#define WIFI_SSID "nodemcu" // Change the name of your WIFI
//#define WIFI_PASSWORD "passwordnodemcu" // Change the password of your WIFI
#define WIFI_SSID "SW2D" // Change the name of your WIFI
#define WIFI_PASSWORD "12345678" // Change the password of your WIFI



float latitude = 28.5458,longitude =77.1703;int fireState=0;

char last;
char indeks1[BUFFER];
char indeks2[BUFFER];
char indeks3[BUFFER];

char j;

char buff[BUFFER];

char variable;
//



void setup() {
   // put your setup code here, to run once:
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(2000);

for(char i=0;i<10;i++){
   // get value 
  
  Serial.print("ConnectFlag: ");
  float data;

  data = Firebase.getFloat("connectFlag");
  Serial.println(data);
  //if(data!=1){ Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);}
  delay(500);
  

}
  pinMode(LEDBUILTIN,OUTPUT);
  
  digitalWrite(LEDBUILTIN,LOW);
  delay(10);
  digitalWrite(LEDBUILTIN,HIGH);
  delay(10);
  digitalWrite(LEDBUILTIN,LOW);
  delay(10);
  digitalWrite(LEDBUILTIN,HIGH);
  
  
   //Interrupt handler 1ms
   interrupt.attach_ms(1, interruptHandler); 
  
 
}


int intervalTime=100;
void loop() {
 static int nowTime,prevTime;
  

  nowTime = millis();
  // put your main code here, to run repeatedly:
if(nowTime-prevTime>intervalTime){

  //if(Firebase.getFloat("connectFlag")){
  Firebase.getFloat("connectFlag");
  
  Firebase.setFloat ("users/-LVYjfOXuFxSGghwi3bl/dtLat",latitude);
  if(Firebase.failed()){//Serial.println("Lat Error = " + Firebase.error());
}
  Firebase.setFloat ("users/-LVYjfOXuFxSGghwi3bl/dtLon",longitude);
  if(Firebase.failed()){//Serial.println("Long Error = " + Firebase.error());     
}
  Firebase.setInt ("users/-LVYjfOXuFxSGghwi3bl/dtApi",fireState);
  if(Firebase.failed()){//Serial.println("api =  " + Firebase.error());
}

  //}

  digitalWrite(LEDBUILTIN, !(digitalRead(LEDBUILTIN)));  //Invert Current State of LED 
prevTime = nowTime;
}
}




void interruptHandler()
{static char flag1,flag2,flag3;
  static int countSerial ,flagSerial;
   if(Serial.available()>0){
   
     byte incomingByte = Serial.read();
      
    if(incomingByte=='#'){
      countSerial=0;flagSerial=1;last=1;}
    else {
      countSerial++;
      if(countSerial<BUFFER){
           buff[countSerial] = incomingByte;
          }
      }
   
    //Parsing serial
      if(incomingByte=='!' && flagSerial == 1){ flagSerial = 0;

        for (int i=1; i<=3; i++) //jumlah data
        {   
          for (j=0; j<11; j++) //panjang data
         {
                    if (buff[j+last]==',' || buff[j+last]=='!'||buff[j+last]=='\0') {
                      last = last + j + 1;
                      break;
                      }
                    
                    switch (i) {
                      case 1: indeks1[j] = buff[j+last]; 
                      case 2: indeks2[j] = buff[j+last];
                      case 3: indeks3[j] = buff[j+last];
                    }
          }
          
         
              switch (i) {
                case 1: indeks1[j] = '\0';
                case 2: indeks2[j] = '\0';
                case 3: indeks3[j] = '\0';
      
              }
                 
     }
         
      latitude         =atof(indeks1);
      longitude        =atof(indeks2);
      fireState        =atoi(indeks3);  

          

//  Serial.print("Latitude = ");
//  Serial.print(latitude);
//  
//  Serial.print(" || Longitude = ");
//  Serial.print(longitude);
//
//  Serial.print(" || fireState = ");
//  Serial.println(fireState);

      
      }

  }
//
//
wdt_reset();

}
