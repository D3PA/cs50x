#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// function to verify that key has exactly 26 unique alphabetic characters

bool validar_clave(string clave);

bool validar_clave(string clave)
{
   if (strlen(clave) != 26)
    {
        return false;
    }

    // track letters (seen)
    bool usadas[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        char c = clave[i];

        // must be alphabetic
        if (!isalpha(c))
        {
            return false;
        }

        int indice = toupper(c) - 'A';

        // check dup
        if (usadas[indice])
        {
            return false;
        }

        usadas[indice] = true;
    }
    return true;
}

int main(int argc, string argv[])
{
    // check commandline args
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string clave = argv[1];

    // validate key
    if (!validar_clave(clave))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // ask user for plain text
    string texto_plano = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(texto_plano); i < n; i++)
    {
        char letra = texto_plano[i];

        if (isupper(letra))
        {
            // index in alphabet
            int indice = letra - 'A';
            // print corresponding uppercase letter from key
            printf("%c", toupper(clave[indice]));
        }
        else if (islower(letra))
        {
            int indice = letra - 'a';
            // print corresponding lowercase letter from key
            printf("%c", tolower(clave[indice]));
        }
        else
        {
            // non alphabetic
            printf("%c", letra);
        }
    }

    printf("\n");
    return 0;
}
