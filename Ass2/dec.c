#include <stdio.h>
#include <stdint.h>
#include <string.h>

void inv_sub_bytes(uint8_t state[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            state[i][j] = inv_s_box[state[i][j]];
        }
    }
}

void inv_shift_rows(uint8_t state[4][4]) {
    uint8_t temp[4];

    // Row 1: right shift by 1
    temp[0] = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp[0];

    // Row 2: right shift by 2
    temp[0] = state[2][0];
    temp[1] = state[2][1];
    state[2][0] = state[2][2];
    state[2][1] = state[2][3];
    state[2][2] = temp[0];
    state[2][3] = temp[1];

    // Row 3: right shift by 3
    temp[0] = state[3][0];
    state[3][0] = state[3][1];
    state[3][1] = state[3][2];
    state[3][2] = state[3][3];
    state[3][3] = temp[0];
}

void inv_mix_columns(uint8_t state[4][4]) {
    uint8_t temp[4][4];

    for (int i = 0; i < 4; ++i) {
        temp[0][i] = gmul(0x0e, state[0][i]) ^ gmul(0x0b, state[1][i]) ^ gmul(0x0d, state[2][i]) ^ gmul(0x09, state[3][i]);
        temp[1][i] = gmul(0x09, state[0][i]) ^ gmul(0x0e, state[1][i]) ^ gmul(0x0b, state[2][i]) ^ gmul(0x0d, state[3][i]);
        temp[2][i] = gmul(0x0d, state[0][i]) ^ gmul(0x09, state[1][i]) ^ gmul(0x0e, state[2][i]) ^ gmul(0x0b, state[3][i]);
        temp[3][i] = gmul(0x0b, state[0][i]) ^ gmul(0x0d, state[1][i]) ^ gmul(0x09, state[2][i]) ^ gmul(0x0e, state[3][i]);
    }

    memcpy(state, temp, 16);
}

// Include the sub_bytes, shift_rows, mix_columns, add_round_key, key_expansion, and aes_128_encrypt functions as provided earlier

void aes_128_decrypt(const uint8_t input[16], const uint8_t key[16], uint8_t output[16]) {
    uint8_t state[4][4];
    uint8_t round_keys[11][4][4];

    memcpy(state, input, 16);
    key_expansion(key, round_keys);

    add_round_key(state, round_keys[10]);
    inv_shift_rows(state);
    inv_sub_bytes(state);

    for (int round = 9; round > 0; --round) {
        add_round_key(state, round_keys[round]);
        inv_mix_columns(state);
        inv_shift_rows(state);
        inv_sub_bytes(state);
    }

    add_round_key(state, round_keys[0]);
    memcpy(output, state, 16);
}

int main() {
    uint8_t plaintext[16] = "This is a test!";
    uint8_t key[16] = "This is a key!!";
    uint8_t ciphertext[16];
    uint8_t decrypted[16];

    aes_128_encrypt(plaintext, key, ciphertext);

    printf("Plaintext: ");
    for (int i = 0; i < 16; ++i) {
        printf("%c", plaintext[i]);
    }
    printf("\n");

    printf("Ciphertext: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    aes_128_decrypt(ciphertext, key, decrypted);

    printf("Decrypted: ");
    for (int i = 0; i < 16; ++i) {
        printf("%c", decrypted[i]);
    }
    printf("\n");

    return 0;
}
