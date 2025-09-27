#include "WioE5.hpp"
#include "gpio.h"
#include "usart.h"
#include "stm32f3xx_hal.h"
#include "stm32f303x8.h"
#include <cstring>
#include <queue>
#include <string>

// 受信バッファ
uint8_t rx_byte;
char rxBuffer[1024];
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

void WioE5::setup()
{
    // 初期化コード
    HAL_Delay(10);
    serial_printf("ReadWioE5 setup complete.\n");
    // HAL_UART_Transmit(&huart1, (uint8_t *)"WioE5 setup complete.\n", 22, 300);
    HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
}

std::queue<std::string> atCmdQueue;
bool atBusy = false;

void WioE5::loop()
{
    // 応答受信後、次のコマンドを送信
    if (rxReady)
    {
        char rx2buffer[128];
        snprintf(rx2buffer, sizeof(rx2buffer), "WioE5: %s\r\n", rxBuffer);
        HAL_UART_Transmit(&huart1, (uint8_t *)rx2buffer, strlen(rx2buffer), 1000);
        rxReady = false;
        atBusy = false;
        HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
    }
    // キューにコマンドがあり、送信中でなければ送信
    if (!atCmdQueue.empty() && !atBusy)
    {
        std::string cmd = atCmdQueue.front();
        atCmdQueue.pop();
        char buffer[64] = {0};
        snprintf(buffer, sizeof(buffer), "%s\r\n", cmd.c_str());
        HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 1000);
        atBusy = true;
    }
}

void WioE5::sendAT(const char *cmd)
{
    // コマンドをキューに追加
    atCmdQueue.push(cmd);
}
