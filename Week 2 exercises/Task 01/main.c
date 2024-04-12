extern char *input(void);

extern void output(char *message);

int main(void) {
    for (;;) {
        char *message = input();
        if (!message) break;
        output(message);
    }
    return 0;
}