/**
 *  \file   raster.c
 *
 *  \brief  Raster LCD APIs.
 *
 *   This file contains the device abstraction layer APIs for Raster LCD.
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


#include "hw_lcdc.h"
#include "hw_types.h"
#include "raster.h"

/*******************************************************************************
*                       INTERNAL API DEFINITIONS
*******************************************************************************/
/**
* \brief  This function configures clkdiv to generate required frequency of
*         of pixel clock and selects the raster control.\n
*
* \param  baseAddr   is the Memory address of LCD.\n
* \param  pClk       is the required Pixel Clock frequency.\n
* \param  modulck    is the input clk to LCD module from PLL.\n
*
* \return none.
**/
void RasterClkConfig(unsigned int baseAddr, unsigned int pClk,
                     unsigned int moduleClk)
{
    unsigned int clkDiv;

    clkDiv = moduleClk / pClk ;

    HWREG(baseAddr + LCDC_LCD_CTRL) = LCDC_LCD_CTRL_MODESEL;

    HWREG(baseAddr + LCDC_LCD_CTRL) |= (clkDiv <<  LCDC_LCD_CTRL_CLKDIV_SHIFT);
}

/**
* \brief  This function will Enable Raster Control.\n
*
* \param baseAddr is the Memory address of the LCD.\n
*
* \return none.
**/
void RasterEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_RASTER_EN;
}

/**
* \brief  This function will Disable Raster Control.\n
*
* \param baseAddr is the Memory address of the LCD.\n
*
* \return none.
**/
void RasterDisable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_RASTER_EN;
}

/**
* \brief  This function will configures LCD to MonoChrome or color mode,
*         TFT or STN mode and palette loading mode.\n
*
* \param baseAddr    is the Memory address of the LCD.\n
* \param displayMode is the vlaue to select either TFT or STN mode.\n
*
*         displayMode can take following value.\n
*
*         RASTER_DISPLAY_MODE_TFT  -  TFT mode is selected.\n
*         RASTER_DISPLAY_MODE_STN  -  STN mode is selected.\n
*
*         Below mentioned macros are only applicable to AM335x.
*
*         RASTER_DISPLAY_MODE_TFT_PACKED   - TFT mode is selected with
*                                            24 bit packed data support.
*         RASTER_DISPLAY_MODE_TFT_UNPACKED - TFT mode is selected with
*                                            24 bit unpacked data support.
*
* \param displayType is the value to select either color or monochrome mode.\n
*
*         displayType can take following value.\n
*
*         RASTER_MONOCHROME  - monochrome mode is selected.\n
*         RASTER_COLOR       - color mode is selected.\n
*
* \param paletteMode is the value to select type of palette loading.\n
*
*        paletteMode can take following values.\n
*
*        RASTER_PALETTE_DATA   - palette and  data is loaded.\n
*        RASTER_PALETTE        - only palette is loaded.\n
*        RASTER_DATA           - only data is loaded.\n
*
* \param flag  Optional argument depending on the display mode and type
*
*        flag can take following values.\n
*
*        RASTER_RIGHT_ALIGNED - Right aligned output pixel data
*        RASTER_EXTRAPOLATE   - Extrapolated (to RGB565) output pixel data
*        RASTER_MONO8B        - Output 8 bit mono pixel data
*        RASTER_MONO4B        - Output 4 bit mono pixel data
*
* \return none.
**/
void RasterModeConfig(unsigned int baseAddr, unsigned int displayMode,
                      unsigned int paletteMode, unsigned int displayType,
                      unsigned flag)
{
    /* Configures raster to TFT or STN Mode */
    HWREG(baseAddr + LCDC_RASTER_CTRL) = displayMode | paletteMode | displayType;

    if(displayMode ==  RASTER_DISPLAY_MODE_TFT)
    {
         if(flag == RASTER_RIGHT_ALIGNED)
         {
              /* Output pixel data for 1,2,4 and 8 bpp is converted to 565 format */
              HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~(LCDC_RASTER_CTRL_TFT_ALT_MAP);
         }
         else
         {
              /* Output pixel data for 1,2,4 and 8 bpp will be right aligned */
             HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_TFT_ALT_MAP;
         }
    }
    else
    {
         if(flag ==  RASTER_MONO8B)
         {
              HWREG(baseAddr + LCDC_RASTER_CTRL) |= LCDC_RASTER_CTRL_MONO8B;
         }
         else
         {
              HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_MONO8B;
         }
    }
}

