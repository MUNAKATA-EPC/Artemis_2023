class Button{
private:
    int pin;
    int value;
public:
    Button(int pin){
        this->pin = pin;
        pinMode(pin, INPUT_PULLUP);
    }
    void loop()
    {
        if(digitalRead(this->pin) == HIGH)
        {
            value++;
        }
        else
        {
            value = 0;
        }
    }

    int isPushed()
    {
        return value == 1;
    }

    int isPushing()
    {
        return value > 1;
    }

    int get_value()
    {
        return this->value;
    }
};