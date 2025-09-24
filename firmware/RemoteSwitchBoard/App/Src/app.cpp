#include "app.hpp"
#include "gpio.h"

void App::setup()
{
    wioE5.sendAT("AT");
    wioE5.sendAT("AT+VER?");
    wioE5.sendAT("AT+FDEFAULT");
    wioE5.sendAT("AT+LW=VER,V103");
    wioE5.sendAT("AT+DR=JP920");
    wioE5.sendAT("AT+MODE=TEST");
    wioE5.sendAT("AT+ID=DevEui");
    wioE5.sendAT("AT+ID=AppEui");
    wioE5.sendAT("");
    wioE5.sendAT("");
    wioE5.sendAT("");
    wioE5.sendAT("");
    wioE5.sendAT("");
}

void App::loop()
{
    wioE5.loop(); // WioE5の受信処理を毎回呼び出す
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
