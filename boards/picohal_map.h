/*
  picoHAL_map.h - Board mapping for PicoHAL (modified for custom use)

  Part of grblHAL

  Copyright (c) 2021-2023 Andrew Marles
  Copyright (c) 2024 Mitchell Grams

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#if TRINAMIC_ENABLE
#error Trinamic plugin not supported!
#endif

#if N_ABC_MOTORS > 1
#error "Axis configuration is not supported!"
#endif

#define BOARD_NAME "PicoHAL"
#define BOARD_URL "https://github.com/Expatria-Technologies/PicoHAL"

// Define step pulse output pins.
#define STEP_PORT             GPIO_PIO  // N_AXIS pin PIO SM
#define STEP_PINS_BASE        23        // N_AXIS number of consecutive pins are used by PIO

// Define step direction output pins.
#define DIRECTION_PORT        GPIO_OUTPUT
#define DIRECTION_OUTMODE     GPIO_MAP
#define X_DIRECTION_PIN       18
#define Y_DIRECTION_PIN       19
#define Z_DIRECTION_PIN       22

#define M3_AVAILABLE
#define M3_DIRECTION_PIN      12

// Define stepper driver enable/disable output pin.
#define ENABLE_PORT           GPIO_OUTPUT
#define STEPPERS_ENABLE_PIN   13

// Define homing/hard limit switch input pins.  Currently configured so that X and Z limit pins are shared.
#define LIMIT_PORT            GPIO_INPUT
#define X_LIMIT_PIN           7
#define Y_LIMIT_PIN           7
#define Z_LIMIT_PIN           7
#define M3_LIMIT_PIN          7

// Aux Outputs
#define AUXOUTPUT0_PORT         GPIO_OUTPUT // MODBUS DIRECTION
#define AUXOUTPUT0_PIN          25
#define AUXOUTPUT1_PORT         GPIO_OUTPUT
#define AUXOUTPUT1_PIN          16
#define AUXOUTPUT2_PORT         GPIO_OUTPUT
#define AUXOUTPUT2_PIN          17
#define AUXOUTPUT3_PORT         GPIO_OUTPUT
#define AUXOUTPUT3_PIN          20
#define AUXOUTPUT4_PORT         GPIO_OUTPUT
#define AUXOUTPUT4_PIN          21
#define AUXOUTPUT5_PORT         GPIO_OUTPUT 
#define AUXOUTPUT5_PIN          15
#define AUXOUTPUT6_PORT         GPIO_OUTPUT
#define AUXOUTPUT6_PIN          10
#define AUXOUTPUT7_PORT         GPIO_OUTPUT
#define AUXOUTPUT7_PIN          5

#if DRIVER_SPINDLE_ENABLE
#define SPINDLE_PORT            GPIO_OUTPUT
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_ENA
#define SPINDLE_ENABLE_PIN      AUXOUTPUT1_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_PWM
#define SPINDLE_PWM_PIN         AUXOUTPUT2_PIN
#endif
#if DRIVER_SPINDLE_ENABLE & SPINDLE_DIR
#define SPINDLE_DIRECTION_PIN   AUXOUTPUT3_PIN
#endif

// Aux Inputs
#define AUXINPUT0_PIN           14  
#define AUXINPUT1_PIN           6 

// Modbus 
#define MODBUS_DIR_AUX          0
#define SERIAL1_PORT            1

#if MODBUS_ENABLE
#define MODBUS_SERIAL_PORT      1
#endif

// UART 0
#define UART_TX_PIN             28
#define UART_RX_PIN             29

#define RESET_PIN               11

// UART 1 (Modbus)
#define UART_1_TX_PIN           8
#define UART_1_RX_PIN           9

// Ethernet
#if ETHERNET_ENABLE
#define SPI_PORT            0
#define SPI_SCK_PIN         2
#define SPI_MOSI_PIN        3
#define SPI_MISO_PIN        0
#define SPI_CS_PIN          1
#define SPI_IRQ_PIN         4
#define SPI_RST_PORT        GPIO_OUTPUT
#endif