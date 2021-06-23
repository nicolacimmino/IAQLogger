#include <Arduino.h>
#include <Wire.h>

#include <FS.h>
#include <SPIFFS.h>

#include "src/Button.h"
#include "src/Peripherals.h"
#include "src/ModeManager.h"

void onButtonPress()
{
    PowerManager::onUserInteratcion();

    ModeManager::currentDisplay->loop();
}

void onButtonAClick()
{
    DIAGNOSTIC("BTN,A");

    ModeManager::changeMode();
    onButtonPress();
}

void onButtonBClick()
{
    DIAGNOSTIC("BTN,B");

    ModeManager::currentDisplay->onBClick();
    onButtonPress();
}

void onButtonCClick()
{
    DIAGNOSTIC("BTN,C");

    onButtonPress();
}

void onButtonALongPress()
{
    DIAGNOSTIC("BTN,AL");

    // ModeManager::currentDisplay->powerDown();
    // PowerManager::enterL3();
}

void setup()
{
    DIAGNOSTIC("SETUP")

    if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER)
    {
        delay(500);

        Serial.begin(115200);

        DataLog::instance()->setup();
        Peripherals::setup();
        ModeManager::setup();

        snprintf(Peripherals::buffer, TEXT_BUFFER_SIZE, "SPIFF,%d,%d", SPIFFS.usedBytes(), SPIFFS.totalBytes());
        DIAGNOSTIC(Peripherals::buffer)

        Peripherals::buttonA->registerOnClickCallback(onButtonAClick);
        Peripherals::buttonA->registerOnLongPressCallback(onButtonALongPress);
        Peripherals::buttonB->registerOnClickCallback(onButtonBClick);
        Peripherals::buttonC->registerOnClickCallback(onButtonCClick);
    }

    // Peripherals::rtc->set(0, 55, 15, 7, 20, 6, 21);
}

void loop()
{
    PowerManager::enterL1();

    PowerManager::loop();
    Peripherals::loop();
    ModeManager::currentDisplay->loop();

    DataLog::instance()->loop();

    PowerManager::enterL2();
}
