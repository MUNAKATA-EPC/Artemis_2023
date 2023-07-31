Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 2, NEO_GRB + NEO_KHZ800);

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
long firstPixelHue = 0;
Timer tim_rainbow;

void rainbow(int wait) {
    tim_rainbow.tick();
    tim_rainbow.start();
    if(tim_rainbow.get_value() >= wait)
    {
        strip.rainbow(firstPixelHue);
        strip.show();
        firstPixelHue += 256;
        tim_rainbow.reset();
        tim_rainbow.start();

        if(firstPixelHue >= 5 * 65536)
        {
            firstPixelHue = 0;
        }

    }
}

void Bright(uint32_t color){
  strip.clear();
  for(int i = 0; i < 16; i++){
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void Initialize_NeoPixel()
{
    strip.begin();
    strip.setBrightness(20);
    strip.show();
}

void Process_NeoPixel()
{
    rainbow(10);
}

void ChangeBrightness(int val)
{
    strip.setBrightness(val);
}

void NeoPixel_Off(){
    for(int i = 0; i < 16; i++)
    {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}
