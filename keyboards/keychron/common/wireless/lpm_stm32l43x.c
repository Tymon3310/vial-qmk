/* Copyright 2022 @ lokher (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/******************************************************************************
 *
 *  Filename:      lpm_stm32l432.c
 *
 *  Description:   Contains low power mode implementation
 *
 ******************************************************************************/

#include "quantum.h"
#include <usb_main.h>
#include "wireless.h"
#include "lpm.h"
#include "lpm_stm32l43x.h"
#include "config.h"
#include "hal.h"

static pm_t power_mode = PM_RUN;

void lpm_post_enter_low_power(void) {
    PWR->CR2 &= ~PWR_CR2_USV;
    /*  USB D+/D- */
    palSetLineMode(A12, PAL_MODE_INPUT_PULLDOWN);
    palSetLineMode(A11, PAL_MODE_INPUT_PULLDOWN);
}

void lpm_pre_wakeup(void) {
    /*  USB D+/D- */
    palSetLineMode(A11, PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING | PAL_MODE_ALTERNATE(10U));
    palSetLineMode(A12, PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING | PAL_MODE_ALTERNATE(10U));

    /* SPI */
#if (HAL_USE_SPI == TRUE)
    palSetLineMode(SPI_SCK_PIN, PAL_MODE_ALTERNATE(5));
    palSetLineMode(SPI_MISO_PIN, PAL_MODE_ALTERNATE(5));
    palSetLineMode(SPI_MOSI_PIN, PAL_MODE_ALTERNATE(5));
#endif

    gpio_write_pin_high(MCU_TO_WIRELESS_INT_PIN);
}

