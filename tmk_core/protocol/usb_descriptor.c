/*
 * Copyright 2012 Jun Wako <wakojun@gmail.com>
 * This file is based on:
 *     LUFA-120219/Demos/Device/Lowlevel/KeyboardMouse
 *     LUFA-120219/Demos/Device/Lowlevel/GenericHID
 */

/*
                         LUFA Library
         Copyright (C) Dean Camera, 2012.

    dean [at] fourwalledcubicle [dot] com
                     www.lufa-lib.org
*/

/*
    Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
    Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)

    Permission to use, copy, modify, distribute, and sell this
    software and its documentation for any purpose is hereby granted
    without fee, provided that the above copyright notice appear in
    all copies and that both that the copyright notice and this
    permission notice and warranty disclaimer appear in supporting
    documentation, and that the name of the author not be used in
    advertising or publicity pertaining to distribution of the
    software without specific, written prior permission.

    The author disclaim all warranties with regard to this
    software, including all implied warranties of merchantability
    and fitness.  In no event shall the author be liable for any
    special, indirect or consequential damages or any damages
    whatsoever resulting from loss of use, data or profits, whether
    in an action of contract, negligence or other tortious action,
    arising out of or in connection with the use or performance of
    this software.
*/

#include "util.h"
#include "report.h"
#include "usb_descriptor.h"
#include "usb_descriptor_common.h"

#ifdef JOYSTICK_ENABLE
#    include "joystick.h"
#endif

#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif

#if defined(SERIAL_NUMBER) || (defined(SERIAL_NUMBER_USE_HARDWARE_ID) && SERIAL_NUMBER_USE_HARDWARE_ID == TRUE)

#    define HAS_SERIAL_NUMBER

#    if defined(SERIAL_NUMBER_USE_HARDWARE_ID) && SERIAL_NUMBER_USE_HARDWARE_ID == TRUE
#        include "hardware_id.h"
#    endif

#endif // defined(SERIAL_NUMBER) || (defined(SERIAL_NUMBER_USE_HARDWARE_ID) && SERIAL_NUMBER_USE_HARDWARE_ID == TRUE)

// clang-format off

/*
 * HID report descriptors
 */
#ifdef KEYBOARD_SHARED_EP
const USB_Descriptor_HIDReport_Datatype_t PROGMEM SharedReport[] = {
#    define SHARED_REPORT_STARTED
#else
const USB_Descriptor_HIDReport_Datatype_t PROGMEM KeyboardReport[] = {
#endif
    HID_RI_USAGE_PAGE(8, 0x01),        // Generic Desktop
    HID_RI_USAGE(8, 0x06),             // Keyboard
    HID_RI_COLLECTION(8, 0x01),        // Application
#ifdef KEYBOARD_SHARED_EP
        HID_RI_REPORT_ID(8, REPORT_ID_KEYBOARD),
#endif
        // Modifiers (8 bits)
        HID_RI_USAGE_PAGE(8, 0x07),    // Keyboard/Keypad
        HID_RI_USAGE_MINIMUM(8, 0xE0), // Keyboard Left Control
        HID_RI_USAGE_MAXIMUM(8, 0xE7), // Keyboard Right GUI
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x08),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        // Reserved (1 byte)
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_CONSTANT),
        // Keycodes (6 bytes)
        HID_RI_USAGE_PAGE(8, 0x07),    // Keyboard/Keypad
        HID_RI_USAGE_MINIMUM(8, 0x00),
        HID_RI_USAGE_MAXIMUM(8, 0xFF),
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, 0x06),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE),

        // Status LEDs (5 bits)
        HID_RI_USAGE_PAGE(8, 0x08),    // LED
        HID_RI_USAGE_MINIMUM(8, 0x01), // Num Lock
        HID_RI_USAGE_MAXIMUM(8, 0x05), // Kana
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x05),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
        // LED padding (3 bits)
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x03),
        HID_RI_OUTPUT(8, HID_IOF_CONSTANT),
    HID_RI_END_COLLECTION(0),
#ifndef KEYBOARD_SHARED_EP
};
#endif

#ifdef MOUSE_ENABLE
#    ifndef MOUSE_SHARED_EP
const USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[] = {
#    elif !defined(SHARED_REPORT_STARTED)
const USB_Descriptor_HIDReport_Datatype_t PROGMEM SharedReport[] = {
#        define SHARED_REPORT_STARTED
#    endif
    HID_RI_USAGE_PAGE(8, 0x01),            // Generic Desktop
    HID_RI_USAGE(8, 0x02),                 // Mouse
    HID_RI_COLLECTION(8, 0x01),            // Application
#    ifdef MOUSE_SHARED_EP
        HID_RI_REPORT_ID(8, REPORT_ID_MOUSE),
#    endif
        HID_RI_USAGE(8, 0x01),             // Pointer
        HID_RI_COLLECTION(8, 0x00),        // Physical
            // Buttons (8 bits)
            HID_RI_USAGE_PAGE(8, 0x09),    // Button
            HID_RI_USAGE_MINIMUM(8, 0x01), // Button 1
            HID_RI_USAGE_MAXIMUM(8, 0x08), // Button 8
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),
            HID_RI_REPORT_COUNT(8, 0x08),
            HID_RI_REPORT_SIZE(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

#    ifdef MOUSE_EXTENDED_REPORT
            // Boot protocol XY ignored in Report protocol
            HID_RI_REPORT_COUNT(8, 0x02),
            HID_RI_REPORT_SIZE(8, 0x08),
            HID_RI_INPUT(8, HID_IOF_CONSTANT),
#    endif
            // X/Y position (2 or 4 bytes)
            HID_RI_USAGE_PAGE(8, 0x01),    // Generic Desktop
            HID_RI_USAGE(8, 0x30),         // X
            HID_RI_USAGE(8, 0x31),         // Y
#    ifndef MOUSE_EXTENDED_REPORT
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x02),
            HID_RI_REPORT_SIZE(8, 0x08),
#    else
            HID_RI_LOGICAL_MINIMUM(16, -32767),
            HID_RI_LOGICAL_MAXIMUM(16,  32767),
            HID_RI_REPORT_COUNT(8, 0x02),
            HID_RI_REPORT_SIZE(8, 0x10),
#    endif
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

            // Vertical wheel (1 or 2 bytes)
            HID_RI_USAGE(8, 0x38),     // Wheel
#    ifndef WHEEL_EXTENDED_REPORT
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x08),
#    else
            HID_RI_LOGICAL_MINIMUM(16, -32767),
            HID_RI_LOGICAL_MAXIMUM(16,  32767),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x10),
#    endif
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),
            // Horizontal wheel (1 or 2 bytes)
            HID_RI_USAGE_PAGE(8, 0x0C),// Consumer
            HID_RI_USAGE(16, 0x0238),  // AC Pan
#    ifndef WHEEL_EXTENDED_REPORT
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x08),
#    else
            HID_RI_LOGICAL_MINIMUM(16, -32767),
            HID_RI_LOGICAL_MAXIMUM(16,  32767),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x10),
