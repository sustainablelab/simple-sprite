#include "str.h"

bool demo_1 = false;
bool demo_2 = false;
bool demo_str_Print_errors = true;
bool test_str_is_valid = false;

int main()
{

    if (demo_1)
    {
        puts("");
        puts("1. Demonstrate str_FromFile()");
        const char* filename = "test-str.c";
        str *Src = str_FromFile(filename);
        printf("\n\t--- BEGIN Contents of \"%s\" ---\n", filename);
        str_Print(Src);
        printf("\t--- END Contents of \"%s\" ---\n", filename);
        // Cleanup
        str_Free(&Src);
    }
    if (demo_2)
    {
        puts("");
        puts("2. Demonstrate:");
        puts("\t- str_FromString()");
        puts("\t- str_Len()");
        puts("\t- use of str->txt with %s");
        str *Bob = str_FromString("hey now");
        printf("Length of \"%s\" is %lld.\n", Bob->txt, str_Len(Bob));
        // Cleanup
        str_Free(&Bob);
    }
    if (test_str_is_valid)
    {
        { puts("\nTEST: Str is invalid if not created with str_New()");
            str *Bad = malloc(sizeof(str));
            if (str_IsValid(Bad) == true) puts("FAIL: This is a valid string.");
            else puts("PASS: This is NOT a valid string.");
            // Cleanup
            free(Bad);
        }
        { puts("\nTEST: Str is valid if created with str_New().");
            str *Good = str_New(3);
            if (str_IsValid(Good) == true) puts("PASS: This is a valid string.");
            else puts("FAIL: This is NOT a valid string.");
            // Cleanup
            str_Free(&Good);
        }
    }
    if (demo_str_Print_errors)
    {
        { // Error if str-txt = NULL
            // Setup
            str *Bad = malloc(sizeof(str));
            printf("\nDEMO: str_Print() error if str->txt is NULL.\n");
            printf("str *: %p", (void*)Bad);
            // Test
            str_Print(Bad);
            // Cleanup
            free(Bad);
        }
        { // Error if (str->end   <   str->txt)
            // Setup
            str *Bad = malloc(sizeof(str));
            Bad->txt = malloc(2);
            printf("\nDEMO: str_Print() error if (str->end  <  str->txt).\n");
            printf("str->end: %p\n", (void*)Bad->end);
            printf("str->txt: %p\n", (void*)Bad->txt);
            // Test
            str_Print(Bad);
            // Cleanup
            str_Free(&Bad);
        }
    }
    return 0;
}
