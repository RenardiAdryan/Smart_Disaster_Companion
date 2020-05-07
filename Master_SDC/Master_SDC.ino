#include "define.h"
int dtSensor[3][7];
int sensor[4];
int fireStatus;
char showing=1;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  Serial.begin(115200); // connect serial 
  gpsSerial.begin(9600); // connect gps sensor
  Wire.begin(); //Connect to fire ensor 

  pinMode(BUTTON1,INPUT_PULLUP);
  pinMode(BUTTON2,INPUT_PULLUP);
  pinMode(BUTTON3,INPUT_PULLUP);
  pinMode(BUTTON4,INPUT_PULLUP);
  
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(LEDBUILTIN,OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("..STARTING UP..");
  lcd.setCursor(0,1);
  lcd.print("___..SDC..___");
  Buzzer();
  delay(1000);
  lcd.clear();    

}
float nowTime,prevTime;int intervalTime= 100;
void loop() {
  // put your main code here, to run repeatedly:

GetGPS();

ReadFireSensor();
if(sensor[1]!=999 ||sensor[2]!=999  ){fireStatus =1 ;
digitalWrite(BUZZER_PIN,HIGH);
}
else {fireStatus =0 ; digitalWrite(BUZZER_PIN,LOW);}

buttonScan();
LCDshow();

nowTime = millis();
if(nowTime-prevTime>intervalTime){
sendToESP();
prevTime = nowTime;
  digitalWrite(LEDBUILTIN, !(digitalRead(LEDBUILTIN)));  //Invert Current State of LED 

}

}


void sendToESP(){Serial.print("#");
 Serial.print(latitude,6);Serial.print(",");
 Serial.print(longitude,6);Serial.print(",");
 Serial.print(fireStatus);Serial.println("!");
}





void LCDshow(){
  static int counter;
  if(counter++>50){counter=0;
     lcd.clear();
  if(showing==1){   
            if(fireStatus == 0 ){     
              lcd.setCursor(0,0);
              lcd.print("SDC IDle !!"); 
                
              lcd.setCursor(0,1);
              lcd.print("Fire undetected"); 
                      }
              
            else   if(fireStatus == 1 ){     
              lcd.setCursor(0,0);
              lcd.print("FIre Detect !!"); 
                
              lcd.setCursor(0,1);
              if(sensor[1]!=999){
              //lcd.print(getDegree(sensor[1]),2); lcd.print(">1");lcd.print("|");
              float degree= sensor[1];
              if(degree<3000){lcd.print("Sensor 1->");lcd.print("Right");}
              else if(degree>=3000 && degree<=4000 ){lcd.print("Sensor 1->");lcd.print("Center");}
              else if(degree>4000){lcd.print("Sensor 1->");lcd.print("Left");}
              }
                
              if(sensor[2]!=999){
              //lcd.print("|");lcd.print(getDegree(sensor[2]),2); lcd.print(">2");}
              float degree= sensor[2];
              if(degree<3000){lcd.print("Sensor 2->");lcd.print("Right");}
              else if(degree>=3000 && degree<=4000 ){lcd.print("Sensor 2->");lcd.print("Center");}
              else if(degree>4000){lcd.print("Sensor 2->");lcd.print("Left");} 
                     
                      }
              
                }

  }
    else if (showing==2){      
      lcd.setCursor(0,0);
      lcd.print("Lat = "); lcd.print(latitude,5);
      lcd.setCursor(0,1);
      lcd.print("Long = "); lcd.print(longitude,5);

    }
}
}

void buttonScan(){
  if(isButtonPressed(BUTTON1)){showing = 1; }
  if(isButtonPressed(BUTTON2)){showing = 2; }
  if(isButtonPressed(BUTTON3)){showing = 3; }
  
  
  }

int isButtonPressed(int pin)//Function to eliminate debouncing
{
  if(!digitalRead(pin))
  {
    delay(5);
    if     (!digitalRead(pin)) return 1;
    else if(digitalRead(pin)) return 0;
  }
  
  return 0;
}



float getDegree(float degree){
//      ------------
//      |         /
//      |       /
//      |     /
//      |   /
//      | /
//tinggi = 11.09 , alas = 29 maka arcTan = 21 derajat     
  degree = map(degree,0,5000,0,21);


 return degree; 
  }
int i2c_read(int id)
{
  Wire.requestFrom(id, 1); // request 1 bytes from slave device #ID
  int data = 0;
  while (Wire.available()) { // slave may send less than requested
    data = Wire.read(); // receive a byte as character
  }

  if(id == fireSensor1){
  dtSensor[1][6] = ((data & 0b00100000) >> 5);
  dtSensor[1][5] = ((data & 0b00010000) >> 4);
  dtSensor[1][4] = ((data & 0b00001000) >> 3);
  dtSensor[1][3] = ((data & 0b00000100) >> 2);
  dtSensor[1][2] = ((data & 0b00000010) >> 1);
  dtSensor[1][1] = data & 0b00000001;
  }

  if(id == fireSensor2){
  dtSensor[2][6] = ((data & 0b00100000) >> 5);
  dtSensor[2][5] = ((data & 0b00010000) >> 4);
  dtSensor[2][4] = ((data & 0b00001000) >> 3);
  dtSensor[2][3] = ((data & 0b00000100) >> 2);
  dtSensor[2][2] = ((data & 0b00000010) >> 1);
  dtSensor[2][1] = data & 0b00000001;
  }

  return data;
}

void ReadFireSensor(){
  
  i2c_read(fireSensor1); 
  i2c_read(fireSensor2);
  
  if (dtSensor[1][6] || dtSensor[1][5] || dtSensor[1][4] || dtSensor[1][3] || dtSensor[1][2] || dtSensor[1][1]) {
    //Calculate the weighted mean!!-->RING sensor
    sensor[1] = (5000  * dtSensor[1][6] + 4000 * dtSensor[1][5] + 3000 * dtSensor[1][4] + 2000 * dtSensor[1][3] + 1000 * dtSensor[1][2] + 0 * dtSensor[1][1]) /
             (dtSensor[1][6] + dtSensor[1][5] + dtSensor[1][4] + dtSensor[1][3] + dtSensor[1][2] + dtSensor[1][1]);
  }
  else sensor[1] = 999;
  
  if (dtSensor[2][6] || dtSensor[2][5] || dtSensor[2][4] || dtSensor[2][3] || dtSensor[2][2] || dtSensor[2][1]) {
    //Calculate the weighted mean!!-->RING sensor
    sensor[2] = (5000  * dtSensor[2][6] + 4000 * dtSensor[2][5] + 3000 * dtSensor[2][4] + 2000 * dtSensor[2][3] + 1000 * dtSensor[2][2] + 0 * dtSensor[2][1]) /
             (dtSensor[2][6] + dtSensor[2][5] + dtSensor[2][4] + dtSensor[2][3] + dtSensor[2][2] + dtSensor[2][1]);
  }
  else sensor[2] = 999;
  
}


//int baca = i2c_read(0x30);
//Serial.print("Data i2C sensor 1= ");
//Serial.print(baca);Serial.print(" || ");
// baca = i2c_read(0x31);
//Serial.print("Data i2C sensor 2= ");
//Serial.println(baca);

//Serial.print("Data sensor 1 = ");
//Serial.print( sensor[1] );Serial.print(" || ");
//Serial.print("Data sensor 2 = ");
//Serial.println( sensor[2] );
