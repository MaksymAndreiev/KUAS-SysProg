#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 1000

char *base64Encoder(char input_str[], int len_str) {
    // Character set of base64 encoding scheme
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // Resultant string
    char *res_str = (char *) malloc(SIZE * sizeof(char));

    int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp;
    int i, j, k = 0;

    // Loop takes 3 characters at a time from
    // input_str and stores it in val
    for (i = 0; i < len_str; i += 3) {
        val = 0, count = 0, no_of_bits = 0;

        for (j = i; j < len_str && j <= i + 2; j++) {
            val = val << 8;
            val = val | input_str[j];
            count++;

        }

        no_of_bits = count * 8;
        padding = no_of_bits % 3;
        while (no_of_bits != 0) {
            if (no_of_bits >= 6) {
                temp = no_of_bits - 6;
                index = (val >> temp) & 63;
                no_of_bits -= 6;
            } else {
                temp = 6 - no_of_bits;
                index = (val << temp) & 63;
                no_of_bits = 0;
            }
            res_str[k++] = char_set[index];
        }
    }

    for (i = 1; i <= padding; i++) {
        res_str[k++] = '=';
    }
    res_str[k] = '\0';
    return res_str;
}


// Driver code
int main() {
    char *input_str = malloc(100);
//    input_str = "hello world\n";
    fgets(input_str, 100, stdin);
    input_str[strlen(input_str) - 1] = '\n';

    printf("Input string is: %s\n", input_str);
    printf("Encoded string is: %s\n", base64Encoder(input_str, strlen(input_str)));
    return 0;
}
