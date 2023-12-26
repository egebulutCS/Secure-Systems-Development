#include <stdint.h>

#define BLOCK_SIZE 16

uint8_t inv_s_box(uint8_t value);

void invSubBytes(uint8_t *state) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        state[i] = inv_s_box(state[i]);
    }
}

void invShiftRows(uint8_t *state) {
    uint8_t temp;

    // Row 1
    temp = state[13];
    state[13] = state[9];
    state[9] = state[5];
    state[5] = state[1];
    state[1] = temp;

    // Row 2
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Row 3
    temp = state[3];
    state[3] = state[7];
    state[7] = state[11];
    state[11] = state[15];
    state[15] = temp;
}

void invMixColumns(uint8_t *state) {
    uint8_t temp[4];

    for (int i = 0; i < 4; i++) {
        temp[0] = state[4 * i + 0];
        temp[1] = state[4 * i + 1];
        temp[2] = state[4 * i + 2];
        temp[3] = state[4 * i + 3];

        state[4 * i + 0] = (0x0e * temp[0]) ^ (0x0b * temp[1]) ^ (0x0d * temp[2]) ^ (0x09 * temp[3]);
        state[4 * i + 1] = (0x09 * temp[0]) ^ (0x0e * temp[1]) ^ (0x0b * temp[2]) ^ (0x0d * temp[3]);
        state[4 * i + 2] = (0x0d * temp[0]) ^ (0x09 * temp[1]) ^ (0x0e * temp[2]) ^ (0x0b * temp[3]);
        state[4 * i + 3] = (0x0b * temp[0]) ^ (0x0d * temp[1]) ^ (0x09 * temp[2]) ^ (0x0e * temp[3]);
    }
}

void invAddRoundKey(uint8_t *state, const uint8_t *round_key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        state[i] ^= round_key[i];
    }
}

uint8_t inv_s_box(uint8_t value) {
    // Implement the inverse S-box functionality here or use a pre-defined inverse S-box array
    return value; // Placeholder, replace with actual implementation
}
