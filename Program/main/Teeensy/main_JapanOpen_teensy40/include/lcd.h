
void DrawString(int x, int y, const char *text, const uint8_t* font)
{
    u8g2.clearBuffer();
    u8g2.setFont(font);
    u8g2.drawStr(x, y, text);
    u8g2.sendBuffer();
}

void Initialize_LCD()
{
    u8g2.begin(); //LCD初期化
    u8g2.setFlipMode(0);  //反転は1(通常表示は0)
    u8g2.setContrast(0);
}