// File: htab_init.c
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 26.3.2025
// Compiled: gcc version 11.4.0

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <assert.h>

htab_t* htab_init(size_t n)
{
    assert(n > 0);
    htab_t* htab = (htab_t*) calloc(1, sizeof(htab_t) + n * sizeof(htab_pair_t*));

    if(htab)
    {
        htab->arr_size = n;
    }

    return htab;
}

