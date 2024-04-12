#include "libio.h"

int main(void) {
    for (;;) {
        char *message = input();
        if (!message) break;
        output(message);
    }
    return 0;
}