/**
* \brief This function configures input FIFO delay.
*
* \param baseAddr is the Memory address of LCD module.
*
* \return None
**/
void RasterFIFODMADelayConfig(unsigned int baseAddr, unsigned int delay)
{

    HWREG(baseAddr + LCDC_RASTER_CTRL) &= ~LCDC_RASTER_CTRL_FIFO_DMA_DELAY;
    HWREG(baseAddr + LCDC_RASTER_CTRL) |= (delay <<                  \
                                          LCDC_RASTER_CTRL_FIFO_DMA_DELAY_SHIFT);
}
/**
* \brief This function configuers horizontal timing parametes and number of
*        pixel per line.
*
* \param baseAddr is the Memory address of the LCD module
*
* \param numOfppl is a value which determine no of pixel required per line.
*
* \param hsw      is a value which detemines the width of HSYNC.
*
* \param hfp      horizontal front porch.
*
* \para  hbp      horizontal back porch.
**/
void RasterHparamConfig(unsigned int baseAddr, unsigned int numOfppl,
                        unsigned int hsw, unsigned int hfp,
                        unsigned hbp)
{
    unsigned int ppl;
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {
         ppl = numOfppl - 1;

         ppl = (ppl & 0x000003f0) | ((ppl & 0x00000400) >> 7);

         HWREG(baseAddr + LCDC_RASTER_TIMING_0) = ppl;
    }
    else if(RASTER_REV_AM1808 == version)
    {

         ppl = (numOfppl / 16) - 1;

         HWREG(baseAddr + LCDC_RASTER_TIMING_0) =  (ppl <<
                                                LCDC_RASTER_TIMING_0_PPL_SHIFT);
    }
    else
    {
         ;/* Do nothing */
    }

    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hsw - 1) <<
                                               LCDC_RASTER_TIMING_0_HSW_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hfp - 1) <<
                                               LCDC_RASTER_TIMING_0_HFP_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_0) |= ((hbp - 1) <<
                                               LCDC_RASTER_TIMING_0_HBP_SHIFT);
}

