#ifndef __STR_H__
#define __STR_H__

// C standard library
#include <stdio.h>
#include <stdlib.h>

// My library
#include "bool.h"

// #class
typedef struct
{
    char *c;
    char *end;
    char *txt; // OK for printf: printf("%s", str->txt)
    bool _valid; // careful: before init _valid is any int, not just 0 or 1
} str;
// #method
bool str_IsValid(str *S)
{ // Return true only if S was made by str_New()
    /* *************DOC***************
     * If S is made by str_New(), _valid is 1 (true).
     *
     * If S is made manually (e.g., with malloc())
     * then _valid is some large positive int.
     * In that case `_valid` evaluates to true even though S is not valid.
     * But I want to return 0 (false) if S is not valid.
     *
     * That case is the reason this function exists.
     * *******************************/
    return true ? (S->_valid == true) : false;
}
// #method
str* str_New(int nc)
{ // Return an empty string that can hold up to nc characters plus a '\0'.
    str *S = malloc(sizeof(str));
    // Add an extra character to hold '\0'.
    S->txt = malloc((nc+1)*sizeof(char));
    // Point at the beginning of the string.
    S->c = S->txt;
    // Set string length to zero.
    S->end = S->c;
    // Mark this string as valid.
    S->_valid = true;
    return S;
}
// #method
void str_Free(str **S)
{ // Free memory for the str. Take &S. Set S->txt = NULL and S = NULL.
    free((*S)->txt);
    (*S)->txt = NULL;
    free(*S);
    (*S) = NULL;
}
// #method
long long int str_Len(str *S)
{
    return S->end - S->txt;
}
// #method
str* str_FromString(const char *string)
{ // Return a str loaded the contents of string.
    int nc = sizeof(string) - sizeof(char);
    // Create a string to hold that many characters
    str *S = str_New(nc);
    while (*string != '\0') *S->c++ = *string++;
    // Store location where string ends.
    S->end = S->c;
    // Insert '\0' at end of string.
    *S->end = '\0';
    // Rewind string.
    S->c = S->txt;
    return S;
}
// #method
str* str_FromFile(const char *filename)
{ // Return a str loaded with the contents of filename.
    FILE *f = fopen(filename, "r");
    // Count number of characters in file.
    int nc=0;
    while (fgetc(f) != EOF) nc++;
    rewind(f);
    // Create a string to hold that many characters.
    str *S = str_New(nc);
    // Load the file into the string.
    while ((*S->c = fgetc(f)) != EOF) S->c++;
    fclose(f);
    // Store location where string ends.
    S->end = S->c;
    // Insert '\0' at end of string.
    *S->end = '\0';
    // Rewind string.
    S->c = S->txt;
    return S;
}
// #method
void str_Print(str *S)
{
    if (str_IsValid(S) == false)
    {
        fprintf(stderr, "ERR str_Print(): string invalid, use str_New()\n");
        return;
    }
    // Check string exists.
    if (S->txt == NULL)
    {
        fprintf(stderr, "ERR str_Print(): str.txt = NULL\n");
        return;
    }
    /* // Check string ends after it starts. */
    /* if (S->end < S->txt) */
    /* { */
    /*     fprintf(stderr, "ERR str_Print(): str->end   <   str->txt\n"); */
    /*     return; */
    /* } */
    // String is OK to print. Point to beginning of string.
    S->c = S->txt;
    // Print it.
    while (S->c != S->end) putchar(*S->c++);
    // Point to beginning of string again.
    S->c = S->txt;
}

#endif // __STR_H__
