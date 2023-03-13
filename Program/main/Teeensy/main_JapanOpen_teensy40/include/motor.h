void Output_MotorPower(int A, int B, int C, int D){
    dsr1202.move(A, B, C, D, false);
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
    power_A = -sin(radians(deg - 30)) * power;
    power_B = sin(radians(deg + 30)) * power;
    power_C = -sin(radians(deg - 135)) * power;
    power_D = sin(radians(deg + 135)) * power;

    double power_max = max(max(max(abs(power_A), abs(power_B)), abs(power_C)), abs(power_D));
    double power_per = power / power_max;

    power_A = power_A * power_per;
    power_B = power_B * power_per;
    power_C = power_C * power_per;
    power_D = power_D * power_per;

    Output_MotorPower((int)power_A, (int)power_B, (int)power_C, (int)power_D);
}