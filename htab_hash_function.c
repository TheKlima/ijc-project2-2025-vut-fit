// File: htab_hash_function.c
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 26.3.2025
// Compiled: gcc version 11.4.0

#include "htab.h"
#include <stdint.h>
#include <assert.h>

size_t htab_hash_function(htab_key_t str)
{
    assert(str);
    
    uint32_t h = 0;
    const unsigned char* p;

    for(p = (const unsigned char*)str; *p != '\0'; ++p)
    {
        h = 65599 * h + *p;
    }

    return h;
}
