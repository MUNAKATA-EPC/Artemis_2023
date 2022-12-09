class Timer{
private:
    int _start_val;
    int value;
    bool ticked;
public:
    void tick(){
        if(ticked)
            value = micros() - _start_val;
    }
    void start(){
        _start_val = micros();
        ticked = true;
    }
    void stop(){
        ticked = false;
    }
    void reset(){
        ticked = false;
        value = 0;
    }
    int get_value(){
        return value;
    }
};