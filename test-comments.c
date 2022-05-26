// My library
#include "bool.h"
#include "str.h"
#include "list.h"
#include "comments.h"

int main()
{
    /* =====[ Setup ]===== */
    // Load source code into one giant string.
    const char *filename = "testfile-comments.c";
    str *Src = str_FromFile(filename);

    if (true)
    /* =====[ Examples ]===== */
    { puts("\n--- Example: get_comments_str() then print comments ---");
        str *Comments = get_comments_str(Src);
        // Use str_Print()
        puts("\n\t--- str_Print() ---");
        str_Print(Comments);
        // Or use printf()
        puts("\n\t--- printf() ---");
        printf("%s", Comments->txt);
        // Cleanup
        str_Free(&Comments);
    }

    if (true)
    { puts("\n--- Example: get_comments_list() then use list ---");
        list *Comments = get_comments_list(Src);

        if (true)
        { puts("\n\t--- list_Len() to count number of comments ---");
            printf("There are %d comments.\n", list_Len(Comments));
        }

        if (true)
        { puts("\n\t--- list_Print() to print each comment ---");
            list_Print(Comments);
        }

        if (true)
        { puts("\n\t--- list_PrintHeadTail() to print first N and last M comments ---");
            list_PrintHeadTail(Comments, 1, 2);
        }

        // Cleanup
        list_Free(Comments);
    }

    /* =====[ Cleanup ]===== */
    str_Free(&Src);
    return 0;
}
