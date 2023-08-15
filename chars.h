#ifndef CHARS_H_SENTRY
#define CHARS_H_SENTRY

struct nodes;

/* As strlen */
int chars_length(const char *chars);

/* Retruns 1 if chars1 and chars2 are similar sequences of chars */
int chars_similar(char *chars1, char *chars2);

/* Sets n bytes of char* with given char
 * Doesnt control if length > chars_length(chars);*/
void chars_set(char *chars, char ch, int length);

/* Returns chars* copy of given chars* */
char *chars_from(const char *chars);

/* As strstr */
char *chars_lfind(char *chars1, const char *chars2);

/* As strstr but starts to search from the end */
char *chars_rfind(char *chars1, const char *chars2);

/* As strstr */
char *chars_find(char *chars1, const char *chars2);

/* Counts how many times chars2* in chars1* */
int chars_count(const char *chars1, const char *chars2);

/* Retruns 1 if chars1* starts with chars2* */
int chars_startswith(const char *chars1, const char *chars2);

/* Retruns 1 if chars1* ends with chars2* */
int chars_endswith(const char *chars1, const char *chars2);

/* Checks if chars* is only numbers */
int chars_is_integer(const char *chars);

/* Like chars_is_integer, but dots ('.') allowed */
int chars_is_float(const char *chars);

/* Returns a new chars* consisting of chars* with oldc*
 * replaced with newc* */
char* chars_replace(char* chars, const char* oldc, const char* newc);

/* Returns a new chars* as reversed chars* */
char *chars_reverse(const char *chars);

/* Returns concateneted chars1* and chars2* */
char *chars_add(const char *chars1, const char *chars2);

/* Returns a new chars as slice of chars* from start to end */
char *chars_slice(const char *chars, int start, int end);

/* Returns a pointer to sequence of char *
 * that ends with NULL */
struct nodes *chars_split(char *chars, const char *pattern);

#endif
