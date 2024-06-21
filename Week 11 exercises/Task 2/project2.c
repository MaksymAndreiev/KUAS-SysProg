#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encChar(char c) {
    switch (c) {
        case '!':
        case '#':
        case '$':
        case '%' :
        case '&':
        case '`':
        case '(':
        case ')':
        case '*':
        case '+':
        case ',':
        case '/':
        case ':':
        case ';':
        case '=':
        case '?':
        case '@':
        case '[':
        case ']':
        case ' ':
            printf("%%%02x", c);
            return;
        default:
            printf("%c", c);
    }
}

//void decChar(char *c) {
//    long decimal = 0;
//    long i = 0;
//    int digit = strlen(c) - 1;
//
//}

void urlencode(char *s) {
    char *q = strstr(s, "q=");
    if (q) {
        q += 2;
        while (*s && s != q) {
            printf("%c", *s++);
        }
        while (*q) {
            encChar(*q++);
        }
    } else {
        while (*s) {
            encChar(*s++);
        }
    }
    printf("\n");
}

void urldecode(char *s) {
    while (*s) {
        if (*s == '%') {
            char hex[3] = {s[1], s[2], 0};
            printf("%c", strtol(hex, NULL, 16));
            s += 3;
        } else {
            printf("%c", *s++);
        }
    }
    printf("\n");
}

int main() {
    urlencode("http://search.brave.com/search?q=bar/baz");
    urldecode("http://search.brave.com/search?q=bar%2fbaz");
    urlencode("I/O: getting stuff in (and out?).");
    urldecode("I%2fO%3a%20getting%20stuff%20in%20%28and%20out%3f%29.");
    return 0;
}
