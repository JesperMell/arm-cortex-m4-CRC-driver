#include <CRC.h>
#include <kinetis.h>

// CRC 16-bit seed
#define SEED 0x0000FFFF

// Polynomial for 16 bits (Low field).
#define POLY 0x00008408

#define CRC_CTRL_FXOR ((uint32_t)0x04000000)

#define CRC_CTRL_WAS_SEED ((uint32_t)0x02000000)
#define CRC_CTRL_WAS_DATA ~CRC_CTRL_WAS_SEED

#define CRC_CTRL_TCRC_32 ((uint32_t)0x01000000)
#define CRC_CTRL_TCRC_16 ~CRC_CTRL_TCRC_32

// Both bits and bytes are transposed.
#define CRC_CTRL_TOT_1 ((uint32_t)0x10000000)
#define CRC_CTRL_TOTR_1 ((uint32_t)0x40000000)

void crc_init(void)
{
  SIM_SCGC6 |= SIM_SCGC6_CRC;    // enable CRC clock
  CRC_CTRL &= CRC_CTRL_TCRC_16;   // Set to CRC 16-bit protocol.
  CRC_CTRL |= CRC_CTRL_TOT_1;     // Set Type of Transpose to type 01 (Write).
  CRC_CTRL |= CRC_CTRL_TOTR_1;    // Set Type of Transpose to type 01 (Read).
  CRC_CTRL |= CRC_CTRL_FXOR;
}

uint16_t crc_generate(uint16_t data)
{
  CRC_GPOLY |= POLY;
  CRC_CTRL |= CRC_CTRL_WAS_SEED;      // Writes to CRC data register are seed value.
  CRC_CRC |= SEED;                   // Add the seed to CRC data.
  CRC_CTRL &= CRC_CTRL_WAS_DATA;      // Clear CRC_CTRL[DATA] to start writing data.
  CRC_CRC &= data;                  // Send the Data.

  return (uint16_t)(CRC_CRC & 0x0000FFFF);  // Read the Data.
}
