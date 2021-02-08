#include <Adafruit_NeoPixel.h>
#include "Keyboard.h"

class MacroKey 
{
  
  private:

    byte signalPin = A0;
    byte ledPin = 9;
    byte numKey = 0;

    unsigned int macroKeyShortcut[20] ;
    unsigned int macroKeyValue[20] ;
    uint32_t macroKeyColor[20] ;

    Adafruit_NeoPixel * led;

  public:
  
    MacroKey(byte signalPin,byte ledPin) 
    {
      this->signalPin = signalPin;
      this->ledPin = ledPin;
    }

    void addKey(unsigned int keyShortcut, unsigned int keyValue, uint32_t keyColor)
    {
      macroKeyShortcut[numKey]  = keyShortcut;
      macroKeyValue[numKey]     = keyValue;
      macroKeyColor[numKey]     = keyColor;
      
      numKey++;
    }
    void initMacroKey()
    {
      led = new Adafruit_NeoPixel(numKey, ledPin, NEO_GRB + NEO_KHZ800); 
      led->begin();
      Keyboard.begin();
      initLeds(3);
    }
    void initLeds(byte cycles)
    {
      unsigned int bdelay = 40;
      for (int k = 0; k < cycles; k++)
      {
        for (int j = 0; j < numKey; j++)
        {
          setKeyLed(j, led->Color(100, 100, 100));
          delay(bdelay);
        }
        for (int j = numKey; j >= 0; j--)
        {
          setKeyLed(j-1, led->Color(100, 100, 100));
          delay(bdelay);
        }
      }
    }
    void setKeyLed(unsigned int ledPosition, uint32_t ledColor)
    {
      led->clear();
      led->setPixelColor(ledPosition, ledColor);
      led->show(); 
    }
    void pressShortcut(unsigned int keyValue, int pressTime)
    {
      Keyboard.press(keyValue);
      delay(pressTime);
      Keyboard.release(keyValue);
    }
    void checkMacroKey()
    {
      unsigned int signalValue = analogRead(signalPin);
      if (signalValue > 10)
      {
        unsigned int i = 0;
        while (signalValue < macroKeyValue[i]) i++;
        
        Serial.print(macroKeyValue[i]);
        Serial.print(" | :");
        Serial.print(signalValue);
        Serial.print(" | bouton :");
        Serial.println(i);
            
        setKeyLed(i, led->Color(100, 100, 100));
    
        pressShortcut(macroKeyShortcut[i],50);
    
        while (analogRead(signalPin) > 10) delay(200);
    
        setKeyLed(i, macroKeyColor[i]); 
      }
      delay(50);
    }
    void setKeyBrightness(int brightValue)
    {
      led->setBrightness(brightValue);
    }
};
