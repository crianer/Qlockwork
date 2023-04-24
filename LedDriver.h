//*****************************************************************************
// LedDriver.h
//*****************************************************************************

#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <Adafruit_NeoPixel.h>
#include "Configuration.h"
#include "Colors.h"

class LedDriver {
public:
    LedDriver();
    ~LedDriver();

    void clear();
    void show();
    void setPixel(uint8_t x, uint8_t y, uint8_t color, uint8_t brightness);
    void setPixel(uint8_t num, uint8_t color, uint8_t brightness);
    void updateColorWheel();

private:
    Adafruit_NeoPixel* strip;
    uint8_t m_wheelPos;
    uint32_t m_wheelColor;
    uint32_t wheel(uint8_t wheelPos);
    uint32_t getColor(uint8_t r, uint8_t g, uint8_t b);

};

#endif