#    endif
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),
        HID_RI_END_COLLECTION(0),
    HID_RI_END_COLLECTION(0),
#    ifndef MOUSE_SHARED_EP
};
#    endif
#endif

#ifdef JOYSTICK_ENABLE
#    ifndef JOYSTICK_SHARED_EP
const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport[] = {
#    elif !defined(SHARED_REPORT_STARTED)
const USB_Descriptor_HIDReport_Datatype_t PROGMEM SharedReport[] = {
#        define SHARED_REPORT_STARTED
#    endif
    HID_RI_USAGE_PAGE(8, 0x01),     // Generic Desktop
    HID_RI_USAGE(8, 0x04),          // Joystick
    HID_RI_COLLECTION(8, 0x01),     // Application
#    ifdef JOYSTICK_SHARED_EP
        HID_RI_REPORT_ID(8, REPORT_ID_JOYSTICK),
#    endif
        HID_RI_COLLECTION(8, 0x00), // Physical
#    if JOYSTICK_AXIS_COUNT > 0
            HID_RI_USAGE_PAGE(8, 0x01), // Generic Desktop
            HID_RI_USAGE(8, 0x30),      // X
#        if JOYSTICK_AXIS_COUNT > 1
            HID_RI_USAGE(8, 0x31),      // Y
#        endif
#        if JOYSTICK_AXIS_COUNT > 2
            HID_RI_USAGE(8, 0x32),      // Z
#        endif
#        if JOYSTICK_AXIS_COUNT > 3
            HID_RI_USAGE(8, 0x33),      // Rx
#        endif
#        if JOYSTICK_AXIS_COUNT > 4
            HID_RI_USAGE(8, 0x34),      // Ry
#        endif
#        if JOYSTICK_AXIS_COUNT > 5
            HID_RI_USAGE(8, 0x35),      // Rz
#        endif
#        if JOYSTICK_AXIS_RESOLUTION == 8
            HID_RI_LOGICAL_MINIMUM(8, -JOYSTICK_MAX_VALUE),
            HID_RI_LOGICAL_MAXIMUM(8, JOYSTICK_MAX_VALUE),
            HID_RI_REPORT_COUNT(8, JOYSTICK_AXIS_COUNT),
            HID_RI_REPORT_SIZE(8, 0x08),
#        else
            HID_RI_LOGICAL_MINIMUM(16, -JOYSTICK_MAX_VALUE),
            HID_RI_LOGICAL_MAXIMUM(16, JOYSTICK_MAX_VALUE),
            HID_RI_REPORT_COUNT(8, JOYSTICK_AXIS_COUNT),
            HID_RI_REPORT_SIZE(8, 0x10),
#        endif
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
#    endif

#    ifdef JOYSTICK_HAS_HAT
            // Hat Switch (4 bits)
            HID_RI_USAGE(8, 0x39), // Hat Switch
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x07),
            HID_RI_PHYSICAL_MINIMUM(8, 0),
            HID_RI_PHYSICAL_MAXIMUM(16, 315),
            HID_RI_UNIT(8, 0x14),  // Degree, English Rotation
            HID_RI_REPORT_COUNT(8, 1),
            HID_RI_REPORT_SIZE(8, 4),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NULLSTATE),
            // Padding (4 bits)
            HID_RI_REPORT_COUNT(8, 0x04),
            HID_RI_REPORT_SIZE(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_CONSTANT),
#    endif

#    if JOYSTICK_BUTTON_COUNT > 0
            HID_RI_USAGE_PAGE(8, 0x09), // Button
            HID_RI_USAGE_MINIMUM(8, 0x01),
            HID_RI_USAGE_MAXIMUM(8, JOYSTICK_BUTTON_COUNT),
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),
            HID_RI_REPORT_COUNT(8, JOYSTICK_BUTTON_COUNT),
            HID_RI_REPORT_SIZE(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

#        if (JOYSTICK_BUTTON_COUNT % 8) != 0
            HID_RI_REPORT_COUNT(8, 8 - (JOYSTICK_BUTTON_COUNT % 8)),
            HID_RI_REPORT_SIZE(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_CONSTANT),
#        endif
#    endif
        HID_RI_END_COLLECTION(0),
    HID_RI_END_COLLECTION(0),
#    ifndef JOYSTICK_SHARED_EP
};
#    endif
#endif

