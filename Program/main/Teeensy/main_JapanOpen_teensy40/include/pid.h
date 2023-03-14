/// @brief pid制御を提供します。
/// @param value pid制御をしたい値
/// @param max_value 
/// @param goal_value 目標値
/// @param gains 各要素のゲイン(倍率)
/// @return 
int pid(int value, int max_value, int goal_value, int gains[3])
{
    //比例、積分、微分
    int operations[3];
    int val_P = value;
    int val_I;
    int val_D;
    if(val_P >= max_value / 2)
    {
        //-(max_value / 2) ~ (max_value / 2)
        val_P = value - 360;
    }

    operations[0] = val_P * gains[0];
    operations[1] = val_I * gains[1];
    operations[2] = val_D * gains[2];

    return operations[0] + operations[1] + operations[2];
}