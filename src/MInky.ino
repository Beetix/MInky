#include <M5CoreInk.h>
#include <BleKeyboard.h>
#include "icons.h"

BleKeyboard bleKeyboard("MInky", "Beetix");

void setup()
{
  M5.begin();
  digitalWrite(LED_EXT_PIN,LOW);
  M5.M5Ink.clear();
  M5.M5Ink.drawBuff((uint8_t *)speaker_icon);
  bleKeyboard.begin();
}

void loop()
{
  M5.update();
  if( M5.BtnPWR.wasPressed())
  {
      digitalWrite(LED_EXT_PIN,LOW);
      M5.shutdown();
  }
  if (bleKeyboard.isConnected())
  {
    if( M5.BtnDOWN.wasPressed() )
    {
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
    if(M5.BtnUP.wasPressed())
    {
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    }
    if (M5.BtnMID.wasPressed())
    {
      bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    }
  }
  delay(10);
}
