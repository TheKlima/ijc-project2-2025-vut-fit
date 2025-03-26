// File: htab_size.c
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 26.3.2025
// Compiled: gcc version 11.4.0

#include "htab.h"
#include "htab_private.h"
#include <assert.h>

size_t htab_size(const htab_t* t)
{
    assert(t);
    return t->size;
}
