#include "arinc429.h"

uint8_t arinc_extract_label(uint32_t raw_word)
{
    return (raw_word & ARINC_MASK_LABEL) >> ARINC_SHIFT_LABEL;
}

uint8_t arinc_extract_sdi(uint32_t raw_word)
{
    return (raw_word & ARINC_MASK_SDI) >> ARINC_SHIFT_SDI;
}

uint32_t arinc_extract_data(uint32_t raw_word)
{
    return (raw_word & ARINC_MASK_DATA) >> ARINC_SHIFT_DATA;
}

uint8_t arinc_extract_ssm(uint32_t raw_word)
{
    return (raw_word & ARINC_MASK_SSM) >> ARINC_SHIFT_SSM;
}

bool arinc_validate_parity(uint32_t raw_word)
{
    int set_bits_count = 0;

    while (raw_word != 0) 
    {
        raw_word &= (raw_word - 1);
        set_bits_count++;
    }

    return (set_bits_count % 2) != 0;
}

void arinc_decode_word(uint32_t raw_word, arinc_word_t* decoded_output)
{
    decoded_output->label = arinc_extract_label(raw_word);
    decoded_output->sdi = arinc_extract_sdi(raw_word);
    decoded_output->ssm = arinc_extract_ssm(raw_word);
    decoded_output->raw_data = arinc_extract_data(raw_word);
    decoded_output->parity_bit = (bool)((raw_word & ARINC_MASK_PARITY) >> ARINC_SHIFT_PARITY);
    decoded_output->is_parity_valid = arinc_validate_parity(raw_word);
}