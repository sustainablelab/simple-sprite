#ifndef __COMMENTS_H__
#define __COMMENTS_H__

// My library
#include "bool.h"
#include "str.h"
#include "list.h"

str* get_comments_str(str *S)
{ // Get comments as one giant string from source code.
    // Return a single string with all comments.
    str *Comments = NULL;

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
                        /* *C->c++ = *S->c++; */
                        *C->c++ = *S->c; // Do not advance in case next char is '\n'
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
    // Rewind source string.
    S->c = S->txt;
    /* ---< Copy to new string sized correctly. >--- */
    // Store location where string ends in temp buffer.
    C->end = C->c;
    // Rewind temp buffer.
    C->c = C->txt;
    // Copy to a single string with the correct size.
    Comments = str_New(str_Len(C));
    while (C->c < C->end) *Comments->c++ = *C->c++;
    // Store location where string ends.
    Comments->end = Comments->c;
    // Insert '\0' at end of string.
    *Comments->end = '\0';
    // Rewind string.
    Comments->c = Comments->txt;
    // Done with the giant comment buffer.
    str_Free(&C);
    return Comments;
}

list* get_comments_list(str *S)
{ // Get comments as list of strings from source code.
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
                        /* *C->c++ = *S->c++; */
                        *C->c++ = *S->c; // Do not advance in case next char is '\n'
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
                list *t = list_New();
                t->item = comment;
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
            }
        }
        // STATE: outside a comment.
        // Get next character.
        else S->c++;
    }
    // Done with the giant comment buffer.
    str_Free(&C);
    return Comments;
}

#endif // __COMMENTS_H__
