#define PID_MAX 8

int operation_PID;
int deviation;
int old_deviation;

/// @brief pid制御を提供します。
/// @param value pid制御をしたい値
/// @param max_value 
/// @param gains 各要素のゲイン(倍率)
/// @return 
int get_pid_value(int value, int max_value, float gains[3])
{
    //比例、積分、微分
    int operations[3];
    int val_P = value;
    int val_I = 0;
    int val_D = 0;
    if(val_P >= max_value / 2)
    {
        //-(max_value / 2) ~ (max_value / 2)
        val_P = value - (max_value);
    }

    deviation = val_P;
    val_D = deviation - old_deviation;
    old_deviation = deviation;

    operations[0] = val_P * gains[0];
    operations[1] = val_I * gains[1];
    operations[2] = val_D * gains[2];

    return operations[0] + operations[1] + operations[2];
}

void PID_loop(int value, float gains[3])
{
    operation_PID = get_pid_value(value, 180, gains);

    if(operation_PID >= PID_MAX)
        operation_PID = PID_MAX; 
    else if(operation_PID <= -PID_MAX)
        operation_PID = -PID_MAX;
}
