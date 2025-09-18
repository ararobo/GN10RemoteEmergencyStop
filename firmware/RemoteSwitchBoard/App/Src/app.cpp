#include "app.hpp"
#include "gpio.h"

App::App(/* args */)
{
}

void App::setup()
{
}

void App::loop()
{
    led_blink();
    HAL_Delay(1);
    readWioE5.sendAT("AT");
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
