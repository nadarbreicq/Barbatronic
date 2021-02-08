#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 5

const int signalIn = A0;
const int ledPin = 6;

unsigned int buttonValue[]={1020,840,710,620,545};

Adafruit_NeoPixel led(NUMPIXELS, ledPin, NEO_GRB + NEO_KHZ800);

int signalValue = 0;

void setup() 
{
  Serial.begin(9600);
  led.begin();
}

void loop() 
{
  signalValue = analogRead(signalIn);
  if (signalValue>0)
  {
    unsigned int i = 0;
    while(signalValue<buttonValue[i]) i++;
    
    Serial.print(signalValue);
    Serial.print(" | bouton :");
    Serial.println(i);
    
    led.clear();
    led.setPixelColor(i, led.Color(0,20, 0));
    led.show();

    Keyboard.press(KEY_MEDIA_VOLUME_INC);
    Keyboard.release(KEY_MEDIA_VOLUME_INC);
    
    delay(200);
  }
}
