#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int contar_letras(string texto);
int contar_palabras(string texto);
int contar_oraciones(string texto);

int main(void)
{
    // ask user for input
    string texto = get_string("Text: ");

    // perfom counts
    int letras = contar_letras(texto);
    int palabras = contar_palabras(texto);
    int oraciones = contar_oraciones(texto);

    // Coleman-Liau index formula
    float L = (100.0 * letras) / palabras;
    float S = (100.0 * oraciones) / palabras;
    float indice = 0.0588 * L - 0.296 * S - 15.8;

    // print grade level according to (indice)
    if (indice < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (indice >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(indice));
    }
}

// count alphabetic characters only
int contar_letras(string texto)
{
    int total = 0;
    for (int i = 0; texto[i] != '\0'; i++)
    {
        if (isalpha(texto[i]))
        {
            total++;
        }
    }
    return total;
}

// count words based on spaces
int contar_palabras(string texto)
{
    int total = 1; // start with 1 since the last word is not followed by a space
    for (int i = 0; texto[i] != '\0'; i++)
    {
        if (texto[i] == ' ')
        {
            total++;
        }
    }
    return total;
}

// count sentences by checking for punctuation marks
int contar_oraciones(string texto)
{
    int total = 0;
    for (int i = 0; texto[i] != '\0'; i++)
    {
        if (texto[i] == '.' || texto[i] == '!' || texto[i] == '?')
        {
            total++;
        }
    }
    return total;
}
