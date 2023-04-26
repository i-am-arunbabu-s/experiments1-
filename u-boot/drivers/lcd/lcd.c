/**
 * \file   lcd.c
 *
 * \brief  This file contains functions which configure the lcd
 */

/*
 * * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * */
/*
 * *  Redistribution and use in source and binary forms, with or without
 * *  modification, are permitted provided that the following conditions
 * *  are met:
 * *
 * *    Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * *
 * *    Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the
 * *    distribution.
 * *
 * *    Neither the name of Texas Instruments Incorporated nor the names of
 * *    its contributors may be used to endorse or promote products derived
 * *    from this software without specific prior written permission.
 * *
 * *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * *
 * */

#include <stdio.h>
#include <asm/gpio.h>
#include "hw_control_AM335x.h"
#include "soc_AM335x.h"
#include "evmskAM335x.h"
#include "hw_cm_per.h"
#include "hw_types.h"
#include "hw_cm_dpll.h"


/**
 * \brief  This API pin multiplexes the lcd data and control signal lines.
 *
 * \param  None
 */

unsigned int LCDPinMuxSetup(void)
{
    HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(0)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(1)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(2)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(3)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(4)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(5)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(6)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(7)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(8)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(9)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(10)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(11)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(12)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(13)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(14)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_DATA(15)) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(15) ) = 1;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(14) ) = 1;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(13) ) = 1;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(12) ) = 1;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(11) ) = 1;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(10) ) = 1;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(9) ) = 1;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_GPMC_AD(8) ) = 1;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_VSYNC) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_HSYNC) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_PCLK) = 0;

	HWREG(SOC_CONTROL_REGS + CONTROL_CONF_LCD_AC_BIAS_EN) = 0;

	return TRUE;
}


/**
 * \brief  This API returns a unique number which identifies itself
 *         with the LCDC IP in AM335x SoC.
 * \param  None
 * \return This returns a number '2' which is unique to LCDC IP in AM335x.
 */
unsigned int LCDVersionGet(void)
{
    return 2;
}

/**
 * \brief   This function will configure the Display PLL to 192MHz.
 *
 * \return  None.
 *
 */
void SetupDisplayPLL(void)
{
    HWREG(SOC_PRCM_REGS + CM_CLKMODE_DPLL_DISP) =
    						CM_CLKMODE_DPLL_DISP_MN_BYPASS;

    while((HWREG(SOC_PRCM_REGS + CM_IDLEST_DPLL_DISP) &
    		CM_IDLEST_DPLL_DISP_CLK) != CM_IDLEST_DPLL_DISP_CLK_BYPASS);

    while((HWREG(SOC_PRCM_REGS + CM_IDLEST_DPLL_DISP) &
    		CM_IDLEST_DPLL_DISP_MN) != CM_IDLEST_DPLL_DISP_MN_BYPASS);

    HWREG(SOC_PRCM_REGS + CM_CLKSEL_DPLL_DISP) =
    						(CM_CLKSEL_DPLL_DISP_MULT << 8);

    HWREG(SOC_PRCM_REGS + CM_CLKSEL_DPLL_DISP) |=
    						CM_CLKSEL_DPLL_DISP_DIV;

    HWREG(SOC_PRCM_REGS + CM_DIV_M2_DPLL_DISP) =
    						CM_DIV_M2_DPLL_DISP_DIV;

    HWREG(SOC_PRCM_REGS + CM_CLKMODE_DPLL_DISP) =
    						CM_CLKMODE_DPLL_DISP_LOCK;

    while((HWREG(SOC_PRCM_REGS + CM_IDLEST_DPLL_DISP) &
    		CM_IDLEST_DPLL_DISP_CLK) != CM_IDLEST_DPLL_DISP_CLK_LOCKED);

    while((HWREG(SOC_PRCM_REGS + CM_IDLEST_DPLL_DISP) &
    		CM_IDLEST_DPLL_DISP_MN) != CM_IDLEST_DPLL_DISP_MN_NO_BYPASS);
}
/**
 * \brief   This function will configure the required clocks for LCDC instance.
 *
 * \return  None.
 *
 */
void LCDModuleClkConfig(void)
{
	SetupDisplayPLL();
    HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) |=
                             CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) &
     CM_PER_L3S_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) |=
                             CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) &
     CM_PER_L3_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_INSTR_CLKCTRL) |=
                             CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_INSTR_CLKCTRL) &
                               CM_PER_L3_INSTR_CLKCTRL_MODULEMODE) !=
                                   CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE);

    HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKCTRL) |=
                             CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKCTRL) &
        CM_PER_L3_CLKCTRL_MODULEMODE) != CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE);

    HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) |=
                             CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
                              CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL) !=
                                CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) |=
                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) &
                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL) !=
                               CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKCTRL) |=
                             CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKCTRL) &
      CM_PER_L4LS_CLKCTRL_MODULEMODE) != CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE);

    /* lcd pixel clock is derived from display pll */
    HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_LCDC_PIXEL_CLK) =
                             CM_DPLL_CLKSEL_LCDC_PIXEL_CLK_CLKSEL_SEL1;

    HWREG(SOC_PRCM_REGS + CM_PER_LCDC_CLKCTRL) |=
                             CM_PER_LCDC_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_PRCM_REGS + CM_PER_LCDC_CLKCTRL) &
      CM_PER_LCDC_CLKCTRL_MODULEMODE) != CM_PER_LCDC_CLKCTRL_MODULEMODE_ENABLE);

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) &
            CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) &
            CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
           (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK |
            CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));

    while(!(HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) &
           (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK |
            CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_LCDC_GCLK)));

}

 /*
 ** Configures ecap pin as gpio pin and pull
 ** it to high,so that backlight is enabled
 */

void LCDBackLightEnable(void)
{

	int ret = 0;
	ret = gpio_request(7, "LCD_BCL");

	if (ret < 0) {
		printf("%s: gpio %d request failed %d\n", __func__,
							7, ret);
		return;
	}

	/* Pull the GPIO HIGH to enable LCD backlight */
	gpio_direction_output(7, 1);
}

