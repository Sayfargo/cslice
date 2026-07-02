#pragma once

#include <stdio.h>
#include <stdlib.h>

#define LOG_ERROR(msg, ...) fprintf(stderr, "ERROR: %s:%d:%s(): " msg "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define PANIC(format, ...) do { \
    fprintf(stderr, "PANIC: %s:%d:%s(): " format "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while(0)
