#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "aes.h"

/* helper function for printing */
static void phex(uint8_t* str)
{
    unsigned char i;
    for(i = 0; i < 64; ++i)
        printf("%.2x", str[i]);
    printf("\n");
}

#define STR_LENGTH 64
#define NR_SAMPLES 50

char input[NR_SAMPLES][STR_LENGTH+1];

void before() {
    FILE* file = fopen("input", "r");
    for (int i = 0; i < NR_SAMPLES; i++) {
        fgets(input[i], STR_LENGTH+1, file);
        assert(strlen(input[i]) == STR_LENGTH);
        int newline = fgetc(file);
        assert(newline == '\n');
    }
    fclose(file);
}

void after() {
    
}

#include "../../harness.h"

void benchmark() {
    before();
    uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t iv[]  = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };
    for (int j = 0; j < 100; j++) {
        for (int i = 0; i < NR_SAMPLES; i++) {
            uint8_t in[STR_LENGTH];
            memcpy(in, input[i], STR_LENGTH * sizeof(uint8_t));
            uint8_t buffer[STR_LENGTH];
            uint8_t out[STR_LENGTH];
            AES128_CBC_encrypt_buffer(buffer, in, STR_LENGTH, key, iv);
            AES128_CBC_decrypt_buffer(out, buffer,  STR_LENGTH, key, iv);
            if (memcmp((char*) input[i], (char*) out, STR_LENGTH)) {
                fprintf(stderr, "input and decrypted data do not match!\n");
                abort();
            }        
        }
    }
}

