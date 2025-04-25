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

    // Read characters until the word ends or max - 1 characters are stored
    while(c != EOF && !isspace(c))
    {
        if(word_length < max - 1)
        {
            s[word_length++] = (char)c;
        }
        else
        {
            if(!is_warning_printed)
            {
                fprintf(stderr, "Warning! Too long word.\n");
                is_warning_printed = true;
            }
        }
        c = getc(f);
    }

    s[word_length] = '\0'; // always safe
    return word_length;
}
