int soundlevel[8] = {262, 294, 330, 349, 392, 440, 494, 523};

void Play_buzzer(int frequency, int duration = 200){
  tone(BUZZER_PIN, frequency, duration) ;  //レ
  delay(duration) ;
  noTone(BUZZER_PIN) ;
  delay(duration) ;
}

void Setup_buzzer(){
}