#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3_header.h"

// color code
#define RESET "\033[0m"
#define RED   "\033[1;31m"

int main(int argc, char *argv[])
{
    MP3 tag_reader;

    // --- Edit Mode ---
    if (argc == 5 && strcmp(argv[1], "-e") == 0) 
    {
        edit_mp3(argv[2], argv[3], argv[4]);
        return 0;
    }

    // --- View Mode ---
    if (argc == 3 && strcmp(argv[1], "-v") == 0)
    {
        // Check for .mp3 extension
        char *ret = strstr(argv[2], ".mp3");
        if (ret == NULL) 
        {
            printf(RED "❌ Error: Not an MP3 file (invalid extension)\n" RESET);
            return 0;
        }

        view_mp3(argv[2], &tag_reader);
        return 0;
    }

    // --- Help Mode ---
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
        print_help();
        return 0;
    }

    // --- Invalid Usage ---
    printf(RED "⚠️  Invalid arguments!\n" RESET);
    printf("------------------------------------------------------------\n");
    printf("Usage:\n");
    printf("  🔍 View : ./a.out -v <filename.mp3>\n");
    printf("  ✏️  Edit : ./a.out -e <tag_option> \"new_value\" <filename.mp3>\n");
    printf("  ❓ Help : ./a.out -h\n");
    printf("\nExamples:\n");
    printf("  ./a.out -e -t \"New Title\" sample.mp3\n");
    printf("  ./a.out -v sample.mp3\n");
    printf("------------------------------------------------------------\n");

    return 0;
}
