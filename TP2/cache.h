//
// Created by Antoine MAZURE on 07/03/2024.
//

#include <stdint.h>

#ifndef ARCHI_CACHE_H
#define ARCHI_CACHE_H

#endif //ARCHI_CACHE_H

typedef struct RAM_H {
    int data;
    int size;
} ram;

typedef struct cache_t {
    //int8_t height_word;
    int size;
    int data;
    //int8_t nb_words;
    //int8_t nb_lines;
    //int8_t lines_words;
} cache;

cache init_cache();
