//
// Created by Wei-Chung Huang on 3/30/18.
//

#include "FileUtility.h"
#include <iostream>

#define BUF_SIZE 100

void FileUtility::tail(char *file_path, int n) {
    FILE *file = fopen(file_path, "r");
    if (!file) return;

    long long pos = 0;
    char str[BUF_SIZE];
    int n_lines = 0;

    if (fseek(file, 0, SEEK_END)) {
        perror("fseek() error");
    } else {
        pos = ftell(file);
        while (pos) {
            if (fseek(file, --pos, SEEK_SET)) {
                perror("fseek() error");
            } else {
                char ch = fgetc(file);
                if (ch == '\n') {
                    if (n_lines++ == n) break;
                }
            }
        }
    }

    while (fgets(str, sizeof(str), file)) {
        printf("%s", str);
    }

    fclose(file);
}