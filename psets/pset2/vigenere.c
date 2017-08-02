#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(int argc, char **argv){
    
    string plaintext, a;
    int i=0,j=0, asciiVal, newAscii, alen;                          //inicijalizacija promenljivih

    if(argc == 1 || argc > 2) {                                     //proveravamo broj unetih parametara 
        printf("Wrong number of parameters, one is expected!\n");   //proizvoljan ispis
        return 1;                                                   //po zahtevu zadatka vraca se 1 main-u
    }
    a = argv[1];
    alen = strlen(a);
    int addit[alen];
    while(a[i] != '\0') {                                            //smestamo brojevnu vrednost stringa u brojevni niz prolazeci kroz sve karaktere stringa
        if((int)a[i] >= 65 && (int)a[i] <= 90) {                    //proveravamo da li je karakter malo ili veliko slovo
            addit[i]=((int)a[i]) - 65;                                //dodeljujemo clanu niza brojevnu vrednost karaktera
        }
        else if((int)a[i] >= 97 && (int)a[i] <= 122){               //analogno radimo za mala slova
            addit[i]=((int)a[i]) - 97;
        }
        else if((int)a[i] >= 48 && (int)a[i] <= 57){                //proveravamo da li je unutar unetog stringa broj, i ako jeste bacamo gresku
            printf("Keyword must only contain letters A-Z and a-z!\n");
            return 1;
        }
        i++;
    }
    i = 0;
    printf("plaintext:");
    plaintext = get_string();                                       //cekamo unos korisnika teksta koji sifrujemo
    printf("ciphertext:");
    while(plaintext[i] != '\0'){
        asciiVal = (int)plaintext[i];
        if(asciiVal >= 65 && asciiVal <= 90) {                      //proveravamo da li je uneti karakter veliko slovo
            newAscii = asciiVal - 65;                               //svodimo vrednost karaktera na 0 da bi dodali sifru
            newAscii += addit[j % alen];                            //paralelno prolazimo i kroz kljuc a moduo sluzi da ne izadjemo iz granica
            newAscii = newAscii % 26;                               //ubacujemo formulu da ne izadjemo iz granica a-z
            newAscii+=65;                                           //dobijamo vrednost karaktera nakon kriptovanja
        }
        else if(asciiVal >= 97 && asciiVal <= 122){                 //proveravamo da li je uneti karakter malo slovo
            newAscii = asciiVal - 97;                               //radimo analogni postupak kao i za velika slova
            newAscii += addit[j % alen];
            newAscii = newAscii % 26;
            newAscii += 97;
        }
        else{
            newAscii=plaintext[i];                                  //u slucaju da je trenutni karakter izvan opsega velikih i malih slova ignorisemo ga i prelazimo na sledeci
            j--;                                                    //umanjujemo vrednost brojaca sifre da bi kriptovala pravilno i ignorisala sve druge karaktere sem slova
        }
        printf("%c",newAscii);                                      //ispis sifre
        i++;
        j++;
    }
    printf("\n");
}

