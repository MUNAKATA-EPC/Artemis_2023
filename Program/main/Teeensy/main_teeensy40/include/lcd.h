#define LEFT_BUTTON 33
#define RIGHT_BUTTON 32
#define START_BUTTON 30
#define STOP_BUTTON 31

U8G2_ST7565_AK_AQM1248_F_4W_HW_SPI u8g2(U8G2_R0, 10, 34, 35);

void DrawString(int x, int y, const char *text, const uint8_t* font)
{
    u8g2.clearBuffer();
    u8g2.setFont(font);
    u8g2.drawStr(x, y, text);
    u8g2.sendBuffer();
}

void Setup_LCD()
{
    u8g2.begin();
    u8g2.setFlipMode(1);
}

void Process_LCD()
{
    int unko = analogRead(6);
    Serial.println(unko);
}