#ifdef DIGITIZER_ENABLE
#    ifndef DIGITIZER_SHARED_EP
const USB_Descriptor_HIDReport_Datatype_t PROGMEM DigitizerReport[] = {
#    elif !defined(SHARED_REPORT_STARTED)
const USB_Descriptor_HIDReport_Datatype_t PROGMEM SharedReport[] = {
#        define SHARED_REPORT_STARTED
#    endif
#    ifdef DIGITIZER_HAS_STYLUS
    HID_RI_USAGE_PAGE(8, 0x0D),            // Digitizers
    HID_RI_USAGE(8, 0x02),                 // Pen
    HID_RI_COLLECTION(8, 0x01),            // Application
        HID_RI_REPORT_ID(8, REPORT_ID_DIGITIZER_STYLUS),
        HID_RI_USAGE(8, 0x20),             // Stylus
        HID_RI_COLLECTION(8, 0x00),        // Physical
            // In Range, Tip Switch & Barrel Switch (3 bits)
            HID_RI_USAGE(8, 0x32),         // In Range
            HID_RI_USAGE(8, 0x42),         // Tip Switch
            HID_RI_USAGE(8, 0x44),         // Barrel Switch
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),
            HID_RI_REPORT_COUNT(8, 0x03),
            HID_RI_REPORT_SIZE(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
            // Padding (5 bits)
            HID_RI_REPORT_COUNT(8, 0x05),
            HID_RI_INPUT(8, HID_IOF_CONSTANT),

            // X/Y Position (4 bytes)
            HID_RI_USAGE_PAGE(8, 0x01),    // Generic Desktop
            HID_RI_PUSH(0),
            HID_RI_LOGICAL_MINIMUM(8, 0x0),
            HID_RI_LOGICAL_MAXIMUM(16, DIGITIZER_RESOLUTION_X),
            HID_RI_REPORT_SIZE(8, 16),
            HID_RI_UNIT_EXPONENT(8, 0x0E), // -2
            HID_RI_UNIT(8, 0x11),          // CM, English Linear
            HID_RI_USAGE(8, 0x30),         // X
            HID_RI_PHYSICAL_MINIMUM(8, 0x0),
            HID_RI_PHYSICAL_MAXIMUM(16, (DIGITIZER_WIDTH_MM * 10)),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
            HID_RI_LOGICAL_MAXIMUM(16, DIGITIZER_RESOLUTION_Y),
            HID_RI_PHYSICAL_MAXIMUM(16, (DIGITIZER_HEIGHT_MM * 10)),
            HID_RI_USAGE(8, 0x31),         // Y
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
            HID_RI_POP(0),
        HID_RI_END_COLLECTION(0),
    HID_RI_END_COLLECTION(0),
#    endif

#    if DIGITIZER_FINGER_COUNT > 0
    HID_RI_USAGE_PAGE(8, 0x0D),            // Digitizers
    HID_RI_USAGE(8, 0x05),                 // Touchpad
    HID_RI_COLLECTION(8, 0x01),            // Application
        HID_RI_REPORT_ID(8, REPORT_ID_DIGITIZER),
// The digitizer finger report is large and repetitive, so it has been moved into a macro
#        define DIGITIZER_FINGER_REPORT                                              \
        HID_RI_USAGE_PAGE(8, 0x0D),        /*  Digitizers */                     \
        HID_RI_USAGE(8, 0x22),             /*  Finger */                         \
        HID_RI_COLLECTION(8, 0x00),        /*  Physical */                       \
            HID_RI_PUSH(0),                                                      \
            HID_RI_LOGICAL_MINIMUM(8, 0x00),                                     \
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),                                     \
            /*  Tip Switch, Confidence (2 bits) */                               \
            HID_RI_USAGE(8, 0x47),         /*  Confidence */                     \
            HID_RI_USAGE(8, 0x42),         /*  Tip Switch */                     \
            HID_RI_REPORT_COUNT(8, 0x02),                                        \
            HID_RI_REPORT_SIZE(8, 0x01),                                         \
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE), \
                                                                                 \
            /*  Padding (6 bits) */                                              \
            HID_RI_REPORT_SIZE(8, 0x01),                                         \
            HID_RI_REPORT_COUNT(8, 0x06),                                        \
            HID_RI_INPUT(8, HID_IOF_CONSTANT),                                   \
                                                                                 \
            /*  Contact identifier (3 bits) */                                   \
            HID_RI_REPORT_COUNT(8, 0x01),                                        \
            HID_RI_REPORT_SIZE(8, 0x03),                                         \
            HID_RI_LOGICAL_MAXIMUM(8, 0x05),                                     \
            HID_RI_USAGE(8, 0x51),         /*  Contact identifier */             \
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE), \
                                                                                 \
            /*  Padding (5 bits) */                                              \
            HID_RI_REPORT_SIZE(8, 0x01),                                         \
            HID_RI_REPORT_COUNT(8, 0x05),                                        \
            HID_RI_INPUT(8, HID_IOF_CONSTANT),                                   \
                                                                                 \
            /*  X/Y Position (4 bytes) */                                        \
            HID_RI_USAGE_PAGE(8, 0x01),    /*  Generic Desktop */                \
            HID_RI_LOGICAL_MINIMUM(8, 0x0),                                      \
            HID_RI_LOGICAL_MAXIMUM(16, DIGITIZER_RESOLUTION_X),                  \
            HID_RI_REPORT_SIZE(8, 16),                                           \
            HID_RI_UNIT_EXPONENT(8, 0x0E), /*  -2 */                             \
            HID_RI_UNIT(8, 0x11),          /*  CM, English Linear */             \
            HID_RI_USAGE(8, 0x30),         /*  X */                              \
            HID_RI_PHYSICAL_MINIMUM(8, 0x0),                                     \
            HID_RI_PHYSICAL_MAXIMUM(16, (DIGITIZER_WIDTH_MM * 10)),              \
            HID_RI_REPORT_COUNT(8, 0x01),                                        \
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE), \
            HID_RI_LOGICAL_MAXIMUM(16, DIGITIZER_RESOLUTION_Y),                  \
            HID_RI_PHYSICAL_MAXIMUM(16, (DIGITIZER_HEIGHT_MM * 10)),             \
            HID_RI_USAGE(8, 0x31),         /*  Y */                              \
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE), \
            HID_RI_POP(0),                                                       \
        HID_RI_END_COLLECTION(0)
        DIGITIZER_FINGER_REPORT,
#    endif
#    if DIGITIZER_FINGER_COUNT > 1
        DIGITIZER_FINGER_REPORT,
#    endif
#    if DIGITIZER_FINGER_COUNT > 2
        DIGITIZER_FINGER_REPORT,
#    endif
#    if DIGITIZER_FINGER_COUNT > 3
        DIGITIZER_FINGER_REPORT,
#    endif
#    if DIGITIZER_FINGER_COUNT > 4
        DIGITIZER_FINGER_REPORT,
