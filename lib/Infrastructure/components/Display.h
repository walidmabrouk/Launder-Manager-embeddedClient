#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display
{
private:
  static const int SCREEN_WIDTH = 128;
  static const int SCREEN_HEIGHT = 64;
  static const int OLED_RESET = -1;
  static const int SCREEN_ADDRESS = 0x3C;

  Adafruit_SSD1306 _display;
  bool _isMotorRunning;
  int _timer;
  unsigned long _elapsedTime;

  void render();

public:
  Display();
  void init();
  void updateStatus(bool isMotorRunning, int timer, unsigned long elapsedTime);
};

#endif // DISPLAY_H