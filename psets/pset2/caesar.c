#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv){
    
    string plaintext;
    int a,asciiVal,newAscii,i=0;                                    //definisanje promenljivih
    if(argc == 1 || argc > 2) {                                     //proveravamo koliko je argumenata uneto i ispisujemo gresku ako je uneto vise od jednog
        printf("Wrong number of parameters, one is expected!\n");   //proizvoljno ispisana greska
        return 1;                                                   //naglaseno je da funkcija treba da vrati jedan
    }
     a = atoi(argv[1]);                                             //smestamo unetu vrednost u promenljivu
    if(a < 0) {                                                     //proveravamo da li je uneta vrednost manja od 0
        printf("Argument can't be a negative number!\n");           //proizvoljno ispisana greska
        return 1;                                                   //naglaseno je da funkcija treba da vrati jedan
    }
    printf("plaintext: ");
    plaintext = get_string();
    printf("ciphertext: ");
    while(plaintext[i] != '\0') {
        asciiVal = (int)plaintext[i];                               //smestamo brojnu vrednost karaktera u pomocnu promenljivu
        if(asciiVal >= 65 && asciiVal <= 90) {                      //gledamo da li je brojna vrednost veliko slovo
            newAscii = asciiVal - 65;                               //umanjujemo vrednost promenljive da bi mogli da dodajemo kljuc
            newAscii+=a;                                            //primena formule
            newAscii=newAscii%26;                                   //primena formule
            newAscii+=65;                                           //vracamo vrednost odgovarajuceg karaktera iz ascii tabele
        }
        else if(asciiVal >= 97 && asciiVal <= 122){                 //analogno radimo za mala slova
            newAscii = asciiVal - 97;
            newAscii+=a;
            newAscii=newAscii%26;
            newAscii+=97;
        }
        else{
            newAscii=plaintext[i];                                  //u slucaju da je prazan karakter vrednost se ne menja
        }
        printf("%c",newAscii);                                      //ispis sifrovanog teksta
        i++;
    }                             
    printf("\n");
    return 0;
   
    
}

