/**
 * \file  rasterDisplay.c
 *
 * \brief Sample application for raster
 *
*/

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#include "soc_AM335x.h"
#include "evmskAM335x.h"
#include "raster.h"
#include "image.h"

static void SetUpLCD(void);


void Lcd_Init(void)
{
	LCDBackLightEnable();
    SetUpLCD();

    RasterDMAFBConfig(SOC_LCDC_0_REGS,
                      (unsigned int)image1,
                      (unsigned int)image1 + sizeof(image1) - 2,
                      0);

    RasterDMAFBConfig(SOC_LCDC_0_REGS,
                      (unsigned int)image1,
                      (unsigned int)image1 + sizeof(image1) - 2,
                      1);

    RasterEnable(SOC_LCDC_0_REGS);
}

/*
** Configures raster to display image
*/
static void SetUpLCD(void)
{
    /* Enable clock for LCD Module */
    LCDModuleClkConfig();

    LCDPinMuxSetup();

    /*
    **Clock for DMA,LIDD and for Core(which encompasses
    ** Raster Active Matrix and Passive Matrix logic)
    ** enabled.
    */
    RasterClocksEnable(SOC_LCDC_0_REGS);

    /* Disable raster */
    RasterDisable(SOC_LCDC_0_REGS);

    /* Configure the pclk */
    RasterClkConfig(SOC_LCDC_0_REGS, 32000000, 192000000);

    /* Configuring DMA of LCD controller */
    RasterDMAConfig(SOC_LCDC_0_REGS, RASTER_DOUBLE_FRAME_BUFFER,
                    RASTER_BURST_SIZE_16, RASTER_FIFO_THRESHOLD_8,
                    RASTER_BIG_ENDIAN_DISABLE);

    /* Configuring modes(ex:tft or stn,color or monochrome etc) for raster controller */
    RasterModeConfig(SOC_LCDC_0_REGS, RASTER_DISPLAY_MODE_TFT_UNPACKED,
                     RASTER_PALETTE_DATA, RASTER_COLOR, RASTER_RIGHT_ALIGNED);


     /* Configuring the polarity of timing parameters of raster controller */
    RasterTiming2Configure(SOC_LCDC_0_REGS, RASTER_FRAME_CLOCK_LOW |
                                            RASTER_LINE_CLOCK_LOW  |
                                            RASTER_PIXEL_CLOCK_HIGH|
                                            RASTER_SYNC_EDGE_RISING|
                                            RASTER_SYNC_CTRL_ACTIVE|
                                            RASTER_AC_BIAS_HIGH     , 0, 255);

    /* Configuring horizontal timing parameter */
    RasterHparamConfig(SOC_LCDC_0_REGS, 800, 47, 39, 39);
    //RasterHparamConfig(SOC_LCDC_0_REGS, 1024, 136, 24, 160);
    /* Configuring vertical timing parameters */
    RasterVparamConfig(SOC_LCDC_0_REGS, 600, 2, 13, 29);
    //RasterVparamConfig(SOC_LCDC_0_REGS, 768, 6, 3, 29);

    RasterFIFODMADelayConfig(SOC_LCDC_0_REGS, 128);

}

