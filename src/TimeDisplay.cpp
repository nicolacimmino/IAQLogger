#include "TimeDisplay.h"

void TimeDisplay::onBClick()
{
    // this->mode = (this->mode + 1) % TIME_MODES_COUNT;
    // this->lastModeChangeTime = millis();
}

void TimeDisplay::onBLongPress()
{
    //Status::timeSync();
}

void TimeDisplay::loop()
{
    if (PowerManager::level != PS_LEVEL_0 || Status::shouldAbortLoop())
    {
        return;
    }

    if (millis() - this->lastModeChangeTime > TIME_REVERT_TO_DEFAULT_DELAY_MS)
    {
        this->mode = TIME_MODE_TIME;
    }

    this->displayTime();
}

void TimeDisplay::displayTime()
{
    char buffer[128];

    if (millis() - this->lastRefreshTime < 60000)
    {
        return;
    }

    Peripherals::rtc->refresh();

    sprintf(buffer, "%02i-%02i-%02i %02i:%02i", Peripherals::rtc->day(), Peripherals::rtc->month(), Peripherals::rtc->year(), Peripherals::rtc->hour(), Peripherals::rtc->minute());

    this->printValue(buffer, 0, 120, EPD_WIDTH, 120, (GFXfont *)&sevenSeg70);

    if (Peripherals::sht2x->idDataValid())
    {
        sprintf(buffer, "Temp: %0.2f C", Peripherals::sht2x->temperature);

        this->printValue(buffer, 0, 210, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);

        sprintf(buffer, "Humidity: %d %%RH", Peripherals::sht2x->humidity);

        this->printValue(buffer, EPD_WIDTH / 2, 210, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);
    }
    else
    {
        sprintf(buffer, "Temp: ---");

        this->printValue(buffer, 0, 210, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);

        sprintf(buffer, "Humidity: ---");

        this->printValue(buffer, EPD_WIDTH / 2, 210, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);
    }

    Wire.setClock(80000L);
    if (Peripherals::iaq->hasValue() && Peripherals::iaq->isValid())
    {
        snprintf(buffer, 128, "CO2: %i ppm", Peripherals::iaq->getCO2());
        this->printValue(buffer, 0, 300, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);

        snprintf(buffer, 128, "TVOC: %i ppb", Peripherals::iaq->getTVOC());
        this->printValue(buffer, EPD_WIDTH / 2, 300, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);
    }
    else
    {
        snprintf(buffer, 128, "CO2: ---");
        this->printValue(buffer, 0, 300, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);

        snprintf(buffer, 128, "TVOC: ---");
        this->printValue(buffer, EPD_WIDTH / 2, 300, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);
    }

    snprintf(buffer, 128, "INT: %i", Status::thunderInterferers);
    this->printValue(buffer, 0, 390, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);

    snprintf(buffer, 128, "STK: %i", Status::thunderStrikes);
    this->printValue(buffer, EPD_WIDTH / 2, 390, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);

    snprintf(buffer, 128, "DST: %i km", Status::thunderDistance);
    this->printValue(buffer, 0, 480, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);

    if (Status::barometricPressure > 0)
    {
        snprintf(buffer, 128, "Baro: %i hPa", Status::barometricPressure);
    }
    else
    {
        snprintf(buffer, 128, "Baro: ---", Status::barometricPressure);
    }

    this->printValue(buffer, EPD_WIDTH / 2, 480, EPD_WIDTH / 2, 90, (GFXfont *)&FiraSans);

    this->displayFramebuffer();

    this->lastRefreshTime = millis();
}