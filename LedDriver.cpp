//*****************************************************************************
// LedDriver.cpp
//*****************************************************************************

#include "LedDriver.h"

LedDriver::LedDriver() {
    strip = new Adafruit_NeoPixel(NUMPIXELS, PIN_LEDS_DATA, NEOPIXEL_TYPE);
    strip->begin();
}

LedDriver::~LedDriver() {
}

void LedDriver::clear() {
    strip->clear();
}

void LedDriver::show() {
    strip->show();
}

void LedDriver::setPixel(uint8_t x, uint8_t y, uint8_t color, uint8_t brightness) {
    setPixel(x + y * 11, color, brightness);
}

void LedDriver::setPixel(uint8_t num, uint8_t color, uint8_t brightness) {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
      
    if (color != MOOD){
      red = brightness * 0.0039 * defaultColors[color].red;
      green = brightness * 0.0039 * defaultColors[color].green;
      blue = brightness * 0.0039 * defaultColors[color].blue;
    } else {
      red = brightness * 0.0039 * getRed(m_wheelColor);
      green = brightness * 0.0039 * getGreen(m_wheelColor);
      blue = brightness * 0.0039 * getBlue(m_wheelColor);
    }

//Serial.println( "red: " + String(red) + " green: " + String(green) + " blue: " + String(blue));

#ifdef NEOPIXEL_RGBW
    uint8_t white = 0xFF;
    if (red < white) white = red;
    if (green < white) white = green;
    if (blue < white) white = blue;
    strip->setPixelColor(ledMap[num], red - white, green - white, blue - white, white);
#endif

#ifdef NEOPIXEL_RGB
    strip->setPixelColor(ledMap[num], red, green, blue);
#endif

    return;
}

void LedDriver::setPixelRGB(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue)
{
    setPixelRGB(x + y * 11, red, green, blue);
}

void LedDriver::setPixelRGB(uint8_t num, uint8_t red, uint8_t green, uint8_t blue )
{
#ifdef NEOPIXEL_RGBW
    uint8_t white = 0xFF;
    if (red < white) white = red;
    if (green < white) white = green;
    if (blue < white) white = blue;
    strip->setPixelColor(ledMap[num], red - white, green - white, blue - white, white);
#endif

#ifdef NEOPIXEL_RGB
    strip->setPixelColor(ledMap[num], red, green, blue);
#endif
}

void LedDriver::updateColorWheel() {
  m_wheelPos += 2;
  m_wheelColor = wheel(m_wheelPos);
}

uint32_t LedDriver::wheel(uint8_t wheelPos) {
  if (wheelPos < 85) {
    return getColor(wheelPos * 3, 255 - wheelPos * 3, 0);
  } else if (wheelPos < 170) {
    wheelPos -= 85;
    return getColor(255 - wheelPos * 3, 0, wheelPos * 3);
  } else {
    wheelPos -= 170;
    return getColor(0, wheelPos * 3, 255 - wheelPos * 3);
  }
}

uint32_t LedDriver::getColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t) r << 16) | ((uint32_t) g << 8) | b;
}
