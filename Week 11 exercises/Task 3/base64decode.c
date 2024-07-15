#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

int findIndex(char c, char *char_set) {
    for (int i = 0; i < 64; i++) {
        if (char_set[i] == c) {
            return i;
        }
    }
    return -1;
}

char *base64Decoder(char input_str[], int len_str) {
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Resultant string
    char *res_str = (char *) malloc(SIZE * sizeof(char));

    int val = 0, valb = -8;
    int i, j = 0;

    for (i = 0; i < len_str; i++) {
        if (input_str[i] == '=') {
            break;
        }

        int index = findIndex(input_str[i], char_set);
        if (index == -1) {
            continue;
        }

        val = (val << 6) + index;
        valb += 6;

        if (valb >= 0) {
            res_str[j++] = (char) ((val >> valb) & 0xFF); // one byte mask
            valb -= 8;
        }
    }

    res_str[j] = '\0';
    return res_str;
}

int main() {
    char *input_str = malloc(100);
    printf("Enter Base64 encoded string:");
    fgets(input_str, 100, stdin);
    input_str[strlen(input_str) - 1] = '\0';

    printf("Encoded string is: %s\n", input_str);
    printf("Decoded string is: %s\n", base64Decoder(input_str, strlen(input_str)));
    return 0;
}
