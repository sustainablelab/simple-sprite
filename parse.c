#include "str.h"

typedef struct list
{
    str *item;
    struct list *next;
} list;

/* *************DOC***************
 * Testing multiline.
 * *******************************/
list* get_comments(str *S)
{ // Get comments from source code.
    // Return a list of comments.
    list *Comments = NULL;
    list *current;
    bool is_head = true;

    // Make a temporary buffer for comment strings.
    str *C = str_New(str_Len(S));

    bool is_comment = false;
    bool is_multiline = false;
    while (S->c <= S->end)
    {
        // STATE: not inside a comment.
        if (!is_comment)
        {
            char c0 = *S->c;
            char c1 = *(S->c+1);
            if ((c0=='/')&&(c1=='/'))
            {
                is_comment = true;
            }
            else if ((c0=='/')&&(c1=='*'))
            {
                is_comment = true;
                is_multiline = true;
            }
        }
        // STATE: inside a comment.
        if (is_comment)
        {
            while(*S->c != '\n')
            {
                // STATE: inside a multiline comment.
                if (is_multiline)
                {
                    // Look for end of multiline comment.
                    // Handle the rare case: /* comment */ C-code\n
                    char c0 = *S->c;
                    char c1 = *(S->c+1);
                    if ((c0=='*')&&(c1=='/'))
                    {
                        // Copy the '*/'
                        *C->c++ = *S->c++;
                        *C->c++ = *S->c++;
                        is_multiline = false;
                        is_comment = false;
                    }
                }
                // Continue copying if this is still a comment.
                if (is_comment) *C->c++ = *S->c++;
                // If comment is over, walk to the line break without copying.
                else S->c++;
            }
            // Copy the line break.
            *C->c++ = *S->c++;
            // If that was a single line comment, it is over.
            if (!is_multiline) is_comment = false;

            // STATE: transitioning out of comment
            // Capture this comment as a single string.
            if (!is_comment)
            {
                /* ---< Copy to new string sized correctly. >--- */
                // Store location where string ends in temp buffer.
                C->end = C->c;
                // Rewind temp buffer.
                C->c = C->txt;
                // Copy to a new string.
                str *comment = str_New(str_Len(C));
                while (C->c < C->end) *comment->c++ = *C->c++;
                // Store location where string ends.
                comment->end = comment->c;
                // Insert '\0' at end of string.
                *comment->end = '\0';
                // Rewind strings.
                C->c = C->txt;
                comment->c = comment->txt;

                /* ---< Insert comment in the list >--- */
                list *t = malloc(sizeof(list));
                t->item = comment;
                t->next = NULL;
                if (is_head)
                {
                    Comments = t;
                    current = t;
                    is_head = false;
                }
                else
                {
                    current->next = t;
                    current = t;
                }
                // TEMPORARY CODE
                /* head = malloc(sizeof(list)); */
                /* head->item = comment; */
            }
        }
        // STATE: outside a comment.
        // Get next character.
        else S->c++;
    }
    /* // Set end of comment */
    /* C->end = C->c; */
    /* // Rewind temporary buffer. */
    /* C->c = C->txt; */
    /* // A list with one item. */
    /* Comments->item = C; */
    // Done with the giant comment buffer.
    str_Free(C);
    return Comments;
}
str* old_but_good_get_comments_str(str *S)
{
    // Return a string of all comments.
    str *C = str_New(str_Len(S));

    bool is_comment = false;
    bool is_multiline = false;
    while (S->c <= S->end)
    {
        // STATE: not inside a comment.
        if (!is_comment)
        {
            char c0 = *S->c;
            char c1 = *(S->c+1);
            if ((c0=='/')&&(c1=='/'))
            {
                is_comment = true;
            }
            else if ((c0=='/')&&(c1=='*'))
            {
                is_comment = true;
                is_multiline = true;
            }
        }
        // STATE: inside a comment.
        if (is_comment)
        {
            while(*S->c != '\n')
            {
                // STATE: inside a multiline comment.
                if (is_multiline)
                {
                    // Look for end of multiline comment.
                    // Handle the rare case: /* comment */ C-code\n
                    char c0 = *S->c;
                    char c1 = *(S->c+1);
                    if ((c0=='*')&&(c1=='/'))
                    {
                        // Copy the '*/'
                        *C->c++ = *S->c++;
                        *C->c++ = *S->c++;
                        is_multiline = false;
                        is_comment = false;
                    }
                }
                // Continue copying if this is still a comment.
                if (is_comment) *C->c++ = *S->c++;
                // If comment is over, walk to the line break without copying.
                else S->c++;
            }
            // Copy the line break.
            *C->c++ = *S->c++;
            // If that was a single line comment, it is over.
            if (!is_multiline) is_comment = false;
        }
        // STATE: outside a comment.
        // Get next character.
        else S->c++;
    }
    C->end = C->c;
    C->c = C->txt;
    return C;
}
list* old_get_comments(str *S)
{ // Get comments from source code.
    // Return a list of comments.
    list *Comments = malloc(sizeof(list));
    // Create temp buffer for worst case that Src is one giant comment.
    str *Tmp = str_New(str_Len(S));
    printf("Src: %lld\n", str_Len(S)); // DEBUG
    printf("Tmp: %lld\n", str_Len(Tmp)); // DEBUG
    // Find a comment.
    // When the comment ends, copy it to its own string.
    // Reuse Tmp for the next comment.
    //
    bool is_comment = false;
    bool is_multiline = false;
    while (S->c <= S->end)
    {
        // STATE: not inside a comment.
        if (!is_comment)
        {
            // Look ahead two characters for `//` or `/*`.
            char c0 = *S->c;
            char c1 = *(S->c + 1);
            if ( (c0=='/') && ((c1=='/') || (c1=='*')) )
            {
                is_comment = true;
                // is this a multiline comment `/*`
                if (c1 == '*') is_multiline = true;
            }
        }
        // STATE: inside a comment
        if (is_comment)
        {
            // Copy characters until a line break or until multiline ends.
            while ((*S->c != '\n') && (is_comment))
            {
                // Handle case that next two chars are `*/`.
                if (is_multiline)
                {
                    // Look ahead two characters for `*/`.
                    char c0 = *S->c;
                    char c1 = *(S->c + 1);
                    // is this the end of the multiline comment
                    if ( (c0=='*') && (c1=='/') )
                    {
                        is_comment = false;
                        is_multiline = false;
                        // Copy the `*/`
                        /* putchar(*S->c); */
                        *Tmp->c++ = *S->c++;
                        /* putchar(*S->c); */
                        *Tmp->c++ = *S->c++;
                        break;
                    }
                }
                // Copy the character.
                /* putchar(*S->c); */
                *Tmp->c++ = *S->c++;
            }
            // Copy the line break
            *Tmp->c = *S->c;
            /* putchar(*S->c); */
            // If this is not a multiline comment, the comment is over.
            if (!is_multiline) is_comment = false;
        }
        // whatever state it is, advance to next character.
        /* S->c++; */
    }
    // Set end of comment string.
    Tmp->end = Tmp->c;
    printf("Tmp->c: %p\n", (void*)Tmp->c); // DEBUG
    printf("Tmp->end: %p\n", (void*)Tmp->end); // DEBUG
    // Rewind comment and source strings.
    Tmp->c = Tmp->txt;
    str_Print(Tmp); // DEBUG
    S->c = S->txt;
    printf("Src: %lld\n", str_Len(S)); // DEBUG
    printf("Tmp: %lld\n", str_Len(Tmp)); // DEBUG
    str_Free(Tmp);
    return Comments;
}

