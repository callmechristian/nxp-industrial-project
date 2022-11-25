/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v12.0
processor: MK22FN512xxx12
package_id: MK22FN512VLH12
mcu_data: ksdk2_0
processor_version: 12.0.0
board: FRDM-K22F
pin_labels:
- {pin_num: '23', pin_signal: PTA1/UART0_RX/FTM0_CH6/JTAG_TDI/EZP_DI, label: 'J2[4]/LSCAN_SI', identifier: LEDRGB_RED;LSCAN_CAM_SI}
- {pin_num: '24', pin_signal: PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO, label: 'J1[8]/GREEN_LED', identifier: LEDRGB_GREEN;LSCAN_CAM_CK}
- {pin_num: '25', pin_signal: PTA3/UART0_RTS_b/FTM0_CH0/JTAG_TMS/SWD_DIO, label: 'J11[2]/LSCAN_CK', identifier: LSCAN_CAM_CK}
- {pin_num: '26', pin_signal: PTA4/LLWU_P3/FTM0_CH1/NMI_b/EZP_CS_b, label: 'J1[10]/LSCAN_CK', identifier: LSCAN_CAM_CK}
- {pin_num: '35', pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA, label: 'J24[2]/LSCAN_AO', identifier: LSCAN_CAM_AO}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
    LSCAN_CAM();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', prefix: BOARD_, coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '1', peripheral: UART1, signal: TX, pin_signal: ADC1_SE4a/PTE0/CLKOUT32K/SPI1_PCS1/UART1_TX/I2C1_SDA/RTC_CLKOUT}
  - {pin_num: '2', peripheral: UART1, signal: RX, pin_signal: ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/I2C1_SCL/SPI1_SIN}
  - {pin_num: '24', peripheral: TPIU, signal: SWO, pin_signal: PTA2/UART0_TX/FTM0_CH7/JTAG_TDO/TRACE_SWO/EZP_DO, identifier: LEDRGB_GREEN, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    /* PORTA2 (pin 24) is configured as TRACE_SWO */
    PORT_SetPinMux(BOARD_LEDRGB_GREEN_PORT, BOARD_LEDRGB_GREEN_PIN, kPORT_MuxAlt7);

    PORTA->PCR[2] = ((PORTA->PCR[2] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the
                      * corresponding PE field is set. */
                     | PORT_PCR_PS(kPORT_PullDown)

                     /* Pull Enable: Internal pullup or pulldown resistor is not enabled on the corresponding pin. */
                     | PORT_PCR_PE(kPORT_PullDisable));

    /* PORTE0 (pin 1) is configured as UART1_TX */
    PORT_SetPinMux(PORTE, 0U, kPORT_MuxAlt3);

    /* PORTE1 (pin 2) is configured as UART1_RX */
    PORT_SetPinMux(BOARD_DEBUG_UART_RX_PORT, BOARD_DEBUG_UART_RX_PIN, kPORT_MuxAlt3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART1TXSRC_MASK)))

                  /* UART 1 transmit data source select: UART1_TX pin. */
                  | SIM_SOPT5_UART1TXSRC(SOPT5_UART1TXSRC_UART_TX));
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
LSCAN_CAM:
- options: {createDeInit: 'true', callFromInitBoot: 'true', coreID: core0, enableClock: 'true', fullInit: 'true'}
- pin_list:
  - {pin_num: '23', peripheral: GPIOA, signal: 'GPIO, 1', pin_signal: PTA1/UART0_RX/FTM0_CH6/JTAG_TDI/EZP_DI, identifier: LSCAN_CAM_SI, direction: OUTPUT, gpio_init_state: 'false',
    slew_rate: fast, open_drain: disable, drive_strength: low, pull_select: up, pull_enable: enable, passive_filter: disable}
  - {pin_num: '26', peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/LLWU_P3/FTM0_CH1/NMI_b/EZP_CS_b, direction: OUTPUT, gpio_init_state: 'false', slew_rate: fast,
    open_drain: disable, drive_strength: low, pull_select: up, pull_enable: enable, passive_filter: disable}
  - {pin_num: '35', peripheral: ADC0, signal: 'SE, 8', pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/FTM1_QD_PHA, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable, passive_filter: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : LSCAN_CAM
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void LSCAN_CAM(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    gpio_pin_config_t LSCAN_CAM_SI_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA1 (pin 23)  */
    GPIO_PinInit(LSCAN_CAM_LSCAN_CAM_SI_GPIO, LSCAN_CAM_LSCAN_CAM_SI_PIN, &LSCAN_CAM_SI_config);

    gpio_pin_config_t LSCAN_CAM_CK_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA4 (pin 26)  */
    GPIO_PinInit(LSCAN_CAM_LSCAN_CAM_CK_GPIO, LSCAN_CAM_LSCAN_CAM_CK_PIN, &LSCAN_CAM_CK_config);

    const port_pin_config_t LSCAN_CAM_SI = {/* Internal pull-up resistor is enabled */
                                            kPORT_PullUp,
                                            /* Fast slew rate is configured */
                                            kPORT_FastSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as PTA1 */
                                            kPORT_MuxAsGpio,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTA1 (pin 23) is configured as PTA1 */
    PORT_SetPinConfig(LSCAN_CAM_LSCAN_CAM_SI_PORT, LSCAN_CAM_LSCAN_CAM_SI_PIN, &LSCAN_CAM_SI);

    const port_pin_config_t LSCAN_CAM_CK = {/* Internal pull-up resistor is enabled */
                                            kPORT_PullUp,
                                            /* Fast slew rate is configured */
                                            kPORT_FastSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as PTA4 */
                                            kPORT_MuxAsGpio,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTA4 (pin 26) is configured as PTA4 */
    PORT_SetPinConfig(LSCAN_CAM_LSCAN_CAM_CK_PORT, LSCAN_CAM_LSCAN_CAM_CK_PIN, &LSCAN_CAM_CK);

    const port_pin_config_t LSCAN_CAM_AO = {/* Internal pull-up/down resistor is disabled */
                                            kPORT_PullDisable,
                                            /* Fast slew rate is configured */
                                            kPORT_FastSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as ADC0_SE8 */
                                            kPORT_PinDisabledOrAnalog,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTB0 (pin 35) is configured as ADC0_SE8 */
    PORT_SetPinConfig(LSCAN_CAM_LSCAN_CAM_AO_PORT, LSCAN_CAM_LSCAN_CAM_AO_PIN, &LSCAN_CAM_AO);
}


/* FUNCTION ************************************************************************************************************
 *
 * Function Name : LSCAN_CAM_deinit
 * Description   : This is a de-initialization function for 'LSCAN_CAM' function.
 * It sets all pins features (routing, direction and electrical) to their after-reset state.
 * It also tries to route the previous peripheral signals to their default pins.
 *
 * END ****************************************************************************************************************/
void LSCAN_CAM_deinit(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);

    const port_pin_config_t porta1_pin23_config = {/* Internal pull-up resistor is enabled */
                                                   kPORT_PullUp,
                                                   /* Fast slew rate is configured */
                                                   kPORT_FastSlewRate,
                                                   /* Passive filter is disabled */
                                                   kPORT_PassiveFilterDisable,
                                                   /* Open drain is disabled */
                                                   kPORT_OpenDrainDisable,
                                                   /* Low drive strength is configured */
                                                   kPORT_LowDriveStrength,
                                                   /* Pin is configured as JTAG_TDI */
                                                   kPORT_MuxAlt7,
                                                   /* Pin Control Register fields [15:0] are not locked */
                                                   kPORT_UnlockRegister};
    /* PORTA1 (pin 23) is configured as JTAG_TDI */
    PORT_SetPinConfig(PORTA, 1U, &porta1_pin23_config);

    const port_pin_config_t LSCAN_CAM_CK = {/* Internal pull-up resistor is enabled */
                                            kPORT_PullUp,
                                            /* Fast slew rate is configured */
                                            kPORT_FastSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as NMI_b */
                                            kPORT_MuxAlt7,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTA4 (pin 26) is configured as NMI_b */
    PORT_SetPinConfig(LSCAN_CAM_DEINIT_LSCAN_CAM_CK_PORT, LSCAN_CAM_DEINIT_LSCAN_CAM_CK_PIN, &LSCAN_CAM_CK);

    const port_pin_config_t LSCAN_CAM_AO = {/* Internal pull-up/down resistor is disabled */
                                            kPORT_PullDisable,
                                            /* Fast slew rate is configured */
                                            kPORT_FastSlewRate,
                                            /* Passive filter is disabled */
                                            kPORT_PassiveFilterDisable,
                                            /* Open drain is disabled */
                                            kPORT_OpenDrainDisable,
                                            /* Low drive strength is configured */
                                            kPORT_LowDriveStrength,
                                            /* Pin is configured as ADC0_SE8 */
                                            kPORT_PinDisabledOrAnalog,
                                            /* Pin Control Register fields [15:0] are not locked */
                                            kPORT_UnlockRegister};
    /* PORTB0 (pin 35) is configured as ADC0_SE8 */
    PORT_SetPinConfig(LSCAN_CAM_DEINIT_LSCAN_CAM_AO_PORT, LSCAN_CAM_DEINIT_LSCAN_CAM_AO_PIN, &LSCAN_CAM_AO);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/