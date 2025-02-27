/**
 * @file main.c
 * @author Haolan Zhan | Leanna Nguyen
 * @version 1
 * @date 6/2020
 *
 * @brief Simple doodle jump - like game
 * @note 
 * Once the microbit is powered on, the device enters it's initial state, where
 * a string is displayed on the led matrix. 
 * 
 * Once either button on the microbit is pressed, the game transistions into the play state
 * 
 * In the play state, the character is a 1x1 pixel that is falling a constant speed. 
 * 
 * Platform of random sizes and x-positions are falling slower than the speed that the 
 * character falls. Tilt the microbit in order for the character to move left and right
 * as it is falling. The goal is to have the character land on a platform before the 
 * platform falls below the last row. Once the character has made contact with a platform, 
 * it jumps up a few rows. 
 * 
 * Keep tilting and making contact with the platforms to stay alive. Note that the character will 
 * not detect a collision on the way up with platforms (i.e. the character will jump only when
 * making contact with a platform on its way down, just like doodle jump the game). Every platform
 * that falls below the last row earns the player points. 
 * 
 * The game is over when the character falls below the last row, and the game transitions 
 * to a game over state, where a string is displayed for the score. 
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf_delay.h"

#include "led_matrix.h"
#include "microbit_v2.h"
#include "lsm303agr.h"
#include "nrf_twi_mngr.h"
#include "rng.h"

NRF_TWI_MNGR_DEF(twi_mngr_instance, 1, 0);

int main(void)
{
  printf("Board started!\n");
  map_char('!');

  // initialize led_matrix and rng peripheral
  led_matrix_init(); //this also essentially begins the first state of the game
  rng_init();

  // Initialize I2C peripheral and driver based on IO pin configurations
  nrf_drv_twi_config_t i2c_config = NRF_DRV_TWI_DEFAULT_CONFIG;
  i2c_config.scl = I2C_SCL; // SCL pin definition
  i2c_config.sda = I2C_SDA; // SDA pin definition
  i2c_config.frequency = NRF_TWIM_FREQ_100K;
  i2c_config.interrupt_priority = 0;
  nrf_twi_mngr_init(&twi_mngr_instance, &i2c_config);

  // Initialize the LSM303AGR accelerometer/magnetometer sensor
  lsm303agr_init(&twi_mngr_instance);

  // Main application loop - the init functions should take care of all the timer initialization, and the behavior
  // of the game is determined by all the timer callback functions
  while (1)
  {
    /// testing purposes
    // Acceleration
    // accel = lsm303agr_read_accelerometer();
    // printf("Accel_X: %f     Accel_Y: %f     Accel_Z: %f\n", accel.x_axis, accel.y_axis, accel.z_axis);
    // Tilt
    // theta = get_theta(accel);
    // printf("Tilt angel theta: %f\n", theta);
    nrf_delay_ms(1000);
  }
}
