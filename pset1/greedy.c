#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
  
    float fchange;
    int ichange, money=0, i=0, novcici[]={25,10,5,1};
    printf("O hai!");
    do {
        printf("How much change is owed?\n");
        fchange = get_float();
    } while( fchange < 0); 
    ichange = round(fchange * 100);
    while(ichange>0){
        if(ichange-novcici[i]<0){
            i++;
        }
        else{
            ichange-=novcici[i];
            money++;
        }
    }
    printf("%i\n",money);
}