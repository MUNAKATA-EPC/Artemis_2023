namespace Attacker
{
    #define MOTOR_SPEED_A 14

    Timer Line_Timer;

    float gains[3] = {0.60, 0, 15};
    float gains_gyro[3] = {1.2, 0, 12};

    int Line_Move_deg;

    int CulcSpeed()
    {
        // plus gain / minus gain
        float deg_gain[2] = {0.04, 0.1};
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
        Line_Timer.tick();
        
        if(Cam_GoalY_Deg != 255)
        {
            PID_loop(180 - Cam_GoalY_Deg, gains);
        }
        else
        {
            PID_loop(Gyro_Deg, gains_gyro);
        }

        CulcSpeed();

        if(Line_Value != 510)
        {
            if(!Line_Timer.isticking())
            {
                Line_Timer.reset();
                Line_Timer.start();
                Line_Move_deg = Line_Value;
            }
        }

        if(Line_Timer.isticking())
        {
            if(Line_Timer.get_value() <= 400)
            {
                int move_deg = ((Line_Move_deg + 360) - 180) % 360;
                Move(move_deg, MOTOR_SPEED_A);
            }
            else
            {
                Line_Timer.reset();
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
                    Move(0, MOTOR_SPEED_A);
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
        }
    }
}

namespace Defencer
{
    #define MOTOR_SPEED_B 15

    float gain[3] = {0.6, 0, 12};

    void Main_Program(bool yellow)
    {
        //Process_NeoPixel();

        PID_loop(Gyro_Deg, gain);

        Move(0, 0);
    }
} 