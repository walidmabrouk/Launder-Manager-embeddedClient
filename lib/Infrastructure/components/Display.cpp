#include "Display.h"

Display::Display() : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET),
                     _isMotorRunning(false),
                     _timer(0),
                     _elapsedTime(0)
{
}

void Display::init()
{
  if (!_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  _display.clearDisplay();
  _display.setTextSize(1);
  _display.setTextColor(SSD1306_WHITE);
  _display.display();
}

void Display::updateStatus(bool isMotorRunning, int timer, unsigned long elapsedTime)
{
  _isMotorRunning = isMotorRunning;
  _timer = timer;
  _elapsedTime = elapsedTime;
  render();
}

void Display::render()
{
  _display.clearDisplay();
  _display.setCursor(0, 0);

  // Afficher le titre
  _display.setTextSize(2);
  _display.println(F("Motor Status"));

  // Ligne de séparation
  _display.drawLine(0, 16, SCREEN_WIDTH, 16, SSD1306_WHITE);

  // Retour à la taille normale pour les détails
  _display.setTextSize(1);

  // État du moteur
  _display.setCursor(0, 24);
  _display.print(F("Status: "));
  _display.println(_isMotorRunning ? F("RUNNING") : F("STOPPED"));

  // Timer
  _display.setCursor(0, 34);
  _display.print(F("Timer: "));
  if (_isMotorRunning)
  {
    _display.print(_timer);
    _display.println(F("s"));
  }
  else
  {
    _display.println(F("-"));
  }

  // Temps total de fonctionnement
  _display.setCursor(0, 44);
  _display.print(F("Total time: "));
  _display.print(_elapsedTime);
  _display.println(F("s"));

  _display.display();
}