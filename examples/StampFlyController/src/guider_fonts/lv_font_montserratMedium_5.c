/*
 * Copyright 2024 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */
/*******************************************************************************
 * Size: 5 px
 * Bpp: 4
 * Opts: --user-data-dir=C:\Users\qweas\AppData\Roaming\gui-guider --app-path=E:\Apps\NXP\GUI-Guider-1.7.0-GA\resources\app.asar --no-sandbox --no-zygote --lang=zh-CN --device-scale-factor=1 --num-raster-threads=4 --enable-main-frame-before-activation --renderer-client-id=5 --time-ticks-at-unix-epoch=-1719450359119055 --launch-time-ticks=26573557346 --mojo-platform-channel-handle=2980 --field-trial-handle=1752,i,1625669015711095544,15175541659787701925,131072 --disable-features=SpareRendererForSitePerProcess,WinRetrieveSuggestionsOnlyOnDemand /prefetch:1
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef LV_FONT_MONTSERRATMEDIUM_5
#define LV_FONT_MONTSERRATMEDIUM_5 1
#endif

#if LV_FONT_MONTSERRATMEDIUM_5

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x87, 0x45,

    /* U+0022 "\"" */
    0x66, 0x33,

    /* U+0023 "#" */
    0x5, 0x50, 0x49, 0x92, 0x68, 0x91, 0x31, 0x50,

    /* U+0024 "$" */
    0x2, 0x6, 0xa5, 0x78, 0x0, 0x79, 0x6a, 0x80,
    0x20,

    /* U+0025 "%" */
    0x55, 0x33, 0x4, 0x56, 0x0, 0x38, 0x45, 0x1,
    0x54, 0x60,

    /* U+0026 "&" */
    0x27, 0x40, 0x2a, 0x20, 0x75, 0x90, 0x77, 0x92,
    0x0, 0x0,

    /* U+0027 "'" */
    0x63,

    /* U+0028 "(" */
    0x25, 0x60, 0x70, 0x60, 0x25,

    /* U+0029 ")" */
    0x70, 0x51, 0x43, 0x51, 0x70,

    /* U+002A "*" */
    0x66, 0x66, 0x0,

    /* U+002B "+" */
    0x3, 0x4, 0xa4, 0x6, 0x0,

    /* U+002D "-" */
    0x54,

    /* U+002E "." */
    0x50,

    /* U+002F "/" */
    0x0, 0x30, 0x6, 0x1, 0x50, 0x50, 0x6, 0x0,
    0x60,

    /* U+0030 "0" */
    0x48, 0x70, 0x70, 0x70, 0x70, 0x70, 0x48, 0x70,

    /* U+0031 "1" */
    0x95, 0x25, 0x25, 0x25,

    /* U+0032 "2" */
    0x68, 0x40, 0x16, 0x8, 0xa, 0x85,

    /* U+0033 "3" */
    0x6a, 0x50, 0xa0, 0x3, 0x87, 0x85,

    /* U+0034 "4" */
    0x5, 0x20, 0x35, 0x30, 0x87, 0xb2, 0x0, 0x70,

    /* U+0035 "5" */
    0x78, 0x46, 0x73, 0x0, 0x87, 0x85,

    /* U+0036 "6" */
    0x37, 0x58, 0x75, 0xa0, 0x84, 0x87,

    /* U+0037 "7" */
    0xa8, 0xa1, 0x25, 0x7, 0x0, 0x70,

    /* U+0038 "8" */
    0x67, 0x86, 0x89, 0x80, 0x86, 0x78,

    /* U+0039 "9" */
    0x67, 0x58, 0xa, 0x47, 0x94, 0x74,

    /* U+003A ":" */
    0x50, 0x50,

    /* U+003B ";" */
    0x50, 0x45,

    /* U+003C "<" */
    0x0, 0x3, 0x73, 0x47, 0x30, 0x1,

    /* U+003D "=" */
    0x47, 0x44, 0x74,

    /* U+003E ">" */
    0x0, 0x4, 0x73, 0x37, 0x31, 0x0,

    /* U+003F "?" */
    0x68, 0x50, 0x35, 0x6, 0x0, 0x50,

    /* U+0040 "@" */
    0x17, 0x56, 0x16, 0x36, 0x76, 0x67, 0x7, 0x56,
    0x57, 0x96, 0x6, 0x53, 0x0,

    /* U+0041 "A" */
    0x8, 0x40, 0x5, 0x60, 0x57, 0x91, 0x70, 0x7,

    /* U+0042 "B" */
    0x77, 0x91, 0x70, 0x34, 0x77, 0xa2, 0x77, 0x75,

    /* U+0043 "C" */
    0x29, 0x82, 0x80, 0x0, 0x80, 0x0, 0x29, 0x82,

    /* U+0044 "D" */
    0x78, 0x93, 0x70, 0x8, 0x70, 0x8, 0x78, 0x84,

    /* U+0045 "E" */
    0x78, 0x80, 0x70, 0x0, 0x77, 0x50, 0x78, 0x70,

    /* U+0046 "F" */
    0x78, 0x87, 0x0, 0x77, 0x57, 0x0,

    /* U+0047 "G" */
    0x29, 0x82, 0x80, 0x0, 0x80, 0x7, 0x29, 0x84,

    /* U+0048 "H" */
    0x70, 0x8, 0x70, 0x8, 0x77, 0x78, 0x70, 0x8,

    /* U+0049 "I" */
    0x70, 0x70, 0x70, 0x70,

    /* U+004A "J" */
    0x5, 0xb1, 0x0, 0x61, 0x0, 0x60, 0x8, 0x90,

    /* U+004B "K" */
    0x70, 0x62, 0x76, 0x40, 0x78, 0x70, 0x70, 0x53,

    /* U+004C "L" */
    0x70, 0x7, 0x0, 0x70, 0x7, 0x87,

    /* U+004D "M" */
    0x73, 0x6, 0x47, 0x80, 0xa4, 0x74, 0x95, 0x47,
    0x4, 0x34,

    /* U+004E "N" */
    0x74, 0x8, 0x79, 0x18, 0x71, 0x98, 0x70, 0x38,

    /* U+004F "O" */
    0x29, 0x84, 0x80, 0x8, 0x80, 0x8, 0x29, 0x84,

    /* U+0050 "P" */
    0x78, 0x91, 0x70, 0x44, 0x77, 0x80, 0x70, 0x0,

    /* U+0051 "Q" */
    0x29, 0x84, 0x8, 0x0, 0x80, 0x80, 0x8, 0x2,
    0x98, 0x40, 0x0, 0x56, 0x0,

    /* U+0052 "R" */
    0x78, 0x91, 0x70, 0x44, 0x77, 0xa0, 0x70, 0x62,

    /* U+0053 "S" */
    0x67, 0x57, 0x40, 0x3, 0x96, 0x77,

    /* U+0054 "T" */
    0x7c, 0x70, 0x80, 0x8, 0x0, 0x80,

    /* U+0055 "U" */
    0x80, 0x7, 0x80, 0x7, 0x70, 0x16, 0x29, 0x91,

    /* U+0056 "V" */
    0x80, 0x25, 0x61, 0x70, 0x17, 0x70, 0xa, 0x30,

    /* U+0057 "W" */
    0x80, 0x83, 0x25, 0x61, 0x77, 0x60, 0x18, 0x47,
    0x70, 0xc, 0x5, 0x60,

    /* U+0058 "X" */
    0x71, 0x80, 0xb, 0x30, 0x1a, 0x50, 0x80, 0x81,

    /* U+0059 "Y" */
    0x8, 0x6, 0x0, 0x36, 0x60, 0x0, 0xa0, 0x0,
    0x7, 0x0,

    /* U+005A "Z" */
    0x68, 0xc0, 0x4, 0x40, 0x18, 0x0, 0xa8, 0x71,

    /* U+005B "[" */
    0x74, 0x70, 0x70, 0x70, 0x74,

    /* U+005C "\\" */
    0x2, 0x0, 0x60, 0x7, 0x0, 0x42, 0x0, 0x60,
    0x7,

    /* U+005D "]" */
    0x92, 0x52, 0x52, 0x52, 0x92,

    /* U+005E "^" */
    0x4, 0x1, 0x90, 0x51, 0x50,

    /* U+005F "_" */
    0x55, 0x20,

    /* U+0060 "`" */
    0x3,

    /* U+0061 "a" */
    0x48, 0x54, 0x68, 0x76, 0x80,

    /* U+0062 "b" */
    0x70, 0x0, 0x87, 0x80, 0x80, 0x52, 0x87, 0x80,

    /* U+0063 "c" */
    0x57, 0x47, 0x0, 0x57, 0x40,

    /* U+0064 "d" */
    0x0, 0x75, 0x7b, 0x70, 0x85, 0x7b,

    /* U+0065 "e" */
    0x57, 0x59, 0x67, 0x57, 0x40,

    /* U+0066 "f" */
    0x56, 0xa5, 0x70, 0x70,

    /* U+0067 "g" */
    0x57, 0xb8, 0x8, 0x57, 0xc3, 0x78,

    /* U+0068 "h" */
    0x70, 0x8, 0x89, 0x80, 0x77, 0x7,

    /* U+0069 "i" */
    0x50, 0x70, 0x70, 0x70,

    /* U+006A "j" */
    0x5, 0x0, 0x70, 0x7, 0x0, 0x70, 0x38, 0x0,

    /* U+006B "k" */
    0x70, 0x0, 0x72, 0x60, 0x8b, 0x10, 0x70, 0x80,

    /* U+006C "l" */
    0x77, 0x77,

    /* U+006D "m" */
    0x88, 0xa8, 0x88, 0x8, 0x7, 0x70, 0x70, 0x70,

    /* U+006E "n" */
    0x87, 0x88, 0x7, 0x70, 0x70,

    /* U+006F "o" */
    0x57, 0x67, 0x7, 0x57, 0x60,

    /* U+0070 "p" */
    0x87, 0x80, 0x80, 0x52, 0x87, 0x80, 0x70, 0x0,

    /* U+0071 "q" */
    0x57, 0xb7, 0x8, 0x57, 0xb0, 0x7,

    /* U+0072 "r" */
    0x87, 0x80, 0x70,

    /* U+0073 "s" */
    0x77, 0x15, 0x71, 0x68, 0x30,

    /* U+0074 "t" */
    0x30, 0xa5, 0x70, 0x46,

    /* U+0075 "u" */
    0x70, 0x77, 0x8, 0x48, 0xb0,

    /* U+0076 "v" */
    0x7, 0x7, 0x6, 0x53, 0x1, 0xb0,

    /* U+0077 "w" */
    0x71, 0x92, 0x46, 0x67, 0x60, 0x29, 0x29, 0x0,

    /* U+0078 "x" */
    0x75, 0x41, 0xc0, 0x74, 0x50,

    /* U+0079 "y" */
    0x7, 0x7, 0x6, 0x53, 0x0, 0xb0, 0x8, 0x40,

    /* U+007A "z" */
    0x5a, 0x31, 0x70, 0x97, 0x20,

    /* U+007B "{" */
    0x36, 0x52, 0x81, 0x52, 0x36,

    /* U+007C "|" */
    0x77, 0x77, 0x70,

    /* U+007D "}" */
    0x90, 0x61, 0x54, 0x61, 0x90,

    /* U+007E "~" */
    0x43, 0x33, 0x33,

    /* U+F001 "" */
    0x0, 0x0, 0x10, 0x28, 0xdf, 0xb, 0xc7, 0xb0,
    0xa0, 0xa, 0x4b, 0xb, 0xfb, 0x90, 0x11,

    /* U+F008 "" */
    0x79, 0x79, 0x79, 0x71, 0x88, 0x99, 0x5a, 0x89,
    0xa7, 0xb8,

    /* U+F00B "" */
    0x0, 0x11, 0xf, 0xaf, 0xff, 0xa6, 0xbb, 0xab,
    0x7b, 0xbb, 0xe9, 0xff, 0xe4, 0x24, 0x44,

    /* U+F00C "" */
    0x0, 0x1, 0x84, 0x1, 0xd7, 0xba, 0xd7, 0x0,
    0xa7, 0x0,

    /* U+F00D "" */
    0x60, 0x42, 0x9c, 0xd1, 0x5f, 0xb0, 0xa2, 0x84,

    /* U+F011 "" */
    0x0, 0x10, 0x2, 0x5c, 0x51, 0xb2, 0xc2, 0xbc,
    0x7, 0xc, 0x96, 0x16, 0x90, 0x8b, 0x70,

    /* U+F013 "" */
    0x0, 0x30, 0x3, 0x7f, 0x83, 0x8f, 0x7e, 0xa7,
    0xe3, 0xd9, 0x5b, 0xfb, 0x60, 0x7, 0x10,

    /* U+F015 "" */
    0x0, 0x0, 0x0, 0x2, 0xb9, 0xc0, 0x4b, 0xca,
    0xc1, 0x6d, 0xff, 0x94, 0x1f, 0x6b, 0xb0, 0x4,
    0x13, 0x30,

    /* U+F019 "" */
    0x0, 0x50, 0x0, 0x2f, 0x20, 0x8, 0xf8, 0x0,
    0x7f, 0x70, 0xee, 0x9e, 0xe9, 0x99, 0x87,

    /* U+F01C "" */
    0xa, 0xaa, 0x70, 0x92, 0x0, 0x83, 0xfd, 0x58,
    0xe9, 0xef, 0xff, 0xf8,

    /* U+F021 "" */
    0x1, 0x41, 0x34, 0xb7, 0xcd, 0x90, 0x1b, 0xc8,
    0x81, 0x5, 0xfa, 0x17, 0x86, 0x6a, 0x60,

    /* U+F026 "" */
    0x2, 0x5c, 0xf8, 0xff, 0x80, 0x57, 0x0, 0x0,

    /* U+F027 "" */
    0x2, 0x50, 0xdf, 0x85, 0xff, 0x87, 0x5, 0x70,
    0x0, 0x0,

    /* U+F028 "" */
    0x0, 0x0, 0x10, 0x2, 0x52, 0x81, 0xcf, 0x86,
    0x77, 0xff, 0x87, 0x77, 0x5, 0x73, 0x73, 0x0,
    0x0, 0x40,

    /* U+F03E "" */
    0xab, 0xcc, 0xab, 0x8f, 0x9f, 0xe6, 0x40, 0xac,
    0xaa, 0xac,

    /* U+F043 "" */
    0x2, 0x0, 0xd, 0x40, 0x6f, 0xd0, 0xdf, 0xf5,
    0xaa, 0xf4, 0x29, 0x60,

    /* U+F048 "" */
    0x0, 0x0, 0x91, 0x88, 0x9a, 0xf8, 0x9d, 0xf8,
    0x92, 0xb8, 0x20, 0x1,

    /* U+F04B "" */
    0x30, 0x0, 0xf, 0xd4, 0x0, 0xff, 0xfa, 0x1f,
    0xff, 0xd2, 0xff, 0x80, 0x7, 0x20, 0x0,

    /* U+F04C "" */
    0x0, 0x1, 0xf, 0xd7, 0xf5, 0xfe, 0x8f, 0x6f,
    0xe8, 0xf6, 0xfd, 0x7f, 0x53, 0x31, 0x40,

    /* U+F04D "" */
    0x1, 0x10, 0xf, 0xff, 0xf5, 0xff, 0xff, 0x6f,
    0xff, 0xf6, 0xff, 0xff, 0x54, 0x55, 0x40,

    /* U+F051 "" */
    0x0, 0x0, 0x5a, 0xb, 0x6f, 0xbb, 0x6f, 0xdb,
    0x6d, 0x1b, 0x11, 0x3,

    /* U+F052 "" */
    0x0, 0x0, 0x0, 0x0, 0x8d, 0x10, 0x7, 0xff,
    0xc0, 0xa, 0xbb, 0xb3, 0xe, 0xff, 0xf5, 0x4,
    0x44, 0x41,

    /* U+F053 "" */
    0x3, 0xa3, 0xc1, 0x6a, 0x0, 0x79, 0x0, 0x10,

    /* U+F054 "" */
    0x85, 0x0, 0xb5, 0x8, 0x87, 0x90, 0x10, 0x0,

    /* U+F067 "" */
    0x0, 0x0, 0x0, 0x4a, 0x0, 0x58, 0xc5, 0x19,
    0xbd, 0x93, 0x4, 0xa0, 0x0, 0x2, 0x0,

    /* U+F068 "" */
    0x12, 0x22, 0xc, 0xdd, 0xd4,

    /* U+F06E "" */
    0x6, 0x88, 0x30, 0x99, 0x67, 0xe4, 0xc8, 0xe9,
    0xd6, 0x19, 0x89, 0x70,

    /* U+F070 "" */
    0x30, 0x0, 0x0, 0x7, 0x98, 0x85, 0x0, 0x35,
    0xba, 0xa8, 0x7, 0xc1, 0xcb, 0xb0, 0x7, 0x95,
    0x97, 0x0, 0x0, 0x0, 0x51,

    /* U+F071 "" */
    0x0, 0x5, 0x10, 0x0, 0x1, 0xfa, 0x0, 0x0,
    0x97, 0xc3, 0x0, 0x2f, 0x8d, 0xc0, 0xb, 0xf8,
    0xdf, 0x50, 0x8a, 0xaa, 0xa5,

    /* U+F074 "" */
    0x0, 0x0, 0xa, 0x51, 0xbc, 0x17, 0xb6, 0x50,
    0xa8, 0x43, 0xc7, 0x3d, 0xd0, 0x0, 0x11,

    /* U+F077 "" */
    0x0, 0x0, 0x0, 0x9d, 0x10, 0x98, 0x3c, 0x13,
    0x0, 0x21,

    /* U+F078 "" */
    0x0, 0x0, 0xb, 0x41, 0xc2, 0xc, 0xd3, 0x0,
    0x3, 0x0,

    /* U+F079 "" */
    0x39, 0x19, 0xa5, 0x6, 0xc4, 0x0, 0x90, 0xa,
    0x0, 0x6b, 0x30, 0xaa, 0x74, 0xa0,

    /* U+F07B "" */
    0xac, 0x52, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xfe,

    /* U+F093 "" */
    0x0, 0x30, 0x0, 0x7f, 0x70, 0x8, 0xf8, 0x0,
    0x2f, 0x20, 0xec, 0xbc, 0xe9, 0x99, 0x87,

    /* U+F095 "" */
    0x0, 0x0, 0x22, 0x0, 0x0, 0xcf, 0x0, 0x0,
    0x8c, 0x0, 0x21, 0xd4, 0xe, 0xfe, 0x60, 0x7,
    0x72, 0x0,

    /* U+F0C4 "" */
    0x0, 0x0, 0xb, 0xa1, 0xb2, 0x9e, 0xd4, 0x6,
    0xde, 0x40, 0xba, 0x2c, 0x20, 0x0, 0x0,

    /* U+F0C5 "" */
    0x1, 0x20, 0x6, 0xcf, 0xa0, 0xfc, 0xff, 0x2f,
    0xcf, 0xf2, 0xf9, 0xba, 0x19, 0xa9, 0x0,

    /* U+F0C7 "" */
    0xca, 0xab, 0xa, 0x0, 0xe5, 0xfe, 0xcf, 0x5f,
    0xdb, 0xf4, 0x1, 0x11, 0x0,

    /* U+F0C9 "" */
    0xbb, 0xbb, 0x43, 0x44, 0x41, 0x67, 0x77, 0x2b,
    0xbb, 0xb4,

    /* U+F0E0 "" */
    0xac, 0xcc, 0xa9, 0xff, 0xf9, 0xfa, 0xaa, 0xfe,
    0xff, 0xfe,

    /* U+F0E7 "" */
    0x1, 0x20, 0x0, 0xbf, 0x10, 0xe, 0xe9, 0x0,
    0xae, 0xa0, 0x0, 0xc1, 0x0, 0x7, 0x0,

    /* U+F0EA "" */
    0x4, 0x0, 0xf, 0xdd, 0x0, 0xfa, 0xb5, 0xf,
    0xbf, 0x91, 0xeb, 0xff, 0x20, 0x6d, 0xd1,

    /* U+F0F3 "" */
    0x0, 0x20, 0x0, 0xbd, 0x30, 0x5f, 0xfb, 0x8,
    0xff, 0xe0, 0xab, 0xbb, 0x30, 0x26, 0x0,

    /* U+F11C "" */
    0xaa, 0xaa, 0xa6, 0xd9, 0x98, 0x9a, 0xe9, 0x77,
    0x9a, 0xcc, 0xaa, 0xc8,

    /* U+F124 "" */
    0x0, 0x0, 0x4, 0x0, 0x1, 0x7e, 0xd0, 0x8,
    0xff, 0xf6, 0x0, 0x67, 0xee, 0x0, 0x0, 0xd,
    0x70, 0x0, 0x0, 0x61, 0x0,

    /* U+F15B "" */
    0x78, 0x40, 0xff, 0x86, 0xff, 0xfb, 0xff, 0xfc,
    0xff, 0xfc, 0x77, 0x75,

    /* U+F1EB "" */
    0x0, 0x0, 0x0, 0x3, 0xbc, 0xcc, 0x50, 0x83,
    0x66, 0x38, 0x10, 0x96, 0x5a, 0x0, 0x0, 0x58,
    0x0, 0x0, 0x1, 0x20, 0x0,

    /* U+F240 "" */
    0x8a, 0xaa, 0xa8, 0xa, 0x99, 0x97, 0xc0, 0xac,
    0xcc, 0x9c, 0x9, 0xaa, 0xaa, 0x90,

    /* U+F241 "" */
    0x8a, 0xaa, 0xa8, 0xa, 0x99, 0x80, 0xc0, 0xac,
    0xca, 0xc, 0x9, 0xaa, 0xaa, 0x90,

    /* U+F242 "" */
    0x8a, 0xaa, 0xa8, 0xa, 0x99, 0x0, 0xc0, 0xac,
    0xc0, 0xc, 0x9, 0xaa, 0xaa, 0x90,

    /* U+F243 "" */
    0x8a, 0xaa, 0xa8, 0xa, 0x91, 0x0, 0xc0, 0xac,
    0x10, 0xc, 0x9, 0xaa, 0xaa, 0x90,

    /* U+F244 "" */
    0x8a, 0xaa, 0xa8, 0xa, 0x0, 0x0, 0xc0, 0xa0,
    0x0, 0xc, 0x9, 0xaa, 0xaa, 0x90,

    /* U+F287 "" */
    0x0, 0x3b, 0x10, 0x6, 0x36, 0x20, 0x30, 0xa6,
    0x85, 0x48, 0x0, 0x0, 0x7d, 0x0, 0x0, 0x0,
    0x0, 0x0,

    /* U+F293 "" */
    0x0, 0x10, 0x3, 0xfb, 0x90, 0x9a, 0x4d, 0xa,
    0xb4, 0xf0, 0x8c, 0x5d, 0x1, 0xab, 0x50,

    /* U+F2ED "" */
    0x3, 0x50, 0xa, 0xaa, 0xa3, 0xbe, 0xee, 0x1b,
    0xba, 0xb1, 0xbb, 0xab, 0x15, 0xaa, 0x90,

    /* U+F304 "" */
    0x0, 0x0, 0x21, 0x0, 0x2, 0xbd, 0x0, 0x3e,
    0xc4, 0x3, 0xef, 0x60, 0xe, 0xf6, 0x0, 0x9,
    0x50, 0x0,

    /* U+F55A "" */
    0x7, 0xcc, 0xcb, 0x17, 0xfd, 0x67, 0xf4, 0xbf,
    0xe4, 0x7f, 0x40, 0xbf, 0xfe, 0xf2,

    /* U+F7C2 "" */
    0x7, 0x84, 0xb7, 0x6a, 0xff, 0xfb, 0xff, 0xfc,
    0xff, 0xfb, 0x57, 0x74,

    /* U+F8A2 "" */
    0x0, 0x0, 0x23, 0x60, 0xc, 0xde, 0xcc, 0xc1,
    0x50, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 22, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 21, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 31, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 4, .adv_w = 56, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 50, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 21, .adv_w = 67, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 55, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 41, .adv_w = 17, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 42, .adv_w = 27, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 47, .adv_w = 27, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 52, .adv_w = 32, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 55, .adv_w = 47, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 60, .adv_w = 31, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 61, .adv_w = 18, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 28, .box_w = 3, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 71, .adv_w = 53, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 30, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 46, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 46, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 54, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 46, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 49, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 48, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 52, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 49, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 18, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 18, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 137, .adv_w = 47, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 47, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 146, .adv_w = 47, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 46, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 83, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 171, .adv_w = 59, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 61, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 58, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 66, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 54, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 51, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 62, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 25, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 41, .box_w = 4, .box_h = 4, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 58, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 48, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 76, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 58, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 67, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 306, .adv_w = 58, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 50, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 47, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 63, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 57, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 90, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 54, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 52, .box_w = 5, .box_h = 4, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 53, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 27, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 385, .adv_w = 28, .box_w = 3, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 394, .adv_w = 27, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 399, .adv_w = 47, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 404, .adv_w = 40, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 406, .adv_w = 48, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 407, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 55, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 46, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 55, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 28, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 55, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 446, .adv_w = 54, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 22, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 23, .box_w = 3, .box_h = 5, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 464, .adv_w = 49, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 22, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 85, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 54, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 51, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 55, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 500, .adv_w = 55, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 506, .adv_w = 33, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 40, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 33, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 54, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 45, .box_w = 4, .box_h = 3, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 72, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 45, .box_w = 4, .box_h = 4, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 550, .adv_w = 42, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 28, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 560, .adv_w = 24, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 563, .adv_w = 28, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 568, .adv_w = 47, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 571, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 586, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 611, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 55, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 644, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 659, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 677, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 692, .adv_w = 90, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 719, .adv_w = 40, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 727, .adv_w = 60, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 737, .adv_w = 90, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 755, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 55, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 777, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 789, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 804, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 819, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 834, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 846, .adv_w = 70, .box_w = 6, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 864, .adv_w = 50, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 872, .adv_w = 50, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 880, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 895, .adv_w = 70, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 900, .adv_w = 90, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 912, .adv_w = 100, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 933, .adv_w = 90, .box_w = 7, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 954, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 969, .adv_w = 70, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 979, .adv_w = 70, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 989, .adv_w = 100, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1003, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1013, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1028, .adv_w = 80, .box_w = 6, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 1046, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1061, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1076, .adv_w = 70, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1089, .adv_w = 70, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1099, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 50, .box_w = 5, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 1124, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1139, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1154, .adv_w = 90, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1166, .adv_w = 80, .box_w = 7, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 1187, .adv_w = 60, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1199, .adv_w = 100, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1220, .adv_w = 100, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1234, .adv_w = 100, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1248, .adv_w = 100, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1262, .adv_w = 100, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1276, .adv_w = 100, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1290, .adv_w = 100, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1308, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1323, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1338, .adv_w = 80, .box_w = 6, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 1356, .adv_w = 100, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1370, .adv_w = 60, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1382, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_2[] = {
    0x0, 0x7, 0xa, 0xb, 0xc, 0x10, 0x12, 0x14,
    0x18, 0x1b, 0x20, 0x25, 0x26, 0x27, 0x3d, 0x42,
    0x47, 0x4a, 0x4b, 0x4c, 0x50, 0x51, 0x52, 0x53,
    0x66, 0x67, 0x6d, 0x6f, 0x70, 0x73, 0x76, 0x77,
    0x78, 0x7a, 0x92, 0x94, 0xc3, 0xc4, 0xc6, 0xc8,
    0xdf, 0xe6, 0xe9, 0xf2, 0x11b, 0x123, 0x15a, 0x1ea,
    0x23f, 0x240, 0x241, 0x242, 0x243, 0x286, 0x292, 0x2ec,
    0x303, 0x559, 0x7c1, 0x8a1
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 12, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 45, .range_length = 82, .glyph_id_start = 13,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 61441, .range_length = 2210, .glyph_id_start = 95,
        .unicode_list = unicode_list_2, .glyph_id_ofs_list = NULL, .list_length = 60, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 1, 2, 0, 3, 4, 5,
    2, 6, 7, 8, 9, 9, 10, 11,
    12, 0, 13, 14, 15, 16, 17, 18,
    19, 12, 20, 20, 0, 0, 0, 21,
    22, 23, 24, 25, 22, 26, 27, 28,
    29, 29, 30, 31, 32, 29, 29, 22,
    33, 34, 35, 3, 36, 30, 37, 37,
    38, 39, 40, 41, 42, 43, 0, 44,
    0, 45, 46, 47, 48, 49, 50, 51,
    45, 52, 52, 53, 48, 45, 45, 46,
    46, 54, 55, 56, 57, 51, 58, 58,
    59, 58, 60, 41, 0, 0, 9, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 0, 3, 4, 5,
    2, 6, 7, 8, 9, 9, 10, 11,
    12, 13, 14, 15, 16, 17, 12, 18,
    19, 20, 21, 21, 0, 0, 0, 22,
    23, 24, 25, 23, 25, 25, 25, 23,
    25, 25, 26, 25, 25, 25, 25, 23,
    25, 23, 25, 3, 27, 28, 29, 29,
    30, 31, 32, 33, 34, 35, 0, 36,
    0, 37, 38, 39, 39, 39, 0, 39,
    38, 40, 41, 38, 38, 42, 42, 39,
    42, 39, 42, 43, 44, 45, 46, 46,
    47, 46, 48, 0, 0, 35, 9, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 0, 2, -2, 0, 0, 0,
    0, -4, -5, 1, 4, 2, 1, -3,
    1, 4, 0, 3, 1, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 5, 1, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, -2,
    1, 2, 0, 0, -1, 0, -1, 1,
    0, -1, 0, -1, 0, -2, 0, 0,
    0, 0, -1, 0, 0, -1, -1, 0,
    0, -1, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, 0,
    0, -2, 0, -10, 0, 0, -2, 0,
    2, 2, 0, 0, -2, 1, 1, 3,
    2, -1, 2, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, -4, 0, -3, -1, 0, 0, 0,
    0, 0, 3, 0, -2, -1, 0, 0,
    0, -1, 0, 0, -1, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, -1, 3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 3, 0, 1, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 3, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 2, 1, 2, -1, 0, 0, 2,
    -1, -3, -11, 1, 2, 2, 0, -1,
    0, 3, 0, 3, 0, 3, 0, -7,
    0, -1, 2, 0, 3, -1, 2, 1,
    0, 0, 0, -1, 0, 0, -1, 6,
    0, 6, 0, 2, 0, 3, 1, 1,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, -1, 0, 1, -1, -1, -2, 1,
    0, -1, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -5, 0, 0, 0, 0,
    -1, 0, 8, -1, -1, 1, 1, -1,
    0, -1, 1, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 5, 0, 0, -3, 0, 3, 0,
    -5, -8, -5, -2, 2, 0, 0, -5,
    0, 1, -2, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 2, -10, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1,
    1, -1, -2, 0, 0, 0, -1, 0,
    0, -1, 0, 0, 0, -2, 0, -1,
    0, -2, -2, 0, -2, -3, -3, -2,
    0, -2, 0, -2, 0, 0, 0, 0,
    -1, 0, 0, 1, 0, 1, -1, 0,
    0, 0, 0, 1, -1, 0, 0, 0,
    -1, 1, 1, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, -1, 0, -1, 0, -1, 0,
    0, -1, 0, 2, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    0, -1, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, -1, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, -1, -1, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, 0,
    0, -2, -1, -2, 2, 0, 0, -2,
    1, 2, 2, 0, -2, 0, -1, 0,
    0, -4, 1, -1, 1, -4, 1, 0,
    0, 0, -4, 0, -4, -1, -7, -1,
    0, -4, 0, 2, 2, 0, 1, 0,
    0, 0, 0, 0, 0, -1, -1, 0,
    0, 0, 0, -1, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, -1, -1, 0, -1, -1, -1, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, 0,
    0, -1, 0, -2, 1, 0, 0, -1,
    0, 1, 1, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 1,
    0, 0, -1, 0, -1, -1, -1, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    -1, 0, 0, 0, 0, -1, -1, 0,
    0, 2, -1, 0, -3, 0, 0, 2,
    -4, -4, -3, -2, 1, 0, -1, -5,
    -1, 0, -1, 0, -2, 1, -1, -5,
    0, -2, 0, 0, 0, 0, 1, -1,
    0, 1, 0, -2, -3, 0, -4, -2,
    -2, -2, -2, -1, -2, 0, -2, -2,
    0, 0, 0, -1, 0, 0, 0, 1,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, -1, 0, -1, -2, -2, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, -2, 0, 0, 0,
    0, -4, -2, 0, 0, 0, -1, -4,
    0, 0, -1, 1, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 1, 0,
    1, -2, -2, 0, -1, -1, -1, 0,
    0, 0, 0, 0, 0, -2, 0, -1,
    0, -1, -1, 0, -2, -2, -2, -1,
    0, -2, 0, -2, 0, 0, 0, 0,
    6, 0, 0, 0, 0, 0, -1, 0,
    0, -3, 0, 0, 0, 0, 0, -7,
    -1, 3, 2, -1, -3, 0, 1, -1,
    0, -4, 0, -1, 1, -6, -1, 1,
    0, 1, -3, -1, -3, -3, -3, 0,
    0, -5, 0, 5, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -2, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, -1, -1, 0,
    0, -2, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 2,
    0, 1, 0, -2, 1, -1, 0, -2,
    -1, 0, -1, -1, -1, 0, -1, -1,
    0, 0, -1, 0, -1, -1, -1, 0,
    0, -1, 0, 1, -1, 0, -2, 0,
    0, 0, -2, 0, -1, 0, -1, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 1, 0, -1, 0, -1, -1, -2,
    -1, -1, -1, 0, -1, -1, 0, 0,
    0, 0, 0, 0, -1, -1, -1, 0,
    0, 0, 0, 1, -1, 0, -1, 0,
    0, 0, -1, -1, -1, -1, -1, -1,
    1, 3, 0, 0, -2, 0, -1, 2,
    0, -1, -3, -1, 1, 0, 0, -4,
    -1, 1, -1, 1, 0, -1, -1, -3,
    0, -1, 0, 0, 0, -1, 0, 0,
    0, 1, 1, -2, -2, 0, -1, -1,
    -1, -1, -1, 0, -1, 0, -2, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, -1, 0, 0, -1, -1, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, 0, -1, 0, -2, 0, 0, 0,
    -3, 0, 1, -2, 2, 0, -1, -4,
    0, 0, -2, -1, 0, -3, -2, -2,
    0, 0, -3, -1, -3, -3, -4, 0,
    -2, 0, 1, 5, -1, 0, -2, -1,
    0, -1, -1, -2, -1, -3, -3, -2,
    0, 0, -1, 0, 0, 0, 0, -6,
    -1, 2, 2, -2, -3, 0, 0, -2,
    0, -4, -1, -1, 2, -7, -1, 0,
    0, 0, -5, -1, -4, -1, -6, 0,
    0, -6, 0, 5, 0, 0, -1, 0,
    0, 0, 0, 0, -1, -3, -1, 0,
    0, 0, 0, 0, -3, 0, -1, 0,
    0, -2, -4, 0, 0, 0, -1, -2,
    -1, 0, -1, 0, 0, 0, 0, -4,
    -1, -3, -3, -1, -1, -2, -1, -1,
    0, -2, -1, -3, -1, 0, -1, -2,
    -1, -2, 0, 0, 0, -1, -3, 0,
    0, -1, 0, 0, 0, 0, 1, 0,
    1, -2, 3, 0, -1, -1, -1, 0,
    0, 0, 0, 0, 0, -2, 0, -1,
    0, -1, -1, 0, -2, -2, -2, -1,
    0, -2, 1, 3, 0, 0, 0, 0,
    6, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, -1, 0, 0, -2, -1, 0,
    0, -2, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 1, -1, 0, -3, -1, 0, 2,
    -3, -3, -2, -2, 3, 1, 1, -7,
    -1, 2, -1, 0, -1, 1, -1, -3,
    0, -1, 1, -1, -1, -2, -1, 0,
    0, 2, 2, 0, -2, 0, -4, -1,
    2, -1, -3, 0, -1, -3, -3, -1,
    1, 0, -1, 0, -2, 0, 1, 3,
    -2, -3, -3, -2, 2, 0, 0, -6,
    -1, 1, -1, -1, -2, 0, -2, -3,
    -1, -1, -1, 0, 0, -2, -2, -1,
    0, 2, 2, -1, -4, 0, -4, -1,
    0, -3, -5, 0, -3, -1, -3, -2,
    0, 0, -1, 0, -2, -1, 0, -1,
    -1, 0, 1, -3, 1, 0, 0, -4,
    0, -1, -2, -1, -1, -2, -2, -3,
    -2, 0, -2, -1, -2, -2, -2, -1,
    0, 0, 0, 4, -1, 0, -2, -1,
    0, -1, -2, -2, -2, -2, -3, -1,
    2, 0, -1, 0, -4, -1, 0, 2,
    -3, -3, -2, -3, 3, -1, 0, -7,
    -1, 2, -2, -1, -3, 0, -2, -3,
    -1, -1, -1, -1, -2, -2, 0, 0,
    0, 2, 2, -1, -5, 0, -5, -2,
    2, -3, -5, -2, -3, -3, -4, -3,
    0, 0, 0, 0, -1, 0, 0, 1,
    -1, 2, 1, -2, 2, 0, 0, -2,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 1, 2, 0, 0, -1, 0,
    0, 0, 0, -1, -1, -1, 0, 0,
    0, 1, 0, 0, 0, 0, 1, 0,
    -1, 0, 3, 0, 1, 0, 0, -1,
    0, 2, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, -1, 1, 0, 2, 0,
    0, 8, 1, -2, -2, 1, 1, -1,
    0, -4, 0, 0, 4, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 3, 11, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, -2, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, -2, 0, 0, 0, 0,
    0, 1, 10, -2, -1, 3, 2, -2,
    1, 0, 0, 1, 1, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, -2,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, -2, 0, -1, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, -1, 0, -2, 0, 0, 0, -1,
    1, -1, 0, 0, -2, -1, -2, 0,
    0, -2, 0, -1, 0, -4, 0, -1,
    0, 0, -6, -2, -3, -1, -3, 0,
    0, -5, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, -1,
    0, 0, 0, 0, -2, 0, -2, 1,
    -1, 2, 0, -1, -2, -1, -1, -2,
    0, -1, 0, -1, 1, -2, 0, 0,
    0, 0, -7, -1, -1, 0, -2, 0,
    -1, -4, -1, 0, 0, -1, -1, 0,
    0, 0, 0, 1, 0, -1, -1, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0,
    0, -2, 0, -1, 0, 0, 0, -2,
    1, 0, 0, 0, -2, -1, -2, 0,
    0, -2, 0, -1, 0, -4, 0, 0,
    0, 0, -8, 0, -2, -3, -4, 0,
    0, -5, 0, -1, -1, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, 0,
    0, 0, 0, 1, -1, 0, 2, 4,
    -1, -1, -2, 1, 4, 1, 2, -2,
    1, 3, 1, 2, 2, 2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 5, 4, -1, -1, 0, -1, 6,
    3, 6, 0, 0, 0, 1, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, -7, -1, -1, -3, -4, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, -7, -1, -1, -3, -4, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    -2, 1, 0, -1, 1, 1, 1, -2,
    0, 0, -1, 1, 0, 1, 0, 0,
    0, 0, -2, 0, -1, -1, -2, 0,
    -1, -3, 0, 5, -1, 0, -2, -1,
    0, -1, -1, 0, -1, -2, -2, -1,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, -7, -1, -1, -3, -4, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, -3, -1, -1, 2,
    -1, -1, -3, 0, 0, 0, -1, -2,
    0, 2, 0, 1, 0, 1, -2, -3,
    -1, 0, -3, -2, -2, -3, -3, 0,
    -1, -2, -1, -1, -1, -1, -1, -1,
    0, -1, 0, 1, 0, 1, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -1, -1, 0,
    0, -2, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, 0,
    0, 0, 0, 0, -1, 0, 0, -1,
    -1, 1, 0, -1, -2, -1, 0, -2,
    -1, -2, -1, -1, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 3, 0, 0, -1, 0,
    0, 0, 0, -1, 0, -1, 0, 0,
    0, 0, -1, 0, -2, 0, 0, 3,
    -1, -3, -2, 1, 1, 1, 0, -2,
    1, 1, 1, 2, 1, 3, -1, -2,
    0, 0, -3, 0, 0, -2, -2, 0,
    0, -2, 0, -1, -1, 0, -1, 0,
    -1, 0, -1, 1, 0, -1, -2, -1,
    0, 0, -1, 0, -2, 0, 0, 1,
    -2, 0, 1, -1, 1, 0, 0, -3,
    0, -1, 0, 0, -1, 1, -1, 0,
    0, 0, -3, -1, -2, 0, -2, 0,
    0, -4, 0, 3, -1, 0, -1, 0,
    0, 0, -1, 0, -1, -2, 0, -1,
    0, 0, 0, 0, -1, 0, 0, 1,
    -1, 0, 0, 0, -1, -1, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 2, 0, 0, -1, 0,
    0, 0, 0, 0, 0, -1, -1, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 60,
    .right_class_cnt     = 48,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 3,
    .bpp = 4,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t lv_font_montserratMedium_5 = {
#else
lv_font_t lv_font_montserratMedium_5 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 5,          /*The maximum line height required by the font  default: (f.src.ascent - f.src.descent)*/
    .base_line = 1,                          /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LV_FONT_MONTSERRATMEDIUM_5*/

