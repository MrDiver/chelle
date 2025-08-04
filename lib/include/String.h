#ifndef CGH_STRING_H
#define CGH_STRING_H

#include <string.h>
#include <unistd.h>

typedef struct String {
  char *text;
  size_t size;
} String;

String String_new(char *text);
void String_delete(String *s);

/**
 * Moves the `pos` pointer forward until a whitespace character is reached
 * @param `str` The string to be searched
 * @param `pos` the position to be started from and to be moved
 */
void skip_space(String const *str, size_t *pos);

/**
 * Moves the `pos` pointer forward until a character in `skipchrs` is reached
 * @param `str` The string to be searched
 * @param `pos` the position to be started from and to be moved
 * @param `skipchrs` the characters to be skipped
 */
void skip_any(String const *str, size_t *pos, const char *skipchrs);

/**
 * The find function moves the `pos` pointer forward until the character `c` is
 * reached After calling the function
 * @param `str` is the string to be searched
 * @param `pos` is the position to be started from and to be moved
 * @param `c` is the character to be searched for
 */
void find(String const *str, size_t *pos, const char c);

/**
 * The findany function moves the `pos` pointer forward until any character in
 * `chrs` is reached
 * @param `str` is the string to be searched
 * @param `pos` is the position to be started from and to be moved
 * @param `chrs` is the character set to be searched for
 */
void findany(String const *str, size_t *pos, const char *chrs);

String *splitatwhite(String const *line, size_t *out_size);

String *splitat(String const *line, size_t *out_size, const char *splitchrs);

#endif
