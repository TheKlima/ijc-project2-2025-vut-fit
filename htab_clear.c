// File: htab_clear.c
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

void htab_clear(htab_t* t)
{
    assert(t && t->items);

    for(int i = 0; i < t->arr_size; ++i)
    {
        for(const htab_item_t* current_item = t->items[i], *tmp; current_item != NULL; current_item = tmp)
        {
            tmp = current_item->next;
            free(current_item->data->key);
            free(current_item->data);
            free(current_item);
        }

        t->items[i] = NULL;
    }

    t->size = 0;
}
