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

static const uint8_t IP[64] = {
        58, 50, 42, 34, 26, 18, 10,  2, 60, 52, 44, 36, 28, 20, 12,  4,
        62, 54, 46, 38, 30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 16,  8,
        57, 49, 41, 33, 25, 17,  9,  1, 59, 51, 43, 35, 27, 19, 11,  3,
        61, 53, 45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 31, 33, 15,  7,
};

static const uint8_t FP[64] = {
        40,  8, 48, 16, 56, 24, 64, 32, 39,  7, 47, 15, 55, 23, 63, 31,
        38,  6, 46, 14, 54, 22, 62, 30, 37,  5, 45, 13, 53, 21, 61, 29,
        36,  4, 44, 12, 52, 20, 60, 28, 35,  3, 43, 11, 51, 19, 59, 27,
        34,  2, 42, 10, 50, 18, 58, 26, 33,  1, 41,  9, 49, 17, 57, 25,
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

static const uint8_t EB[48] = {
       32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
        8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
       16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
       24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};

static const uint8_t P[32] = {
       16,  7, 20, 21, 29, 12, 28, 17,
        1, 15, 23, 26,  5, 18, 31, 10,
        2,  8, 24, 14, 32, 27,  3,  9,
       19, 13, 30,  6, 22, 11,  4, 25
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
static void split_64bit_into_32bits(uint64_t from, uint32_t *l, uint32_t *r);
static void split_48bit_into_6bits(uint64_t from, uint8_t *to);
static void split_64bit_into_8bits(uint64_t from, uint8_t *to);
static uint64_t join_28bits_to_56bit(uint32_t a, uint32_t b);
static uint64_t join_32bits_to_64bit(uint32_t a, uint32_t b);
static inline uint32_t cyclic_left_shift_28bit(uint32_t num, size_t n);

static uint64_t initial_permutation(uint64_t key);
static uint64_t final_permutation(uint64_t key);

size_t des(uint8_t *to, uint8_t *from, size_t length, uint8_t *keys, enum MODE mode);

void feistel_cipher(uint32_t *l, uint32_t *r, uint64_t *round_keys, enum MODE mode);
void round_feistel_cipher(uint32_t *l, uint32_t *r, uint64_t round_key);
static inline void swap(uint32_t *l, uint32_t *r);

uint32_t f(uint32_t r, uint32_t k);
uint64_t e(uint32_t r);
uint32_t s(uint64_t a);
uint32_t p(uint32_t b);

int main(void) {
    uint8_t encrypted[BUFF_SIZE], decrypted[BUFF_SIZE];
    uint8_t buffer[BUFF_SIZE] = { 0 };

    uint8_t key[8];
    input_keys_8_byte(key);

    size_t length = input_plain_text(buffer);

    printf("Length: %zu:\n", length);
    print_text(buffer, length);

    length = des(encrypted, buffer, length, key, ENCRYPT);
    printf("Length: %zu:\n", length);
    print_text(encrypted, length);

    length = des(decrypted, encrypted, length, key, DECRYPT);
    printf("Length: %zu:\n", length);
    print_text(decrypted, length);
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
    for (size_t i = 0; i < length; ++i) printf("%d ", buff[i]);
    printf("\n");
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

static void split_64bit_into_32bits(uint64_t from, uint32_t *l, uint32_t *r) {
    *l = (uint32_t)(from >> 32);
    *r = (uint32_t)(from & 0xFFFFFFFF);
}

static void split_48bit_into_6bits(uint64_t from, uint8_t *to) {
    for (int8_t i = 7; i >= 0; --i) {
        to[i] = from & 0b111111;
        from >>= 6;
    }
}

static void split_64bit_into_8bits(uint64_t from, uint8_t *to) {
    for (size_t i = 0; i < 8; ++i) {
        to[i] = (uint8_t)((from >> ((7 - i) * 8)) & 0xFF);
    }
}

static uint64_t join_28bits_to_56bit(uint32_t a, uint32_t b) {
    return ((uint64_t)a << 28) | b;
}

static uint64_t join_32bits_to_64bit(uint32_t a, uint32_t b) {
    return ((uint64_t)a << 32) | b;
}

static inline uint32_t cyclic_left_shift_28bit(uint32_t num, size_t n) {
    return ((num << n) | (num >> (-n & 27))) & ((1ull << 28) - 1);
}

static uint64_t initial_permutation(uint64_t key) {
    uint64_t p_ = 0;
    for (size_t i = 0; i < 64; ++i) p_ = (p_ << 1) | ((key >> (64 - IP[i])) & 0b1);

    return p_;
}

static uint64_t final_permutation(uint64_t key) {
    uint64_t f_ = 0;
    for (size_t i = 0; i < 64; ++i) f_ = (f_ << 1) | ((key >> (64 - FP[i])) & 0b1);

    return f_;
}

size_t des(uint8_t *to, uint8_t *from, size_t length, uint8_t *keys, enum MODE mode) {
    if (length % 8 != 0) {
        size_t new_length = length + (8 - length % 8);
        for (size_t i = length; i < new_length; ++i) from[i] = (uint8_t)0;
        length = new_length;
    }

    uint64_t key_56bit = reduce_from_64bit_to_56bit(from_8bits_to_64bit(keys));
    uint64_t round_keys[16] = {0};

    uint32_t c = 0, d = 0;
    split_56bit_into_28bits(key_56bit, &c, &d);

    for (size_t i = 0; i < 16; ++i) {
        c = cyclic_left_shift_28bit(c, ROUND_KEY_SHIFTS[i]);
        d = cyclic_left_shift_28bit(d, ROUND_KEY_SHIFTS[i]);

        round_keys[i] = reduce_from_56bit_to_48bit(join_28bits_to_56bit(c, d));
    }

    uint32_t l = 0, r = 0;

    for (size_t i = 0; i < length; i += 8) {
        uint64_t block = from_8bits_to_64bit(from + i);
        uint64_t p_block = initial_permutation(block);

        split_64bit_into_32bits(p_block, &l, &r);

        feistel_cipher(&l, &r, round_keys, mode);

        uint64_t joined_block = join_32bits_to_64bit(l, r);
        uint64_t final_block = final_permutation(joined_block);

        split_64bit_into_8bits(final_block, to + i);
    }

    return length;
}

void feistel_cipher(uint32_t *l, uint32_t *r, uint64_t *round_keys, enum MODE mode) {
    switch (mode) {
        case ENCRYPT: {
            for (int8_t round = 0; round < 16; ++round) round_feistel_cipher(l, r, round_keys[round]);
            swap(l, r);

            break;
        }
        case DECRYPT: {
            for (int8_t round = 15; round >= 0; --round) round_feistel_cipher(l, r, round_keys[round]);
            swap(l, r);

            break;
        }
    }
}

void round_feistel_cipher(uint32_t *l, uint32_t *r, uint64_t round_key) {
    uint32_t temp = *r;
    *r = f(*r, round_key) ^ *l;
    *l = temp;
}

static inline void swap(uint32_t *l, uint32_t *r) {
    uint32_t temp = *r;
    *r = *l;
    *l = temp;
}

uint32_t f(uint32_t r, uint32_t k) {
    return p(s(e(r) ^ k));
}

uint64_t e(uint32_t r) {
    uint64_t res_48bit = 0;
    for (size_t i = 0; i < 48; ++i) res_48bit = (res_48bit << 1) | ((r >> (32 - EB[i])) & 0b1);

    return res_48bit;
}

uint32_t s(uint64_t block_48bit) {
    uint8_t blocks_6bit[8] = {0};
    split_48bit_into_6bits(block_48bit, blocks_6bit);

    uint32_t block_32bit = 0;
    for (size_t i = 0; i < 8; ++i) {
        uint8_t a = ((blocks_6bit[i] >> 5) << 1) | (blocks_6bit[i] & 0b1);
        uint8_t d = (blocks_6bit[i] >> 1) & 0xF;

        block_32bit = (block_32bit << 4) | S_BOX[i][a][d];
    }

    return block_32bit;
}

uint32_t p(uint32_t b) {
    uint32_t res = 0;
    for (size_t i = 0; i < 32; ++i) {
        res = (res << 1) | ((b >> (32 - P[i])) & 0b1);
    }

    return res;
}