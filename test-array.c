#include <stdio.h>

int main()
{
    FILE *f = fopen("test-array.c", "r");
    // Count the number of characters in the file.
    int nc = 0;
    char c;
    while ((c = fgetc(f)) != EOF) nc++;
    fclose(f);
    // Make an array that fits exactly that number of characters.
    char txt[nc];
    char *t = txt;
    // Copy the file into the array.
    f = fopen("test-array.c", "r");
    while ((c = fgetc(f)) != EOF) *t++ = c;
    fclose(f);
    char *end = t;
    t = txt;
    // Print the array.
    while (t != end) putchar(*t++);
    t = txt;
    return 0;
}
