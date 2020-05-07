#ifndef _DEFINE_H
#define _DEFINE_H

#include <SoftwareSerial.h> 
#include <TinyGPS++.h> 
#include <Wire.h>
#include <LiquidCrystal.h>
#include "pitches.h"
TinyGPSPlus gps; // create gps object 



const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial gpsSerial(10,11);//rx,tx 

#define fireSensor2   0x25
#define fireSensor1   0x31
#define BUZZER_PIN 12
#define LEDBUILTIN 13

#define BUTTON4   A0
#define BUTTON3   A1
#define BUTTON2   A2
#define BUTTON1   A3




extern void GetGPS();
extern double latitude,longitude;
extern void Buzzer();
#endif
