/*
 * This file is part of the libohiboard examples project.
 *
 * Copyright (C) 2020 A. C. Open Hardware Ideas Lab
 *
 * Authors:
 *   Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "libohiboard.h"

char receivedChar = '\0';
bool send = FALSE;

void callbackRx (struct _Uart_Device* dev, void* obj)
{
    (void)obj;

    uint8_t c = 0;
    Uart_read(dev,&c,100);
    receivedChar = c;
    send = TRUE;

}

int main(void)
{
    Clock_Config clkConfig =
    {
        .source = CLOCK_INTERNAL_HSI,

        .sysSource = CLOCK_SYSTEMSOURCE_HSI,

        .hsiState = CLOCK_OSCILLATORSTATE_ON,
        .lsiState = CLOCK_OSCILLATORSTATE_OFF,
        .lseState = CLOCK_OSCILLATORSTATE_OFF,

        .output = CLOCK_OUTPUT_SYSCLK | CLOCK_OUTPUT_HCLK | CLOCK_OUTPUT_PCLK1 | CLOCK_OUTPUT_PCLK2,
        .ahbDivider = CLOCK_AHBDIVIDER_1,
        .apb1Divider = CLOCK_APBDIVIDER_1,
        .apb2Divider = CLOCK_APBDIVIDER_1,
    };

    Uart_Config uartConfig =
    {
        .clockSource = UART_CLOCKSOURCE_SYSCLK,
        .mode = UART_MODE_BOTH,

        .rxPin = UART_PINS_PA10,
        .txPin = UART_PINS_PA9,

        .baudrate = 115200,

        .dataBits = UART_DATABITS_EIGHT,
        .flowControl = UART_FLOWCONTROL_NONE,
        .parity = UART_PARITY_NONE,
        .stop = UART_STOPBITS_ONE,
    };

    // Initialize clock...
    Clock_init(&clkConfig);

    Uart_init(OB_UART1, &uartConfig);
    Uart_addRxCallback(OB_UART1,callbackRx);

    uint32_t i = 0;

    while (1)
    {
        i++;
        if (send)
        {
            send = FALSE;
            Uart_write(OB_UART1,(uint8_t*)&receivedChar,100);

        }

    }
}
