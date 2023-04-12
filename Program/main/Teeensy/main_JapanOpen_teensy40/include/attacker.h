namespace Attacker
{
    #define MOTOR_SPEED_A 20

    Timer Line_Timer;

    float gains[3] = {0.30, 0, 15};
    float gains_gyro[3] = {0.30, 0, 15};

    int Line_Move_deg;

    int Cam_Data[2];

    bool Line_Moving;

    int CulcSpeed()
    {
        // plus gain / minus gain
        float deg_gain[2] = {0.04, 0.05};
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

        return MOTOR_SPEED_A + add_speed;
    }

    void Main_Program(bool yellow)
    {
        if(yellow)
        {
            Cam_Data[0] = Cam_GoalY_Deg;
            Cam_Data[1] = Cam_GoalY_Dis;

            if(Cam_GoalY_Deg == 255)
                PID_loop(Gyro_Deg / 2, gains_gyro);
            else
                PID_loop(180 - Cam_GoalY_Deg, gains);
        }
        else
        {
            Cam_Data[0] = Cam_GoalB_Deg;
            Cam_Data[1] = Cam_GoalB_Dis;

            if(Cam_GoalB_Deg == 255)
                PID_loop(Gyro_Deg / 2, gains_gyro);
            else
                PID_loop(180 - Cam_GoalB_Deg, gains);
        }

        Line_Timer.tick();
        
        CulcSpeed();

        if(Line_Value != 510)
        {
            if(!Line_Moving)
            {
                Line_Timer.reset();
                Line_Timer.start();
                Line_Move_deg = Cam_Court_Deg;
                Line_Moving = true;
            }
        }

        if(Line_Moving)
        {
            if(Line_Timer.get_value() <= 500)
            {
                Move(Cam_Court_Deg * 2, MOTOR_SPEED_A + 2);
            }
            else
            {
                Line_Timer.reset();
                Line_Moving = false;
            }
        }
        else
        {
            if(Ball_Deg >= 500 || Ball_Deg < 0)
            {
                Move(0, 0);
            }
            else
            {
                if(Ball_Deg <= 32 || Ball_Deg >= 360)
                {
                    if(Cam_Data[1] <= 88)
                    {
                        Move(0, MOTOR_SPEED_A - 6);
                    }
                    else
                    {
                        Move(0, MOTOR_SPEED_A);
                    }
                }
                else 
                {
                    if(Ball_Deg <= 180)
                    {
                        int move_deg = Ball_Deg + (90 - min(max(Ball_Distance - 60, 0) / 15.0 * 80.0, 85));
                        Move(move_deg, MOTOR_SPEED_A);
                    }
                    else
                    {
                        int move_deg = Ball_Deg - (90 - min(max(Ball_Distance - 60, 0) / 45.0 * 90.0, 70));
                        Move(move_deg, MOTOR_SPEED_A);
                    }
        
                }
            }
        }

        Serial.println(Cam_Court_Deg);
    }
}