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
    DrawString(0, 30, "unko", u8g2_font_ncenB10_tr);
}
