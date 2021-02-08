
MacroKey keyboard = MacroKey(A0,9);

void setup()
{
  Serial.begin(9600);
  keyboard.addKey(KEY_F13,1020, 0x00ff00);
  keyboard.addKey(KEY_F14,840 , 0xffff00);
  keyboard.addKey(KEY_F15,710 , 0x00ffff);
  keyboard.addKey(KEY_F16,620 , 0xff0000);
  keyboard.addKey(KEY_F17,540 , 0xff00ff);

  keyboard.initMacroKey();

  keyboard.setKeyBrightness(20);
}

void loop()
{
  keyboard.checkMacroKey();
}
