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
    WioE5 wioE5; // WioE5制御用

public:
    WioE5CmdState wioE5CmdState = Init;
    uint16_t lastRxCount = 0;
    int check = 0;
    int operation = 0;
    void setup();
    void loop();
};
