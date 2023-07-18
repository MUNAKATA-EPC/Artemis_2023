namespace Defencer
{
    #define MOTOR_SPEED_B 15
    #define MOTOR_SPEED_B_LATE 10
    #define MOTOR_SPEED_B_FAST 18
    #define BALL_WAIT_TIME_SHORT 750
    #define BALL_WAIT_TIME_LONG 1250

    Timer Line_Move;
    Timer Ball_Wait;

    int Cam_Data_Deg;
    int Cam_Data_Dis;
    int Line_Move_Deg;

    float gain[3] = {0.45, 0, 12};

    void Main_Program(bool yellow)
    {
        PID_loop(Gyro_Deg, gain);

        Cam_Data_Deg = yellow ? Cam_GoalY_Deg : Cam_GoalB_Deg;
        Cam_Data_Dis = yellow ? Cam_GoalY_Dis : Cam_GoalB_Dis;

        Ball_Wait.tick();
        Line_Move.tick();

        if(Line_Value != 510)
        {
            Line_Move.reset();
            Line_Move.start();
            Line_Move_Deg = Line_Value;
        }

        if(Line_Move.isticking())
        {
            if(Line_Move.get_value() <= 200)
            {
                Move((Line_Move_Deg + 360 - 180) % 360, MOTOR_SPEED_B_FAST);
            }
            else
            {
                Line_Move.reset();
            }
        }
        else
        {
            if(Ball_Deg < 510)//ボールが見えているか
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
                        if(Ball_Deg <= 22)
                        {
                            if(Ball_Wait.get_value() >= BALL_WAIT_TIME_SHORT)
                            {
                                Move(0, MOTOR_SPEED_B_FAST);
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
                                Move(0, MOTOR_SPEED_B_FAST);
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
                            
                            if(Ball_Deg <= 78)
                            {
                                Move(90, MOTOR_SPEED_B);
                            }
                            else if(Ball_Deg <= 122)
                            {
                                Move(135, MOTOR_SPEED_B);
                            }
                            else if(Ball_Deg <= 168)
                            {
                                Move(90, MOTOR_SPEED_B);
                            }
                            else if(Ball_Deg <= 202)
                            {
                                Move(0, 0);
                            }
                            else if(Ball_Deg <= 258)
                            {
                                Move(270, MOTOR_SPEED_B);
                            }
                            else if(Ball_Deg <= 310)
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
                    if(Ball_Deg <= 130)
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
                        if(Ball_Deg <= 30)
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
                if(Cam_Data_Deg >= 255)
                {
                        Move(180, MOTOR_SPEED_B);
                } 

                else
                {
                    if(Cam_Data_Dis >= 42)
                    {
                        Move(Cam_Data_Deg * 2, MOTOR_SPEED_B);
                    }
                    else
                    {
                        if(Cam_Data_Dis <= 60)
                        {
                            Move(0, MOTOR_SPEED_B_LATE);
                        }
                        else
                        {
                            if(Cam_Data_Deg >= 65 && Cam_Data_Deg <= 85)
                            {
                                Move(0, 0);
                            }
                            else if(Cam_Data_Deg >= 70)
                            {
                                Move(90, MOTOR_SPEED_B);
                            }
                            else if(Cam_Data_Deg <= 121)
                            {
                                Move(270, MOTOR_SPEED_B);
                            }
                            else if(Cam_Data_Deg >= 50 || Cam_Data_Deg <= 134)
                            {
                                Move(0, MOTOR_SPEED_B);
                            }  
                        }   
                    }
                }
            }         
        } 
    }
} 