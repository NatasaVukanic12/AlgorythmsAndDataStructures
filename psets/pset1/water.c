#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int minutes, bottles;
    do {
         printf("Minutes: ");
         minutes = get_int();
    } while( minutes < 0);
     bottles = minutes * 12;
    printf("Bottles: %i\n",bottles);
    
}