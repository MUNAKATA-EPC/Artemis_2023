namespace Attacker
{
    #define MOTOR_SPEED_A 25

    Timer Line_Timer;

    float gains[3] = {0.50, 0, 24};
    float gains_gyro[3] = {0.51, 0, 38};

    int Line_Move_deg;
    int Before_Move_Deg;

    int Cam_Data[2];

    bool Line_Moving;

    int CulcSpeed()
    {
        // plus gain / minus gain
        float deg_gain[2] = {0.04, 1.0};
        float dis_gain = 0.12;
        int ball_change_deg = 60;
        int ball_deg_val;
        int ball_dis_val;
        int add_speed;

        ball_deg_val = Ball_Deg;
        if(Ball_Deg >= 180)
            ball_deg_val = 180 - (Ball_Deg - 180) - ball_change_deg;
        else 
            ball_deg_val = ball_deg_val - ball_change_deg;
        
        ball_dis_val = (Ball_Distance - 60) * 0.1;
        
        ball_deg_val = ball_deg_val > 0 ? ball_deg_val * deg_gain[0] : ball_deg_val * deg_gain[1];

        add_speed = ball_deg_val <= 0 ? min((ball_deg_val) + (ball_dis_val * dis_gain), 0) : max((ball_deg_val) + (ball_dis_val * dis_gain), 0); //(-90 ~ 90) * gain

        return MOTOR_SPEED_A + add_speed;
    }

    void Main_Program(bool yellow)
    {
        rainbow(50);

        Line_Timer.tick();

        if(yellow)
        {
            
            Cam_Data[0] = Cam_GoalY_Deg;
            Cam_Data[1] = Cam_GoalY_Dis;

            if(Cam_GoalY_Deg == 255)
                PID_loop(Gyro_Deg - 90, gains_gyro, 180);
            else
                PID_loop(180 - Cam_GoalY_Deg, gains, 180);
        }
        else
        {
            Cam_Data[0] = Cam_GoalB_Deg;
            Cam_Data[1] = Cam_GoalB_Dis;

            if(Cam_GoalB_Deg == 255)
                PID_loop(Gyro_Deg - 90, gains_gyro);
            else
                PID_loop(180 - Cam_GoalB_Deg, gains, 180);

        }


        

        if(Line_Value < 10 && !Line_Moving)
        {
            Line_Moving = true;
            Line_Timer.reset();
            Line_Timer.start();
            
            Move(0, 0);
        }


        if(Line_Timer.get_value() <= 500)
        {
            Move(0, 0);
        }
        else if(Line_Timer.get_value() <= 1000)
        {
            Move((Before_Move_Deg + 180) % 360, 20);
        }
        else if(Ball_Deg >= 500 || Ball_Deg < 0)
        {
            Line_Moving = false;
            Move(0, 0);
        }
        else
        {
            Line_Moving = false;
            
            if(Ball_Deg <= 32 || Ball_Deg >= 360)
            {
                Move(0, MOTOR_SPEED_A);  
                Before_Move_Deg = 0;
            }
            else 
            {
                if(Ball_Deg <= 202)
                {
                    int move_deg = Ball_Deg + (90 - min(max(Ball_Distance - 55, 0) / 15.0 * 80.0, 85));
                    int move_speed = min(Ball_Distance / 2.5, 30);
                    Move(move_deg, move_speed);
                    Before_Move_Deg = move_deg;
                }
                else
                {
                    int move_deg = Ball_Deg - (90 - min(max(Ball_Distance - 55, 0) / 45.0 * 90.0, 70));
                    int move_speed = min(Ball_Distance / 2.5, 30);
                    Move(move_deg, move_speed);
                    Before_Move_Deg = move_deg;
                }
    
            }
        }
    }
}
