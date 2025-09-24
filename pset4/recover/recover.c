#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;

int main(int argc, char *argv[])
{
    // ensure exactly one argument: the raw file
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover raw_file\n");
        return 1;
    }

    // open the input raw
    FILE *raw_input = fopen(argv[1], "r");
    if (!raw_input)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 2;
    }

    byte block[512];           // buffer to read 512byte
    FILE *current_jpeg = NULL; // pointer to jpeg being written
    int jpeg_counter = 0;      // counts the number of recovered

    while (fread(block, sizeof(byte), 512, raw_input) == 512)
    {
        // check if the block starts a new jpeg
        int jpeg_start = block[0] == 0xff && block[1] == 0xd8 &&
                         block[2] == 0xff && (block[3] & 0xf0) == 0xe0;

        if (jpeg_start)
        {
            // close the previous jpeg
            if (current_jpeg != NULL)
                fclose(current_jpeg);

            // create a new jpeg file with a unique name
            char filename[20];
            sprintf(filename, "%03d.jpg", jpeg_counter);
            current_jpeg = fopen(filename, "w");
            if (!current_jpeg)
            {
                fprintf(stderr, "Could not create %s\n", filename);
                fclose(raw_input);
                return 3;
            }

            jpeg_counter++;
        }

        // if inside a jpeg, write current block
        if (current_jpeg != NULL)
            fwrite(block, sizeof(byte), 512, current_jpeg);
    }

    // close remaining open files
    if (current_jpeg != NULL)
        fclose(current_jpeg);
    fclose(raw_input);

    return 0;
}