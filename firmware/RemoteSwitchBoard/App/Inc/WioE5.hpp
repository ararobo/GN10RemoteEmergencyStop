#pragma once
#include <stdint.h>
#include "main.h"
#include "serial_printf.hpp"
class WioE5
{
private:
public:
    void setup();
    void loop();
    void sendAT(const char *cmd);
};
