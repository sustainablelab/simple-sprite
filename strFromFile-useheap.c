#include <stdio.h>
#include <stdlib.h>

// #class
typedef struct
{
    char *c;
    char *end;
    char *txt; // OK for printf: printf("%s", str->txt)
} str;
str* str_FromFile(const char *filename)
{ // Return a string loaded with the contents of filename.
    // Allocate memory for the string struct.
    str *S = malloc(sizeof(str));
    // Open the file.
    FILE *f = fopen(filename, "r");
    // Count number of characters in file.
    int nc=0;
    while (fgetc(f) != EOF) nc++;
    rewind(f);
    // Allocate memory for the char array plus an extra char to hold '\0'.
    S->txt = malloc((nc+1)*sizeof(char));
    // Point at the beginning of the string.
    S->c = S->txt;
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

int main()
{
    const char* filename = "strFromFile-useheap.c";
    str *Src = str_FromFile(filename);
    // Print to stdout without printf.
    while (Src->c != Src->end) putchar(*Src->c++);
    // Rewind string.
    Src->c = Src->txt;
    // Print to stdout with printf.
    printf("%s", Src->txt);
    // Exit program
    free(Src->txt);
    free(Src);
    return 0;
}
