// My library
#include "bool.h"
#include "str.h"
#include "list.h"
#include "comments.h"

int main()
{
    // Try parsing comments in str.h
    str *Src = str_FromFile("str.h");

    list *Clist = get_comments_list(S);
    // Find comments with tags.
    list_Free(Clist);


    str_Free(&Src);
    return 0;
}
