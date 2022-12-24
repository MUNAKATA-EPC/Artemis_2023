class Timer{
private:
    int _start_val;
    int value;
    bool ticking;
public:
    void tick(){
        if(ticking)
            value = millis() - _start_val;
    }
    void start(){
        _start_val = millis();
        ticking = true;
    }
    void stop(){
        ticking = false;
    }
    void reset(){
        ticking = false;
        value = 0;
    }
    int get_value(){
        return value;
    }
};