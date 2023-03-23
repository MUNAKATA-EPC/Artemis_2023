namespace Defencer
{
    #define MOTOR_SPEED_B 15

    float gain[3] = {0.6, 0, 12};

    void Main_Program(bool yellow)
    {
        //Process_NeoPixel();

        PID_loop(Gyro_Deg, gain);

        if(Ball_Deg < 510)
        {   
            if(Ball_Distance <= 70)
            {
                if(Ball_Deg <= 16 || Ball_Deg >= 360)
                {
                    Move(0, MOTOR_SPEED_B);
                }
                else if(Ball_Deg <= 44)
                {
                    Move(90, MOTOR_SPEED_B);
                }
                else if(Ball_Deg <= 100)
                {
                    Move(135, MOTOR_SPEED_B);
                }
                else if(Ball_Deg <= 156)
                {
                    Move(90, MOTOR_SPEED_B);
                }
                else if(Ball_Deg <= 190)
                {
                    Move(0, 0);
                }
                else if(Ball_Deg <= 236)
                {
                    Move(270, MOTOR_SPEED_B);
                }
                else if(Ball_Deg <= 320)
                {
                    Move(225, MOTOR_SPEED_B);
                }
                else if(Ball_Deg < 360)
                {
                    Move(270, MOTOR_SPEED_B);
                }
            }
            else
            {
            if(Ball_Deg <= 22 || Ball_Deg >= 360)
            {
                Move(0, 0);
            }  
                else if(Ball_Deg <= 180)
            {
                    Move(90, MOTOR_SPEED_B);
            }
                else if(Ball_Deg <= 360)
            {
                    Move(270, MOTOR_SPEED_B);
            }
            }
        }
        else
        {
            Move(0, 0);
        }
    }         
} 