#    endif
#    if DIGITIZER_FINGER_COUNT > 0
        HID_RI_PUSH(0),
        HID_RI_UNIT_EXPONENT(8, 0x0C),  // -4
        HID_RI_UNIT(16, 0x1001),        // Seconds, SI Linear
        HID_RI_USAGE_PAGE(8, 0x0D),    // Digitizers
        HID_RI_USAGE(8, 0x56),         // Scan Time
        HID_RI_PHYSICAL_MINIMUM(0),
        HID_RI_LOGICAL_MINIMUM(0),
        HID_RI_PHYSICAL_MAXIMUM(32, 65535),
        HID_RI_LOGICAL_MAXIMUM(32, 65535),
        HID_RI_REPORT_SIZE(8, 16),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_USAGE(8, 0x54),         // Contact count
        HID_RI_LOGICAL_MAXIMUM(8, 5),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x04),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        // Buttons
        HID_RI_USAGE_PAGE(8, 0x09),    // Buttons
        HID_RI_USAGE(8, 0x01),         // Button 1
        HID_RI_USAGE(8, 0x02),         // Button 2
        HID_RI_USAGE(8, 0x03),         // Button 3
        HID_RI_LOGICAL_MAXIMUM(8, 1),
        HID_RI_REPORT_SIZE(8, 1),
        HID_RI_REPORT_COUNT(8, 3),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        // Padding (1 bits)
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_CONSTANT),

        HID_RI_USAGE_PAGE(8, 0x0D),    // Digitizers
        HID_RI_REPORT_ID(8, REPORT_ID_DIGITIZER_GET_FEATURE),
        HID_RI_USAGE(8, 0x55),         // Contact Count Maximum
        HID_RI_REPORT_SIZE(8, 0x04),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_LOGICAL_MAXIMUM(8, 15),
        HID_RI_FEATURE(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_USAGE(8, 0x59),         // Pad type
        HID_RI_REPORT_SIZE(8, 0x03),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_LOGICAL_MAXIMUM(8, 7),
        HID_RI_FEATURE(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_USAGE(8, 0x57),         // Surface switch - Apple want this, not sure if they are happy with the collection below
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_LOGICAL_MAXIMUM(8, 1),
        HID_RI_FEATURE(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        HID_RI_USAGE_PAGE(16, 0xFF),           // Vendor
        HID_RI_REPORT_ID(8, REPORT_ID_DIGITIZER_CERTIFICATE),
        HID_RI_USAGE(8, 0xC5),                 // Vendor usage
        HID_RI_LOGICAL_MAXIMUM(16, 255),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_REPORT_COUNT(16, 256),
        HID_RI_FEATURE(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        HID_RI_POP(0),
        HID_RI_END_COLLECTION(0),

        HID_RI_USAGE_PAGE(8, 0x0D),            // Digitizers
        HID_RI_USAGE(8, 0x0E),                 // Configuration
        HID_RI_COLLECTION(8, 0x01),            // Application
        HID_RI_PUSH(0),
        HID_RI_REPORT_ID(8, REPORT_ID_DIGITIZER_CONFIGURATION),
        HID_RI_USAGE(8, 0x22),                 // Finger
        HID_RI_COLLECTION(8, 0x02),            // Logical
        HID_RI_USAGE(8, 0x52),                 // Input mode
        HID_RI_LOGICAL_MINIMUM(8, 0),
        HID_RI_LOGICAL_MAXIMUM(8, 10),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_FEATURE(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_END_COLLECTION(0),

        HID_RI_USAGE(8, 0x22),                 // Finger
        HID_RI_COLLECTION(8, 0x00),            // Physical
        HID_RI_REPORT_ID(8, REPORT_ID_DIGITIZER_FUNCTION_SWITCH),
        HID_RI_USAGE(8, 0x57),                 // Surface switch
        HID_RI_USAGE(8, 0x58),                 // Button switch
        HID_RI_LOGICAL_MAXIMUM(8, 1),
        HID_RI_REPORT_COUNT(8, 0x02),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_FEATURE(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_REPORT_COUNT(8, 0x06),
        HID_RI_FEATURE(8, HID_IOF_CONSTANT | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_POP(0),
        HID_RI_END_COLLECTION(0),
    HID_RI_END_COLLECTION(0),
#    endif
#    ifndef DIGITIZER_SHARED_EP
};
#    endif
#endif

#if defined(SHARED_EP_ENABLE) && !defined(SHARED_REPORT_STARTED)
const USB_Descriptor_HIDReport_Datatype_t PROGMEM SharedReport[] = {
#endif

#ifdef EXTRAKEY_ENABLE
    HID_RI_USAGE_PAGE(8, 0x01),           // Generic Desktop
    HID_RI_USAGE(8, 0x80),                // System Control
    HID_RI_COLLECTION(8, 0x01),           // Application
        HID_RI_REPORT_ID(8, REPORT_ID_SYSTEM),
        HID_RI_USAGE_MINIMUM(8, 0x01),    // Pointer
        HID_RI_USAGE_MAXIMUM(16, 0x00B7), // System Display LCD Autoscale
        HID_RI_LOGICAL_MINIMUM(8, 0x01),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00B7),
        HID_RI_REPORT_COUNT(8, 1),
        HID_RI_REPORT_SIZE(8, 16),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE),
    HID_RI_END_COLLECTION(0),

    HID_RI_USAGE_PAGE(8, 0x0C),           // Consumer
    HID_RI_USAGE(8, 0x01),                // Consumer Control
    HID_RI_COLLECTION(8, 0x01),           // Application
        HID_RI_REPORT_ID(8, REPORT_ID_CONSUMER),
        HID_RI_USAGE_MINIMUM(8, 0x01),    // Consumer Control
        HID_RI_USAGE_MAXIMUM(16, 0x02A0), // AC Desktop Show All Applications
        HID_RI_LOGICAL_MINIMUM(8, 0x01),
        HID_RI_LOGICAL_MAXIMUM(16, 0x02A0),
        HID_RI_REPORT_COUNT(8, 1),
        HID_RI_REPORT_SIZE(8, 16),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE),
    HID_RI_END_COLLECTION(0),
#endif

#ifdef PROGRAMMABLE_BUTTON_ENABLE
    HID_RI_USAGE_PAGE(8, 0x0C),            // Consumer
    HID_RI_USAGE(8, 0x01),                 // Consumer Control
    HID_RI_COLLECTION(8, 0x01),            // Application
        HID_RI_REPORT_ID(8, REPORT_ID_PROGRAMMABLE_BUTTON),
        HID_RI_USAGE(8, 0x03),             // Programmable Buttons
        HID_RI_COLLECTION(8, 0x04),        // Named Array
            HID_RI_USAGE_PAGE(8, 0x09),    // Button
            HID_RI_USAGE_MINIMUM(8, 0x01), // Button 1
            HID_RI_USAGE_MAXIMUM(8, 0x20), // Button 32
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),
            HID_RI_REPORT_COUNT(8, 32),
            HID_RI_REPORT_SIZE(8, 1),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_END_COLLECTION(0),
    HID_RI_END_COLLECTION(0),
#endif

#ifdef NKRO_ENABLE
    HID_RI_USAGE_PAGE(8, 0x01),        // Generic Desktop
    HID_RI_USAGE(8, 0x06),             // Keyboard
    HID_RI_COLLECTION(8, 0x01),        // Application
        HID_RI_REPORT_ID(8, REPORT_ID_NKRO),
        // Modifiers (8 bits)
        HID_RI_USAGE_PAGE(8, 0x07),    // Keyboard/Keypad
        HID_RI_USAGE_MINIMUM(8, 0xE0), // Keyboard Left Control
        HID_RI_USAGE_MAXIMUM(8, 0xE7), // Keyboard Right GUI
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x08),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        // Keycodes
        HID_RI_USAGE_PAGE(8, 0x07),    // Keyboard/Keypad
        HID_RI_USAGE_MINIMUM(8, 0x00),
        HID_RI_USAGE_MAXIMUM(8, NKRO_REPORT_BITS * 8 - 1),
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, NKRO_REPORT_BITS * 8),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        // Status LEDs (5 bits)
        HID_RI_USAGE_PAGE(8, 0x08),    // LED
        HID_RI_USAGE_MINIMUM(8, 0x01), // Num Lock
        HID_RI_USAGE_MAXIMUM(8, 0x05), // Kana
        HID_RI_REPORT_COUNT(8, 0x05),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
        // LED padding (3 bits)
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x03),
        HID_RI_OUTPUT(8, HID_IOF_CONSTANT),
    HID_RI_END_COLLECTION(0),
#endif

#ifdef SHARED_EP_ENABLE
};
#endif

#ifdef RAW_ENABLE
const USB_Descriptor_HIDReport_Datatype_t PROGMEM RawReport[] = {
    HID_RI_USAGE_PAGE(16, RAW_USAGE_PAGE), // Vendor Defined
    HID_RI_USAGE(8, RAW_USAGE_ID),         // Vendor Defined
    HID_RI_COLLECTION(8, 0x01),    // Application
        // Data to host
        HID_RI_USAGE(8, 0x62),     // Vendor Defined
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, RAW_EPSIZE),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        // Data from host
        HID_RI_USAGE(8, 0x63),     // Vendor Defined
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, RAW_EPSIZE),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
    HID_RI_END_COLLECTION(0),
};
#endif

#ifdef CONSOLE_ENABLE
const USB_Descriptor_HIDReport_Datatype_t PROGMEM ConsoleReport[] = {
    HID_RI_USAGE_PAGE(16, 0xFF31), // Vendor Defined (PJRC Teensy compatible)
    HID_RI_USAGE(8, 0x74),         // Vendor Defined (PJRC Teensy compatible)
    HID_RI_COLLECTION(8, 0x01),    // Application
        // Data to host
        HID_RI_USAGE(8, 0x75),     // Vendor Defined
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, CONSOLE_EPSIZE),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
    HID_RI_END_COLLECTION(0),
};
#endif

