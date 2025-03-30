// File: htab_for_each.c
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

void htab_for_each(const htab_t* t, void (*f)(htab_pair_t* data))
{
    assert(t && t->items && f);

    for(size_t i = 0; i < t->arr_size; ++i)
    {
        for(const htab_item_t* current_item = t->items[i]; current_item != NULL; current_item = current_item->next)
        {
            f(current_item->data);
        }
    }
}
