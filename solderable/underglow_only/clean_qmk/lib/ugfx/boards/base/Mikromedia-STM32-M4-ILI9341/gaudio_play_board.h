/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef GAUDIO_PLAY_BOARD_H
#define GAUDIO_PLAY_BOARD_H

#define SET_CS		palSetPad(GPIOC, GPIOC_MP3_CS)
#define CLR_CS		palClearPad(GPIOC, GPIOC_MP3_CS)
#define SET_RST		palSetPad(GPIOC, GPIOC_MP3_RST)
#define CLR_RST		palClearPad(GPIOC, GPIOC_MP3_RST)
#define SET_DCS		palSetPad(GPIOC, GPIOC_MP3_DCS)
#define CLR_DCS		palClearPad(GPIOC, GPIOC_MP3_DCS)
#define GET_DREQ	palReadPad(GPIOC, GPIOC_MP3_DREQ)
#define SPI_PORT	&SPID3

static const SPIConfig spicfg_init = {
    0,
	GPIOC,
	GPIOC_MP3_CS,
    SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
};

static const SPIConfig spicfg = {
    0,
	GPIOC,
	GPIOC_MP3_CS,
	SPI_CR1_BR_0,
};

// Initialise the board
static GFXINLINE void board_init(void) {
	palSetPadMode(GPIOC, GPIOC_MP3_CS, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, GPIOC_MP3_RST, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, GPIOC_MP3_DCS, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, GPIOC_MP3_DREQ, PAL_MODE_INPUT);
	SET_CS; SET_RST; SET_DCS;
	spiStart(SPI_PORT, &spicfg_init);
}

// Chip is initialised enough so we can talk fast to it
#define board_init_end()	spiStart(SPI_PORT, &spicfg)

// Reset the board
#define board_reset()		{ CLR_RST; gfxSleepMilliseconds(1); SET_RST; }

// Returns the state of the dreq pin
#define board_dreq()		GET_DREQ

// Start a command write
static GFXINLINE void board_startcmdwrite(void) {
	#if SPI_USE_MUTUAL_EXCLUSION
		spiAcquireBus(SPI_PORT);
	#endif
	CLR_CS;
}

// End a command write
static GFXINLINE void board_endcmdwrite(void) {
	SET_CS;
	#if SPI_USE_MUTUAL_EXCLUSION
		spiReleaseBus(SPI_PORT);
	#endif
}

// Start a command read
#define board_startcmdread()	board_startcmdwrite()

// End a command read
#define board_endcmdread()		board_endcmdwrite()

// Start a data write
static GFXINLINE void board_startdatawrite(void) {
	#if SPI_USE_MUTUAL_EXCLUSION
		spiAcquireBus(SPI_PORT);
	#endif
	CLR_DCS;
}

// End a data write
static GFXINLINE void board_enddatawrite(void) {
	#if SPI_USE_MUTUAL_EXCLUSION
		spiReleaseBus(SPI_PORT);
	#endif
	SET_DCS;
}

// Write data to the SPI port
#define board_spiwrite(buf, len)	spiSend(SPI_PORT, len, buf)

// Read data from the SPI port
#define board_spiread(buf, len)		spiReceive(SPI_PORT, len, buf)

#endif	/* GAUDIO_PLAY_BOARD_H */
