#pragma once
#include <stdint.h>

//https://github.com/robey/font-problems/tree/master/fonts
/* row data, little-endian (smallest bit on left) */

static const int bizcat_font_glyphs = 256;
static const int bizcat_font_height = 16;

static uint8_t bizcat_font_data[] = {
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, /* 5 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, /* 10 */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x01, /* 15 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0c, 0x7e, 0x7f, 0x7e, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x3f, 0x7f, 0x3f, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x3e, 0x7f, 0x1c, 0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1c, 0x1c, 0x1c, 0x1c, 0x7f, 0x3e, 0x1c, 0x08, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 20 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 25 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 30 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x01, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x36, 0x36, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x36, 0x36, 0x7f, 0x7f, 0x36, 0x36, 0x7f, 0x7f, 0x36, 0x36, 0x00, 0x00, 0x00, /* 35 */
  0x00, 0x00, 0x0c, 0x0c, 0x3e, 0x3f, 0x03, 0x1f, 0x3e, 0x30, 0x3f, 0x1f, 0x0c, 0x0c, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0x65, 0x77, 0x38, 0x1c, 0x0e, 0x77, 0x53, 0x70, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0e, 0x1f, 0x1b, 0x1f, 0x6e, 0x7f, 0x3b, 0x33, 0x7f, 0x6e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x18, 0x18, 0x18, 0x1c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e, 0x06, 0x06, 0x06, 0x06, 0x0e, 0x0c, 0x1c, 0x18, 0x00, 0x00, /* 40 */
  0x00, 0x00, 0x06, 0x0e, 0x0c, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x1c, 0x0c, 0x0e, 0x06, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x1c, 0x7f, 0x7f, 0x1c, 0x36, 0x36, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x3f, 0x3f, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x1c, 0x0c, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 45 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x73, 0x7b, 0x6f, 0x67, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x18, 0x1c, 0x1e, 0x1a, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x7f, 0x7f, 0x00, 0x00, 0x00, /* 50 */
  0x00, 0x00, 0x00, 0x7f, 0x7f, 0x30, 0x18, 0x3c, 0x70, 0x60, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x38, 0x3c, 0x3e, 0x37, 0x33, 0x7f, 0x7f, 0x30, 0x30, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0x7f, 0x03, 0x3f, 0x7f, 0x60, 0x60, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3c, 0x3e, 0x07, 0x03, 0x3f, 0x7f, 0x63, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0x7f, 0x60, 0x70, 0x38, 0x18, 0x1c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, /* 55 */
  0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x63, 0x3e, 0x7f, 0x63, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x63, 0x7f, 0x7e, 0x60, 0x70, 0x3e, 0x1e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x1c, 0x0c, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x38, 0x1c, 0x0e, 0x07, 0x07, 0x0e, 0x1c, 0x38, 0x30, 0x00, 0x00, 0x00, /* 60 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x00, 0x00, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x60, 0x70, 0x3c, 0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x6b, 0x7b, 0x7b, 0x3b, 0x03, 0x3f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x1c, 0x1c, 0x36, 0x36, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, /* 65 */
  0x00, 0x00, 0x00, 0x3f, 0x7f, 0x66, 0x66, 0x3e, 0x7e, 0x66, 0x66, 0x7f, 0x3f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3c, 0x7e, 0x67, 0x03, 0x03, 0x03, 0x03, 0x67, 0x7e, 0x3c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1f, 0x3f, 0x33, 0x63, 0x63, 0x63, 0x63, 0x33, 0x3f, 0x1f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0x7f, 0x03, 0x03, 0x3f, 0x3f, 0x03, 0x03, 0x7f, 0x7f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0x7f, 0x03, 0x03, 0x3f, 0x3f, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, /* 70 */
  0x00, 0x00, 0x00, 0x3c, 0x7e, 0x67, 0x03, 0x7b, 0x7b, 0x63, 0x67, 0x7e, 0x3c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0x3f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3f, 0x3f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x73, 0x3f, 0x1e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x63, 0x73, 0x3b, 0x1f, 0x0f, 0x0f, 0x1f, 0x3b, 0x73, 0x63, 0x00, 0x00, 0x00, /* 75 */
  0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x7f, 0x7f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x63, 0x63, 0x77, 0x7f, 0x7f, 0x6b, 0x6b, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x63, 0x63, 0x67, 0x6f, 0x6f, 0x7b, 0x7b, 0x73, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0x7f, 0x63, 0x63, 0x7f, 0x3f, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, /* 80 */
  0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x63, 0x63, 0x7b, 0x7b, 0x33, 0x7f, 0x6e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0x7f, 0x63, 0x63, 0x7f, 0x3f, 0x1f, 0x3b, 0x73, 0x63, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x07, 0x1e, 0x3c, 0x70, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0x3f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, /* 85 */
  0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x36, 0x36, 0x36, 0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x63, 0x63, 0x6b, 0x6b, 0x6b, 0x6b, 0x7f, 0x3e, 0x36, 0x36, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x63, 0x63, 0x36, 0x36, 0x1c, 0x1c, 0x36, 0x36, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x33, 0x33, 0x33, 0x1e, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0x7f, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x7f, 0x7f, 0x00, 0x00, 0x00, /* 90 */
  0x00, 0x00, 0x3e, 0x3e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x3e, 0x3e, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0x00, 0x00, 
  0x00, 0x00, 0x3e, 0x3e, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3e, 0x3e, 0x00, 0x00, 
  0x00, 0x00, 0x08, 0x1c, 0x3e, 0x77, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x00, 0x00, /* 95 */
  0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x1c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x60, 0x7e, 0x7f, 0x63, 0x7f, 0x7e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 0x03, 0x1b, 0x3f, 0x77, 0x63, 0x63, 0x77, 0x3f, 0x1b, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x67, 0x03, 0x03, 0x67, 0x7e, 0x3c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x60, 0x60, 0x60, 0x6c, 0x7e, 0x77, 0x63, 0x63, 0x77, 0x7e, 0x6c, 0x00, 0x00, 0x00, /* 100 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x63, 0x7f, 0x7f, 0x03, 0x3e, 0x3c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x78, 0x7c, 0x0c, 0x3f, 0x3f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x7e, 0x77, 0x63, 0x63, 0x77, 0x7e, 0x6c, 0x70, 0x3e, 0x1e, 
  0x00, 0x00, 0x03, 0x03, 0x03, 0x3b, 0x7f, 0x67, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x18, 0x18, 0x00, 0x1e, 0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, /* 105 */
  0x00, 0x00, 0x30, 0x30, 0x00, 0x3c, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x38, 0x1f, 0x0f, 
  0x00, 0x00, 0x03, 0x03, 0x03, 0x63, 0x73, 0x3b, 0x1f, 0x1f, 0x3b, 0x73, 0x63, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1e, 0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x7f, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x6b, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x7f, 0x67, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, /* 110 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x3f, 0x77, 0x63, 0x63, 0x77, 0x3f, 0x1b, 0x03, 0x03, 0x03, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x7e, 0x77, 0x63, 0x63, 0x77, 0x7e, 0x6c, 0x60, 0x60, 0x60, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x7f, 0x67, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x7f, 0x03, 0x3f, 0x7e, 0x60, 0x7f, 0x3e, 0x00, 0x00, 0x00, /* 115 */
  0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x7f, 0x7f, 0x0c, 0x0c, 0x0c, 0x0c, 0x7c, 0x78, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x73, 0x7f, 0x6e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x36, 0x36, 0x1c, 0x1c, 0x08, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x6b, 0x6b, 0x6b, 0x7f, 0x36, 0x36, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x77, 0x3e, 0x1c, 0x1c, 0x3e, 0x77, 0x63, 0x00, 0x00, 0x00, /* 120 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x36, 0x36, 0x3e, 0x1c, 0x18, 0x1c, 0x0f, 0x07, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x30, 0x18, 0x0c, 0x06, 0x7f, 0x7f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x70, 0x78, 0x18, 0x18, 0x1c, 0x0f, 0x0f, 0x1c, 0x18, 0x18, 0x78, 0x70, 0x00, 0x00, 
  0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0x0f, 0x0c, 0x0c, 0x1c, 0x78, 0x78, 0x1c, 0x0c, 0x0c, 0x0f, 0x07, 0x00, 0x00, /* 125 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x6f, 0x7b, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x33, 0x33, 0x0c, 0x0c, 0x33, 0x33, 0x0c, 0x0c, 0x33, 0x33, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 130 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 135 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 140 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 145 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 150 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 155 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, /* 160 */
  0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x1e, 0x07, 0x03, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x36, 0x1b, 0x1b, 0x36, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x36, 0x6c, 0x6c, 0x36, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x18, 0x18, 0x7e, 0x7f, 0x1b, 0x1b, 0x7f, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x3c, 0x7e, 0x66, 0x06, 0x1f, 0x1f, 0x06, 0x06, 0x07, 0x7f, 0x7f, 0x00, 0x00, 0x00, /* 165 */
  0x00, 0x00, 0x78, 0x7c, 0x0e, 0x3f, 0x3f, 0x06, 0x3f, 0x3f, 0x0e, 0x7c, 0x78, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x33, 0x33, 0x33, 0x1e, 0x3f, 0x3f, 0x0c, 0x3f, 0x3f, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x7f, 0x7f, 0x30, 0x7f, 0x7f, 0x30, 0x3f, 0x1f, 0x38, 0x70, 0x60, 0x00, 0x00, 0x00, 
  0x00, 0x1c, 0x3e, 0x36, 0x3e, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x63, 0x77, 0x3e, 0x1c, 0x1c, 0x3e, 0x77, 0x63, 0x00, 0x00, 0x00, 0x00, /* 170 */
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x3f, 0x3f, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x3e, 0x3e, 0x3e, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x57, 0x72, 0x72, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1c, 0x3e, 0x63, 0x4d, 0x55, 0x4d, 0x55, 0x55, 0x63, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1c, 0x3e, 0x63, 0x41, 0x5d, 0x45, 0x5d, 0x41, 0x63, 0x3e, 0x1c, 0x00, 0x00, 0x00, /* 175 */
  0x00, 0x00, 0x00, 0x78, 0x7c, 0x1e, 0x1f, 0x7b, 0x7b, 0x1f, 0x1f, 0x7b, 0x7b, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x7f, 0x6c, 0x7e, 0x3f, 0x1b, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7e, 0x7f, 0x1b, 0x1b, 0x7b, 0x7b, 0x1b, 0x1b, 0x7f, 0x7e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x7f, 0x6b, 0x7b, 0x3b, 0x1b, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x1c, 0x30, 0x3c, 0x36, 0x3c, 0x00, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 180 */
  0x00, 0x1c, 0x36, 0x36, 0x36, 0x1c, 0x00, 0x3e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdb, 0xdb, 0x00, 0x00, 0x00, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 185 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 190 */
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 
  0x0e, 0x3e, 0x38, 0x08, 0x1c, 0x1c, 0x36, 0x36, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x38, 0x3e, 0x0e, 0x08, 0x1c, 0x1c, 0x36, 0x36, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x1c, 0x3e, 0x77, 0x08, 0x1c, 0x1c, 0x36, 0x36, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x6e, 0x7f, 0x3b, 0x08, 0x1c, 0x1c, 0x36, 0x36, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, /* 195 */
  0x00, 0x36, 0x36, 0x08, 0x1c, 0x1c, 0x36, 0x36, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x1c, 0x36, 0x36, 0x1c, 0x1c, 0x1c, 0x36, 0x36, 0x63, 0x7f, 0x7f, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x0e, 0x3e, 0x38, 0x00, 0x7f, 0x7f, 0x03, 0x3f, 0x3f, 0x03, 0x03, 0x7f, 0x7f, 0x00, 0x00, 0x00, 
  0x38, 0x3e, 0x0e, 0x00, 0x7f, 0x7f, 0x03, 0x3f, 0x3f, 0x03, 0x03, 0x7f, 0x7f, 0x00, 0x00, 0x00, 
  0x1c, 0x3e, 0x77, 0x00, 0x7f, 0x7f, 0x03, 0x3f, 0x3f, 0x03, 0x03, 0x7f, 0x7f, 0x00, 0x00, 0x00, /* 200 */
  0x00, 0x36, 0x36, 0x00, 0x7f, 0x7f, 0x03, 0x3f, 0x3f, 0x03, 0x03, 0x7f, 0x7f, 0x00, 0x00, 0x00, 
  0x07, 0x1f, 0x1c, 0x00, 0x3f, 0x3f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3f, 0x3f, 0x00, 0x00, 0x00, 
  0x38, 0x3e, 0x0e, 0x00, 0x3f, 0x3f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3f, 0x3f, 0x00, 0x00, 0x00, 
  0x0c, 0x1e, 0x33, 0x00, 0x3f, 0x3f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3f, 0x3f, 0x00, 0x00, 0x00, 
  0x00, 0x33, 0x33, 0x00, 0x3f, 0x3f, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3f, 0x3f, 0x00, 0x00, 0x00, /* 205 */
  0x00, 0x00, 0x00, 0x3c, 0x7e, 0x67, 0x03, 0x03, 0x03, 0x03, 0x67, 0x7e, 0x3c, 0x18, 0x1e, 0x0c, 
  0x6e, 0x7f, 0x3b, 0x00, 0x63, 0x63, 0x67, 0x6f, 0x7f, 0x7b, 0x73, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x0e, 0x3e, 0x38, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x38, 0x3e, 0x0e, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x1c, 0x3e, 0x77, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, /* 210 */
  0x6e, 0x7f, 0x3b, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x36, 0x36, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x6c, 0x7e, 0x37, 0x7b, 0x7b, 0x6f, 0x6f, 0x76, 0x3f, 0x1b, 0x00, 0x00, 0x00, 
  0x0e, 0x3e, 0x38, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x38, 0x3e, 0x0e, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, /* 215 */
  0x1c, 0x3e, 0x77, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x00, 0x36, 0x36, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00, 
  0x1c, 0x1f, 0x07, 0x00, 0x33, 0x33, 0x33, 0x3f, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x33, 0x33, 0x00, 0x33, 0x33, 0x33, 0x1e, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1e, 0x3e, 0x36, 0x66, 0x6f, 0x6f, 0x66, 0x36, 0x3e, 0x1e, 0x00, 0x00, 0x00, /* 220 */
  0x00, 0x00, 0x00, 0x03, 0x03, 0x3f, 0x7f, 0x63, 0x63, 0x7f, 0x3f, 0x03, 0x03, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7e, 0x7f, 0x33, 0x1b, 0x3b, 0x73, 0x63, 0x63, 0x7b, 0x3b, 0x00, 0x00, 0x00, 
  0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, 0x00, 
  0x00, 0x0e, 0x3e, 0x38, 0x00, 0x3c, 0x7e, 0x60, 0x7e, 0x7f, 0x63, 0x7f, 0x7e, 0x00, 0x00, 0x00, 
  0x00, 0x38, 0x3e, 0x0e, 0x00, 0x3c, 0x7e, 0x60, 0x7e, 0x7f, 0x63, 0x7f, 0x7e, 0x00, 0x00, 0x00, /* 225 */
  0x00, 0x1c, 0x3e, 0x77, 0x00, 0x3c, 0x7e, 0x60, 0x7e, 0x7f, 0x63, 0x7f, 0x7e, 0x00, 0x00, 0x00, 
  0x00, 0x6e, 0x7f, 0x3b, 0x00, 0x3c, 0x7e, 0x60, 0x7e, 0x7f, 0x63, 0x7f, 0x7e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x36, 0x36, 0x00, 0x3c, 0x7e, 0x60, 0x7e, 0x7f, 0x63, 0x7f, 0x7e, 0x00, 0x00, 0x00, 
  0x00, 0x1c, 0x36, 0x36, 0x1c, 0x3c, 0x7e, 0x60, 0x7e, 0x7f, 0x63, 0x7f, 0x7e, 0x00, 0x00, 0x00, 
  0x00, 0x0e, 0x3e, 0x38, 0x00, 0x1c, 0x3e, 0x63, 0x7f, 0x7f, 0x03, 0x3e, 0x3c, 0x00, 0x00, 0x00, /* 230 */
  0x00, 0x38, 0x3e, 0x0e, 0x00, 0x1c, 0x3e, 0x63, 0x7f, 0x7f, 0x03, 0x3e, 0x3c, 0x00, 0x00, 0x00, 
  0x00, 0x1c, 0x3e, 0x77, 0x00, 0x1c, 0x3e, 0x63, 0x7f, 0x7f, 0x03, 0x3e, 0x3c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x36, 0x36, 0x00, 0x1c, 0x3e, 0x63, 0x7f, 0x7f, 0x03, 0x3e, 0x3c, 0x00, 0x00, 0x00, 
  0x00, 0x0e, 0x3e, 0x38, 0x00, 0x1e, 0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x38, 0x3e, 0x0e, 0x00, 0x1e, 0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, /* 235 */
  0x00, 0x1c, 0x3e, 0x77, 0x00, 0x1e, 0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x36, 0x36, 0x00, 0x1e, 0x1e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x7e, 0x67, 0x03, 0x03, 0x67, 0x7e, 0x3c, 0x18, 0x1e, 0x0c, 
  0x00, 0x6e, 0x7f, 0x3b, 0x00, 0x3b, 0x7f, 0x67, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
  0x00, 0x0e, 0x3e, 0x38, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, /* 240 */
  0x00, 0x38, 0x3e, 0x0e, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x1c, 0x3e, 0x77, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x6e, 0x7f, 0x3b, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x36, 0x36, 0x00, 0x1c, 0x3e, 0x77, 0x63, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x7e, 0x37, 0x7b, 0x6f, 0x76, 0x3f, 0x1b, 0x00, 0x00, 0x00, /* 245 */
  0x00, 0x0e, 0x3e, 0x38, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x73, 0x7f, 0x6e, 0x00, 0x00, 0x00, 
  0x00, 0x38, 0x3e, 0x0e, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x73, 0x7f, 0x6e, 0x00, 0x00, 0x00, 
  0x00, 0x1c, 0x3e, 0x77, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x73, 0x7f, 0x6e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x36, 0x36, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x73, 0x7f, 0x6e, 0x00, 0x00, 0x00, 
  0x00, 0x38, 0x3e, 0x0e, 0x00, 0x63, 0x63, 0x63, 0x36, 0x36, 0x3e, 0x1c, 0x18, 0x1c, 0x0f, 0x07, /* 250 */
  0x00, 0x00, 0x36, 0x36, 0x00, 0x63, 0x63, 0x63, 0x36, 0x36, 0x3e, 0x1c, 0x18, 0x1c, 0x0f, 0x07, 
  0x00, 0x00, 0x0c, 0x3c, 0x1e, 0x38, 0x3c, 0x7e, 0x77, 0x63, 0x77, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0x03, 0x03, 0x1b, 0x3f, 0x77, 0x63, 0x63, 0x77, 0x3f, 0x1b, 0x03, 0x03, 0x03, 
  0x00, 0x00, 0x1e, 0x3f, 0x33, 0x33, 0x1b, 0x3b, 0x73, 0x63, 0x63, 0x7b, 0x3b, 0x00, 0x00, 0x00, 
  0x00, 0x6b, 0x55, 0x6b, 0x41, 0x6b, 0x41, 0x5d, 0x55, 0x55, 0x5d, 0x41, 0x6b, 0x41, 0x41, 0x41, /* 255 */
};