int main()
{
    // Load source code into one giant string.
    const char *filename = "parse.c";
    str *Src = str_FromFile(filename);
    // Extract the comments as a list of strings.
    list *Comments = get_comments(Src);
    /* str *Comments = get_comments_str(Src); */
    /* str_Print(Comments); */

    { // Count number of comments
        list *t = Comments;
        int nc = 0;
        while(1)
        {
            nc++;
            if (t->next == NULL) break;
            t = t->next;
        }
        printf("There are %d comments.\n", nc);
    }
    /* { // Print each comment. */
    /*     list *Comment = Comments; */
    /*     while(1) */
    /*     { */
    /*         str_Print(Comment->item); */
    /*         if (Comment->next == NULL) break; */
    /*         Comment = Comment->next; */
    /*     } */
    /* } */
    { // Print first and last comment.
        list *t = Comments;
        str_Print(t->item);
        while(1)
        {
            if (t->next == NULL) break;
            t = t->next;
        }
        str_Print(t->item);
    }

    // Exit program
    // TODO: #define the types to check for to know what free to call, include int type in list typedef.
    //
    // Free each link and its comment.
    list *Comment = Comments;
    while(1)
    {
        // Free the str
        str_Free(Comment->item);
        // if last item
        if (Comment->next == NULL)
        {
            // free it
            free(Comment);
            break;
        }
        // not last item
        list *t = Comment;
        // get next item
        Comment = Comment->next;
        // free this item
        free(t);
    }

    str_Free(Src);
    return 0;
}
