#include <stdio.h>
#include <string.h>
#include "polyalphabetic.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <src_file> <dst_file>\n", argv[0]);
        return 1;
    }

    FILE *src_file = fopen(argv[2], "r");
    FILE *dst_file = fopen(argv[3], "w");

    if (src_file == NULL || dst_file == NULL) {
        perror("Error opening files");
        return 2;
    }

    char key[62] = "defghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abc";
    void *codec = createCodec(key);

    if (codec == NULL) {
        fprintf(stderr, "Invalid key\n");
        fclose(src_file);
        fclose(dst_file);
        return 3;
    }

    if (strcmp(argv[1], "encode") == 0) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), src_file) != NULL) {
            int len = strlen(buffer);
            char encoded[len + 1];
            int count = encode(buffer, encoded, len, codec);
            fprintf(dst_file, "%s", encoded);
            printf("%d characters encoded\n", count);
        }
    } else if (strcmp(argv[1], "decode") == 0) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), src_file) != NULL) {
            int len = strlen(buffer);
            char decoded[len + 1];
            int count = decode(buffer, decoded, len, codec);
            fprintf(dst_file, "%s", decoded);
            printf("%d characters decoded\n", count);
        }
    } else {
        fprintf(stderr, "Invalid command: %s\n", argv[1]);
        fclose(src_file);
        fclose(dst_file);
        freecodec(codec);
        return 4;
    }

    fclose(src_file);
    fclose(dst_file);
    freecodec(codec);
    return 0;
}
