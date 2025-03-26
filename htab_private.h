// File: htab_private.h
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 26.3.2025
// Compiled: gcc version 11.4.0

#ifndef HTAB_PRIVATE_H
#define HTAB_PRIVATE_H

#include "htab.h"

struct htab_item;
typedef struct htab_item htab_item_t;

struct htab_item {
    htab_item_t* next;
    htab_pair_t* data;
};

struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t* items[];
};

#endif // HTAB_PRIVATE_H
