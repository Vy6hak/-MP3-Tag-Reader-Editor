#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mp3_header.h"

 // ANSI color codes
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
void print_help() {
   


    printf("------------------------------------------------------------\n");
    printf(CYAN "             🎵        Help Menu        🎶          \n" RESET);
    printf("------------------------------------------------------------\n\n");

    printf(YELLOW "Usage:\n" RESET);
    printf("  View   : ./a.out -v <filename.mp3>\n");
    printf("  Edit   : ./a.out -e <tag_option> \"new_value\" <filename.mp3>\n");
    printf("  Help   : ./a.out -h\n\n");

    printf(YELLOW "Tag options for editing:\n" RESET);
    printf("  🎤  -t   Title\n");
    printf("  👤  -a   Artist\n");
    printf("  💿  -A   Album\n");
    printf("  📅  -y   Year\n");
    printf("  🎼  -m   Genre/Music\n");
    printf("  💬  -c   Comment\n\n");

    printf(YELLOW "Examples:\n" RESET);
    printf("  ✏️  ./a.out -e -t \"New Song\" sample.mp3\n");
    printf("  🔍  ./a.out -v sample.mp3\n");
    printf("  ❓  ./a.out -h\n");

    printf("------------------------------------------------------------\n");
}
