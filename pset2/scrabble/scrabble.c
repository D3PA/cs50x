#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// points for each letter
int PUNTOS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// compute score using (string.h)
int calcular_puntaje(string palabra)
{
    int puntaje = 0;
    size_t largo = strlen(palabra); // get length

    for (size_t i = 0; i < largo; i++)
    {
        if (!isalpha(palabra[i]))
            continue;                                 // skip non-letters
        puntaje += PUNTOS[toupper(palabra[i]) - 'A']; // direct conversion
    }
    return puntaje;
}

int main(void)
{
    // get input
    string palabra1 = get_string("Player 1: ");
    string palabra2 = get_string("Player 2: ");

    // calculate scores
    int puntaje1 = calcular_puntaje(palabra1);
    int puntaje2 = calcular_puntaje(palabra2);

    // decide winner
    switch ((puntaje1 > puntaje2) - (puntaje2 > puntaje1))
    {
        case 1:
            printf("Player 1 wins!\n");
            break;
        case -1:
            printf("Player 2 wins!\n");
            break;
        default:
            printf("Tie!\n");
            break;
    }
}
