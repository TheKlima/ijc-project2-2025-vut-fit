// File: htab_find.c
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 26.3.2025
// Compiled: gcc version 11.4.0

#include "htab.h"
#include "htab_private.h"
#include <assert.h>
#include <string.h>

htab_pair_t* htab_find(const htab_t* t, htab_key_t key)
{
    assert(t && t->items && key);

    for(const htab_item_t* current_item = t->items[htab_hash_function(key) % t->arr_size]; current_item != NULL; current_item = current_item->next)
    {
        assert(current_item->data && current_item->data->key);

        if(strcmp(key, current_item->data->key) == 0)
        {
            return current_item->data;
        }
    }

    return NULL;
}