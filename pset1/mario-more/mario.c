#include <cs50.h>
#include <stdio.h>

int main(void)

{
    int altura_piramide = 0;

    // ask the user the pyramid height between one and height
    do
    {
        altura_piramide = get_int("Height: ");
    }
    while (altura_piramide < 1 || altura_piramide > 8);

    // loop through each row
    for (int fila = 1; fila <= altura_piramide; fila++)
    {
        // print spaces before the left side
        for (int espacio = 0; espacio < altura_piramide - fila; espacio++)
        {
            printf(" ");
        }

        // print left hashes
        for (int izquierda = 0; izquierda < fila; izquierda++)
        {
            printf("#");
        }

        // print spaces in the middle
        printf("  "); // i think it should be two spaces??

        // print right hashes
        for (int derecha = 0; derecha < fila; derecha++)
        {
            printf("#");
        }

        // move to the new line
        printf("\n");
    }
}
