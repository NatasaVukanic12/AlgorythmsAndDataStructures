/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

typedef struct trie{
    bool rec;
    struct trie* djeca[27]; // 26 abeceda + '
} trie;

trie* root;
int reci = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word){
    trie* trenutni = root;
    while(*word != '\0') {
        int pom = tolower(*word) - 'a';
         
        if(*word == '\''){
            pom = 26;
        }
            
        if(trenutni -> djeca[pom] == NULL) {
            return false;
        }
        else{
            trenutni = trenutni -> djeca[pom];
        }
        word++;
    }
    if(trenutni -> rec) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary) {
    FILE *f = fopen(dictionary, "rb");
    if (f == NULL)
        return false;
        
    root = (trie*) malloc(sizeof(trie));
    trie* trenutni = root;
    for (char c = fgetc(f); c != EOF; c = fgetc(f)) {
        int pom = tolower(c) - 'a';
        if(c == '\''){ //ako je apostrof
            pom = 26;
        }
        
        if(c == '\n') { // stigli smo do kraja reci
            trenutni -> rec = true; 
            trenutni = root; 
            reci++;
        }
        else {  // nije kraj reci
            if(trenutni -> djeca[pom] == NULL) {
                trenutni -> djeca[pom] = (trie*) malloc(sizeof(trie)); 
            }
            trenutni = trenutni -> djeca[pom];
        }
            
    }
    fclose(f);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return reci;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    free(root);
    return true;
}
