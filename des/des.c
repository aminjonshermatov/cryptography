//
// Created by aminjonshermatov on 5/7/2022.
//
#include <stdio.h>
#include <stdint.h>

static const uint8_t S_BOX[8][4][16] = {
        {
                {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0, 7},
                { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3, 8},
                { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5, 0},
                {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
        },
        {
                {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
                { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11, 5},
                { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3, 12, 15},
                {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14, 9}
        },
        {
                {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2, 8},
                {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15, 1},
                {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14, 7},
                { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
        },
        {
                { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
                {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14, 9},
                {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8, 4},
                { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
        },
        {
                { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14, 9},
                {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8, 6},
                { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
                {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5, 3}
        },
        {
                {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
                {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3, 8},
                { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11, 6},
                { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
        },
        {
                { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6, 1},
                {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8, 6},
                { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9, 2},
                { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 12,  2,  3, 12}
        },
        {
                {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12, 7},
                { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9, 2},
                { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5, 8},
                { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
        }
};

static const uint8_t IP[4][16] = {
        {58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4},
        {62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8},
        {57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3},
        {61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 33, 15,  7}
};

static const uint8_t FP[4][16] = {
        {40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31},
        {38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29},
        {36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27},
        {34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25}
};

static const uint8_t PS_1[56] = {
        57, 49, 41, 33, 25, 17,  9,
        1, 58, 50, 42, 34, 26, 18,
        10,  2, 59, 51, 43, 35, 27,
        19, 11,  3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14,  6, 61, 53, 45, 37, 29,
        21, 13,  5, 28, 20, 12,  4
};

static const uint8_t PC_2[48] = {
        14,  7, 11, 24,  1,  5,
        3, 28, 15,  6, 21, 10,
        23, 19, 12,  4, 26,  8,
        16,  7, 27, 20, 13,  2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
};

static const size_t ROUND_KEY_SHIFTS[16] = {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

#define BUFF_SIZE 1024

enum MODE {
    ENCRYPT = 1 << 0,
    DECRYPT = 1 << 1
};

static inline void input_keys_8_byte(uint8_t *buff);
static inline size_t input_plain_text(uint8_t *buff);
static inline void print_text(uint8_t *buff, size_t length);

static uint64_t from_8bits_to_64bit(uint8_t *buff);
static uint64_t reduce_from_64bit_to_56bit(uint64_t num);
static uint64_t reduce_from_56bit_to_48bit(uint64_t num);
static void split_56bit_into_28bits(uint64_t from, uint32_t *c, uint32_t *d);
static uint64_t join_28bits_to_56bit(uint32_t a, uint32_t b);
static inline uint32_t cyclic_left_shift_28bit(uint32_t num, size_t n);

size_t des(uint8_t *to, uint8_t *from, size_t length, uint8_t *keys, enum MODE mode);

int main(void) {
    uint8_t encrypted[BUFF_SIZE], decrypted[BUFF_SIZE];
    uint8_t buffer[BUFF_SIZE] = { 0 };

    uint8_t key[8];
    input_keys_8_byte(key);

    size_t length = input_plain_text(buffer);

    printf("Length: %zu:\n", length);
    print_text(buffer, length);

    des(encrypted, buffer, length, key, ENCRYPT);
}

static inline void input_keys_8_byte(uint8_t *buff) {
    for (size_t i = 0; i < 8; ++i) buff[i] = getchar();

    // ingore `\n` symbol from stdin
    getchar();
}

static inline size_t input_plain_text(uint8_t *buff) {
size_t pos = 0;
int16_t ch;

while ((ch = getchar()) != EOF && ch != '\n' && pos < BUFF_SIZE - 1) buff[pos++] = (uint8_t)ch;
buff[pos] = '\n';

return pos;
}

static inline void print_text(uint8_t *buff, size_t length) {
    for (size_t i = 0; i < length; ++i) printf("%c", buff[i]);
    printf("\n");
}

static uint64_t from_8bits_to_64bit(uint8_t *buff) {
    uint64_t block_64bit = 0;
    for (uint8_t *it = buff; it < buff + 8; ++it) block_64bit = (block_64bit << 8) | *it;

    return block_64bit;
}

static uint64_t reduce_from_64bit_to_56bit(uint64_t num) {
    uint64_t reduced = 0;
    for (size_t i = 0; i < 56; ++i) reduced = (reduced << 1) | ((num >> (64 - PS_1[i])) & 0b1);

    return reduced;
}

static uint64_t reduce_from_56bit_to_48bit(uint64_t num) {
    uint64_t reduced = 0;
    for (size_t i = 0; i < 48; ++i) reduced = (reduced << 1) | ((num >> (56 - PC_2[i])) & 0b1);

    return reduced;
}

static void split_56bit_into_28bits(uint64_t from, uint32_t *c, uint32_t *d) {
    for (size_t i = 0; i < 28; ++i) *c = (*c << 1) | ((from >> (55 - i)) & 0b1);
    for (size_t i = 0; i < 28; ++i) *d = (*d << 1) | ((from >> (27 - i)) & 0b1);
}

static uint64_t join_28bits_to_56bit(uint32_t a, uint32_t b) {
    uint64_t block_56bit = a;
    block_56bit = (block_56bit << 28) | b;

    return block_56bit;
}

static inline uint32_t cyclic_left_shift_28bit(uint32_t num, size_t n) {
return ((num << n) | (num >> (-n & 27))) & ((1ull << 28) - 1);
}

size_t des(uint8_t *to, uint8_t *from, size_t length, uint8_t *keys, enum MODE mode) {
    length = length % 8 == 0 ? length : length + (8 - length % 8);

    uint64_t key_56bit = reduce_from_64bit_to_56bit(from_8bits_to_64bit(keys));
    uint64_t round_keys[16] = {0};

    uint32_t c = 0, d = 0;
    split_56bit_into_28bits(key_56bit, &c, &d);

    for (size_t i = 0; i < 16; ++i) {
        c = cyclic_left_shift_28bit(c, ROUND_KEY_SHIFTS[i]);
        d = cyclic_left_shift_28bit(d, ROUND_KEY_SHIFTS[i]);

        round_keys[i] = reduce_from_56bit_to_48bit(join_28bits_to_56bit(c, d));
    }


}