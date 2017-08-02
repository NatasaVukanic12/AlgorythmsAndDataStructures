/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"
#define max 65536

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{   
    int top=-1, bot=n;
    if(n < 0){
        return false;
    }
   while(top != bot) {
     int mid=(top+bot)/2;
       if(values[mid] == value){
           return true;
       }
       else if(values[n/2] == value){
           return true;
       }
       else if(values[mid] < value ){
           top=mid+1;
       }
       else if(values[mid] > value){
          bot=mid-1;
       }
   }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n){
    int i, j, k;
    int count[max+1] = {0};
    for(i = 0; i < n; i++){
        count[values[i]] += 1;
    }
    
    k = 0;
    for(i = 0; i < max+1; i++){
        if(count[i] != 0) {
            for(j = 0; j < count[i]; j++){
                values[k] = i;
                k++;
            }
        }
    }
 
}
