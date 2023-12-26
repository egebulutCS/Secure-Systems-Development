#include <stdio.h>
#include <stdlib.h>

void aes_encrypt(uint8_t input_block[16], uint8_t key[16], uint8_t output_block[16]);
void aes_decrypt(uint8_t input_block[16], uint8_t key[16], uint8_t output_block[16]);