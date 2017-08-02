#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int i = 0;
    bool flag = true;                                               //inicijalizacija promenljivih, promenljiva bool sluzi kao signal
    string name = get_string();                                     //unos korisnika

    while(name[i] != '\0') {                                        //petlja koja prolazi kroz string
        if(name[i] == ' ') {                                        //proveravamo da li su unete vrednosti space ili tacka
            flag = true;                                            //vrednost boola ostaje ista i taj karakter se ignorise
        }
        else if(flag == true && name[i] != ' ') {                   //proveravamo da li je trenutni deo stringa karakter
            name[i]=toupper(name[i]);                               //postavljamo na veliko slovo(zahtevi zadatka)
            printf("%c", name[i]);                                  //ispis karaktera
            flag = false;                                           //zaobilazimo ostale karaktere iz stringa dok ne naidjemo na space ili tacku
        }
        i++;
    }
    printf("\n");
}