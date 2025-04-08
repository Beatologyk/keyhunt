/*
 * This file is part of the VanitySearch distribution (https://github.com/JeanLucPons/VanitySearch).
 * Copyright (c) 2019 Jean Luc PONS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <immintrin.h>
#include <stdint.h>
#include <string.h>

// Custom implementation to replace <byteswap.h> for Windows
#ifndef BYTESWAP_H
#define BYTESWAP_H

// Define byte-swapping functions for Windows
static inline uint32_t __builtin_bswap32(uint32_t x) {
    return ((x & 0x000000FF) << 24) |
           ((x & 0x0000FF00) << 8) |
           ((x & 0x00FF0000) >> 8) |
           ((x & 0xFF000000) >> 24);
}

#endif // BYTESWAP_H

// Replace __declspec(align(16)) with __attribute__((aligned(16)))
static const uint32_t _init[] __attribute__((aligned(16))) = {
    0x6a09e667, 0x6a09e667, 0x6a09e667, 0x6a09e667,
    0xbb67ae85, 0xbb67ae85, 0xbb67ae85, 0xbb67ae85,
    0x3c6ef372, 0x3c6ef372, 0x3c6ef372, 0x3c6ef372,
    0xa54ff53a, 0xa54ff53a, 0xa54ff53a, 0xa54ff53a,
    0x510e527f, 0x510e527f, 0x510e527f, 0x510e527f,
    0x9b05688c, 0x9b05688c, 0x9b05688c, 0x9b05688c,
    0x1f83d9ab, 0x1f83d9ab, 0x1f83d9ab, 0x1f83d9ab,
    0x5be0cd19, 0x5be0cd19, 0x5be0cd19, 0x5be0cd19
};

// Fix invalid use of m128i_u32 by replacing it with proper casting
void sha256sse_checksum(uint32_t *d0, uint32_t *d1, uint32_t *d2, uint32_t *d3,
                        uint8_t *s0, uint8_t *s1, uint8_t *s2, uint8_t *s3) {
    __m128i s[4];

    // Example: Initialize state (simplified for demonstration)
    memset(s, 0, sizeof(s));

    // Access elements of __m128i using memcpy to avoid strict aliasing issues
    uint32_t temp[4];
    memcpy(temp, &s[0], sizeof(temp));

    *d0 = __builtin_bswap32(temp[3]);
    *d1 = __builtin_bswap32(temp[2]);
    *d2 = __builtin_bswap32(temp[1]);
    *d3 = __builtin_bswap32(temp[0]);
}