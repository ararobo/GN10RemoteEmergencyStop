#include "WioE5.hpp"
#include "gpio.h"
#include "usart.h"
#include "stm32f3xx_hal.h"
#include "stm32f303x8.h"
#include <cstring>
#include <queue>
#include <string>
#include <cctype>
#include <string>

std::string extractNumber(const char *str)
{
    std::string result;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (std::isdigit(static_cast<unsigned char>(str[i])))
        {
            result.push_back(str[i]);
        }
    }
    return result;
}

// 受信バッファ
uint8_t rx_byte;
char rxBuffer[1024];
char oncheck[1024] = "+TEST: RX \"8152743601\"";
char offcheck[1024] = "+TEST: RX \"8152743600\"";
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
    HAL_Delay(1000);
    serial_printf("ReadWioE5 setup complete.\n");
    // HAL_UART_Transmit(&huart1, (uint8_t *)"WioE5 setup complete.\n", 22, 300);
    HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
    HAL_GPIO_WritePin(GPIOB, RELAY_A_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, RELAY_B_Pin, GPIO_PIN_SET);
}

std::queue<std::string> atCmdQueue;
bool atBusy = false;

void WioE5::loop()
{
    if (rxReady)
    {
        char rx2buffer[128];

        // 受信した文字列から数値だけを抽出
        std::string num = extractNumber(rxBuffer);

        // チェック用の数値
        std::string onNum = extractNumber(oncheck);   // "8152743601"
        std::string offNum = extractNumber(offcheck); // "8152743600"

        if (num == onNum)
        {
            serial_printf("on\n");
            HAL_GPIO_WritePin(GPIOB, RELAY_A_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB, RELAY_B_Pin, GPIO_PIN_RESET);
        }
        else if (num == offNum)
        {
            serial_printf("off\n");
            HAL_GPIO_WritePin(GPIOB, RELAY_A_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB, RELAY_B_Pin, GPIO_PIN_SET);
        }

        snprintf(rx2buffer, sizeof(rx2buffer), "WioE5: %s\r\n", rxBuffer);
        HAL_UART_Transmit(&huart1, (uint8_t *)rx2buffer, strlen(rx2buffer), 1000);

        rxReady = false;
        atBusy = false;
        HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
    }

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
