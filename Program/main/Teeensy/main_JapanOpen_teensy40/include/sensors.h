int Ball_Deg;
int Ball_Distance;

int Gyro_Deg;

int Line_Value;

int Cam_Court_Deg;
int Cam_Court_Dis;
int Cam_GoalY_Deg;
int Cam_GoalY_Dis;
int Cam_GoalB_Deg;
int Cam_GoalB_Dis;

void Initialize_Sensors(){
    Serial3.begin(115200);      //Mega      ======> Teensy
    Serial4.begin(115200);      //Line_Ring ======> Teensy
    Serial5.begin(115200);      //OpenMV    ======> Teensy
}

void Read_Sensors(){
    //Ball Deg And Distance From Mega
    
    if(Serial3.available() > 0)
    {
        int head_ball = Serial3.read();
        if(head_ball == 255)
        {
            int test = Serial3.read();
            if(test != -1)
                Ball_Deg = test * 2;

            test = Serial3.read();
            if(test != -1)
                Ball_Distance   = test;
        }
    }
    if(Serial5.available() > 0)
    {
        Cam_Court_Deg   = Serial5.readStringUntil('a').toInt();
        Cam_Court_Dis   = Serial5.readStringUntil('b').toInt();
        Cam_GoalY_Deg   = Serial5.readStringUntil('c').toInt();
        Cam_GoalY_Dis   = Serial5.readStringUntil('d').toInt();
        Cam_GoalB_Deg   = Serial5.readStringUntil('e').toInt();
        Cam_GoalB_Dis   = Serial5.readStringUntil('f').toInt(); 
    }
}   