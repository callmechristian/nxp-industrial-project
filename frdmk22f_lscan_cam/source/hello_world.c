/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_adc16.h"
#include "fsl_dmamux.h"
#include "fsl_edma.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_common.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

//LSCAN CAM
//------------------------------------------------------------------------------
//LSCAN CAM PARAMS
#define NPIXELS 128
uint32_t Pixel[NPIXELS];

// LSCAN CAM PINS
/* -- CAMERA SI OUTPUT GPIO PORT -- */
#define CAM_SI_GPIO LSCAN_CAM_LSCAN_CAM_SI_GPIO
#define CAM_SI_PORT LSCAN_CAM_LSCAN_CAM_SI_PORT
#define CAM_SI_PIN LSCAN_CAM_LSCAN_CAM_SI_PIN
#define CAM_SI_PIN_MASK LSCAN_CAM_LSCAN_CAM_SI_GPIO_PIN_MASK

/* -- CAMERA CK OUTPUT GPIO PORT -- */
#define CAM_CK_GPIO LSCAN_CAM_LSCAN_CAM_CK_GPIO
#define CAM_CK_PORT LSCAN_CAM_LSCAN_CAM_CK_PORT
#define CAM_CK_PIN LSCAN_CAM_LSCAN_CAM_CK_PIN
#define CAM_CK_PIN_MASK LSCAN_CAM_LSCAN_CAM_CK_GPIO_PIN_MASK

/* -- CAMERA ANALOG 0 INPUT PORT -- */
#define CAM_AO_PORT LSCAN_CAM_LSCAN_CAM_AO_PORT
#define CAM_AO_PIN LSCAN_CAM_LSCAN_CAM_AO_PIN
#define CAM_AO_PIN_MASK LSCAN_CAM_LSCAN_CAM_AO_GPIO_PIN_MASK

// ADC DEFINITIONS
#define CAM_ADC16_BASE          ADC0
#define CAM_ADC16_CHANNEL_GROUP 0U
#define CAM_ADC16_USER_CHANNEL  8U /* PTB0, ADC0_SE8 */

#define CAM_ADC16_IRQn             ADC0_IRQn
#define CAM_ADC16_IRQ_HANDLER_FUNC ADC0_IRQHandler
//------------------------------------------------------------------------------

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
// FUNCTIONS
// ----------------------------------------------------------------------------
/*!
 * @brief set lscan cam CLOCK to [0,1]
 */
void setCamCLK(int boolval) {
	if(boolval == 0) {
    	// SET CLK OUTPUT TO --LOW--
    	GPIO_PinWrite(CAM_CK_GPIO, CAM_CK_PIN, 0);
	} else {
    	// SET CLK OUTPUT TO --HIGH--
    	GPIO_PinWrite(CAM_CK_GPIO, CAM_CK_PIN, 1);
	}
}

/*!
 * @brief set lscan cam SI to [0,1]
 */
void setCamSI(int boolval) {
	if(boolval == 0) {
    	// SET SI OUTPUT TO --LOW--
    	GPIO_PinWrite(CAM_SI_GPIO, CAM_SI_PIN, 0);
	} else {
    	// SET SI OUTPUT TO --HIGH--
    	GPIO_PinWrite(CAM_SI_GPIO, CAM_SI_PIN, 1);

	}
}

/*!
 * @brief read lscan cam ANALOG OUTPUT
 */
uint32_t getCamAO() {

	return 0;
}

// -----------------------------------------------------------------------------

/*!
 * @brief Main function
 */
int main(void)
{
    char ch;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    PRINTF("hello world.\r\n");

    // main reading loop
    while (1)
    {
    	int i;
    	int expTime;
    	int val;

    	// integration time as delay ??

    	// SET CLK OUTPUT TO --LOW--
    	setCamCLK(0);
    	// SET SI OUTPUT TO --HIGH--
    	setCamSI(1);
    	// SET CLK OUTPUT TO --HIGH--
    	setCamCLK(1);
    	// SET SI OUTPUT TO --LOW--
    	setCamSI(0);

    	/* read the real image */
    	for(i = 0; i < NPIXELS; i++) {
    		// READ ANALOG INPUT AS INT
    		// 8-bit is enough
    		Pixel[i] = getCamAO()/4;
    		// SET CLK OUTPUT TO --LOW--
    		setCamCLK(0);
    		// delay of 1 ??
    		// SET CLK OUTPUT TO --HIGH--
    		setCamCLK(1);

    		// print debug
    		PRINTF("Pixel[i]: %d;\n", getCamAO());
    	}
    }
}
