/*
 * This file is part of the libohiboard examples project.
 *
 * Copyright (C) 2021 A. C. Open Hardware Ideas Lab
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
#include "hts221/hts221_reg.h"

#define DEVICE_PERIPHERAL                        OB_IIC1
#define DEVICE_PERIPHERAL_PIN_SDA                IIC_PINS_PB9
#define DEVICE_PERIPHERAL_PIN_SCL                IIC_PINS_PB8

#define DEVICE_ADDRESS                           0x5F

int32_t readRegister (void *handle,
                      uint8_t regAddress,
                      uint8_t *data,
                      uint16_t length)
{
    System_Errors err = Iic_readRegister((Iic_DeviceHandle)handle,
                                         DEVICE_ADDRESS,
                                         regAddress,
                                         IIC_REGISTERADDRESSSIZE_8BIT,
                                         data,
                                         length,
                                         50);
    if (err == ERRORS_NO_ERROR)
    {
        return 0;
    }
    return -1;
}

int32_t writeRegister (void *handle,
                       uint8_t regAddress,
                       uint8_t *data,
                       uint16_t length)
{
    System_Errors err = Iic_writeRegister((Iic_DeviceHandle)handle,
                                          DEVICE_ADDRESS,
                                          regAddress,
                                          IIC_REGISTERADDRESSSIZE_8BIT,
                                          data,
                                          length,
                                          50);
    if (err == ERRORS_NO_ERROR)
    {
        return 0;
    }
    return -1;
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

    // Initialize clock...
    Clock_init(&clkConfig);

    Iic_Config iicConfig =
    {
        .sclPin          = DEVICE_PERIPHERAL_PIN_SCL,
        .sdaPin          = DEVICE_PERIPHERAL_PIN_SDA,

        .baudrate        = 100000,
        .devType         = IIC_MASTER_MODE,
        .addressMode     = IIC_SEVEN_BIT,

        .pullupEnable    = false,

        .sclTimeout      = 0,
        .clockSource     = IIC_CLOCKSOURCE_SYSCLK,

        .address1        = 0,
        .address2        = 0,

        .dualAddressMode = IIC_DUALADDRESS_DISABLE,
        .dualAddressMask = IIC_DUALADDRESSMASK_NO_MASK,
        .noStretch       = IIC_NOSTRETCH_DISABLE,
    };
    Iic_init(DEVICE_PERIPHERAL,&iicConfig);

    stmdev_ctx_t ctx;
    ctx.handle    = DEVICE_PERIPHERAL;
    ctx.read_reg  = (stmdev_read_ptr)readRegister;
    ctx.write_reg = (stmdev_write_ptr)writeRegister;

    uint32_t i = 0;
    uint8_t val = 0;

    while (1)
    {
        i++;
        val = 0;
        hts221_device_id_get(&ctx,&val);

        if (val == HTS221_ID)
        {
            // TODO: LED ON!
        }
        else
        {
            // TODO: LED OFF!
        }

        System_delay(1000);

    }
}
