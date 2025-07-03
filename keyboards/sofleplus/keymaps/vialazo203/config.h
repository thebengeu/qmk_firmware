/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 * Modification for Vial support by Drew Petersen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// clang-format off

#pragma once
#define EE_HANDS
#define SPLIT_WATCHDOG_ENABLE


/* i2c oled for left*/
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3

#define AZOTEQ_IQS5XX_TPS43
#define AZOTEQ_IQS5XX_ROTATION_180


/* azoteq config: extend drag time */
#define AZOTEQ_IQS5XX_HOLD_TIME 500 // Default 300
#define AZOTEQ_IQS5XX_SCROLL_INITIAL_DISTANCE 10 // Default 50

#define AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE true //(Optional) Emulates holding left click to select text.