bool lpm_set(pm_t mode) {

    switch (mode) {
#    ifdef LOW_POWER_RUN_MODE_ENABLE
        case PM_RUN:
            if (power_mode != PM_LOW_POWER_RUN)) return;
            /* Set main regulator */
            PWR->CR1 &= ~PWR_CR1_LPR;
            while (PWR->SR2 & PWR_SR2_REGLPF)
                ;
            // TODO: restore sysclk
            return true;
            // break;

        case PM_LOW_POWER_RUN:
            if (power_mode != PM_RUN) return;

            // FLASH->ACR |= FLASH_ACR_RUN_PD;   // Optional
            // TODO: Decrease sysclk below 2 MHz
            PWR->CR1 |= PWR_CR1_LPR;
            return true;
            // break;
#    endif
        case PM_SLEEP:
            /* Wake source: Any interrupt or event */
            if (power_mode != PM_RUN) return false;

            SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            break;

#    ifdef LOW_POWER_RUN_MODE_ENABLE
        case PM_LOW_POWER_SLEEP:
            /* Wake source: Any interrupt or event */
            if (power_mode != PM_LOW_POWER_RUN) return; /* Can only transit from PM_LOW_POWER_RUN */

            SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            __WFI();
            exit_low_power_mode();
            break;
#    endif
        case PM_STOP0:
            /* Wake source: Reset pin, all I/Os, BOR, PVD, PVM, RTC, LCD, IWDG,
               COMPx, USARTx, LPUART1, I2Cx, LPTIMx, USB, SWPMI */
            if (power_mode != PM_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STOP0;
            break;

        case PM_STOP1:
            /* Wake source: Reset pin, all I/Os, BOR, PVD, PVM, RTC, LCD, IWDG,
               COMPx, USARTx, LPUART1, I2Cx, LPTIMx, USB, SWPMI */
            if (power_mode != PM_RUN && power_mode != PM_LOW_POWER_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STOP1;
            break;

        case PM_STOP2:
            /* Wake source: Reset pin, all I/Os, BOR, PVD, PVM, RTC, LCD, IWDG,
               COMPx (x=1, 2), I2C3, LPUART1, LPTIM1, LPTIM2 */
            if (power_mode != PM_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STOP2;
            break;

        case PM_STANDBY_WITH_RAM:
            /* Wake source: Reset, 5 I/O(PA0, PC13, PE6, PA2, PC5), BOR, RTC, IWDG */
            if (power_mode != PM_RUN && power_mode != PM_LOW_POWER_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STANDBY;
            PWR->CR3 |= PWR_CR3_RRS;
            break;

        case PM_STANDBY:
            /* Wake source: Reset, 2 I/O(PA0, PA2) in STM32L432Kx,, BOR, RTC, IWDG */
            if (power_mode != PM_RUN && power_mode != PM_LOW_POWER_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_STANDBY;
            PWR->CR3 &= ~PWR_CR3_RRS;
            break;

        case PM_SHUTDOWN:
            /* Wake source: Reset, 2 I/O(PA0, PA2) in STM32L432Kx, RTC */
            if (power_mode != PM_RUN && power_mode != PM_LOW_POWER_RUN) return false;

            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            PWR->CR1 |= PWR_CR1_LPMS_SHUTDOWN;
            break;

        default:
            return false;
    }

    return true;
}

void lpm_standby(pm_t mode) {
    __WFI();

    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
    PWR->SCR |= PWR_SCR_CWUF;
    PWR->SCR |= PWR_SCR_CSBF;
}

#ifdef KC_BLUETOOTH_ENABLE
/*
 * This is a simplified version of stm32_clock_init() by removing unnecessary clock initlization
 * code snippet. The original stm32_clock_init() take about 2ms, but ckbt51 sends data via uart
 * about 200us after wakeup pin is assert, it means that we must get everything ready before data
 * coming when wakeup pin interrupt of MCU is triggerred.
 * Here we reduce clock init time to less than 100us.
 */
void stm32_clock_fast_init(void) {
#if !STM32_NO_INIT
    /* Clocks setup.*/
    msi_init();   // 6.x us
    hsi16_init(); // 4.x us

    /* PLLs activation, if required.*/
    pll_init();
    pllsai1_init();
    pllsai2_init();
    /* clang-format off */
    /* Other clock-related settings (dividers, MCO etc).*/
  RCC->CFGR = STM32_MCOPRE | STM32_MCOSEL | STM32_STOPWUCK |
              STM32_PPRE2  | STM32_PPRE1  | STM32_HPRE;
    /* CCIPR register initialization, note, must take care of the _OFF
       pseudo settings.*/
    {
    uint32_t ccipr = STM32_DFSDMSEL  | STM32_SWPMI1SEL | STM32_ADCSEL    |
                     STM32_CLK48SEL  | STM32_LPTIM2SEL | STM32_LPTIM1SEL |
                     STM32_I2C3SEL   | STM32_I2C2SEL   | STM32_I2C1SEL   |
                     STM32_UART5SEL  | STM32_UART4SEL  | STM32_USART3SEL |
                     STM32_USART2SEL | STM32_USART1SEL | STM32_LPUART1SEL;
/* clang-format on */
#    if STM32_SAI2SEL != STM32_SAI2SEL_OFF
        ccipr |= STM32_SAI2SEL;
#    endif
#    if STM32_SAI1SEL != STM32_SAI1SEL_OFF
        ccipr |= STM32_SAI1SEL;
#    endif
        RCC->CCIPR = ccipr;
    }

    /* Set flash WS's for SYSCLK source */
    if (STM32_FLASHBITS > STM32_MSI_FLASHBITS) {
        FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_Msk) | STM32_FLASHBITS;
        while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (STM32_FLASHBITS & FLASH_ACR_LATENCY_Msk)) {
        }
    }

    /* Switching to the configured SYSCLK source if it is different from MSI.*/
#    if (STM32_SW != STM32_SW_MSI)
    RCC->CFGR |= STM32_SW; /* Switches on the selected clock source.   */
    /* Wait until SYSCLK is stable.*/
    while ((RCC->CFGR & RCC_CFGR_SWS) != (STM32_SW << 2))
        ;
#    endif

    /* Reduce the flash WS's for SYSCLK source if they are less than MSI WSs */
    if (STM32_FLASHBITS < STM32_MSI_FLASHBITS) {
        FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_Msk) | STM32_FLASHBITS;
        while ((FLASH->ACR & FLASH_ACR_LATENCY_Msk) != (STM32_FLASHBITS & FLASH_ACR_LATENCY_Msk)) {
        }
    }
#endif /* STM32_NO_INIT */
}
#endif

void lpm_wakeup_init(void) {
#ifdef KC_BLUETOOTH_ENABLE
    stm32_clock_fast_init();
#else
    stm32_clock_init();
#endif
}

void usb_power_connect(void) {
    PWR->CR2 |= PWR_CR2_USV;
}

void usb_power_disconnect(void) {
    PWR->CR2 &= ~PWR_CR2_USV;
}

 void lpm_post_wakeup(void) {
    hsi48_init();
    /* Remove USB isolation.*/
    // PWR->CR2 |= PWR_CR2_USV; /* PWR_CR2_USV is available on STM32L4x2xx and STM32L4x3xx devices only. */
    usb_power_connect();
    restart_usb_driver(&USBD1);
 }
