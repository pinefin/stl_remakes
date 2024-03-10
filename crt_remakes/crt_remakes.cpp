#include "crt_remakes.h"

void* memset(void *s, int c, size_t n) {
  char *p = (char*)s;
  while (n--)
    *p++ = c;
  return s;
}

void *memmove(void *dest, const void *src, size_t n) {
  char *d = (char *)dest;
  const char *s = (const char *)src;

  if (s < d && s + n > d) {
    s += n;
    d += n;
    while (n--)
      *--d = *--s;
  } else {
    while (n--)
      *d++ = *s++;
  }
  return dest;
}

size_t strlen(const char *s) {
  int i = 0, sum = 0;
  char c = s[0];

  while (c != '\0') {
    sum++;
    c = s[++i];
  }
  return sum;
}

void* memcpy(void* _dest, void* _src, size_t len) {
  char *dst = (char *)_dest;
  char *src = (char *)_src;

  while (len--)
    *dst++ = *src++;

  return _dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;

  while (n--) {
    if (*p1 != *p2)
      return *p1 - *p2;
    p1++;
    p2++;
  }
  return 0;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

#if _WIN32
void operator delete(void* p)
{
    HeapFree(GetProcessHeap(), NULL, p);
}

void operator delete[](void* p)
{
    HeapFree(GetProcessHeap(), NULL, p);
}

void* operator new(size_t n)
{
    return HeapAlloc(GetProcessHeap(), NULL, n);
}

void* operator new[](size_t n)
{
    return HeapAlloc(GetProcessHeap(), NULL, n);
}

extern "C" {
    void _fltused() { _asm("ud2"); };
    void __chkstk() { };
    void __CxxFrameHandler4( ) { _asm("ud2"); };
}
#else

char* strstr(char* const _str, const char* const substring) {
    const char* a;
    const char* b;

    char* str = _str;

    b = substring;

    if (*b == 0) {
        return (char*)str;
    }

    for (; *str != 0; str += 1) {
        if (*str != *b) {
            continue;
        }

        a = str;
        while (1) {
            if (*b == 0) {
                return (char*)str;
            }
            if (*a++ != *b++) {
                break;
            }
        }
        b = substring;
    }

    return NULL;
}

#endif
