#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "polyalphabetic.h"

typedef struct {
    char key[62];
} Codec;

void *createCodec(char key[62]) {
    Codec *codec = (Codec *)malloc(sizeof(Codec));
    if (!isValidKey(key)) {
        free(codec);
        return NULL;
    }
    strcpy(codec->key, key);
    return codec;
}

int isValidKey(char key[62]) {
    int i, j;
    for (i = 0; i < 62; i++) {
        for (j = i + 1; j < 62; j++) {
            if (key[i] == key[j]) {
                return 0; // Invalid key, duplicate characters found
            }
        }
    }
    return 1; // Valid key
}

int encode(char *textin, char *textout, int len, void *codec) {
    if (textin == NULL || textout == NULL || codec == NULL) {
        return -1;
    }

    Codec *c = (Codec *)codec;

    int i, count = 0;
    for (i = 0; i < len; i++) {
        char current = textin[i];
        if (current >= 'a' && current <= 'z') {
            textout[i] = c->key[current - 'a'];
            count++;
        } else if (current >= 'A' && current <= 'Z') {
            textout[i] = c->key[current - 'A' + 26];
            count++;
        } else if (current >= '0' && current <= '9') {
            textout[i] = c->key[current - '0' + 52];
            count++;
        } else {
            textout[i] = current; // Non-alphanumeric characters remain unchanged
        }
    }

    textout[len] = '\0'; // Null-terminate the output string
    return count;
}

int decode(char *textin, char *textout, int len, void *codec) {
    if (textin == NULL || textout == NULL || codec == NULL) {
        return -1;
    }

    Codec *c = (Codec *)codec;

    int i, count = 0;
    for (i = 0; i < len; i++) {
        char current = textin[i];
        int index;
        if (current >= 'a' && current <= 'z') {
            index = strchr(c->key, current) - c->key;
        } else if (current >= 'A' && current <= 'Z') {
            index = strchr(c->key + 26, current) - (c->key + 26);
        } else if (current >= '0' && current <= '9') {
            index = strchr(c->key + 52, current) - (c->key + 52);
        } else {
            index = -1; // Non-alphanumeric characters remain unchanged
        }

        if (index >= 0) {
            textout[i] = (index < 26) ? 'a' + index : ((index < 52) ? 'A' + index - 26 : '0' + index - 52);
            count++;
        } else {
            textout[i] = current; // Unchanged
        }
    }

    textout[len] = '\0'; // Null-terminate the output string
    return count;
}

void freecodec(void *codec) {
    free(codec);
}
