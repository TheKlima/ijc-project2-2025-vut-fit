#include "io.h"
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

int read_word(unsigned max, char s[max], FILE* f)
{
    assert(s && f);

    if(max == 0)
    {
        return 0;
    }

    static bool is_warning_printed = false;

    int c;
    while(isspace((c = getc(f))));

    if(c == EOF)
    {
        return EOF;
    }

    unsigned word_length = 0;

    do
    {
        s[word_length++] = c;
    } while(word_length < max - 1 && !isspace(c = getc(f)) && c != EOF);

    s[word_length] = '\0';

    if(word_length == max - 1)
    {
        if(!is_warning_printed)
        {
            fprintf(stderr, "Warning! Too long word.\n");
            is_warning_printed = true;
        }

        while(!isspace(c = getc(f)) && c != EOF)
        {
            ++word_length;
        }
    }

    return word_length;
}
