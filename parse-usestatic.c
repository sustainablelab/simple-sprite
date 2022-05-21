#include <stdio.h>

#define MAXLEN 10000

typedef int bool;
#define false 0
#define true 1

// #class
typedef struct
{ // str
    char *c;
    char txt[MAXLEN];
    char *end;
} str;
// #method
void str_ReadFile(str *src, const char * filename)
{ // Read plaintext file into src->txt.
    // Make sure string exists.
    if (src==NULL) {printf("ERR: str_ReadFile"); return;}
    // It is OK if src->c is NULL. Overwrite whatever was in src.
    src->c = src->txt;
    FILE *f = fopen(filename, "r");
    char c; // holds one character from the file
    int nc = 0; // number of characters read so far
    int nl = 0; // number of line breaks
    while ((c = fgetc(f)) != EOF)
    {
        *src->c++ = c;
        nc++;
        if (c == '\n') nl++;
        if (nc == MAXLEN)
        {
            puts("\n\n--- ERROR: string buffer is too small ---");
            break;
        }
    }
    fclose(f);
    src->end = src->c;
    src->c = src->txt;

    printf("%s has %d lines\n", filename, nl);
    printf("%s has %d chars\n", filename, nc);
}
// #method
void str_Print(str *s)
{ // Print str->txt to stdout.
    // Make sure string is initialized.
    if ((s==NULL) || (s->c==NULL) || (s->txt==NULL)) {printf("ERR: str_Print");return;}
    // Start string the beginning.
    s->c = s->txt;
    // Print string to stdout.
    while (s->c != s->end)
    {
        putchar(*s->c++);
    }
    // Reset string.
    s->c = s->txt;
}

void get_comments_from_src(str *cmt, str *src)
{ // Write to cmt->txt with comments from src->txt.
    // Make sure `cmt` and `src` exist.
    if ((cmt==NULL) || (src==NULL)) { printf("ERR: get_comments_from_src"); return; }
    // Start both strings at the beginning.
    src->c = src->txt;
    cmt->c = cmt->txt;

    // Parse source for comments.
    bool is_comment = false;
    bool is_multiline = false;
    while ((src->c + 1) <= src->end)
    {
        // Not in the middle of a comment.
        // See if a new comment is starting.
        if (!is_comment)
        {
            // Look ahead two characters.
            char c0 = *src->c;
            char c1 = *(src->c + 1);
            if ( (c0 == '/') && ( (c1 == '/') || (c1 == '*') ) )
            {
                is_comment = true;
                // Check if it is a multiline comment.
                if (c1 == '*') is_multiline = true;
            }
        }
        // In the middle of a comment or at the start of a new comment.
        if (is_comment)
        {
            // Print characters until a line break.
            while(*src->c != '\n')
            {
                if ((src->c + 1) > src->end) break;
                // Check for multiline ending.
                char c0 = *src->c;
                char c1 = *(src->c + 1);
                if ((c0 == '*') && (c1 == '/')) is_multiline = false;
                // Copy the character from src to cmt.
                *cmt->c++ = *src->c++;
                /* putchar(*src->c++); */
            }
            // Copy the line break.
            *cmt->c++ = '\n';
            // Print the line break.
            /* putchar('\n'); */
            // If this is not multiline, the comment is over.
            if (!is_multiline) is_comment = false;
        }
        src->c++;
    }
    // Set end of comment string
    cmt->end = cmt->c;
    // Reset comment and source strings
    cmt->c = cmt->txt;
    src->c = src->txt;
}
void get_tags_from_comments(str *tags, str *cmt)
{
    if ((tags == NULL) || (cmt == NULL)) {printf("ERR: get_tags_from_comments"); return;}
    if (cmt->end == NULL) {printf("ERR: get_tags_from_comments"); return;}
    cmt->c = cmt->txt;
    tags->c = tags->txt;
    bool is_tag = false;
    while (cmt->c != cmt->end)
    {
        // Find a tag.
        if (*cmt->c == '#')
        {
            is_tag = true;
        }
        // Whitespace marks the end of the tag.
        if ((*cmt->c == ' ') || (*cmt->c == '\n') || (*cmt->c == '\t'))
        {
            is_tag = false;
        }
        // Save tags->
        if (is_tag)
        {
            *tags->c = *cmt->c;
        }
        cmt->c++;
        tags->c++;
    }
    cmt->c = cmt->txt;
    tags->end = tags->c;
    tags->c = tags->txt;
}

int main()
{ // Get comments in "main.c".
    // Load all of source code "main.c" into a string.
    str src;
    /* str_ReadFile(&src, "main.c"); */
    str_ReadFile(&src, "parse.c");
    // Get the comments from the source code.
    str cmt;
    get_comments_from_src(&cmt, &src);
    // Check I have the comments in memory.
    /* str_Print(&cmt); */
    // Get tags from the comments.
    str tags;
    get_tags_from_comments(&tags, &cmt);
    // Check I have the tags.
    /* str_Print(&tags); */
    // Look up each tag in the source file and extract the information.
    return 0;
}
