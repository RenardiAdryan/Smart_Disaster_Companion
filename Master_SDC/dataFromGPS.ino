#include "define.h"

double latitude = 28.5458,longitude =77.1703;
void GetGPS(){
  static int counter;
 // static float lat = 28.5458,lon = 77.1703;
   if(counter++>10){counter = 0;
        while(gpsSerial.available() > 0){
            gps.encode(gpsSerial.read());
                  if (gps.location.isUpdated()){
                    // Latitude in degrees (double)

                    latitude  = gps.location.lat();
                    longitude = gps.location.lng();
                    } 
               }
          }
   }
  
 
