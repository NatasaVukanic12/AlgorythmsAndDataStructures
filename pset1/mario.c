#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int row , i, j;
    do {
        printf("Height: ");
        row=get_int();
    } while( row < 0 || row > 23 );
    
    for(i = 0; i < row; i++) {
        for( j = 0; j < row; j++){
            if(j >= row - i - 1)
                printf("#");
            else
                printf(" ");
        }
        printf("  ");
        for( j = 0; j < row; j++){
            if(j <= i)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
    
}