/*
 * Device descriptor
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor = {
    .Header = {
        .Size                   = sizeof(USB_Descriptor_Device_t),
        .Type                   = DTYPE_Device
    },
    .USBSpecification           = VERSION_BCD(2, 0, 0),

#if VIRTSER_ENABLE
    .Class                      = USB_CSCP_IADDeviceClass,
    .SubClass                   = USB_CSCP_IADDeviceSubclass,
    .Protocol                   = USB_CSCP_IADDeviceProtocol,
#else
    .Class                      = USB_CSCP_NoDeviceClass,
    .SubClass                   = USB_CSCP_NoDeviceSubclass,
    .Protocol                   = USB_CSCP_NoDeviceProtocol,
#endif

    .Endpoint0Size              = FIXED_CONTROL_ENDPOINT_SIZE,
    // Specified in config.h
    .VendorID                   = VENDOR_ID,
    .ProductID                  = PRODUCT_ID,
    .ReleaseNumber              = DEVICE_VER,
    .ManufacturerStrIndex       = 0x01,
    .ProductStrIndex            = 0x02,
#ifdef HAS_SERIAL_NUMBER
    .SerialNumStrIndex          = 0x03,
#else // HAS_SERIAL_NUMBER
    .SerialNumStrIndex          = 0x00,
#endif // HAS_SERIAL_NUMBER
    .NumberOfConfigurations     = FIXED_NUM_CONFIGURATIONS
};

#ifndef USB_MAX_POWER_CONSUMPTION
#    define USB_MAX_POWER_CONSUMPTION 500
#endif

#ifndef USB_POLLING_INTERVAL_MS
#    define USB_POLLING_INTERVAL_MS 1
#endif

/*
 * Configuration descriptors
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor = {
    .Config = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Configuration_Header_t),
            .Type               = DTYPE_Configuration
        },
        .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
        .TotalInterfaces        = TOTAL_INTERFACES,
        .ConfigurationNumber    = 1,
        .ConfigurationStrIndex  = NO_DESCRIPTOR,
        .ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_REMOTEWAKEUP),
        .MaxPowerConsumption    = USB_CONFIG_POWER_MA(USB_MAX_POWER_CONSUMPTION)
    },
#ifndef KEYBOARD_SHARED_EP
    /*
     * Keyboard
     */
    .Keyboard_Interface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = KEYBOARD_INTERFACE,
        .AlternateSetting       = 0x00,
        .TotalEndpoints         = 1,
        .Class                  = HID_CSCP_HIDClass,
        .SubClass               = HID_CSCP_BootSubclass,
        .Protocol               = HID_CSCP_KeyboardBootProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Keyboard_HID = {
        .Header = {
            .Size               = sizeof(USB_HID_Descriptor_HID_t),
            .Type               = HID_DTYPE_HID
        },
        .HIDSpec                = VERSION_BCD(1, 1, 1),
        .CountryCode            = 0x00,
        .TotalReportDescriptors = 1,
        .HIDReportType          = HID_DTYPE_Report,
        .HIDReportLength        = sizeof(KeyboardReport)
    },
    .Keyboard_INEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | KEYBOARD_IN_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = KEYBOARD_EPSIZE,
        .PollingIntervalMS      = USB_POLLING_INTERVAL_MS
    },
#endif

#ifdef RAW_ENABLE
    /*
     * Raw HID
     */
    .Raw_Interface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = RAW_INTERFACE,
        .AlternateSetting       = 0x00,
        .TotalEndpoints         = 2,
        .Class                  = HID_CSCP_HIDClass,
        .SubClass               = HID_CSCP_NonBootSubclass,
        .Protocol               = HID_CSCP_NonBootProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Raw_HID = {
        .Header = {
            .Size               = sizeof(USB_HID_Descriptor_HID_t),
            .Type               = HID_DTYPE_HID
        },
        .HIDSpec                = VERSION_BCD(1, 1, 1),
        .CountryCode            = 0x00,
        .TotalReportDescriptors = 1,
        .HIDReportType          = HID_DTYPE_Report,
        .HIDReportLength        = sizeof(RawReport)
    },
    .Raw_INEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | RAW_IN_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = RAW_EPSIZE,
        .PollingIntervalMS      = 0x01
    },
    .Raw_OUTEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_OUT | RAW_OUT_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = RAW_EPSIZE,
        .PollingIntervalMS      = 0x01
    },
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
    /*
     * Mouse
     */
    .Mouse_Interface  = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = MOUSE_INTERFACE,
        .AlternateSetting       = 0x00,
        .TotalEndpoints         = 1,
        .Class                  = HID_CSCP_HIDClass,
        .SubClass               = HID_CSCP_BootSubclass,
        .Protocol               = HID_CSCP_MouseBootProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Mouse_HID = {
        .Header = {
            .Size               = sizeof(USB_HID_Descriptor_HID_t),
            .Type               = HID_DTYPE_HID
        },
        .HIDSpec                = VERSION_BCD(1, 1, 1),
        .CountryCode            = 0x00,
        .TotalReportDescriptors = 1,
        .HIDReportType          = HID_DTYPE_Report,
        .HIDReportLength        = sizeof(MouseReport)
    },
    .Mouse_INEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | MOUSE_IN_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = MOUSE_EPSIZE,
        .PollingIntervalMS      = USB_POLLING_INTERVAL_MS
    },
#endif

#ifdef SHARED_EP_ENABLE
    /*
     * Shared
     */
    .Shared_Interface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = SHARED_INTERFACE,
        .AlternateSetting       = 0x00,
        .TotalEndpoints         = 1,
        .Class                  = HID_CSCP_HIDClass,
#    ifdef KEYBOARD_SHARED_EP
        .SubClass               = HID_CSCP_BootSubclass,
        .Protocol               = HID_CSCP_KeyboardBootProtocol,
#    else
        .SubClass               = HID_CSCP_NonBootSubclass,
        .Protocol               = HID_CSCP_NonBootProtocol,
#    endif
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Shared_HID = {
        .Header = {
            .Size               = sizeof(USB_HID_Descriptor_HID_t),
            .Type               = HID_DTYPE_HID
        },
        .HIDSpec                = VERSION_BCD(1, 1, 1),
        .CountryCode            = 0x00,
        .TotalReportDescriptors = 1,
        .HIDReportType          = HID_DTYPE_Report,
        .HIDReportLength        = sizeof(SharedReport)
    },
    .Shared_INEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | SHARED_IN_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = SHARED_EPSIZE,
        .PollingIntervalMS      = USB_POLLING_INTERVAL_MS
    },
#endif

#ifdef CONSOLE_ENABLE
    /*
     * Console
     */
    .Console_Interface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = CONSOLE_INTERFACE,
        .AlternateSetting       = 0x00,
        .TotalEndpoints         = 1,
        .Class                  = HID_CSCP_HIDClass,
        .SubClass               = HID_CSCP_NonBootSubclass,
        .Protocol               = HID_CSCP_NonBootProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Console_HID = {
        .Header = {
            .Size               = sizeof(USB_HID_Descriptor_HID_t),
            .Type               = HID_DTYPE_HID
        },
        .HIDSpec                = VERSION_BCD(1, 1, 1),
        .CountryCode            = 0x00,
        .TotalReportDescriptors = 1,
        .HIDReportType          = HID_DTYPE_Report,
        .HIDReportLength        = sizeof(ConsoleReport)
    },
    .Console_INEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | CONSOLE_IN_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = CONSOLE_EPSIZE,
        .PollingIntervalMS      = 0x01
    },
