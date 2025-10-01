#include "app.hpp"
#include "gpio.h"

void App::setup()
{
    // Wio E5 モジュールの初期化
    wioE5.sendAT("AT");
    wioE5.sendAT("AT+VER?");
    wioE5.sendAT("AT+FDEFAULT");
    wioE5.sendAT("AT+LW=VER,V103");
    wioE5.sendAT("AT+DR=JP920");
    wioE5.sendAT("AT+CLASS=C, SAVE");
    wioE5.sendAT("AT+LW=JDC, ON");
    wioE5.sendAT("AT+MODE=TEST");
    wioE5.sendAT("AT+ID=DevEui");
    wioE5.sendAT("AT+ID=AppEui");
    wioE5.sendAT("AT+TEST=RFCFG,923,SF7,125,12,15,14,OFF,OFF,OFF");
}

void App::loop()
{
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, emstop_Pin);
    if (state == GPIO_PIN_RESET)
    {
        check = 1;
    }
    else
    {
        check = 0;
    }
    if (operation != check)
    {
        if (state == GPIO_PIN_RESET)
        {
            wioE5.sendAT("AT+TEST=TXLRPKT,\"8152743601\"");
            operation = 1;
        }
        else
        {
            wioE5.sendAT("AT+TEST=TXLRPKT,\"8152743600\"");
            operation = 0;
        }
    }
}
