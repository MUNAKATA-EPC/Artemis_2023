#define buzzer 3

int soundlevel[8] = {262, 294, 330, 349, 392, 440, 494, 523};

void Play_buzzer(int frequency, int duration = 200){
  tone(buzzer, frequency, duration) ;  //レ
  delay(duration) ;
  noTone(buzzer) ;
  delay(duration) ;
}

void Setup_buzzer(){
/*
  Play_buzzer(soundlevel[0]);
  Play_buzzer(soundlevel[1]);
  Play_buzzer(soundlevel[2]);
  Play_buzzer(soundlevel[3]);
  Play_buzzer(soundlevel[4]);
  Play_buzzer(soundlevel[5]);
  Play_buzzer(soundlevel[6]);
  Play_buzzer(soundlevel[7]);
*/
}