/**
* \brief This function configuers vertical timing parameters and number of
*        lines per panel.
*
* \param baseAddr is the Memory address of the LCD module
*
* \param lpp      is a value which determine the lines per panel.
*
* \param vsw      is a value which detemines the width of VSYNC.
*
* \param vfp      vertical front porch.
*
* \para  vbp      vertical back porch.
**/
void RasterVparamConfig(unsigned int baseAddr, unsigned int lpp,
                        unsigned int vsw, unsigned int vfp,
                        unsigned vbp)
{
    unsigned int version;

    version = LCDVersionGet();

    if(RASTER_REV_AM335X == version)
    {

         HWREG(baseAddr + LCDC_RASTER_TIMING_1) = ((lpp - 1) & 0x3ff);

         HWREG(baseAddr + LCDC_RASTER_TIMING_2) &=  0xfbffffff;

         HWREG(baseAddr + LCDC_RASTER_TIMING_2) |=  (((lpp - 1) & 0x400) >> 10)
                                                    << LCDC_RASTER_TIMING_2_LPP_B10_SHIFT;
    }
    else if(RASTER_REV_AM1808 == version)
    {

         HWREG(baseAddr + LCDC_RASTER_TIMING_1) =  ((lpp - 1) <<
                                              LCDC_RASTER_TIMING_1_LPP_SHIFT);
    }
    else
    {
         ;/* Do nothing */
    }

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= ((vsw - 1) <<
                                               LCDC_RASTER_TIMING_1_VSW_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= (vfp <<
                                               LCDC_RASTER_TIMING_1_VFP_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_1) |= (vbp <<
                                               LCDC_RASTER_TIMING_1_VBP_SHIFT);
}
/**
* \brief This function configures the polartiy of various timing parameters of
*        LCD Controller.
*
* \param baseAddr  is the Memory Address of the LCD Module.
*
* \param flag      is the value which detemines polarity of various timing
*                  parameter of LCD controller.\n
*
*                  flag can take following values.\n
*
*                   RASTER_FRAME_CLOCK_HIGH - active high frame clock.\n
*                   RASTER_FRAME_CLOCK_LOW  - active low frame clock.\n
*                   RASTER_LINE_CLOCK_HIGH  - active high line clock.\n
*                   RASTER_LINE_CLOCK_LOW   - active low line clock.\n
*                   RASTER_PIXEL_CLOCK_HIGH - active high pixel clock.\n
*                   RASTER_PIXEL_CLOCK_LOW  - active low pixel clock.\n
*                   RASTER_AC_BIAS_HIGH     - active high ac bias.\n
*                   RASTER_AC_BIAS_LOW      - active low ac bias.\n
*                   RASTER_SYNC_EDGE_RISING - rising sync edge.\n
*                   RASTER_SYNC_EDGE_FALLING- falling sync edge.\n
*                   RASTER_SYNC_CTRL_ACTIVE - active sync control.\n
*                   RASTER_SYNC_CTRL_INACTIVE-inactive sync control.\n
*
* \param acb_i      is the value which specify the number of AC Bias
*                   (LCD_AC_ENB_CS) output transition counts before
*                   setting the AC bias interrupt bit in register LCD_STAT.
*
* \param acb        is value which defines the number of Line Clock
*                   (LCD_HSYNC) cycles to count before transitioning
*                    signal LCD_AC_ENB_CS.
*
* \return None.
*
**/
void RasterTiming2Configure(unsigned int baseAddr, unsigned int flag,
                            unsigned int acb_i, unsigned int acb)
{
    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= flag;

    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (acb_i <<                    \
                                              LCDC_RASTER_TIMING_2_ACB_I_SHIFT);

    HWREG(baseAddr + LCDC_RASTER_TIMING_2) |= (acb <<                      \
                                             LCDC_RASTER_TIMING_2_ACB_SHIFT);

}
/**
* \brief This function configures DMA present inside LCD controller.
*
* \param  baseAddr is the Memory address of LCD module.
*
* \param  frmMode  is the value which detemines either to use single frame
*                  or double frame buffer.\n
*
*                 frmMode can take following values.\n
*
*                 RASTER_SINGLE_FRAME_BUFFER - single frame buffer.\n
*                 RASTER_DOUBLE_FRAME_BUFFER - double frame buffer.\n
*
* \param bustSz   is the value which detemines burst size of DMA.\n
*
*                 bustSz can take following values.\n
*
*                 RASTER_BURST_SIZE_1   -  burst size of DMA is one.\n
*                 RASTER_BURST_SIZE_2   -  burst size of DMA is two.\n
*                 RASTER_BURST_SIZE_4   -  burst size of DMA is four.\n
*                 RASTER_BURST_SIZE_16  -  burst size of DMA is sixteen.\n
*
* \param fifoTh   is the value which detemines when the input FIFO can be
*                 read by raster controller.\n
*
*                 fifoTh can take following values.\n
*
*                 RASTER_FIFO_THRESHOLD_8    -   DMA FIFO Threshold is eight.\n
*                 RASTER_FIFO_THRESHOLD_16   -   DMA FIFO Threshold is sixteen.\n
*                 RASTER_FIFO_THRESHOLD_32   -   DMA FIFO Threshold is thirtytwo.\n
*                 RASTER_FIFO_THRESHOLD_64   -   DMA FIFO Threshold is sixtyfour.\n
*                 RASTER_FIFO_THRESHOLD_128  -   DMA FIFO Threshold is one twenty
*                                                eight.\n
*                 RASTER_FIFO_THRESHOLD_256  -   DMA FIFO Threshold is two
*                                                fifty six.\n
*                 RASTER_FIFO_THRESHOLD_512  -   DMA FIFO Threshold is five
*                                                twelve.\n
*
* \param endian   is value determines whether to use big endian for data
*                 reordering or not.\n
*
*                 endian can take following values.\n
*
*                 RASTER_BIG_ENDIAN_ENABLE - big endian enabled.\n
*                 RASTER_BIG_ENDIAN_ENABLE - big endian disabled.\n
*
* \return None
**/
void RasterDMAConfig(unsigned int baseAddr, unsigned int frmMode,
                     unsigned int bustSz, unsigned int fifoTh,
                     unsigned int endian)
{
    HWREG(baseAddr + LCDC_LCDDMA_CTRL) = frmMode | bustSz | fifoTh | endian;
}

/**
* \brief  This function configures base and ceiling value for
*         Frame buffer one or Frame buffer two.
*
* \param  baseAddr is the Memory Address of the LCD Module
*
* \param  base     is the base address of array which contain
*                  pixels of image to be dispalyed on lcd.
*
* \param  ceiling  is the end address of the array which contain
*                  pixels of image to be displayed on lcd.
*
* \param  flag     is the value which determines whether to write
*                  base and ceiling to Frame Buffer one or Fram buffer two.
*
*         passing zero(i.e. 0) as argument configures base and ceiling for
*         frame buffer zero(i.e FB0).
*
*         passing one(i.e. 0) as argument configures base and ceiling for
*         frame buffer one(i.e FB1).
*
* \return None.
*
**/
void RasterDMAFBConfig(unsigned int baseAddr, unsigned int base,
                       unsigned int  ceiling, unsigned int flag)
{
    if(flag == 0)
    {
         HWREG(baseAddr + LCDC_LCDDMA_FB0_BASE) =  base;
         HWREG(baseAddr + LCDC_LCDDMA_FB0_CEILING) = ceiling;
    }
    else
    {
         HWREG(baseAddr + LCDC_LCDDMA_FB1_BASE) =  base;
         HWREG(baseAddr + LCDC_LCDDMA_FB1_CEILING) = ceiling;
    }
}

/**
* \brief This function Enables the clock for the DMA submodule,LIDD submodule and
*        for the core(which encompasses the Raster active matrix and Passive matrix).
*
* \baseAddr is the Memory Address of the LCD Module.
*
* \return none
*
* This API is only supported for AM335x raster.
**/
void RasterClocksEnable(unsigned int baseAddr)
{
    HWREG(baseAddr + LCDC_CLKC_ENABLE) =  (LCDC_CLKC_ENABLE_CORE |
                                           LCDC_CLKC_ENABLE_DMA  |
                                           LCDC_CLKC_ENABLE_LIDD);
}

