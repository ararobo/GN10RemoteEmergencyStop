#include "readWioE5.hpp"
#include "gpio.h"
#include "usart.h"
#include "stm32f3xx_hal.h"
#include "stm32f303x8.h"

// 受信バッファ
uint8_t rx_buf[32] = {0};
volatile uint8_t rx_len = 0;

// USART2受信割り込みコールバック
extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        rx_len = 1; // 1バイト受信（必要に応じて複数バイト対応）
        // 再度受信開始
        HAL_UART_Receive_IT(&huart2, rx_buf, 1);
    }
}

ReadWioE5::ReadWioE5(/* args */)
{
    // USART2受信開始
    HAL_UART_Receive_IT(&huart2, rx_buf, 1);
}

void ReadWioE5::setup()
{
    // 初期化コード
    serial_printf("ReadWioE5 setup complete.\n");
}

void ReadWioE5::loop()
{
    HAL_Delay(1); // Delay for 1 ms
    // USART2受信データがあればserial_printfで出力
    if (rx_len > 0)
    {
        serial_printf("WioE5: %c\n", rx_buf[0]);
        rx_len = 0;
    }
}
