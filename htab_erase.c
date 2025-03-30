// File: htab_erase.c
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 27.3.2025
// Compiled: gcc version 11.4.0

#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

bool htab_erase(htab_t* t, htab_key_t key)
{
    assert(t && t->items && key);

    size_t htab_idx = htab_hash_function(key) % t->arr_size;

    for(htab_item_t* current_item = t->items[htab_idx], *prev_item = NULL; current_item != NULL; prev_item = current_item, current_item = current_item->next)
    {
        assert(current_item->data && current_item->data->key);

        if(strcmp(key, current_item->data->key) == 0) // found an element to remove
        {
            // updating a pointer
            if(prev_item)
            {
                prev_item->next = current_item->next;
            }
            else // we need to delete first item
            {
                t->items[htab_idx] = current_item->next;
            }

            free((void*) current_item->data->key);
            free(current_item->data);
            free(current_item);

            --t->size;
            return true;
        }
    }

    return false;
}
