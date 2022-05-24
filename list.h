#ifndef __LIST_H__
#define __LIST_H__

#include "bool.h"

/* *************DOC***************
 * list_ needs a definition of _Free and _Print
 * for each of my types that I use as
 * a list->item
 * *******************************/
#include "str.h" // for now this is the only type I've defined

// #class
typedef struct list
{
    str *item;
    struct list *next;
} list;
// #method
void list_Free(list *ListStr)
{ // Free each link and its comment.

    /* *************DOC***************
     * TODO: #define or enum list other types besides str.
     * Include `int type` in list typedef.
     * Check `type` to know which _Free to call on the item.
     * Change item to (void *).
     * *******************************/
    while(1)
    {
        // Free the str
        str_Free(ListStr->item);
        // if last item
        if (ListStr->next == NULL)
        {
            // free it
            free(ListStr);
            break;
        }
        // not last item
        list *t = ListStr;
        // get next item
        ListStr = ListStr->next;
        // free this item
        free(t);
    }
}
// #method
list* list_New(void)
{
    list *L = malloc(sizeof(list));
    L->item = NULL;
    L->next = NULL;
    return L;
}
// #method
int list_Len(list *L)
{
    int n = 0;
    while(1)
    {
        n++;
        if (L->next == NULL) break;
        L = L->next;
    }
    return n;
}
// #method
void list_Print(list *L)
{
    /* *************DOC***************
     * TODO: #define or enum list other types besides str.
     * Include `int type` in list typedef.
     * Check `type` to know which _Print to call on the item.
     * Change item to (void *).
     * *******************************/
    while(1)
    {
        str_Print(L->item);
        if (L->next == NULL) break;
        L = L->next;
    }
}
// #method
void list_PrintHeadTail(list *L, int h, int t)
{ // Print the first H items and the last T items
    int len = list_Len(L);
    int i = 1;
    while (i <= h)
    {
        /* printf("i<=h: %d<=%d\n", i, h); */
        str_Print(L->item);
        if (L->next == NULL) {i++; break;}
        L = L->next;
        i++;
    }
    while( i <= (len - t) )
    {
        /* printf("i<=(len-t): %d<=(%d-%d)\n", i, len, t); */
        if (L->next == NULL) {i++; break;}
        L = L->next;
        i++;
    }
    // Put ... only if there are omitted items.
    if ( (h+t) < len ) puts("...");
    while (i <= len)
    {
        /* printf("i<len: %d<%d\n", i, len); */
        str_Print(L->item);
        if (L->next == NULL) break;
        L = L->next;
        i++;
    }
}

#endif // __LIST_H__
