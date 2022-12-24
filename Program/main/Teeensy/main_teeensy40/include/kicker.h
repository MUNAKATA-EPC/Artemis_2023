class Kicker{
    public:
        Kicker(int Control, int Spliter){
            this->ControlPin = Control;
            this->SpliterPin = Spliter;
        }
        void loop(){
            KickTimer.tick();
            if(!kicking){
                analogWrite(SpliterPin, 1024);
                analogWrite(ControlPin, 0);
            }
        };
        void push(){
            if(!kicking){
                KickTimer.start();
                kicking = true;
            }
            
            if(kicking){
                if(KickTimer.get_value() <= 500){
                    Bright(strip.Color(255,   0,   0));
                    analogWrite(SpliterPin, 1024);
                    analogWrite(ControlPin, 1024);
                }
                else{
                    if(KickTimer.get_value() >= 6000){
                        kicking = false;
                        KickTimer.reset();
                    }
                    Bright(strip.Color(0,   255,   0));
                    analogWrite(SpliterPin, 1024);
                    analogWrite(ControlPin, 0);
                }
            }
        };
        bool kicking;
        Timer KickTimer; 
    private:
        int ControlPin;
        int SpliterPin;
};