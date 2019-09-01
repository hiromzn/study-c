/*
 * system header wrapper
 *
 */

#ifndef _WRAP_WRAPPER_H

#define _WRAP_WRAPPER_H 1

// int atoi(const char *nptr);	
#define atoi(a)   ((a) == NULL ? 0 : atoi((a)))

// long atol(const char *nptr);
#define atol(a)   ((a) == NULL ? 0 : atol((a)))

// long long atoll(const char *nptr);
#define atoll(a)   ((a) == NULL ? 0 : atoll((a)))

// char *strcpy(char *dest, const char *src);
#define strcpy(a, b)  (strcpy((a), (b) == NULL ? "" : (b)))

// char *strncpy(char *dest, const char *src, size_t n);
#define strncpy(a, b, c) (strncpy((a), (b) == NULL ? "" : (b), (c)))

// size_t strlen(const char *s);
#define strlen(a)   ((a) == NULL ? 0 : strlen((a)))

// void *memcpy(void *dest, const void *src, size_t n);
#define memcpy(a,b,c) ((b) == NULL ? memset((a), 0, (c)) : memcpy((a),(b),(c)))

// int strcmp(const char *s1, const char *s2);
#define strcmp(a, b) (strcmp((a) == NULL ? "" : (a), (b) == NULL ? "" : (b)))

// int strncmp(const char *s1, const char *s2, size_t n);
#define strncmp(a, b, c)  (strncmp((a) == NULL ? "" : (a), (b) == NULL ? "" : (b), (c)))

// int memcmp(const void *s1, const void *s2, size_t n);
#define memcmp(a, b, c)  (memcmp((a) == NULL ? "" : (a), (b) == NULL ? "" : (b), (c)))

// char *strcat(char *dest, const char *src);
#define strcat(a,b) (strcat((a), (b) == NULL ? "" : (b)))

// char *strncat(char *dest, const char *src, size_t n);
#define strncat(a,b,c) (strncat((a), (b) == NULL ? "" : (b), (c)))

// char *strchr(const char *s, int c);
#define strchr(a,b) ((a) == NULL ? NULL : strchr((a),(b)))

// char *strrchr(const char *s, int c);
#define strrchr(a,b) ((a) == NULL ? NULL : strrchr((a),(b)))

// char *strstr(const char *haystack, const char *needle);
#define strstr(a,b) (((a) == NULL || (b) == NULL) ? (a) : strstr(a,b) )

#endif /* _WRAP_WRAPPER_H */
