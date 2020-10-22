cmake_minimum_required(VERSION 3.15.0)

project(GPIO_Blink_L476)

enable_language(C ASM)
#set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


set(EXECUTABLE ${PROJECT_NAME}.elf)

set(PROJECT_FILES
	../src/main.c
	../src/syscalls.c
	../src/sysmem.c
	../src/system_stm32l4xx.c

	../../startup/startup_stm32l476rgtx.s
	)

set(DRIVER_LIBOHIBOARD_FILES
#	../../../../Drivers/libohiboard/source/STM32L4/adc_STM32L4.c
	../../../../Drivers/libohiboard/source/STM32L4/clock_STM32L4.c
	../../../../Drivers/libohiboard/source/STM32L4/critical_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/dac_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/dma_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/flash_STM32L4.c
	../../../../Drivers/libohiboard/source/STM32L4/gpio_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/i2c_STM32L4.c
	../../../../Drivers/libohiboard/source/STM32L4/interrupt_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/lowpower-timer_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/lowpower_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/rtc_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/spi_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/timer_STM32L4.c
#	../../../../Drivers/libohiboard/source/STM32L4/uart_STM32L4.c

	../../../../Drivers/libohiboard/source/comm-utility.c
	../../../../Drivers/libohiboard/source/errors.c
#	../../../../Drivers/libohiboard/source/ethernet-utility.c
#	../../../../Drivers/libohiboard/source/ethernet.c
#	../../../../Drivers/libohiboard/source/filter.c
#	../../../../Drivers/libohiboard/source/flash.c
	../../../../Drivers/libohiboard/source/libohiboard.c
	../../../../Drivers/libohiboard/source/system.c
#	../../../../Drivers/libohiboard/source/timeday.c
#	../../../../Drivers/libohiboard/source/uart.c
	../../../../Drivers/libohiboard/source/utility-buffer.c
	../../../../Drivers/libohiboard/source/utility-debouncing.c
	../../../../Drivers/libohiboard/source/utility-valid.c
	../../../../Drivers/libohiboard/source/utility.c
	)

add_executable(${EXECUTABLE} ${DRIVER_LIBOHIBOARD_FILES} ${PROJECT_FILES})

target_compile_definitions(${EXECUTABLE} PRIVATE
        -DSTM32L476xx
        -DDEBUG
	-DLIBOHIBOARD_BASIC
	-DLIBOHIBOARD_STM32L476RxT
        )

target_include_directories(${EXECUTABLE} PRIVATE
        ../../../../Drivers/CMSIS/Include
	../../../../Drivers/libohiboard/include
        )

target_compile_options(${EXECUTABLE} PRIVATE
	-std=gnu11
        -g3
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard

        -fdata-sections
        -ffunction-sections
	-fstack-usage

	--specs=nano.specs

        -Wall

	-O0
        )

target_link_options(${EXECUTABLE} PRIVATE
        -T${CMAKE_SOURCE_DIR}/../../memory/STM32L476RGTX_FLASH.ld
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=hard
        -specs=nosys.specs
        -lnosys
        -Wl,-Map=${PROJECT_NAME}.map,--cref
        -Wl,--gc-sections -static --specs=nano.specs
	-Wl,--start-group -lc -lm 
	-Wl,--end-group
        )

# Print executable size
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-size ${EXECUTABLE}
	)

# Create hex file
add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
        COMMAND arm-none-eabi-objcopy -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
	)

