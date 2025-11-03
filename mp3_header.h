#define HEADER_H

typedef struct
{
    char id3[4];
    char tag[5];
    int size;

}MP3;
void view_mp3(char *filename, MP3 *tag_reader);
void convert_BE_TO_LE(int *size);
const char *tag_name(char tag[]);
void edit_mp3(char str[],char new[],char * filename);
void print_help();
