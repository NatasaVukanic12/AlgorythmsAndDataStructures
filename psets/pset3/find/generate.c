/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    //Proveravamo da li su pri pozivu metode uneti parametri, u slucaju da nisu ispisuje se nacin upotrebe (poziva), funkcija vraca gresku
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    //Pretveramo u int uneti parametar na mestu prvog parametra tj dobijamo duzinu niza nasumicnih brojeva
    int n = atoi(argv[1]);

    //Proveravamo da li postoji treci parametar, ako postoji srand48 funkcija postavlja seed na vrednst parametra
    //ako ne postoji onda se za seed postavlja vrednost vremena koje je proteklo od 1.1.1970.
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else
    {
        srand48((long) time(NULL));
    }

    //Stampa se niz sa nasumicnim sklairanim vrednostima pomnozenim sa LIMIT-om, posto drand48 stvara nasumicne vrednosti od 0 do 1 
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
