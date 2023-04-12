namespace Defencer
{
    #define MOTOR_SPEED_B 20
    #define MOTOR_SPEED_B_LATE 15
    #define MOTOR_SPEED_B_FAST 25
    #define BALL_WAIT_TIME_SHORT 750
    #define BALL_WAIT_TIME_LONG 1250

    Timer Ball_Wait;

    float gain[3] = {0.45, 0, 12};

    void Main_Program(bool yellow)
    {
        PID_loop(Gyro_Deg, gain);

        Ball_Wait.tick();

        if(Ball_Deg < 510)
        {   
            if(Ball_Distance <= 77)
            {
                if(Ball_Deg <= 22)
                {
                    if(Ball_Distance <= 61)
                    {
                        Move(0, MOTOR_SPEED_B);
                    }      
                    else
                    {
                        Ball_Wait.start();

                        if(Ball_Wait.get_value() >= BALL_WAIT_TIME_SHORT)
                        {
                            Move(0, MOTOR_SPEED_B);
                        }
                        else
                        {
                            Move(0, 0);
                        }
                    }
                }
                else
                {
                    if(Ball_Deg <= 35)
                    {
                        if(Ball_Wait.get_value() >= BALL_WAIT_TIME_SHORT)
                        {
                            Move(0, MOTOR_SPEED_B);
                        }
                        else
                        {        
                            Ball_Wait.stop();
                            Ball_Wait.reset();
                            Move(90, MOTOR_SPEED_B_LATE );
                        }
                    }
                    else if(Ball_Deg >= 360)
                    {
                        if(Ball_Wait.get_value() >= BALL_WAIT_TIME_SHORT)
                        {
                            Move(0, MOTOR_SPEED_B);
                        }
                        else
                        {        
                            Ball_Wait.stop();
                            Ball_Wait.reset();
                            Move(270, MOTOR_SPEED_B_LATE);
                        }
                    }
                    else
                    {
                        Ball_Wait.stop();
                        Ball_Wait.reset();
                        
                        if(Ball_Deg <= 76)
                        {
                            Move(90, MOTOR_SPEED_B);
                        }
                        else if(Ball_Deg <= 110)
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
                        else if(Ball_Deg <= 360)
                        {
                            Move(270, MOTOR_SPEED_B);
                        }
                    }
                } 
            }
            else
            {
                if(Ball_Deg <= 30)
                {
                    Ball_Wait.start();

                    if(Ball_Wait.get_value() >= BALL_WAIT_TIME_LONG)
                    {
                        Move(0, MOTOR_SPEED_B);
                    }
                    else
                    {
                        Move(90, MOTOR_SPEED_B_FAST);
                    }
                }  
                else if(Ball_Deg >= 360)
                {
                    Ball_Wait.start();

                    if(Ball_Wait.get_value() >= BALL_WAIT_TIME_LONG)
                    {
                        Move(0, MOTOR_SPEED_B);
                    }
                    else
                    {
                        Move(270, MOTOR_SPEED_B_FAST);
                    }
                }  
                else 
                {
                    if(Ball_Deg <= 35)
                    {
                        if(Ball_Wait.get_value() >= BALL_WAIT_TIME_LONG)
                        {
                            Move(0, MOTOR_SPEED_B);
                        }
                        else
                        {        
                            Ball_Wait.stop();
                            Ball_Wait.reset();
                            Move(90, MOTOR_SPEED_B);
                        }
                    }
                    else if(Ball_Deg >= 360)
                    {
                        if(Ball_Wait.get_value() >= BALL_WAIT_TIME_LONG)
                        {
                            Move(0, MOTOR_SPEED_B);
                        }
                        else
                        {        
                            Ball_Wait.stop();
                            Ball_Wait.reset();
                            Move(270, MOTOR_SPEED_B);
                        }
                    }
                    else
                    {
                        Ball_Wait.stop();
                        Ball_Wait.reset();
                    
                        if(Ball_Deg < 180)
                        {
                            Move(90, MOTOR_SPEED_B);
                        }
                        else if(Ball_Deg <= 212)
                        {
                            Move(0, 0);
                        }
                        else if(Ball_Deg <= 360)
                        {
                            Move(270, MOTOR_SPEED_B);
                        }
                    }
                }
            }
        }
        else
        {
            Move(0, 0);
        }
    }         
} 