#include "readWioE5.hpp"
#include "gpio.h"
#include "usart.h"
#include "stm32f3xx_hal.h"
#include "stm32f303x8.h"
#include <cstring>

// 受信バッファ
uint8_t rx_byte;
char rxBuffer[128];
uint16_t rxIndex = 0;
volatile bool rxReady = false;

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        if (rx_byte == '\n') // 改行で1行終わり
        {
            rxBuffer[rxIndex] = '\0';
            rxReady = true;
            rxIndex = 0;
        }
        else
        {
            if (rxIndex < sizeof(rxBuffer) - 1)
            {
                rxBuffer[rxIndex++] = rx_byte;
            }
        }
        // 次の受信をセット
        HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
    }
}

ReadWioE5::ReadWioE5(/* args */)
{
    HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
}

void ReadWioE5::setup()
{
    // 初期化コード
    serial_printf("ReadWioE5 setup complete.\n");
}

void ReadWioE5::loop()
{
    if (rxReady)
    {
        serial_printf("WioE5: %s\n", rxBuffer);
        rxReady = false;
    }
}

void ReadWioE5::sendAT(const char *cmd)
{
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%s\r\n", cmd);
    HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 100);
}
