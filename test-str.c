#include "str.h"

int main()
{
    puts("");
    puts("1. Demonstrate str_FromFile()");
    const char* filename = "test-str.c";
    str *Src = str_FromFile(filename);
    printf("\n\t--- BEGIN Contents of \"%s\" ---\n", filename);
    str_Print(Src);
    printf("\t--- END Contents of \"%s\" ---\n\n", filename);

    puts("2. Demonstrate:");
    puts("\t- str_FromString()");
    puts("\t- str_Len()");
    puts("\t- use of str->txt with %s");
    str *Bob = str_FromString("hey now");
    printf("Length of \"%s\" is %lld.\n", Bob->txt, str_Len(Bob));
    // Exit program
    str_Free(Src);
    str_Free(Bob);
    return 0;
}
