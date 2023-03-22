namespace PID_PROG
{
    float gains_gyro[3] = {0.60, 0, 2};
    
    void Main_Program()
    {
        PID_loop(Gyro_Deg / 2, gains_gyro);

        Move(0, 0);
    }
}

namespace LINE_PROG
{
    float gains_gyro[3] = {0.60, 0, 2};

    void Main_Program()
    {
        PID_loop(Gyro_Deg / 2, gains_gyro);

        if(Line_Value == -1)
        {
            Move(0, 0);
        }
    }
}