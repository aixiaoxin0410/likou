#pragma once

namespace yzz {
// BKDR Hash Function
inline int BKDRHash(const char* str) {
    int hash = 0;
    while (*str) {
        hash = hash * 131 + (*str++); // 131 is a prime number
    }
    return hash & 0x7FFFFFFF; // 确保返回正整数
}

// AP Hash Function
inline int APHash(const char* str) {
    int hash = 0;
    for (int i = 0; *str; ++i, ++str) {
        if ((i & 1) == 0) {
            hash ^= (hash << 7) ^ (*str) ^ (hash >> 3);
        } else {
            hash ^= (~((hash << 11) ^ (*str) ^ (hash >> 5)));
        }
    }
    return hash & 0x7FFFFFFF; // 确保返回正整数
}

// RS Hash Function
inline int RSHash(const char* str) {
    int hash = 0;
    int magic = 63689; // A prime number
    while (*str) {
        hash = hash * magic + (*str++);
        magic *= 378551; // Another prime number
    }
    return hash & 0x7FFFFFFF; // 确保返回正整数
}
} // namespace yzz