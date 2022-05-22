#include <stdio.h>
#include <stdlib.h>

// #class
typedef struct
{
    char *c;
    char *end;
    char *txt; // OK for printf: printf("%s", str->txt)
} str;
// #method
str* str_New(int nc)
{ // Return an empty string.
    str *S = malloc(sizeof(str));
    // Add an extra character to hold '\0'.
    S->txt = malloc((nc+1)*sizeof(char));
    // Point at the beginning of the string.
    S->c = S->txt;
    // Set string length to zero.
    S->end = S->c;
    return S;
}
// #method
void str_Free(str *S)
{
    // txt = NULL sets S->txt = 0.
    free(S->txt); S->txt = NULL;
    // I don't do S = NULL. It does not change S.
    free(S);
}
// #method
long long int str_Len(str *S)
{
    return S->end - S->txt;
}
// #method
str* str_FromString(const char *string)
{
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
{ // Return a string loaded with the contents of filename.
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
    // Check string exists and ends after it starts.
    if ((S->txt == NULL) || (S->end < S->c))
    {
        printf("ERR: str_Print");
        return;
    }
    // String is OK to print. Point to beginning of string.
    S->c = S->txt;
    // Print it.
    while (S->c != S->end) putchar(*S->c++);
    // Point to beginning of string again.
    S->c = S->txt;
}

int main()
{
    const char* filename = "parse-useheap.c";
    str *Src = str_FromFile(filename);

    str_Print(Src);
    str *Bob = str_FromString("hey now");
    printf("Length of \"%s\" is %lld.\n", Bob->txt, str_Len(Bob));
    // Exit program
    str_Free(Src);
    str_Free(Bob);
    return 0;
}
