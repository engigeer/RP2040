/*
  flexihal2350.c - init code for flexihal2350

  Part of grblHAL

  Copyright (c) 2021-2025 Terje Io
  Copyright (c) 2025 Expatria Technologies Inc.
  Copyright (c) 2026 Mitchell Grams
  
  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/

#include "driver.h"

#if defined(BOARD_FLEXIHAL2350)

#include "grbl/task.h"
#include "grbl/state_machine.h"

//static driver_setup_ptr driver_setup;

extern xbar_t *get_motor_fault_inputs (void);
extern xbar_t *iox_pins[IOX_PIN_COUNT];

static control_signals_get_state_ptr hal_control_get_state;
static xbar_t *fault_inputs;
static stepper_status_t stepper_status = {};

static void poll_motor_fault (void *data)
{
    // TODO: use interrupts rather than polling for motor faults
    stepper_status.fault.state = 0;
        
    if(settings.motor_fault_enable.mask) {

        uint_fast8_t idx;

        for(idx = 0; idx < N_AXIS; idx++) {
            uint8_t axis = xbar_fault_pin_to_axis(fault_inputs[idx].function);

            if(bit_istrue(settings.motor_fault_enable.mask, bit(axis))) {
                if(EXPANDER_IN(fault_inputs[idx].pin)^ bit_istrue(settings.motor_fault_invert.mask, bit(axis)))
                    xbar_stepper_state_set(&stepper_status.fault, axis, fault_inputs[idx].function >= Input_MotorFaultX_2); 
            }
        }

        if(stepper_status.fault.state && !(state_get() & (STATE_ALARM|STATE_ESTOP))) {
            control_signals_t signals = hal_control_get_state();
            signals.motor_fault = On;
            hal.control.interrupt_callback(signals);
        }
    }

    task_add_delayed(poll_motor_fault, NULL, 25);
}

static stepper_status_t getDriverStatus (bool reset)
{
    if(reset)
        stepper_status.fault.state = 0;

    return stepper_status;
}

static control_signals_t getControlState (void)
{
    control_signals_t state = hal_control_get_state();

    state.motor_fault = stepper_status.fault.state != 0;

    return state;
}

static void driverSetup (void *data)
{
    if((hal.signals_cap.motor_fault = settings.motor_fault_enable.value && (fault_inputs = get_motor_fault_inputs()))) {

        task_add_delayed(poll_motor_fault, NULL, 25);

        hal.stepper.status = getDriverStatus;

        hal_control_get_state = hal.control.get_state;
        hal.control.get_state = getControlState;
    }
}

void board_init (void)
{
    task_run_on_startup(driverSetup, NULL);

    // driver_setup = hal.driver_setup;
    // hal.driver_setup = driverSetup;

}

#endif
