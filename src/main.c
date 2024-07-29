#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../include/kmp.h"

char *strndup(const char *s, size_t n) {
    char *result;
    size_t len = strlen(s);
    if (len > n) len = n;
    result = (char *)malloc(len + 1);
    if (!result) return 0;
    result[len] = '\0';
    return (char *)memcpy(result, s, len);
}

void print_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    printf("User time: %ld.%06ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System time: %ld.%06ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char *string = NULL, *pattern = NULL;
    size_t len = 0;
    size_t read;

    read = getline(&string, &len, file);
    if (read == -1) {
        perror("Error reading string");
        return 1;
    }
    string[strcspn(string, "\n")] = '\0';

    read = getline(&pattern, &len, file);
    if (read == -1) {
        perror("Error reading pattern");
        return 1;
    }
    pattern[strcspn(pattern, "\n")] = '\0';

    int k;
    fscanf(file, "%d", &k);

    int a, b;
    for (int i = 0; i < k; ++i) {
        fscanf(file, "%d %d", &a, &b);
        char *substring = strndup(string + a - 1, b - a + 1);
        if (kmp(substring, pattern)) {
            printf("sim\n");
        } else {
            printf("nao\n");
        }
        free(substring);
    }

    free(string);
    free(pattern);
    fclose(file);

    print_usage();
    return 0;
}
