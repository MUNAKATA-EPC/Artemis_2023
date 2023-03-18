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
                    analogWrite(SpliterPin, 0);
                        analogWrite(ControlPin, 1023);
                }
                else{
                    if(KickTimer.get_value() >= 6000){
                        kicking = false;
                        KickTimer.reset();
                    }
                    analogWrite(SpliterPin, 1023);
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