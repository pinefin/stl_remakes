#pragma once

#if _WIN32
#include <Windows.h>
#endif

#ifndef NULL
#define NULL (0)
#endif

void* memset(void *s, int c, size_t n);

void *memmove(void *dest, const void *src, size_t n);

size_t strlen(const char *s);

void* memcpy(void *_dest, void*_src, size_t len);

int memcmp(const void *s1, const void *s2, size_t n);

int strcmp(const char *s1, const char *s2);

#if _WIN32
char* strstr(char* const str, const char* const substring);
#endif
