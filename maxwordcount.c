// File: maxwordcount.c
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 28.3.2025
// Compiled: gcc version 11.4.0

#include "htab.h"
#include "htab_private.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>

#define HTAB_SIZE 13001
#define MAX_WORD_LENGTH 255
#define WORD_BUFFER_SIZE (MAX_WORD_LENGTH + 1)

// void printHtabItemData(htab_pair_t* data)
// {
//     printf("%s\t%u\n", data->key, data->value);
// }

int main()
{
    htab_t* htab = htab_init(HTAB_SIZE);

    if(!htab)
    {
        fprintf(stderr, "Error! Couldn't create a hash table.\n");
        return EXIT_FAILURE;
    }

    char current_word[WORD_BUFFER_SIZE] = {0, };

    while(read_word(WORD_BUFFER_SIZE, current_word, stdin) != EOF)
    {
        if(!htab_lookup_add(htab, current_word))
        {
            fprintf(stderr, "Error! Couldn't add a new item to the hash table.\n");
            htab_free(htab);
            return EXIT_FAILURE;
        }
    }

    // htab_for_each(htab, printHtabItemData);

    unsigned max = 0;
    for(unsigned i = 0; i < htab->arr_size; ++i)
    {
        for(const htab_item_t* current_item = htab->items[i]; current_item != NULL; current_item = current_item->next)
        {
            if(current_item->data->value > max)
            {
                max = current_item->data->value;
            }
        }
    }

    for(unsigned i = 0; i < htab->arr_size; ++i)
    {
        for(const htab_item_t* current_item = htab->items[i]; current_item != NULL; current_item = current_item->next)
        {
            if(current_item->data->value == max)
            {
                printf("%s\t%u\n", current_item->data->key, current_item->data->value);
            }
        }
    }

    htab_free(htab);
    return EXIT_SUCCESS;
}
