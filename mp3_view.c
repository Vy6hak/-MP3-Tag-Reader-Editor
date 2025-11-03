#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3_header.h"

// Define color codes (for headings only)
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"

void view_mp3(char *filename, MP3 *tag_reader)
{  
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf(RED "❌ File '%s' doesn't exist!\n" RESET, filename);
        return;
    }

    fread(tag_reader->id3, (sizeof(tag_reader->id3) - 1), 1, fptr);
    tag_reader->id3[(sizeof(tag_reader->id3) - 1)] = '\0';

    if (strcmp(tag_reader->id3, "ID3") == 0)
    {
        printf(GREEN "✅ It is a valid MP3 file!\n" RESET);
    }
    else
    {
        printf(RED "❌ Not an MP3 file!\n" RESET);
        fclose(fptr);
        return;
    }

    fseek(fptr, 7, SEEK_CUR);   // skip 7 bytes of header

    printf("------------------------------------------------------------\n");
    printf(CYAN "               🎵  MP3 Tag Details  🎶               \n" RESET);
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < 6; i++)
    {
        fread(tag_reader->tag, (sizeof(tag_reader->tag) - 1), 1, fptr);
        tag_reader->tag[(sizeof(tag_reader->tag) - 1)] = '\0';

        fread(&(tag_reader->size), sizeof(tag_reader->size), 1, fptr);
        convert_BE_TO_LE(&(tag_reader->size));
        fseek(fptr, 3, SEEK_CUR);

        char str[100];
        fread(str, (tag_reader->size) - 1, 1, fptr);
        str[(tag_reader->size) - 1] = '\0';
        printf("%-10s : %-20s\n", tag_name(tag_reader->tag), str);
    }

    printf("------------------------------------------------------------\n");
    printf(GREEN "✅ MP3 file tags extracted successfully!\n" RESET);

    fclose(fptr);
}

void convert_BE_TO_LE(int *size)
{
    char *ptr = (char *)size;
    char temp;

    temp = ptr[0];
    ptr[0] = ptr[3];
    ptr[3] = temp;

    temp = ptr[1];
    ptr[1] = ptr[2];
    ptr[2] = temp;
}

const char *tag_name(char tag[])
{
    if (strcmp(tag, "TIT2") == 0)
        return "Title";
    if (strcmp(tag, "TPE1") == 0)
        return "Artist";
    if (strcmp(tag, "TALB") == 0)
        return "Album";
    if (strcmp(tag, "TYER") == 0)
        return "Year";
    if (strcmp(tag, "TCON") == 0)
        return "Music";
    if (strcmp(tag, "COMM") == 0)
        return "Comment";
    return tag;
}
