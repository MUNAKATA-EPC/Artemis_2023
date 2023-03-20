DSR1202 dsr1202(1);

void Output_MotorPower(int A, int B, int C, int D){
    dsr1202.move(-A, -B, -C, -D, false);
}

void Break(){
    dsr1202.move(0, 0, 0, 0, true);
}

void Move(int deg, int power)
{
    double power_A;
    double power_B;
    double power_C;
    double power_D;
    power_A = -sin((deg - 30) / 180.0 * 3.14) * power;
    power_B = sin((deg + 30) / 180.0 * 3.14) * power;
    power_C = -sin((deg - 135) / 180.0 * 3.14) * power;
    power_D = sin((deg + 135) / 180.0 * 3.14) * power;

    double power_max = max(1, max(max(max(abs(power_A), abs(power_B)), abs(power_C)), abs(power_D)));
    double power_per = power / power_max;

    power_A = power_A * power_per;
    power_B = power_B * power_per;
    power_C = power_C * power_per;
    power_D = power_D * power_per;

    power_A += operation_PID;
    power_B -= operation_PID;
    power_C += operation_PID;
    power_D -= operation_PID;

    if( abs(power_A) <= 5 && abs(power_B) <= 5 && 
        abs(power_C) <= 5 && abs(power_D) <= 5)
        Break();
    else
        Output_MotorPower((int)power_A, (int)power_B, (int)power_C, (int)power_D);
}