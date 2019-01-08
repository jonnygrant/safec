#ifndef STDIO_CX_H
#define STDIO_CX_H

/* Annex K of C11 style functions ISO/IEC TR 24731-1
http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1967.htm
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>

typedef int errno_t;
typedef size_t rsize_t;

const char NUL = '\0';

/* Returns 0 on success, or error code from standard errno.h */
errno_t fopen_s(FILE ** file, const char * const filename, const char * const mode) __attribute__((nonnull));
errno_t fclose_s(FILE * file) __attribute__((nonnull));
errno_t remove_s(const char * const path) __attribute__((nonnull));

/* Note this is not part of C11 Annex K, but added for completeness */
DIR * opendir_s(const char * const name) __attribute__((nonnull));
int closedir_s(DIR * dirp) __attribute__((nonnull));

/* Based on from http://en.cppreference.com/w/c/string/byte/strerror
Note this formats the error macro name, eg "EINVAL", not the long description */
errno_t strerrno_s(char * const buf, const rsize_t buflen, const errno_t errnum) __attribute__((nonnull));

errno_t system_s(const char * const cmd, int * shell_ret, int * actual_ret) __attribute__((nonnull));

/* TODO
errno_t strncpy_s(char * dst, size_t dst_size, const char * src, size_t count)__attribute__((nonnull));
errno_t strncat_s(char * dst, size_t dst_size, const char * src, size_t count) __attribute__((nonnull));
*/

/* These are not part of C11 */
/* Returns 1 or 0 */
int diraccessible(const char * const name) __attribute__((nonnull));
int filesize(const char * const name) __attribute__((nonnull));


#endif
