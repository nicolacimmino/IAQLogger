
#include "PowerManager.h"
#include "ModeManager.h"

unsigned long PowerManager::lastUserInteractionTime = millis();
uint8_t PowerManager::level = PS_LEVEL_0;
uint8_t PowerManager::previousLevel = PS_LEVEL_0;

bool PowerManager::enterL0()
{
    DIAGNOSTIC("PMA,L0,attempt")

    uint8_t previousLevel = PowerManager::level;

    PowerManager::level = PS_LEVEL_0;
    Peripherals::connectWiFi();

    uint8_t count = 0;
    bool blueLED = true;
    while (!Peripherals::isWiFiConnected() && count < 40)
    {
        count++;
        DIAGNOSTIC("PMA,L0,wifi,wait")
        delay(500);
        Peripherals::setBlueLed(blueLED = !blueLED);
    }

    if (!Peripherals::isWiFiConnected())
    {
        DIAGNOSTIC("PMA,L0,wifi,failed")

        Peripherals::setBlueLed(false);

        PowerManager::level = previousLevel;

        return false;
    }

    Peripherals::setBlueLed(true);

    WiFi.hostname("iaqm");

    if (!MDNS.begin("iaqm"))
    {
        DIAGNOSTIC("PMA,L0,mdns,failed");

        PowerManager::level = previousLevel;

        return false;
    }
    DIAGNOSTIC("PMA,L0,mdns,ok");

    return true;
}

void PowerManager::enterL1()
{
    if (PowerManager::level == PS_LEVEL_1)
    {
        return;
    }

    DIAGNOSTIC("PMA,L1");

    Peripherals::setRedLed(true);

    PowerManager::level = PS_LEVEL_1;
}

void PowerManager::enterL2()
{
    if (PowerManager::level == PS_LEVEL_2)
    {
        return;
    }

    DIAGNOSTIC("PMA,L2");

    Peripherals::setRedLed(false);

    PowerManager::level = PS_LEVEL_2;

    gpio_wakeup_enable(PIN_BUTTON_A, GPIO_INTR_HIGH_LEVEL);
    gpio_wakeup_enable(PIN_BUTTON_B, GPIO_INTR_HIGH_LEVEL);
    gpio_wakeup_enable(PIN_BUTTON_C, GPIO_INTR_HIGH_LEVEL);
    gpio_wakeup_enable(PIN_BUTTON_D, GPIO_INTR_HIGH_LEVEL);
    esp_sleep_enable_gpio_wakeup();
    esp_sleep_enable_timer_wakeup(60 * 1000000); // 60s
    esp_light_sleep_start();
}

void PowerManager::enterL3()
{
    DIAGNOSTIC("PMA,L3");

    PowerManager::level = PS_LEVEL_3;

    ModeManager::currentDisplay->showShutdown();

    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_deep_sleep_start();
}

void PowerManager::loop()
{
}

void PowerManager::onUserInteratcion()
{
    lastUserInteractionTime = millis();
}
