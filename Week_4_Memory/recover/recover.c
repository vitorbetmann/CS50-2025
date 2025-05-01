#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME_LEN 3
char FILE_EXTENSION[] = ".jpg";

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover.c filename\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (strstr(argv[1], ".raw") == NULL || input == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    unsigned int pic_num = 0;
    char filename[FILENAME_LEN + strlen(FILE_EXTENSION) + 1];
    FILE *output = NULL;

    uint8_t buffer[512 * sizeof(uint8_t)];
    while (fread(buffer, sizeof(buffer), 1, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
            {
                fclose(output);
            }
            sprintf(filename, "%03d.jpg", pic_num++);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                fclose(input);
                return 1;
            }
        }

        if (output != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, output);
        }
    }

    fclose(output);
    fclose(input);
    return 0;
}