#endif

#ifdef MIDI_ENABLE
    /*
     * MIDI
     */
    .Audio_Interface_Association = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_Association_t),
            .Type               = DTYPE_InterfaceAssociation
        },
        .FirstInterfaceIndex    = AC_INTERFACE,
        .TotalInterfaces        = 2,
        .Class                  = AUDIO_CSCP_AudioClass,
        .SubClass               = AUDIO_CSCP_ControlSubclass,
        .Protocol               = AUDIO_CSCP_ControlProtocol,
        .IADStrIndex            = NO_DESCRIPTOR,
    },
    .Audio_ControlInterface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = AC_INTERFACE,
        .AlternateSetting       = 0,
        .TotalEndpoints         = 0,
        .Class                  = AUDIO_CSCP_AudioClass,
        .SubClass               = AUDIO_CSCP_ControlSubclass,
        .Protocol               = AUDIO_CSCP_ControlProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Audio_ControlInterface_SPC = {
        .Header = {
            .Size               = sizeof(USB_Audio_Descriptor_Interface_AC_t),
            .Type               = AUDIO_DTYPE_CSInterface
        },
        .Subtype                = AUDIO_DSUBTYPE_CSInterface_Header,
        .ACSpecification        = VERSION_BCD(1, 0, 0),
        .TotalLength            = sizeof(USB_Audio_Descriptor_Interface_AC_t),
        .InCollection           = 1,
        .InterfaceNumber        = AS_INTERFACE,
    },
    .Audio_StreamInterface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = AS_INTERFACE,
        .AlternateSetting       = 0,
        .TotalEndpoints         = 2,
        .Class                  = AUDIO_CSCP_AudioClass,
        .SubClass               = AUDIO_CSCP_MIDIStreamingSubclass,
        .Protocol               = AUDIO_CSCP_StreamingProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Audio_StreamInterface_SPC = {
        .Header = {
            .Size               = sizeof(USB_MIDI_Descriptor_AudioInterface_AS_t),
            .Type               = AUDIO_DTYPE_CSInterface
        },
        .Subtype                = AUDIO_DSUBTYPE_CSInterface_General,
        .AudioSpecification     = VERSION_BCD(1, 0, 0),
        .TotalLength            = offsetof(USB_Descriptor_Configuration_t, MIDI_Out_Jack_Endpoint_SPC) + sizeof(USB_MIDI_Descriptor_Jack_Endpoint_t) - offsetof(USB_Descriptor_Configuration_t, Audio_StreamInterface_SPC)
    },
    .MIDI_In_Jack_Emb = {
        .Header = {
            .Size               = sizeof(USB_MIDI_Descriptor_InputJack_t),
            .Type               = AUDIO_DTYPE_CSInterface
        },
        .Subtype                = AUDIO_DSUBTYPE_CSInterface_InputTerminal,
        .JackType               = MIDI_JACKTYPE_Embedded,
        .JackID = 0x01,
        .JackStrIndex           = NO_DESCRIPTOR
    },
    .MIDI_In_Jack_Ext = {
        .Header = {
            .Size               = sizeof(USB_MIDI_Descriptor_InputJack_t),
            .Type               = AUDIO_DTYPE_CSInterface
        },
        .Subtype                = AUDIO_DSUBTYPE_CSInterface_InputTerminal,
        .JackType               = MIDI_JACKTYPE_External,
        .JackID                 = 0x02,
        .JackStrIndex           = NO_DESCRIPTOR
    },
    .MIDI_Out_Jack_Emb = {
        .Header = {
            .Size               = sizeof(USB_MIDI_Descriptor_OutputJack_t),
            .Type               = AUDIO_DTYPE_CSInterface
        },
        .Subtype                = AUDIO_DSUBTYPE_CSInterface_OutputTerminal,
        .JackType               = MIDI_JACKTYPE_Embedded,
        .JackID                 = 0x03,
        .NumberOfPins           = 1,
        .SourceJackID           = {0x02},
        .SourcePinID            = {0x01},
        .JackStrIndex           = NO_DESCRIPTOR
    },
    .MIDI_Out_Jack_Ext = {
        .Header = {
            .Size               = sizeof(USB_MIDI_Descriptor_OutputJack_t),
            .Type               = AUDIO_DTYPE_CSInterface
        },
        .Subtype                = AUDIO_DSUBTYPE_CSInterface_OutputTerminal,
        .JackType               = MIDI_JACKTYPE_External,
        .JackID                 = 0x04,
        .NumberOfPins           = 1,
        .SourceJackID           = {0x01},
        .SourcePinID            = {0x01},
        .JackStrIndex           = NO_DESCRIPTOR
    },
    .MIDI_In_Jack_Endpoint = {
        .Endpoint = {
            .Header = {
                .Size           = sizeof(USB_Audio_Descriptor_StreamEndpoint_Std_t),
                .Type           = DTYPE_Endpoint
            },
            .EndpointAddress    = (ENDPOINT_DIR_OUT | MIDI_STREAM_OUT_EPNUM),
            .Attributes         = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize       = MIDI_STREAM_EPSIZE,
            .PollingIntervalMS  = 0x05
        },
        .Refresh                = 0,
        .SyncEndpointNumber     = 0
    },
    .MIDI_In_Jack_Endpoint_SPC = {
        .Header = {
            .Size               = sizeof(USB_MIDI_Descriptor_Jack_Endpoint_t),
            .Type               = AUDIO_DTYPE_CSEndpoint
        },
        .Subtype                = AUDIO_DSUBTYPE_CSEndpoint_General,
        .TotalEmbeddedJacks     = 0x01,
        .AssociatedJackID       = {0x01}
    },
    .MIDI_Out_Jack_Endpoint = {
        .Endpoint = {
            .Header = {
                .Size           = sizeof(USB_Audio_Descriptor_StreamEndpoint_Std_t),
                .Type           = DTYPE_Endpoint
            },
            .EndpointAddress    = (ENDPOINT_DIR_IN | MIDI_STREAM_IN_EPNUM),
            .Attributes         = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize       = MIDI_STREAM_EPSIZE,
            .PollingIntervalMS  = 0x05
        },
        .Refresh                = 0,
        .SyncEndpointNumber     = 0
    },
    .MIDI_Out_Jack_Endpoint_SPC = {
        .Header = {
            .Size               = sizeof(USB_MIDI_Descriptor_Jack_Endpoint_t),
            .Type               = AUDIO_DTYPE_CSEndpoint
        },
        .Subtype                = AUDIO_DSUBTYPE_CSEndpoint_General,
        .TotalEmbeddedJacks     = 0x01,
        .AssociatedJackID       = {0x03}
    },
#endif

