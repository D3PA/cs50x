#include <cs50.h>  // include the cs50 library for get_string function
#include <stdio.h> // standard library for input/output

int main(void)
{
    // prompt the user to enter their name and store in variable 'nombre'
    string nombre = get_string("What is your name? ");

    // print a hello message that include the user name
    printf("Hello, %s\n", nombre);
}