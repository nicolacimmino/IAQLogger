
#ifndef __TEMPERATURE_LOGGER_CONFIG_H__
#define __TEMPERATURE_LOGGER_CONFIG_H__

#define DIAGNOSTIC_ENABLE

#ifdef DIAGNOSTIC_ENABLE
#define DIAGNOSTIC(S)                      \
    Serial.printf("%d,%s\n", millis(), S); \
    delay(100);
#else
#define DIAGNOSTIC(S) // do nothing
#endif

#define SHT2x_ADDR 0x40
#define IAQ_ADDR 0x5A
#define RTC_ADDR 0x68

#define PIN_BUTTON_A 2
#define PIN_BUTTON_B 4
#define PIN_BUTTON_C 35
#define PIN_BUTTON_D 32

#define PIN_BUTTON_A_SEL GPIO_SEL_2
#define PIN_BUTTON_B_SEL GPIO_SEL_4
#define PIN_BUTTON_C_SEL GPIO_SEL_35
#define PIN_BUTTON_D_SEL GPIO_SEL_32

#define PIN_LED_RED 5
#define PIN_LED_YELLOW 21 
#define PIN_LED_BLUE 22

#define PIN_SWITCH_SENSE 23

#define PIN_SCL 18
#define PIN_SDA 19

#define PIN_VBAT_SENSE 34

#define DISPLAY_MODES 1

#define LIGHTNING_INT 0x08
#define DISTURBER_INT 0x04
#define NOISE_INT 0x01

#define SMALL_STATUS_SCREEN_FONT &Font8
#define BIG_POWER_DOWN_SCREEN_FONT &Font24

#define MAIN_DISPLAY_MID_FONT &Font16
#define MAIN_DISPLAY_LARGE_FONT &Font24
#define MAIN_DISPLAY_LABEL_FONT &Font12
#define MAIN_DISPLAY_SMALL_FONT &Font12

#define TEXT_BUFFER_SIZE 64

#define NO_VALUE -9999

#define MAX_POLLEN_COUNTS 16

#define PIN_INT 13

#define POWER_SAVE_TIMEOUT_MS 20000

#define MAX_LOG_FILES 15

#endif