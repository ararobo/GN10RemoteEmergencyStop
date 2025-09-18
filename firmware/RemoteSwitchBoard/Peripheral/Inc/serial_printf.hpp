#pragma once
#include <string>
#include <vector>
#include <cstdio>
#include "usart.h"

#define LOG_INFO "[INFO]  "
#define LOG_DEBUG "[DEBUG] "
#define LOG_ERROR "[ERROR] "
#define LOG_WARNING "[WARN]  "

#define DEBUG_MODE true

template <typename... Args>
void serial_printf(const std::string &fmt, Args... args)
{
    // フォーマットされた文字列の長さを取得
    size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args...);
    // バッファを作成してフォーマットされた文字列を格納
    std::vector<char> buf(len + 1);
    std::snprintf(&buf[0], len + 1, fmt.c_str(), args...);
    // ヌル終端された文字列をUARTに送信
    HAL_UART_Transmit(&huart1, (uint8_t *)&buf[0], len, 0xFF);
}
