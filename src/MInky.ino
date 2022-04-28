#include <M5CoreInk.h>
#include <BleKeyboard.h>
#include "icons.h"

typedef enum {
  MODE_MEDIA,
  MODE_PRESENTATION,
  MODE_MAX
} minky_mode_t;

BleKeyboard bleKeyboard("MInky", "Beetix");

void setup()
{
  M5.begin();
  digitalWrite(LED_EXT_PIN,LOW);
  bleKeyboard.begin();
}

void loop()
{
  static minky_mode_t mode = MODE_MEDIA;

  M5.update();
  if( M5.BtnPWR.wasPressed())
  {
    digitalWrite(LED_EXT_PIN,LOW);
    M5.shutdown();
  }
  if( M5.BtnEXT.wasPressed())
  {
    mode = (minky_mode_t) (((int) mode + 1) % MODE_MAX);
    M5.M5Ink.clear();
    switch(mode)
    {
      case MODE_MEDIA:
        M5.M5Ink.drawBuff((uint8_t *)speaker_icon);
        break;
      case MODE_PRESENTATION:
        M5.M5Ink.drawBuff((uint8_t *)dashboard_icon);
        break;
    }
  }
  if (bleKeyboard.isConnected())
  {
    if( M5.BtnDOWN.wasPressed() )
    {
      switch(mode)
      {
        case MODE_MEDIA:
          bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
          break;
        case MODE_PRESENTATION:
          bleKeyboard.write(KEY_DOWN_ARROW);
          break;
      }
    }
    if(M5.BtnUP.wasPressed())
    {
      switch(mode)
      {
        case MODE_MEDIA:
          bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
          break;
        case MODE_PRESENTATION:
          bleKeyboard.write(KEY_UP_ARROW);
          break;
      }
    }
    if (M5.BtnMID.wasPressed())
    {
      switch(mode)
      {
        case MODE_MEDIA:
          bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
          break;
        case MODE_PRESENTATION:
          break;
      }
    }
  }
  delay(10);
}
