#define MOTOR_SPEED 25

Timer Line_Timer;

Timer test;

float gains[3] = {0.60, 0, 12};

int CulcSpeed()
{
    // plus gain / minus gain
    float deg_gain[2] = {0.06, 0.15};
    float dis_gain = 0.12;
    int ball_change_deg = 40;
    int ball_deg_val;
    int ball_dis_val;
    int add_speed;

    ball_deg_val = Ball_Deg;
    if(Ball_Deg >= 180)
        ball_deg_val = 180 - (Ball_Deg - 180) - ball_change_deg;
    else 
        ball_deg_val = ball_deg_val - ball_change_deg;
    
    ball_dis_val = Ball_Distance - 60;
    
    ball_deg_val = ball_deg_val > 0 ? ball_deg_val * deg_gain[0] : ball_deg_val * deg_gain[1];

    add_speed = (ball_deg_val) + (ball_dis_val * dis_gain); //(-90 ~ 90) * gain

    return MOTOR_SPEED + add_speed;
}

void Main_Program()
{
    PID_loop(gains);

    Process_NeoPixel();

    CulcSpeed();

    if(Ball_Deg >= 510 || Ball_Deg < 0)
    {
        Move(0, 0);
    }
    else
    {
        if(Ball_Deg <= 32 || Ball_Deg >= 360)
        {
            Move(0, MOTOR_SPEED);
        }
        else 
        {
            if(Ball_Deg <= 180)
            {
                int move_deg = Ball_Deg + (90 - min(max(Ball_Distance - 60, 0) / 15.0 * 80.0, 85));
                Move(move_deg, CulcSpeed());
            }
            else
            {
                int move_deg = Ball_Deg - (90 - min(max(Ball_Distance - 60, 0) / 45.0 * 90.0, 70));
                Move(move_deg, CulcSpeed());
            }
  
       }
    }

    Serial.println(Ball_Distance);
}
