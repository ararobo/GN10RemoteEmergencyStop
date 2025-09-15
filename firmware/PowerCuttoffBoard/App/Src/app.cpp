#include "app.hpp"
#include "gpio.h"

App::App(/* args */)
{
}

void App::setup()
{
    HAL_GPIO_WritePin(RELAY_A_GPIO_Port, RELAY_A_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RELAY_B_GPIO_Port, RELAY_B_Pin, GPIO_PIN_SET);
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
