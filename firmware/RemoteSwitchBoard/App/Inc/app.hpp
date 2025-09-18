#pragma once
#include <stdint.h>
#include "main.h"
#include "serial_printf.hpp"
class App
{
private:
    uint16_t led_blink_counter = 0;   // LED点滅カウンタ
    uint16_t led_blink_interval = 10; // LED点滅間隔[ms]

    void led_blink();

public:
    App();

    void setup();
    void loop();
};
