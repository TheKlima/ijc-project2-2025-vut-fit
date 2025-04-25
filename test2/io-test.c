#include "../io.h"

int main(void) {
    char buff[256];

    printf("%d", read_word(256, buff, stdin));
    return 0;
}
