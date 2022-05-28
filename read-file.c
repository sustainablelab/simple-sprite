// Read FILENAME using a char buffer of length MAX_LINELEN.
// Stop if any line exceeds MAX_LINELEN characters.
// Otherwise, read and print to stdout until hitting eof.

#include <stdio.h>
#include <string.h>

#define MAX_LINELEN 1000
#define FILENAME "Makefile"

int main()
{
    FILE *f = fopen(FILENAME, "r");
    char txt[MAX_LINELEN]; // store a line of text
    /* printf("%lld ", sizeof(txt)); // MAX_LINELEN */
    while (fgets(txt, MAX_LINELEN, f) != NULL)
    { // Print each line.
        // - fgets reads until a newline or until reading count-1 characters
        // - fgets includes the newline
        // - the next fgets call picks up wherever the last call left off
        if (txt[strlen(txt)-1] != '\n')
        { // Check the last character read was a newline character
            fclose(f);
            char errmsg[100];
            sprintf(errmsg, "fgets: line exceeds %d characters", MAX_LINELEN);
            perror(errmsg);
            return 1;
        }
        // Print the line
        printf("%s", txt);
    }
    fclose(f);
    return 0;
}
