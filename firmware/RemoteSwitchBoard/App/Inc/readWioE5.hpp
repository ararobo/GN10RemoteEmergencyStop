#pragma once
#include <stdint.h>
#include "main.h"
#include "serial_printf.hpp"
class ReadWioE5
{
private:
public:
    ReadWioE5();
    void setup();
    void loop();
    void sendAT(const char *cmd);
};
