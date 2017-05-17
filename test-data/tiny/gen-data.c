#include <stdlib.h>
#include <stdio.h>

/* taken from http://stackoverflow.com/questions/33464816/c-generate-random-string-of-max-length */
void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

#define STR_LENGTH 64
#define NR_SAMPLES 50

/* Generates 64 character long strings that can be used as input data. */
int main() {
    srand(0);
    for (int i = 0; i < NR_SAMPLES; i++) {
        char* str = malloc((STR_LENGTH + 1) * sizeof(char));
        gen_random(str, STR_LENGTH);
        printf("%s\n", str);
        free(str);
    }
}

