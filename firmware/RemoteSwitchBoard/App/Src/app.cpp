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
    wioE5.sendAT("AT+CLASS=C");
    wioE5.sendAT("AT+MODE=TEST");
    wioE5.sendAT("AT+ID=DevEui");
    wioE5.sendAT("AT+ID=AppEui");
    wioE5.sendAT("AT+TEST=RFCFG,923,SF12,125,12,15,14,ON,OFF,OFF");
}

void App::loop()
{
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, emstop_Pin);

    // 1秒ごとの AT コマンド送信（重複防止）
    static uint32_t lastSendTick = 0;
    uint32_t now = HAL_GetTick();

    if (now - lastSendTick >= 1500) // 1000ms = 1秒
    {
        lastSendTick = now; // 先に更新して重複送信を防止
        if (state == GPIO_PIN_SET)
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
