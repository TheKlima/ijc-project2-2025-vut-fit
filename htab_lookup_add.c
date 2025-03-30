// File: htab_lookup_add.c
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

htab_pair_t* htab_lookup_add(htab_t* t, htab_key_t key)
{
    assert(t && t->items && key);

    htab_pair_t* find_result = htab_find(t, key);

    if(find_result)
    {
        ++find_result->value;
        return find_result;
    }

    htab_item_t* new_item = (htab_item_t*) calloc(1, sizeof(htab_item_t));

    if(!new_item)
    {
        return NULL;
    }

    new_item->data = (htab_pair_t*) malloc(sizeof(htab_pair_t));

    if(!new_item->data)
    {
        free(new_item);
        return NULL;
    }

    new_item->data->key = (htab_key_t) malloc(strlen(key) + 1);

    if(!new_item->data->key)
    {
        free(new_item->data);
        free(new_item);
        return NULL;
    }

    strcpy((void*) new_item->data->key, key);
    new_item->data->value = 1;

    size_t htab_idx = htab_hash_function(key) % t->arr_size;

    if(t->items[htab_idx])
    {
        new_item->next = t->items[htab_idx];
    }

    t->items[htab_idx] = new_item;
    ++t->size;

    return new_item->data;
}
