#include <cs50.h>
#include <stdio.h>

int main(void)

{
    int altura_piramide = 0;

    // ask the user the pyramid height between one and eight
    do
    {
        altura_piramide = get_int("Height: ");
    }
    while (altura_piramide < 1 || altura_piramide > 8);

    // loop through each level
    for (int level = 1; level <= altura_piramide; level++)
    {
        // print spaces before the hash
        printf("%*s", altura_piramide - level, "");

        // print hash for the current level
        for (int bloque = 0; bloque < level; bloque++)
        {
            printf("#");
        }

        // move to the new line
        printf("\n");
    }
}