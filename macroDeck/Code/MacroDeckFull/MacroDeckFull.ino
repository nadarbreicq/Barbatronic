#include <Adafruit_NeoPixel.h>

#define NUMLEDS 5

#define KEYCODE_F13 0x68
#define KEYCODE_F14 0x69
#define KEYCODE_F15 0x6A
#define KEYCODE_F16 0x6B
#define KEYCODE_F17 0x6C
#define KEYCODE_F18 0x6D
#define KEYCODE_F19 0x6E
#define KEYCODE_F20 0x6F
#define KEYCODE_F21 0x70
#define KEYCODE_F22 0x71
#define KEYCODE_F23 0x72
#define KEYCODE_F24 0x73

const int signalIn = A0;
const int ledPin = 6;

const unsigned int shortKey[]     = {KEY_F13, KEY_F14,  KEY_F15,  KEY_F16,  KEY_F17};
const unsigned int buttonValue[]  = {1020,    840,      710,      620,      545};
uint32_t colorKey[] = {0,0,0,0,0};

Adafruit_NeoPixel led(NUMLEDS, ledPin, NEO_GRB + NEO_KHZ800);

int signalValue = 0;


void initLeds(byte cycles);
void setKeyLed(unsigned int ledPosition, uint32_t ledColor);

void setup()
{
  Serial.begin(9600);
  led.begin();

  initLeds(3);

  colorKey[0] = led.Color(5, 0, 0);
  colorKey[1] = led.Color(0, 5, 0);
  colorKey[2] = led.Color(0, 0, 5);
  colorKey[3] = led.Color(5, 5, 0);
  colorKey[4] = led.Color(0, 5, 5);

}

void loop()
{
  signalValue = analogRead(signalIn);
  if (signalValue > 10)
  {
    unsigned int i = 0;
    while (signalValue < buttonValue[i]) i++;

    /*
    Serial.print(signalValue);
    Serial.print(" | bouton :");
    Serial.println(i);
    */
    
    setKeyLed(i, led.Color(3, 3, 3));

    Keyboard.press(shortKey[i]);
    Keyboard.release(shortKey[i]);

    delay(200);

    while (analogRead(signalIn) > 10) delay(200);

    setKeyLed(i, colorKey[i]);
    
  }
  delay(50);
}

void setKeyLed(unsigned int ledPosition, uint32_t ledColor)
{
    led.clear();
    led.setPixelColor(ledPosition, ledColor);
    led.show();
}

void initLeds(byte cycles)
{
  unsigned int bdelay = 40;
  
  for (int k = 0; k < cycles; k++)
  {
    for (int j = 0; j < NUMLEDS; j++)
    {
      setKeyLed(j, led.Color(1, 1, 1));
      delay(bdelay);
    }
    for (int j = NUMLEDS; j >= 0; j--)
    {
      setKeyLed(j-1, led.Color(1, 1, 1));
      delay(bdelay);
    }
  }
}
