// File: tail.c
// Subject: IJC
// Project: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 25.3.2025
// Compiled: gcc version 11.4.0

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// if '-n' option was not specified we need to print 10 last lines from the stream
#define DEFAULT_NUMBER_OF_LINES 10

#define MAX_LINE_SIZE 4095
#define LINE_BUFFER_SIZE (MAX_LINE_SIZE + 2) // + '\n' + '\0'

// represents program configuration (arguments)
typedef struct config {
    int line_number; // number of lines (number after '-n' option)
    char *filename; // name of the file that will be processed
} Config_t;

// represents circular buffer data structure
typedef struct circular_buffer {
    int size;  // maximal number of the elements in the circular buffer
    int front; // first (front) element to exit the circular buffer
    int rear;  // last (rear) element to exit the circular buffer (the last one to arrive at the buffer)
    char arr[][LINE_BUFFER_SIZE]; // array holding lines from the file (array of strings with size 4097)
} Circular_buffer_t;

// creates a circular buffer
Circular_buffer_t* cbuf_create(int size)
{
    Circular_buffer_t* cb = (Circular_buffer_t *) malloc(sizeof(Circular_buffer_t) + size * LINE_BUFFER_SIZE);

    if(!cb)
    {
        fprintf(stderr, "Error! malloc() has failed while allocating memory for circular buffer.\n");
        return NULL;
    }

    cb->front = -1;
    cb->rear = -1;
    cb->size = size;

    return cb;
}

// frees memory initialized for circular buffer
void cbuf_free(Circular_buffer_t* cb)
{
    free(cb);
}

// checks if circular buffer is full or not
bool isFullCB(Circular_buffer_t* cb)
{
    return cb->front == (cb->rear + 1) % cb->size;
}

// checks if circular buffer is empty or not
bool isEmptyCB(Circular_buffer_t* cb)
{
    return cb->front == -1;
}

// gets a line from the circular buffer
char *cbuf_get(Circular_buffer_t* cb)
{
    if(isEmptyCB(cb))
    {
        return NULL;
    }

    int prev = cb->front; // previous front element

    if(cb->front == cb->rear) // if there is only one element left in the circular buffer make it empty
    {
        cb->front = -1;
        cb->rear = -1;
    }
    else
    {
        cb->front = (cb->front + 1) % cb->size; // move front index
    }

    return cb->arr[prev];
}

// puts a line into the circular buffer
void cbuf_put(Circular_buffer_t* cb, char* line)
{
    if(isFullCB(cb))
    {
        cbuf_get(cb);
    }

    if(isEmptyCB(cb))
    {
        cb->front = 0;
    }

    cb->rear = (cb->rear + 1) % cb->size; // move rear index
    strcpy(cb->arr[cb->rear], line); // copy a line
}

// checks if there is a valid integer in the string 'str'
bool isValidInt(char *str, int *num/*, bool *printFrom*/)
{
    char *end_ptr;
    *num = (int) strtol(str, &end_ptr, 10);
    return *end_ptr == '\0' && *num >= 0;
}

// parses program arguments
bool parseArguments(int argc, char** argv, Config_t* c/*, bool *printFrom*/)
{
    if(argc > 4) // there can be at most 4 program arguments (example: // ./tail filename -n number)
    {
        fprintf(stderr, "Error! Too many arguments.\n");
        return false;
    }

    bool is_n_met = false;
    // looping through program arguments excluding program name
    for(int i = 1; i < argc; ++i)
    {
        if(strcmp(argv[i], "-n") == 0) // if option '-n' was encountered
        {
            if(is_n_met) // if option '-n' was already used (example: ./tail -n 5 -n)
            {
                fprintf(stderr, "Error! Argument '-n' was provided twice.");
                return false;
            }

            is_n_met = true;
            ++i;

            if(i < argc) // check if there is an argument after option '-n'
            {
                if(!isValidInt(argv[i], &c->line_number/*, printFrom*/))
                {
                    fprintf(stderr, "Error! Invalid value for argument '-n'.\n");
                    return false;
                }
            }
            else
            {
                fprintf(stderr, "Error! Value for argument '-n' was not specified.\n");
                return false;
            }
        }
        else // expecting a filename
        {
            if(!c->filename) // check if file name was already used
            {
                c->filename = argv[i];
            }
            else
            {
                fprintf(stderr, "Error! There were specified two files for processing.\n");
                return false;
            }
        }
    }

    return true;
}

void skipRestOfTheLine(FILE* stream)
{
    int c;
    while((c = getc(stream)) != EOF && c != '\n') // read until EOF or '\n'
    {

    }
}

// processes a stream
void processStream(Circular_buffer_t *cb, FILE *stream)
{
    char line[LINE_BUFFER_SIZE]; // holds a lines from the file
    bool is_err_printed = false; // true if error message was already printed or not

    while(fgets(line, LINE_BUFFER_SIZE, stream) != NULL) // read until EOF
    {
        if(strchr(line, '\n') == NULL) // check line length
        {
            line[LINE_BUFFER_SIZE - 2] = '\n'; // put a '\n' as a last line character

            if(!is_err_printed) // check if error message was already printed
            {
                fprintf(stderr, "Error! Too long line in the file.\n");
                is_err_printed = true;
            }

            skipRestOfTheLine(stream);
        }

        cbuf_put(cb, line);
    }
}

// prints a circular buffer
void printCB(Circular_buffer_t* cb)
{
    if(isEmptyCB(cb))
    {
        return;
    }

    for(int i = cb->front; cb->front != cb->rear ; i = (i + 1) % cb->size)
    {
        printf("%s", cbuf_get(cb));
    }

    printf("%s", cbuf_get(cb));
}

int main(int argc, char** argv)
{
    // initialize config structure
    Config_t c = {.line_number = DEFAULT_NUMBER_OF_LINES, .filename = NULL};

    if(!parseArguments(argc, argv, &c))
    {
        return EXIT_FAILURE;
    }

    if(c.line_number == 0)
    {
        return EXIT_SUCCESS;
    }

    FILE* stream = stdin; // set a default stream

    if(c.filename) // if file name was specified in the config
    {
        stream = fopen(c.filename, "r"); // try to open a file

        if(stream == NULL)
        {
            fprintf(stderr, "Error! Couldn't open a file '%s'.\n", c.filename);
            return EXIT_FAILURE;
        }
    }

    Circular_buffer_t* cb = cbuf_create(c.line_number);

    if(cb == NULL) // if malloc has failed
    {
        if(c.filename) // if file name was specified in the config (i.e. it is not a default stdin)
        {
            fclose(stream);
        }

        return EXIT_FAILURE;
    }

    processStream(cb, stream);
    printCB(cb);

    if(c.filename) // if file name was specified in the config (i.e. it is not a default stdin)
    {
        fclose(stream);
    }

    cbuf_free(cb);

    return EXIT_SUCCESS;
}