#ifndef ARINC429_DECODER_H
#define ARINC429_DECODER_H

#include <stdint.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
// ARINC 429 Bit Masks
// -----------------------------------------------------------------------------
#define ARINC_MASK_LABEL  0x000000FF // Bits 1-8  (Label / Parameter ID)
#define ARINC_MASK_SDI    0x00000300 // Bits 9-10 (Source/Destination Identifier)
#define ARINC_MASK_DATA   0x1FFFFC00 // Bits 11-29 (Payload)
#define ARINC_MASK_SSM    0x60000000 // Bits 30-31 (Sign/Status Matrix)
#define ARINC_MASK_PARITY 0x80000000 // Bit 32    (Odd Parity)

// -----------------------------------------------------------------------------
// ARINC 429 Bit Shifts
// -----------------------------------------------------------------------------
#define ARINC_SHIFT_SDI    8
#define ARINC_SHIFT_DATA   10
#define ARINC_SHIFT_SSM    29
#define ARINC_SHIFT_PARITY 31

// -----------------------------------------------------------------------------
// Data Structures
// -----------------------------------------------------------------------------

// A clean struct to hold the decoded values for application use
typedef struct 
{
    uint8_t  label;
    uint8_t  sdi;
    uint32_t raw_data;
    uint8_t  ssm;
    bool     parity_bit;
    bool     is_parity_valid;
} arinc_word_t;

// Core extraction functions
uint8_t arinc_extract_label(uint32_t raw_word);
uint8_t arinc_extract_sdi(uint32_t raw_word);
uint32_t arinc_extract_data(uint32_t raw_word);
uint8_t arinc_extract_ssm(uint32_t raw_word);

// Validation
bool arinc_validate_parity(uint32_t raw_word);

// Main decoding interface
void arinc_decode_word(uint32_t raw_word, arinc_word_t* decoded_output);

#endif