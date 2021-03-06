#include <proxmark3.h>
#include "apps.h"

//-----------------------------------------------------------------------------
// Set up the Serial Peripheral Interface as master
// Used to talk to the attached peripherals (FPGA, LCD, uSD)
//-----------------------------------------------------------------------------
void SetupSpi(int mode)
{
	// PA5  -> SPI_NCS3 chip select (spare)
	// PA9  -> SPI_NCS1 chip select (microSD)
	// PA10 -> SPI_NCS2 chip select (LCD)
	// PA11 -> SPI_NCS0 chip select (FPGA)
	// PA12 -> SPI_MISO Master-In Slave-Out
	// PA13 -> SPI_MOSI Master-Out Slave-In
	// PA14 -> SPI_SPCK Serial Clock

	// Disable PIO control of the following pins, allows use by the SPI peripheral
	AT91C_BASE_PIOA->PIO_PDR =
			GPIO_NCS0	|
			GPIO_NCS1 	|
			GPIO_NCS2 	|
			GPIO_NCS3 	|
			GPIO_MISO	|
			GPIO_MOSI	|
			GPIO_SPCK;

	AT91C_BASE_PIOA->PIO_ASR =
			GPIO_NCS0	|
			GPIO_MISO	|
			GPIO_MOSI	|
			GPIO_SPCK;

	AT91C_BASE_PIOA->PIO_BSR =
			GPIO_NCS1	|
			GPIO_NCS2	|
			GPIO_NCS3;

	//enable the SPI Peripheral clock
	AT91C_BASE_PMC->PMC_PCER = (1<<AT91C_ID_SPI);
	// Enable SPI
	AT91C_BASE_SPI->SPI_CR = AT91C_SPI_SPIEN;

	switch (mode) {
	case SPI_FPGA_MODE:
		AT91C_BASE_SPI->SPI_MR =
				(14 << 16)			|	// Peripheral Chip Select (selects FPGA SPI_NCS0 or PA11)
				AT91C_SPI_MODFDIS	|	// Mode Fault Detection disabled
				AT91C_SPI_MSTR;			// Master Mode
		AT91C_BASE_SPI->SPI_CSR[0] =
				( 1 << 24)			|	// Delay between Consecutive Transfers (32 MCK periods)
				( 1 << 16)			|	// Delay Before SPCK (1 MCK period)
				( 6 << 8)			|	// Serial Clock Baud Rate (baudrate = MCK/6 = 24Mhz/6 = 4M baud
				AT91C_SPI_BITS_16	|	// Bits per Transfer (16 bits)
				AT91C_SPI_NCPHA;	 	// Clock Phase data captured on leading edge, changes on following edge
			break;
		case SPI_MSD_MODE:
			AT91C_BASE_SPI->SPI_MR =
				(13 << 16)			|	// Peripheral Chip Select (selects FPGA SPI_NCS1 or PA9)
				AT91C_SPI_MODFDIS	|	// Mode Fault Detection disabled
				AT91C_SPI_MSTR;			// Master Mode
				AT91C_BASE_SPI->SPI_CSR[1] =
				( 1 << 24)			|	// Delay between Consecutive Transfers (32 MCK periods)
				( 1 << 16)			|	// Delay Before SPCK (1 MCK period)
				( 6 << 8)			|	// Serial Clock Baud Rate (baudrate = MCK/6 = 24Mhz/6 = 4M baud
				AT91C_SPI_BITS_8	|	// Bits per Transfer (16 bits)
				AT91C_SPI_NCPHA;	 	// Clock Phase data captured on leading edge, changes on following edge
			break;
		case SPI_LCD_MODE:
			AT91C_BASE_SPI->SPI_MR =
				(11 << 16)			|	// Peripheral Chip Select (selects LCD SPI_NCS2 or PA10)
				AT91C_SPI_MODFDIS	|	// Mode Fault Detection disabled
				AT91C_SPI_MSTR;			// Master Mode
				AT91C_BASE_SPI->SPI_CSR[2] =
				( 1 << 24)			|	// Delay between Consecutive Transfers (32 MCK periods)
				( 1 << 16)			|	// Delay Before SPCK (1 MCK period)
				( 6 << 8)			|	// Serial Clock Baud Rate (baudrate = MCK/6 = 24Mhz/6 = 4M baud
				AT91C_SPI_BITS_9	|	// Bits per Transfer (9 bits)
				AT91C_SPI_NCPHA;		// Clock Phase data captured on leading edge, changes on following edge
			break;
		case SPI_SPARE_MODE:
			AT91C_BASE_SPI->SPI_MR =
				(7 << 16)			|	// Peripheral Chip Select (selects FPGA SPI_NCS3 or PA5)
				AT91C_SPI_MODFDIS	|	// Mode Fault Detection disabled
				AT91C_SPI_MSTR;			// Master Mode
				AT91C_BASE_SPI->SPI_CSR[3] =
				( 1 << 24)			|	// Delay between Consecutive Transfers (32 MCK periods)
				( 1 << 16)			|	// Delay Before SPCK (1 MCK period)
				( 6 << 8)			|	// Serial Clock Baud Rate (baudrate = MCK/6 = 24Mhz/6 = 4M baud
				AT91C_SPI_BITS_8	|	// Bits per Transfer (8 bits)
				AT91C_SPI_NCPHA;	 	// Clock Phase data captured on leading edge, changes on following edge
			break;
		default:						// Disable SPI
			AT91C_BASE_SPI->SPI_CR = AT91C_SPI_SPIDIS;
			break;
	}
}

//-----------------------------------------------------------------------------
// Transmit data over the SPI then receive any incoming data.
// Data can be variable length (8 - 16 bits)
 //-----------------------------------------------------------------------------
unsigned int spi_com(unsigned int channel, unsigned int dout, unsigned char last)
{
	unsigned int din;

    SetupSpi(channel);		// enable relevant channel

    while ( !( AT91C_BASE_SPI->SPI_SR & AT91C_SPI_TDRE ) ); // wait for SPI ready state

    AT91C_BASE_SPI->SPI_TDR = dout;	// send data

    while ( !( AT91C_BASE_SPI->SPI_SR & AT91C_SPI_RDRF ) );   // wait for incoming data

    din = AT91C_BASE_SPI->SPI_RDR ;	// receive data

    if (last) AT91C_BASE_SPI->SPI_CR = AT91C_SPI_SPIEN | AT91C_SPI_LASTXFER;

    return (din & 0xffff);
}
