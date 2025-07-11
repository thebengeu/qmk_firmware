/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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

#pragma once

/* Handedness. */
#define SPLIT_HAND_PIN GP29
#define SPLIT_HAND_PIN_LOW_IS_LEFT // High -> right, Low -> left.

/* VBUS detection. */
#define USB_VBUS_PIN GP19

/* CRC. */
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

#if 1
#   define I2C_DRIVER I2CD1
#   define I2C1_SDA_PIN GP2
#   define I2C1_SCL_PIN GP3
#   define I2C1_CLOCK_SPEED 1000000
#   define DIGITIZER_MOTION_PIN GP12
#   define DIGITIZER_MOTION_PIN_ACTIVE_LOW yes
#   define PROCYON_42_50
#else
    /* Cirque trackpad over SPI. */
#   define SPI_DRIVER SPID0
#   define SPI_SCK_PIN GP22
#   define SPI_MOSI_PIN GP23
#   define SPI_MISO_PIN GP20
#   define POINTING_DEVICE_CS_PIN GP21
#   undef CIRQUE_PINNACLE_DIAMETER_MM
#   define CIRQUE_PINNACLE_DIAMETER_MM 40
#endif

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

// Reduce soft serial speed: Work around rp2040 issues
#define SELECT_SOFT_SERIAL_SPEED 4
