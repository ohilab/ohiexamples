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

#define LED GPIO_PINS_PA5

uint32_t blink = 0ul;

static void timerBlink (Timer_DeviceHandle dev)
{
    blink++;
    if (blink == 500)
    {
        blink = 0;
        Gpio_toggle(LED);
    }
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

    Timer_Config timerCountConfig =
    {
        .mode = TIMER_MODE_FREE,
        .clockSource = TIMER_CLOCKSOURCE_INTERNAL,
        .timerFrequency = 1000, // [Hz]
        .autoreload = FALSE,

        .freeCounterCallback = timerBlink,
    };

    // Initialize clock...
    Clock_init(&clkConfig);

    // Initialize timer...
    Timer_init(OB_TIM2, &timerCountConfig);
    Timer_start(OB_TIM2);

    // Initialize GPIO to output...
    Gpio_config(LED,GPIO_PINS_OUTPUT);

    uint32_t i = 0;

    while (1)
    {
        i++;
    }
}
