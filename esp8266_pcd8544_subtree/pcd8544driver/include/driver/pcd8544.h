/*
 * gpio_intr.h
 *
 *  GPIO interrupt handler
 *
 *  Created on: Jan 7, 2015
 *      Author: EaD
 */

#ifndef INCLUDE_DRIVER_PCD8544_H_
#define INCLUDE_DRIVER_PCD8544_H_

#include "ctype.h"
#include "c_types.h"

/**
 * Draws a full screen image.
 * The image must be exactly 528 bytes.
 * (84+filler * 48) bits
 */
void PCD8544_lcdXbmImage(uint8_t *image);
void PCD8544_lcdImage(uint8_t *image);
void PCD8544_lcdClear(void);
void PCD8544_lcdCharacter(char character);
/**
 * Writes a null terminated string
 */
void PCD8544_lcdString(char *characters);
/**
 * debug prints a binary to console
 */
void PCD8544printBinary(uint32_t data);
void PCD8544_gotoXY(int x, int y);
void PCD8544_drawLine(void);

void PCD8544_initLCD(void);
/**
 */
void PCD8544_init(void);

#endif /* INCLUDE_DRIVER_PCD8544_H_ */
