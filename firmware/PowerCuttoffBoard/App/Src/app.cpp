#include "app.hpp"
#include "gpio.h"

App::App(/* args */)
{
}

void App::setup()
{
    HAL_GPIO_WritePin();
}

void App::loop()
{
    led_blink();
    HAL_Delay(1);
}

void App::led_blink()
{
    led_blink_counter++;
    if (led_blink_counter >= led_blink_interval)
    {
        HAL_GPIO_TogglePin(LED_DEBUG_GPIO_Port, LED_DEBUG_Pin); // LEDをトグル
        led_blink_counter = 0;
    }
}
