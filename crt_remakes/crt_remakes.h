#pragma once

typedef __SIZE_TYPE__ size_t;

#ifndef NULL
#define NULL (0)
#endif

size_t memset(char *s, int c, size_t n);

void *memmove(void *dest, const void *src, size_t n);

size_t strlen(const char *s);

void memcpy(char *_dest, const char *_src, size_t len);

int memcmp(const void *s1, const void *s2, size_t n);

int strcmp(const char *s1, const char *s2);

char *strstr(const char *str, const char *substring);
