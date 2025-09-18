#include "app.hpp"
#include "gpio.h"

void App::setup()
{
    wioE5.sendAT("AT");
    wioE5.sendAT("AT+VER?");
}

void App::loop()
{
    led_blink();
}

void App::led_blink()
{
    led_blink_counter++;
    if (led_blink_counter >= led_blink_interval)
    {
        HAL_GPIO_TogglePin(LED_6_GPIO_Port, LED_6_Pin); // LEDをトグル
        led_blink_counter = 0;
    }
}
