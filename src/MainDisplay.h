
#ifndef __MAIN_DISPLAY_H__
#define __MAIN_DISPLAY_H__

#include "Display.h"

class MainDisplay : public Display
{
protected:
    void refreshDisplay();

private:
    unsigned long lastGraphPlotTime = 0;
    uint16_t getAreaX(uint8_t areaNumber);
    uint16_t getAreaY(uint8_t areaNumber);

public:
};

#endif