#ifdef VIRTSER_ENABLE
    /*
     * Virtual Serial
     */
    .CDC_Interface_Association = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_Association_t),
            .Type               = DTYPE_InterfaceAssociation
        },
        .FirstInterfaceIndex    = CCI_INTERFACE,
        .TotalInterfaces        = 2,
        .Class                  = CDC_CSCP_CDCClass,
        .SubClass               = CDC_CSCP_ACMSubclass,
        .Protocol               = CDC_CSCP_ATCommandProtocol,
        .IADStrIndex            = NO_DESCRIPTOR,
    },
    .CDC_CCI_Interface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = CCI_INTERFACE,
        .AlternateSetting       = 0,
        .TotalEndpoints         = 1,
        .Class                  = CDC_CSCP_CDCClass,
        .SubClass               = CDC_CSCP_ACMSubclass,
        .Protocol               = CDC_CSCP_ATCommandProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .CDC_Functional_Header = {
        .Header = {
            .Size               = sizeof(USB_CDC_Descriptor_FunctionalHeader_t),
            .Type               = CDC_DTYPE_CSInterface
        },
        .Subtype                = 0x00,
        .CDCSpecification       = VERSION_BCD(1, 1, 0),
    },
    .CDC_Functional_ACM = {
        .Header = {
            .Size               = sizeof(USB_CDC_Descriptor_FunctionalACM_t),
            .Type               = CDC_DTYPE_CSInterface
        },
        .Subtype                = 0x02,
        .Capabilities           = 0x02,
    },
    .CDC_Functional_Union = {
        .Header = {
            .Size               = sizeof(USB_CDC_Descriptor_FunctionalUnion_t),
            .Type               = CDC_DTYPE_CSInterface
        },
        .Subtype                = 0x06,
        .MasterInterfaceNumber  = CCI_INTERFACE,
        .SlaveInterfaceNumber   = CDI_INTERFACE,
    },
    .CDC_NotificationEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | CDC_NOTIFICATION_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = CDC_NOTIFICATION_EPSIZE,
        .PollingIntervalMS      = 0xFF
    },
    .CDC_DCI_Interface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = CDI_INTERFACE,
        .AlternateSetting       = 0,
        .TotalEndpoints         = 2,
        .Class                  = CDC_CSCP_CDCDataClass,
        .SubClass               = CDC_CSCP_NoDataSubclass,
        .Protocol               = CDC_CSCP_NoDataProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .CDC_DataOutEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_OUT | CDC_OUT_EPNUM),
        .Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = CDC_EPSIZE,
        .PollingIntervalMS      = 0x05
    },
    .CDC_DataInEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | CDC_IN_EPNUM),
        .Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = CDC_EPSIZE,
        .PollingIntervalMS      = 0x05
    },
#endif

#if defined(JOYSTICK_ENABLE) && !defined(JOYSTICK_SHARED_EP)
    /*
     * Joystick
     */
    .Joystick_Interface = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = JOYSTICK_INTERFACE,
        .AlternateSetting       = 0x00,
        .TotalEndpoints         = 1,
        .Class                  = HID_CSCP_HIDClass,
        .SubClass               = HID_CSCP_NonBootSubclass,
        .Protocol               = HID_CSCP_NonBootProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Joystick_HID = {
        .Header = {
            .Size               = sizeof(USB_HID_Descriptor_HID_t),
            .Type               = HID_DTYPE_HID
        },
        .HIDSpec                = VERSION_BCD(1, 1, 1),
        .CountryCode            = 0x00,
        .TotalReportDescriptors = 1,
        .HIDReportType          = HID_DTYPE_Report,
        .HIDReportLength        = sizeof(JoystickReport)
    },
    .Joystick_INEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | JOYSTICK_IN_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = JOYSTICK_EPSIZE,
        .PollingIntervalMS      = USB_POLLING_INTERVAL_MS
    },
#endif

#if defined(DIGITIZER_ENABLE) && !defined(DIGITIZER_SHARED_EP)
    /*
     * Digitizer
     */
    .Digitizer_Interface  = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Interface_t),
            .Type               = DTYPE_Interface
        },
        .InterfaceNumber        = DIGITIZER_INTERFACE,
        .AlternateSetting       = 0x00,
        .TotalEndpoints         = 1,
        .Class                  = HID_CSCP_HIDClass,
        .SubClass               = HID_CSCP_NonBootSubclass,
        .Protocol               = HID_CSCP_NonBootProtocol,
        .InterfaceStrIndex      = NO_DESCRIPTOR
    },
    .Digitizer_HID = {
        .Header = {
            .Size               = sizeof(USB_HID_Descriptor_HID_t),
            .Type               = HID_DTYPE_HID
        },
        .HIDSpec                = VERSION_BCD(1, 1, 1),
        .CountryCode            = 0x00,
        .TotalReportDescriptors = 1,
        .HIDReportType          = HID_DTYPE_Report,
        .HIDReportLength        = sizeof(DigitizerReport)
    },
    .Digitizer_INEndpoint = {
        .Header = {
            .Size               = sizeof(USB_Descriptor_Endpoint_t),
            .Type               = DTYPE_Endpoint
        },
        .EndpointAddress        = (ENDPOINT_DIR_IN | DIGITIZER_IN_EPNUM),
        .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
        .EndpointSize           = DIGITIZER_EPSIZE,
        .PollingIntervalMS      = USB_POLLING_INTERVAL_MS
    },
#endif
};

/*
 * String descriptors
 */

#define USB_DESCRIPTOR_SIZE_LITERAL_U16STRING(str) \
    (sizeof(USB_Descriptor_Header_t) + sizeof(str) - sizeof(wchar_t)) // include header, don't count null terminator

const USB_Descriptor_String_t PROGMEM LanguageString = {
    .Header = {
        .Size                   = sizeof(USB_Descriptor_Header_t) + sizeof(uint16_t),
        .Type                   = DTYPE_String
    },
    .UnicodeString              = {LANGUAGE_ID_ENG}
};

const USB_Descriptor_String_t PROGMEM ManufacturerString = {
    .Header = {
        .Size                   = USB_DESCRIPTOR_SIZE_LITERAL_U16STRING(USBSTR(MANUFACTURER)),
        .Type                   = DTYPE_String
    },
    .UnicodeString              = USBSTR(MANUFACTURER)
};

const USB_Descriptor_String_t PROGMEM ProductString = {
    .Header = {
        .Size                   = USB_DESCRIPTOR_SIZE_LITERAL_U16STRING(USBSTR(PRODUCT)),
        .Type                   = DTYPE_String
    },
    .UnicodeString              = USBSTR(PRODUCT)
};

// clang-format on

#if defined(SERIAL_NUMBER)
// clang-format off
const USB_Descriptor_String_t PROGMEM SerialNumberString = {
    .Header = {
        .Size                   = USB_DESCRIPTOR_SIZE_LITERAL_U16STRING(USBSTR(SERIAL_NUMBER)),
        .Type                   = DTYPE_String
    },
    .UnicodeString              = USBSTR(SERIAL_NUMBER)
};
// clang-format on

#else // defined(SERIAL_NUMBER)

