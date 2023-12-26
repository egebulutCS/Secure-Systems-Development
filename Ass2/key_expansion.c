#include <stdio.h>
#include <stdint.h>

#define KEY_SIZE 16
#define EXP_KEY_SIZE 176
#define ROUNDS 10

uint8_t s_box(uint8_t value);

void key_expansion(const uint8_t *key, uint8_t *expanded_key) {
    int i, j;
    uint8_t temp[4], k;

    for (i = 0; i < KEY_SIZE; i++) {
        expanded_key[i] = key[i];
    }

    for (; i < EXP_KEY_SIZE; i += 4) {
        for (j = 0; j < 4; j++) {
            temp[j] = expanded_key[i - 4 + j];
        }

        if (i % KEY_SIZE == 0) {
            // Rotate
            k = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = k;

            // Substitute bytes using S-box
            for (j = 0; j < 4; j++) {
                temp[j] = s_box(temp[j]);
            }

            // XOR with Rcon
            temp[0] ^= (0x1 << ((i / KEY_SIZE) - 1)) ^ (((i / KEY_SIZE) > 1) * 0x1b);
        }

        for (j = 0; j < 4; j++) {
            expanded_key[i + j] = expanded_key[i - KEY_SIZE + j] ^ temp[j];
        }
    }
}

uint8_t s_box(uint8_t value) {
    // Implement the S-box functionality here or use a pre-defined S-box array
    return value; // Placeholder, replace with actual implementation
}

int main() {
    uint8_t key[KEY_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    uint8_t expanded_key[EXP_KEY_SIZE];

    key_expansion(key, expanded_key);

    for (int i = 0; i < EXP_KEY_SIZE; i++) {
        if (i % 16 == 0) printf("\n");
        printf("%02x ", expanded_key[i]);
    }

    return 0;
}
