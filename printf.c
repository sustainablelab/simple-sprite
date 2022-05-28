/* *************File I/O in C-Standard ***************
 * Free PDF :: https://www.open-std.org/jtc1/sc22/WG14/www/docs/n1256.pdf
 *
 * Input/output <stdio.h>:: PDF page 274 (doc page 262, Section 7.19.1)
 *
 * Also see:
 * -  Streams :: PDF page 276 (doc page 264, Section 7.19.2)
 * *******************************/
/* *************FILE***************
 * C-standard says:
 * FILE
 * An "object type" to record all stream info:
 * - location
 * - data (stored as a pointer)
 * - error status
 * - eof indicator
 *
 * Use FILE to read/write a "file on disk".
 * Also use FILE to read/write a stream:
 * - Use FILE to write to stdout and stderr.
 * - Use FILE to read from stdin.
 * *******************************/
 /* *************stdout stderr stdin***************
 * C-standard says:
 * stdout
 * stderr
 * stdin
 * These are type (FILE *).
 *
 * MinGW implementation:
 *
 * _CRTIMP FILE *__cdecl __acrt_iob_func(unsigned index);
 * #define stdin (__acrt_iob_func(0))
 * #define stdout (__acrt_iob_func(1))
 * #define stderr (__acrt_iob_func(2))
 * *******************************/
// File I/O that is NOT part of the C-Standard!!
/* *************STDIN_FILENO STDOUT_FILENO STDERR_FILENO***************
 * These are not part of the C-standard.
 * STDIN_FILENO
 * STDOUT_FILENO
 * STDERR_FILENO
 *
 * MinGW implementation:
 * STDIN_FILENO
 * STDOUT_FILENO
 * STDERR_FILENO
 * Defined in stdio.h
 * Also defined in unistd.h
 *
 * These are simple #define constants:
 * #define STDIN_FILENO  0
 * #define STDOUT_FILENO 1
 * #define STDERR_FILENO 2
 *
 * Again, not part of the C-standard, but it looks like these are used as file
 * descriptors by read, write, lseek, close.
 * *******************************/
 /* *************read, write, seek (or lseek), and close***************
 * These functions are not part of the C-standard either.
 *
 * Cygwin implementation of read, write, seek, close in stdio.h:
 *
 *  typedef struct
 *  {
 *    cookie_read_function_t  *read;
 *    cookie_write_function_t *write;
 *    cookie_seek_function_t  *seek;
 *    cookie_close_function_t *close;
 *  } cookie_io_functions_t;
 *
 * typedef ssize_t cookie_read_function_t(void *__cookie, char *__buf, size_t __n);
 * typedef ssize_t cookie_write_function_t(void *__cookie, const char *__buf, size_t __n);
 * typedef int cookie_seek_function_t(void *__cookie, off_t *__off, int __whence);
 * typedef int cookie_close_function_t(void *__cookie);
 *
 * I can't find where __cookie is defined.
 *
 * Cygwin implementation of read, write, lseek, close in sys/unistd.h:
 *
 * _READ_WRITE_RETURN_TYPE read (int __fd, void *__buf, size_t __nbyte);
 * _READ_WRITE_RETURN_TYPE write (int __fd, const void *__buf, size_t __nbyte);
 * int     close (int __fildes);
 * _off_t   _lseek (int __fildes, _off_t __offset, int __whence);
 *
 * MinGW implementation of read, write, seek, close in io.h (included by unistd.h):
 *
 * int __cdecl read(int _FileHandle,void *_DstBuf,unsigned int _MaxCharCount)  __MINGW_ATTRIB_DEPRECATED_MSVC2005;
 * int __cdecl write(int _Filehandle,const void *_Buf,unsigned int _MaxCharCount) __MINGW_ATTRIB_DEPRECATED_MSVC2005;
 * int __cdecl close(int _FileHandle) __MINGW_ATTRIB_DEPRECATED_MSVC2005;
 * long __cdecl lseek(int _FileHandle,long _Offset,int _Origin) __MINGW_ATTRIB_DEPRECATED_MSVC2005;
 * *******************************/

#include <stdio.h>

void print(const char *s)
{
    fputs(s, stdout);
    fputs("\n", stdout);
    fflush(stdout);
}
/* *************TODO: what defines read()?***************
 * - #include <unistd.h>
 * - Make lib-tags
 * - hop to read
 * *******************************/

/* *************Without fflush(stdout)***************
 * Here is the output if my print function does NOT fflush(stdout):
 *
 * perror after first printf: No error
 * perror after first my print: No error
 * C
 * Using perror after second printf: No error
 * Using perror after second my print: No error
 * First printf
 * First my print
 * C
 * Second printf
 * Second my print
 * *******************************/

/* *************With fflush(stdout)***************
 * And here is the output if my print does fflush(stdout):
 *
 * perror after first printf: No error
 * First printf
 * First my print
 * perror after first my print: No error
 * C
 * Using perror after second printf: No error
 * C
 * Second printf
 * Second my print
 * Using perror after second my print: No error
 * *******************************/
int main()
{
    printf("First printf\n");
    perror("perror after first printf");
    print("First my print");
    perror("perror after first my print");
    // Read from input to test need to flush stdout.
    int c = getc(stdin);
    putchar(c); putchar('\n');
    printf("Second printf\n");
    perror("Using perror after second printf");
    print("Second my print");
    perror("Using perror after second my print");
    return 0;
}
