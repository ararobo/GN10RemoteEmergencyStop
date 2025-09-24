#pragma once
#include <stdint.h>
#include "main.h"
#include "serial_printf.hpp"
#include "WioE5.hpp"
enum WioE5CmdState
{
    Init,
    SentAT,
    SentVER,
    Done
};

class App
{
private:
    uint16_t led_blink_counter = 0;   // LED点滅カウンタ
    uint16_t led_blink_interval = 10; // LED点滅間隔[ms]
    WioE5 wioE5;                      // WioE5制御用
    void led_blink();

public:
    WioE5CmdState wioE5CmdState = Init;
    uint16_t lastRxCount = 0;
    void setup();
    void loop();
};