#    if defined(SERIAL_NUMBER_USE_HARDWARE_ID) && SERIAL_NUMBER_USE_HARDWARE_ID == TRUE

#        if defined(__AVR__)
#            error Dynamically setting the serial number on AVR is unsupported as LUFA requires the string to be in PROGMEM.
#        endif // defined(__AVR__)

#        ifndef SERIAL_NUMBER_LENGTH
#            define SERIAL_NUMBER_LENGTH (sizeof(hardware_id_t) * 2)
#        endif

#        define SERIAL_NUMBER_DESCRIPTOR_SIZE                                            \
            (sizeof(USB_Descriptor_Header_t)                     /* Descriptor header */ \
             + (((SERIAL_NUMBER_LENGTH) + 1) * sizeof(wchar_t))) /* Length of serial number, with potential extra character as we're converting 2 nibbles at a time */

uint8_t SerialNumberString[SERIAL_NUMBER_DESCRIPTOR_SIZE] = {0};

void set_serial_number_descriptor(void) {
    static bool is_set = false;
    if (is_set) {
        return;
    }
    is_set = true;

    static const char        hex_str[] = "0123456789ABCDEF";
    hardware_id_t            id        = get_hardware_id();
    USB_Descriptor_String_t* desc      = (USB_Descriptor_String_t*)SerialNumberString;

    // Copy across nibbles from the hardware ID as unicode hex characters
    int      length = MIN(sizeof(id) * 2, SERIAL_NUMBER_LENGTH);
    uint8_t* p      = (uint8_t*)&id;
    for (int i = 0; i < length; i += 2) {
        desc->UnicodeString[i + 0] = hex_str[p[i / 2] >> 4];
        desc->UnicodeString[i + 1] = hex_str[p[i / 2] & 0xF];
    }

    desc->Header.Size = sizeof(USB_Descriptor_Header_t) + (length * sizeof(wchar_t)); // includes header, don't count null terminator
    desc->Header.Type = DTYPE_String;
}

#    endif // defined(SERIAL_NUMBER_USE_HARDWARE_ID) && SERIAL_NUMBER_USE_HARDWARE_ID == TRUE

#endif // defined(SERIAL_NUMBER)

/**
 * This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 * documentation) by the application code so that the address and size of a requested descriptor can be given
 * to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 * is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 * USB host.
 */
uint16_t get_usb_descriptor(const uint16_t wValue, const uint16_t wIndex, const uint16_t wLength, const void** const DescriptorAddress) {
    const uint8_t DescriptorType  = (wValue >> 8);
    const uint8_t DescriptorIndex = (wValue & 0xFF);
    const void*   Address         = NULL;
    uint16_t      Size            = NO_DESCRIPTOR;

    switch (DescriptorType) {
        case DTYPE_Device:
            Address = &DeviceDescriptor;
            Size    = sizeof(USB_Descriptor_Device_t);

            break;
        case DTYPE_Configuration:
            Address = &ConfigurationDescriptor;
            Size    = sizeof(USB_Descriptor_Configuration_t);

            break;
        case DTYPE_String:
            switch (DescriptorIndex) {
                case 0x00:
                    Address = &LanguageString;
                    Size    = pgm_read_byte(&LanguageString.Header.Size);

                    break;
                case 0x01:
                    Address = &ManufacturerString;
                    Size    = pgm_read_byte(&ManufacturerString.Header.Size);

                    break;
                case 0x02:
                    Address = &ProductString;
                    Size    = pgm_read_byte(&ProductString.Header.Size);

                    break;
#ifdef HAS_SERIAL_NUMBER
                case 0x03:
                    Address = (const USB_Descriptor_String_t*)&SerialNumberString;
#    if defined(SERIAL_NUMBER)
                    Size = pgm_read_byte(&SerialNumberString.Header.Size);
#    else
                    set_serial_number_descriptor();
                    Size = ((const USB_Descriptor_String_t*)SerialNumberString)->Header.Size;
#    endif

                    break;
#endif // HAS_SERIAL_NUMBER
            }
#ifdef OS_DETECTION_ENABLE
            process_wlength(wLength);
#endif

            break;
        case HID_DTYPE_HID:
            switch (wIndex) {
#ifndef KEYBOARD_SHARED_EP
                case KEYBOARD_INTERFACE:
                    Address = &ConfigurationDescriptor.Keyboard_HID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);
                    break;
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
                case MOUSE_INTERFACE:
                    Address = &ConfigurationDescriptor.Mouse_HID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);

                    break;
#endif

#ifdef SHARED_EP_ENABLE
                case SHARED_INTERFACE:
                    Address = &ConfigurationDescriptor.Shared_HID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);

                    break;
#endif

#ifdef RAW_ENABLE
                case RAW_INTERFACE:
                    Address = &ConfigurationDescriptor.Raw_HID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);

                    break;
#endif

#ifdef CONSOLE_ENABLE
                case CONSOLE_INTERFACE:
                    Address = &ConfigurationDescriptor.Console_HID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);

                    break;
#endif
#if defined(JOYSTICK_ENABLE) && !defined(JOYSTICK_SHARED_EP)
                case JOYSTICK_INTERFACE:
                    Address = &ConfigurationDescriptor.Joystick_HID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);
                    break;
#endif
#if defined(DIGITIZER_ENABLE) && !defined(DIGITIZER_SHARED_EP)
                case DIGITIZER_INTERFACE:
                    Address = &ConfigurationDescriptor.Digitizer_HID;
                    Size    = sizeof(USB_HID_Descriptor_HID_t);

                    break;
#endif
            }

            break;
        case HID_DTYPE_Report:
            switch (wIndex) {
#ifndef KEYBOARD_SHARED_EP
                case KEYBOARD_INTERFACE:
                    Address = &KeyboardReport;
                    Size    = sizeof(KeyboardReport);

                    break;
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
                case MOUSE_INTERFACE:
                    Address = &MouseReport;
                    Size    = sizeof(MouseReport);

                    break;
#endif

#ifdef SHARED_EP_ENABLE
                case SHARED_INTERFACE:
                    Address = &SharedReport;
                    Size    = sizeof(SharedReport);

                    break;
#endif

#ifdef RAW_ENABLE
                case RAW_INTERFACE:
                    Address = &RawReport;
                    Size    = sizeof(RawReport);

                    break;
#endif

#ifdef CONSOLE_ENABLE
                case CONSOLE_INTERFACE:
                    Address = &ConsoleReport;
                    Size    = sizeof(ConsoleReport);

                    break;
#endif
#if defined(JOYSTICK_ENABLE) && !defined(JOYSTICK_SHARED_EP)
                case JOYSTICK_INTERFACE:
                    Address = &JoystickReport;
                    Size    = sizeof(JoystickReport);
                    break;
#endif
#if defined(DIGITIZER_ENABLE) && !defined(DIGITIZER_SHARED_EP)
                case DIGITIZER_INTERFACE:
                    Address = &DigitizerReport;
                    Size    = sizeof(DigitizerReport);
                    break;
#endif
            }

            break;
    }

    *DescriptorAddress = Address;

    return Size;
}
