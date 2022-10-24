#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        return 1;
    }

    int BLOCK_SIZE = 512;
    BYTE *buffer = malloc(BLOCK_SIZE);
    int num_image = 0;
    char *filename = malloc(8);
    FILE *img;
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (num_image == 0)
            {
                sprintf(filename, "%03i.jpg", num_image);
                img = fopen(filename, "w");
                num_image += 1;
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", num_image);
                img = fopen(filename, "w");
                num_image += 1;
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
        else
        {
            if (num_image >= 1)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
    }
    fclose(img);
    free(filename);
    free(buffer);
}