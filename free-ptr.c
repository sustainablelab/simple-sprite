#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *txt;
} String;

String* String_New(size_t len)
{
    String *S = malloc(sizeof(String));
    S->txt = malloc(len*sizeof(char));
    return S;
}
void String_Free(String **S)
{
    puts("Before free()");
    printf("S: %p\n", (void*)(*S));         // S: 000001f7503e6c70
    printf("S->txt: %p\n", (*S)->txt);      // S->txt: 000001f7503e6c90

    free((*S)->txt);
    (*S)->txt = NULL;

    puts("After free(S->txt) and set it to NULL:");
    printf("S->txt: %p\n", (*S)->txt);      // S->txt: 0000000000000000

    free(*S);
    *S = NULL;

    puts("After free(S) and set it to NULL:");
    printf("S: %p\n", (void*)(*S));         // S: 0000000000000000
}
int main()
{
    String *S = String_New(4);
    S->txt[0] = 'B';
    S->txt[1] = 'O';
    S->txt[2] = 'B';
    S->txt[3] = '\0';
    puts(S->txt);            // BOB
    String_Free(&S);
    return 0;
}
