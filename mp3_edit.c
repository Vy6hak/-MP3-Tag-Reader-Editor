#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mp3_header.h"

// color codes
#define RESET "\033[0m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"

void edit_mp3(char str[], char new[], char *filename)
{
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        printf(RED "❌ Error: File '%s' doesn't exist!\n" RESET, filename);
        return;
    }

    char header[10];
    fread(header, 10, 1, fptr);

    FILE *fp = fopen("temp.mp3", "wb");
    if (fp == NULL)
    {
        printf(RED "❌ Error: Unable to create temporary file!\n" RESET);
        fclose(fptr);
        return;
    }

    fwrite(header, 10, 1, fp);

    char tag_name[5];
    int edited = 0; // Flag to check if tag was updated

    // --- Tag Detection ---
    if (strcmp(str, "-t") == 0)
        strcpy(tag_name, "TIT2");
    else if (strcmp(str, "-a") == 0)
        strcpy(tag_name, "TPE1");
    else if (strcmp(str, "-A") == 0)
        strcpy(tag_name, "TALB");
    else if (strcmp(str, "-m") == 0)
        strcpy(tag_name, "TCON");
    else if (strcmp(str, "-c") == 0)
        strcpy(tag_name, "COMM");
    else if (strcmp(str, "-y") == 0)
    {
        // --- Year validation ---
        if (strlen(new) != 4)
        {
            printf(RED "❌ Invalid year format! Year must be exactly 4 digits (e.g., 2024).\n" RESET);
            fclose(fptr);
            fclose(fp);
            remove("temp.mp3");
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            if (!isdigit(new[i]))
            {
                printf(RED "❌ Invalid year! Only numeric digits are allowed (e.g., 2024).\n" RESET);
                fclose(fptr);
                fclose(fp);
                remove("temp.mp3");
                return;
            }
        }

        strcpy(tag_name, "TYER");
    }
    else
    {
        printf(RED "⚠️  Unknown tag option: %s\n" RESET, str);
        fclose(fptr);
        fclose(fp);
        remove("temp.mp3");
        return;
    }

    tag_name[4] = '\0';

    char tag[5];
    int temp_size, new_size;
    char flag[2];

    // --- Frame Reading Loop ---
    while (fread(tag, 4, 1, fptr) == 1)
    {
        if (tag[0] == 0)
            break;

        tag[4] = '\0';
        fwrite(tag, 4, 1, fp);

        fread(&temp_size, 4, 1, fptr);
        fread(flag, 2, 1, fptr);
        convert_BE_TO_LE(&temp_size);

        if (strcmp(tag, tag_name) == 0)
        {
            edited = 1;
            new_size = strlen(new) + 1;
            convert_BE_TO_LE(&new_size);
            fwrite(&new_size, 4, 1, fp);
            fwrite(flag, 2, 1, fp);
            fputc('\0', fp);
            fwrite(new, strlen(new), 1, fp);
            fseek(fptr, temp_size, SEEK_CUR);
        }
        else
        {
            int size2 = temp_size;
            convert_BE_TO_LE(&size2);
            fwrite(&size2, 4, 1, fp);
            fwrite(flag, 2, 1, fp);

            char *frame_content = malloc(temp_size);
            fread(frame_content, temp_size, 1, fptr);
            fwrite(frame_content, temp_size, 1, fp);
            free(frame_content);
        }
    }

    // --- Copy remaining bytes if any ---
    int ch;
    while ((ch = fgetc(fptr)) != EOF)
        fputc(ch, fp);

    fclose(fptr);
    fclose(fp);

    remove(filename);
    rename("temp.mp3", filename);

    // --- Final Output ---
    if (edited)
    {
        printf(GREEN "✅ Successfully updated MP3 tag in '%s'!\n" RESET, filename);
    }
    else
    {
        printf(RED "⚠️  The specified tag was not found in '%s'.\n" RESET, filename);
    }
}
