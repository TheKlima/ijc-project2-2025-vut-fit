// File: htab_free.c
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 27.3.2025
// Compiled: gcc version 11.4.0

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <assert.h>

void htab_free(htab_t* t)
{
    assert(t && t->items);

    htab_clear(t);
    free(t);
}
