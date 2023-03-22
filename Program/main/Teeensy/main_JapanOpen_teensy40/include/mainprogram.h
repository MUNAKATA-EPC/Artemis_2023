namespace Attacker
{
    #define MOTOR_SPEED_A 25

    Timer Line_Timer;

    float gains[3] = {0.60, 0, 6};
    float gains_gyro[3] = {1.2, 0, 12};

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

        return MOTOR_SPEED_A + add_speed;
    }

    void Main_Program(bool yellow)
    {
        PID_loop(180 - Cam_GoalY_Deg, gains);

        Process_NeoPixel();

        CulcSpeed();

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

namespace Defencer
{
    #define MOTOR_SPEED_B 20

    float gain[3] = {0.6, 0, 12};

    void Main_Program(bool yellow)
    {
        Process_NeoPixel();

        PID_loop(Gyro_Deg, gain);

        Move(0, 0);
    }
} 