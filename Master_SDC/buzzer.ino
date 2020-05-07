//=========================================================================
#include "define.h"
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_F5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5,
  NOTE_D5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_F5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_F5, 
  NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_C5,NOTE_D5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5
};

int noteDurations[] = {
  3, 8, 4, 4, 3, 8, 2, 3, 8, 4, 4, 1, 3, 8, 4, 4, 2, 2, 3, 8, 4, 4, 1, 3, 8, 4, 4, 3, 8, 2, 3, 8, 4, 4, 1, 3, 8, 4, 4, 2, 2, 3, 8, 4, 4, 1
};


void Buzzer() {

 /* for (int thisNote = 0; thisNote < 46; thisNote++) {
    int noteDuration = 1500 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(13);
  }*/
tone(BUZZER_PIN, NOTE_C5,1500/10);
delay(1500/10*1.30);
tone(BUZZER_PIN, NOTE_E5,1500/10);
delay(1500/10*1.30);
tone(BUZZER_PIN, NOTE_F5,1500/10);
delay(1500/10*1.30);

  
}
//--------------------------------------------------------------------------
