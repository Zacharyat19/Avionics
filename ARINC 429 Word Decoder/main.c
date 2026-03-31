#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "arinc429.h"

// -----------------------------------------------------------------------------
// Helper Function: Pretty-print the decoded struct
// -----------------------------------------------------------------------------
void print_decoded_word(const char* test_name, uint32_t raw_hex, arinc_word_t* word)
{
    printf("--- %s ---\n", test_name);
    printf("Raw Word (Hex) : 0x%08X\n", raw_hex);
    printf("Label (Octal)  : %03o\n", word->label); // Aviation traditionally reads Labels in Octal
    printf("SDI            : %u\n", word->sdi);
    printf("Data Payload   : %u (0x%X)\n", word->raw_data, word->raw_data);
    printf("SSM            : %u\n", word->ssm);
    printf("Parity Bit     : %u\n", word->parity_bit);
    
    // Print the validation status clearly
    if (word->is_parity_valid) 
    {
        printf("Status         : [VALID] Odd Parity Confirmed\n\n");
    } 
    else 
    {
        printf("Status         : [ERROR] Even Parity Detected (Data Corrupted)\n\n");
    }
}

// -----------------------------------------------------------------------------
// Main Execution
// -----------------------------------------------------------------------------
int main(void)
{
    arinc_word_t decoded_result;

    /* * TEST CASE 1: Perfectly Valid ARINC Word
     * * Breakdown of 0x0068AE45:
     * Label: 0x45 (Octal 105)
     * SDI:   0x02
     * Data:  0x1A2B
     * SSM:   0x00
     * * If you count the binary '1's in 0x0068AE45, there are exactly 11.
     * Because 11 is an odd number, the parity bit (the 32nd bit) is left as 0.
     */
    uint32_t valid_word = 0x0068AE45;
    
    arinc_decode_word(valid_word, &decoded_result);
    print_decoded_word("Test Case 1: Valid Word", valid_word, &decoded_result);


    /* * TEST CASE 2: Intentionally Corrupted Word (Simulated EMI Noise)
     * * We take the exact same valid word, but we simulate a cosmic ray or 
     * electromagnetic interference flipping the 32nd bit to a '1'.
     * The hex changes from 0x0068AE45 to 0x8068AE45.
     * The total number of '1's is now 12 (an even number). The validator must catch this.
     */
    uint32_t corrupted_word = 0x8068AE45;

    arinc_decode_word(corrupted_word, &decoded_result);
    print_decoded_word("Test Case 2: Corrupted Word", corrupted_word, &decoded_result);

    return 0;
}